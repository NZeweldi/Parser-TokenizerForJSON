/** ***************************************************************************
 * @remark CS 315: Implementation of Token member function
 *
 * @author Ali Kooshesh and Suzanne Rivoire
 * @file  Token.cpp
 * @date  Fall 2023
 *
 * @remark Implementation for the only Token member function that's not just
 *         a one-liner.
 **************************************************************************** */

#include <iostream>
#include <cassert>
#include <string>
#include "Token.hpp"

/** ***************************************************************************
 * Return a string representation of this token that can be printed to 
 * cerr or cout.
 * Most of the valid tokens are single characters, with the exceptions of 
 * quoted strings and the special end-of-file token.
 **************************************************************************** */
std::string Token::toString() {
    if (isQuotedString()) {
        return quotedString();
    }
    else if (isOpenBrace() || isCloseBrace() || isOpenSquareBracket() ||
             isCloseSquareBracket() || isComma() ||  isColon()) {
        return std::string(1, symbol());
    }
    else if (eof()) {
        return "EOF";
    }
    
    // this should never happen!
    assert(true); // if we reach this point, our program has a bug -- exit!
    return "Unknown token!";
}