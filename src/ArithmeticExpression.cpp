#include "ArithmeticExpression.h"
#include <stack>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iostream>

using sl::ArithmeticExpression;
using std::string;
using std::vector;
using std::stack;
using std::istringstream;
using std::cout;
using std::endl;
using std::cin;
using std::ostream;

ArithmeticExpression::ArithmeticExpression(const string &expre_,
                                           const ArithmeticExpression::Type &type_)
    : expre(expre_), type(type_) {}

void ArithmeticExpression::setType(const ArithmeticExpression::Type &type_) {
    type = type_;
}

void ArithmeticExpression::setExpression(const string &expre_) {
    expre = expre_;
}

ArithmeticExpression::Type ArithmeticExpression::getType() const {
    return type;
}

string ArithmeticExpression::getExpression() const {
    return expre;
}

bool ArithmeticExpression::match(string &unMatch) const {
    if (expre.empty()) {
        throw std::range_error("Expression is empty.");
    }
    const vector<string> left = {"", "(", "[", "{"};
    const vector<string> right = {"", ")", "]", "}"};

    stack<string> s;
    bool match = true;
    istringstream in(expre);
    string word;
    while (in >> word) {
        vector<string>::const_iterator it = std::find(left.begin(), left.end(), word);
        if (it != left.end()) {  // Left notation, push
            s.push(word);
        } else {
            vector<string>::const_iterator it = std::find(right.begin(), right.end(), word);
            if (it != right.end()) {  // Right notation
                if (s.empty()) {  // Match fail if empty stack
                    match = false;
                    unMatch = (*it);
                    break;
                } else {
                    string top = s.top();
                    s.pop();
                    // If top notation isn't correspond to the current notation, matching fails
                    if (top != left[it - right.begin()]) {
                        match = false;
                        unMatch = top;
                        break;
                    }
                }
            }
        }
    }
    // Match fail if the stack is not empty
    if (!s.empty() && match) {
        match = false;
        unMatch = s.top();
    }
    return match;
}

double ArithmeticExpression::calculate() {
    if (expre.empty()) {
        throw std::range_error("Expression is empty.");
    }
    if (type == INFIX) {
        toPostfix();
    }
    stack<double> s2;
    string word;
    istringstream postfixStream(expre);
    while (postfixStream >> word) {
        if (word.size() == 1 && !isdigit(word[0])) {  // An operator
            if (word[0] == '#') {  // Negative unary operator
                double top = s2.top();
                s2.pop();
                s2.push(-top);
            } else {  // Binary operator
                double b = s2.top();
                s2.pop();
                double a = s2.top();
                s2.pop();
                double tmp = 0;
                switch (word[0]) {
                    case '+':
                        tmp = a + b; break;
                    case '-':
                        tmp = a - b; break;
                    case '*':
                        tmp = a * b; break;
                    case '/':
                        tmp = a / b; break;
                }
                s2.push(tmp);
            }
        } else {  // Digits will be pushed into stack directly
            istringstream tmp(word);
            double number;
            tmp >> number;
            s2.push(number);
        }
    }
    return s2.top();
}

void ArithmeticExpression::toPostfix() {
    if (expre.empty()) {
        throw std::range_error("Expression is empty.");
    }
    if (type == INFIX) {
        stack<string> s1;
        string postfix, word;
        istringstream infixStream(expre);
        while (infixStream >> word) {
            if (word.size() == 1 && word[0] == '(') {  // Left bracket
                s1.push(word);
            } else if (word.size() == 1 && word[0] == ')') {  // Right bracket
                // Pop until meeting a right bracket
                string top;
                while ((top = s1.top()) != "(") {
                    s1.pop();
                    postfix += top;
                    postfix += " ";
                }
                s1.pop();
            } else if (word.size() == 1 && !isdigit(word[0])) {  // An operator
                while (!s1.empty()) {
                    string top = s1.top();
                    if (priorityExceed(top, word)) {
                        postfix += top;
                        postfix += " ";
                        s1.pop();
                    } else {
                        break;
                    }
                }
                s1.push(word);  // Push word to stack
            } else {  // Digits is added to result string directly
                postfix += word;
                postfix += " ";
            }
        }
        // Add remain operators to the end of the result
        while (!s1.empty()) {
            string top = s1.top();
            s1.pop();
            postfix += top;
            postfix += " ";
        }
        expre = postfix;
        type = POSTFIX;
    }
}

bool ArithmeticExpression::priorityExceed(const string &a, const string &b) {
    if (a == "(") return false;  // Left bracket has the highest priority
    int priority1 = -1, priority2 = -1;
    if (a == "*" || a == "/") {
        priority1 = 1;
    } else if (a == "+" || a == "-") {
        priority1 = 0;
    } else if (a == "#") {  // Unary operator has the second-highest priority
        priority1 = 2;
    }
    if (b == "*" || b == "/") {
        priority2 = 1;
    } else if (b == "+" || b == "-") {
        priority2 = 0;
    } else if (b == "#") {  // Unary operator has the second-highest priority
        priority2 = 2;
    }
    return priority1 >= priority2;  // >= is critical
}

string ArithmeticExpression::parseInfixExpre(string &expre) {
    string infix;
    for (size_t i = 0; i < expre.size(); ++i) {
        switch (expre[i]) {
            case '[':
            case '{':
                expre[i] = '('; break;
            case ']':
            case '}':
                expre[i] = ')'; break;
            case '-':
                // Change negative unary operator to '#'
                if (i == 0 || expre[i - 1] == '(') {
                    expre[i] = '#';
                }
                break;
        }
        switch (expre[i]) {
            case '+':
            case '*':
            case '-':
            case '/':
            case '(':
            case ')':
            case '#':
                infix += " ";
                infix += expre[i];
                infix += " ";
                break;
            default:
                infix += expre[i];  // Digit
        }
    }
    return infix;
}

void ArithmeticExpression::test() {
    std::cout << "Test ArithmeticExpression:\n\n";
    std::cin.clear();
    while (1) {
        cout << "Input the type of the expression (0->Postfix, 1->Infix): ";
        unsigned type;
        cin >> type;
        while (!(type == 0 || type == 1)) {
            cout << "Invalid inputs, please try again.: ";
            cin >> type;
        }
        getchar();
        cout << "\nInput the expression: ";
        string tmp;
        getline(cin, tmp);
        if (type == ArithmeticExpression::Type::INFIX) {
            tmp = ArithmeticExpression::parseInfixExpre(tmp);
        }
        try {
            ArithmeticExpression expre(tmp, static_cast<ArithmeticExpression::Type>(type));
            string unMatch;
            if (expre.match(unMatch)) {
                cout << "\nMatch succeed.\n" << endl;
                if (type == POSTFIX) {
                    cout << "This is a postfix expression." << endl;
                } else if (type == INFIX) {
                    cout << "This is an infix expression and "
                        << "the corresponding postfix expression is:" << endl;
                    expre.toPostfix();
                    cout << expre.getExpression() << endl;
                }
                cout << "\nAnswer: " << expre.calculate() << endl;
            } else {
                cout << "\nMatch error: "
                    << "Operator " << unMatch << " unmatch." << endl;
            }
            cout << endl;
        } catch (std::exception e) {
            cout << e.what() << endl;
        }
    }
}
