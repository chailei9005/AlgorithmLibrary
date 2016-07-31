#pragma once

#include "Base.h"
#include <string>

NS_BEGIN

/*
Class for calculating arithmetic expression

Operators support:
+, -, *, /, (), [], {} (Use '#' instead of negative unary operator)

For usage, see function test().
*/
class ArithmeticExpression {
public:
    /*
    The type of an expression.
    */
    enum Type {
        POSTFIX,
        INFIX
    };

    /*
    Initialize an expression.

    @param expre_ the content of the expression
    @param type_ the type of the expression
    */
    ArithmeticExpression(const std::string &expre_, const Type &type_);

    /*
    Check if the brackets in the expresison match.

    @param unMatch the operator that does not match.
                   (if match, this field will be useless)
    @return true if the brackets in the expresison match
    */
    bool match(std::string &unMatch) const;

    /*
    Calculate current expresison.

    @return the calculation result
    */
    double calculate();

    /*
    Convert current expression to postfix.
    */
    void toPostfix();

    /*
    Parse an expression to an infix expression that
    can be calculated.
    
    E.g.
    input  [(3+15)/2]-1
    output ( ( 3 + 15 ) / 2 ) - 1

    @param expre the expression to parse.
    @return the parsed result
    */
    static std::string parseInfixExpre(std::string &expre);

    /*
    Set the type of the expresison.
    */
    void setType(const Type &type_);

    /*
    Set the content of the expresison.
    */
    void setExpression(const std::string &expre_);

    /*
    Get the type of the expresison.
    */
    Type getType() const;

    /*
    Get the content of the expresison.
    */
    std::string getExpression() const;

private:
    std::string expre;
    Type type;

    /*
    Check if the priority of the first operator
    exceeds the priority of the second operator

    @param a the first operator
    @param b the second operator
    @return true if exceed, false otherwise
    */
    bool priorityExceed(const std::string &a, const std::string &b);

public:
    /*
    Test the function of the class.

    Sample #1: (ans: 24)
    Infix:   1+[2*(3+4)+{5-2}*3]
    Postfix: 1 2 3 4 + * 5 2 - 3 * + +

    Sample #1: (ans: 47)
    Infix:   -8-(20/4+(3-5)*20)+3+4+88/8-1+3
    Postfix: -8 20 4 / 3 5 - 20 * + - 3 + 4 + 88 8 / + 1 - 3 +

    Sample #2: (ans: 40)
    Infix:   (60/(2*(3+4)+(5-2)/3)-1-1)*8-(20/4+(3-5)*20+3+(-4)+88/8-(2-3))
    Postfix: 60 2 3 4 + * 5 2 - 3 / + / 1 - 1 - 8 * 20 4 / 3 5 - 20 * + 3 + -4 + 88 8 / + 2 3 - - -

    Sample #3: (ans: 288)
    Infix:   (6*((5+((2+3)*8))+3))
    Postfix: 6 5 2 3 + 8 * + 3 + *

    Sample #4: (ans: 153)
    Infix:   -3*(-20+(-(2*(3+5))-(8+7)))
    Postfix: 3 # 20 # 2 3 5 + * # 8 7 + - + *

    Sample #5: (ans: 0)
    Infix:   -3*(-1+(-(1-2)))
    Postfix: 3 # 1 # 1 2 - # + *
    */
    static void test();
};

NS_END
