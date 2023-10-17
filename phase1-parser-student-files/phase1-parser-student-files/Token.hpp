/** ***************************************************************************
 * @remark CS 315: Definition of Token class
 *
 * @author Ali Kooshesh and Suzanne Rivoire
 * @file  Token.hpp
 * @date  Fall 2023
 *
 * @remark Most of these member functions are so short, we've just implemented
 *         them right here in the header file. The one exception, which
 *         is implemented in the .cpp file, is Token::print().
 **************************************************************************** */

#ifndef CANBETAKENTOGETHER_TOKEN_HPP
#define CANBETAKENTOGETHER_TOKEN_HPP

#include <string>

class Token {
public:
    Token() {}
    bool &eof() { return _eof; }
    bool isOpenSquareBracket()   { return _symbol == '['; }
    bool isCloseSquareBracket()  { return _symbol == ']'; }
    bool isOpenBrace()   { return _symbol == '{'; }
    bool isCloseBrace()  { return _symbol == '}'; }

    bool isComma() { return _symbol == ','; }
    bool isColon() { return _symbol == ':'; }

    bool isQuotedString() { return _quotedString != ""; }
    std::string &quotedString() { return _quotedString; }

    char &symbol() { return _symbol; }

    std::string toString(); // return string representation of token

private:
    char _symbol = '\0';
    std::string _quotedString = "";
    bool _eof = false;

};

#endif //CANBETAKENTOGETHER_TOKEN_HPP
