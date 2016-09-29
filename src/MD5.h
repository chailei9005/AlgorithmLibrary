#pragma once

#include "Base.h"
#include <string>

NS_BEGIN

/*
MD5 algorithm.

For usage, see function test().
*/
class MD5 {
public:
    /*
    Encrypt the message using MD5 algorithm.

    @param msg the message to be encrypted
    @return the encrypted string
    */
    static std::string encrypt(const std::string &msg);

private:


public:
    /*
    Test the function of the class.

    Sample #1:
    */
    static void test();
};

NS_END
