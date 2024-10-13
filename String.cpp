/**
 *  A class that stores a string and generates a hash code for it.
 *
 **/

#include "String.h"
#include <string>
#include <limits>  // 用來取得 INT_MIN 和 INT_MAX

/**
 *  Construct a new String with the given variable.
 *  @param str the string by which the String stores.
 */
String::String(const string& str) {
    this->str = str;
}

/**
 *  Get the value of the string variable.
 *  @return the stored value.
 */
string String::getvalue() const {
    return str;
}

/**
 *  Returns true if "this" String and "strg" have identical values.
 *  @param strg is the second String.
 *  @return true if the string values are equal, false otherwise.
 */
bool String::equals(const String& strg) {
    // Replace the following line with your solution.  Be sure to return false
    //   (rather than throwing a ClassCastException) if "strg" is not
    //   a String.
    return str.compare(strg.getvalue())==0;
}

/**
 *  Returns a hash code for this String.
 *  @return a number between Integer.MIN_VALUE and Integer.MAX_VALUE.
 */
int String::hashCode() const {
    // Replace the following line with your solution.
    const unsigned int FNV_prime = 16777619;
    const unsigned int offset_basis = 2166136261;

    unsigned int hash = offset_basis;

    for (char c : str) {
        hash ^= static_cast<unsigned char>(c);  // XOR 當前字元
        hash *= FNV_prime;  // 乘上質數
    }

    // 將無符號整數轉換成帶符號的範圍
    int signedHash = static_cast<int>(hash);

    // 若 hash 溢出到負數，將其範圍重新調整
    if (signedHash < 0) {
        signedHash = (signedHash & std::numeric_limits<int>::max()) - std::numeric_limits<int>::min();
    }

    return signedHash;
}
