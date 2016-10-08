#pragma once

#include "Base.h"
#include <string>
#include <vector>

NS_BEGIN

/*
MD5 algorithm.
This is a singleton.

For usage, see function test().
*/
class MD5 {
public:
    typedef uint32_t UInt32;
    typedef uint64_t UInt64;

    ~MD5();

    /*
    Forbid copy
    */
    MD5(const MD5 &m) = delete;
    MD5& operator=(const MD5 &m) = delete;

    /*
    Return the only instance
    */
    static MD5* getInstance();

    /*
    Encrypt the message using MD5 algorithm.

    @param msg the message to be encrypted
    @return the encrypted string
    */
    std::string encrypt(const std::string &msg);

private:
    // Hexadecimal character
    const std::string hex;

    // Left shift number
    const std::vector<UInt32> s;

    // Constants in main loop
    const std::vector<UInt32> k;

    /*
    Private constructor for singleton.
    */
    MD5();

    /*
    Pad the string to make the length of the string satisfy: #(length) mod 512 = 0.
    The last 64 bits of the result is #(length of the original string) mod 2^64.

    @param str the string to be filled up
    @param groupNum the number of the groups
    @return the filled string stored in an array of 32-bit integer.
    */
    UInt32* pad(const std::string &str, UInt32 &groupNum);

    /*
    Loop 64 times for each group and calculate a, b, c and d.

    @param group the group to be processed.
    @param a/b/c/d the four 32-bit integer of cyphertext. 
    */
    void loop(const UInt32 *const group, UInt32 &a, UInt32 &b, UInt32 &c, UInt32 &d);

    /*
    Map a 32-bit integer to its hexadecimal presentation.

    @param num the 32-bit integer
    @return a string that stores the hexadecimal presentation. 
    */
    std::string toHexStr(const UInt32 num);

    /*
    Cycle shift left.

    @param num the number to be shifted
    @param shiftCnt the shift count
    @return the number after shifted
    */
    UInt32 cycleShiftLeft(const UInt32 num, const UInt32 shiftCnt);

public:
    /*
    Test the function of the class.

    Sample #1: (ans: d41d8cd98f00b204e9800998ecf8427e)
    (empty string)

    Sample #2: (ans: 9e107d9d372bb6826bd81d3542a419d6)
    The quick brown fox jumps over the lazy dog

    Sample #3: (ans: e4d909c290d0fb1ca068ffaddf22cbd0)
    The quick brown fox jumps over the lazy dog.

    Sample #4: (ans: f96b697d7cb7938d525a2f31aaf161d0)
    message digest

    Sample #5: (ans: c3fcd3d76192e4007dfb496cca67e13b)
    abcdefghijklmnopqrstuvwxyz

    Sample #6: (ans: 603f52d844017e83ca267751fee5b61b)
    jklmn

    Sample #7: (ans: 0cc175b9c0f1b6a831c399e269772661)
    a

    Sample #8: (ans: 51bbd89663cb10b67a15aad3f5121637)
    (data/md5_msg.txt)
    */
    static void test();
};

NS_END
