// Created by Ali Kooshesh on 9/26/23.
// Natnael Zeweldi
#include <iostream>
#include "Tokenizer.hpp"
#include "constants.hpp"
// opens file
Tokenizer::Tokenizer(std::string inputFileName) {
    inputStream.open(inputFileName, std::ios::in);
}

// input a token a deal with whether it is a symbol or a string
// there is also some minor changes that prevent strings
// from including characters that should appear after the
// class major and number

Token Tokenizer::getToken() {
    if(!inputStream.is_open()) {
        std::cerr << "(Tokenizer::getToken())" << errorMessages[2] << std::endl;
        exit(E_BAD_INPUT_FILE);
    }

    // In quoted strings sometimes the characters ']' and ','
    // get attached which prevents my parser from distinguishing
    // the string the precedes the characters.  I set these two
    // if statements in case it happens, making the rest of my
    // code work 100% perfectly

    if(lastToken.quotedString() == "],"){

        Token tokens;
        lastToken.quotedString()=",";
        tokens.symbol()=']';
        return tokens;

    } else if (lastToken.quotedString()==","){

        Token tokens;
        tokens.symbol()=',';
        lastToken.quotedString()="";
        return tokens;
    }
    // if character is stuck in readQuotedString()
    // use this to separate
    if(_hasUngottenToken){

        _hasUngottenToken=false;
        return lastToken;
    }

    Token token;

    char c;
    inputStream >> c;

    if(inputStream.eof()) { // end of file

        token.eof() = true;
        return token;
    }
    if(isASymbol(c)) { // a character came from the file

        if (c == '[') {
            token.symbol() = '[';
        }
        else if (c == ']') {

            token.symbol() = ']';
        }
        else if (c == ',') {

            token.symbol() = ',';
        }
        else if (c == '{') {
            token.symbol() = '{';
        }
        else if (c == '}') {
            token.symbol() = '}';
        }
        else if (c == ':'){
            token.symbol()= ':';
            return token;
        }

        else {

            std::cerr << "(Tokenizer::getToken())" << errorMessages[3]
                      << "Unexpected character in Tokenizer::getToken ->"
                      << c << "<-" << std::endl;
            exit(E_BAD_TOKEN);
        }
        return token;

    } else { // dealing with quoted string

            inputStream.putback(c);
            std::string desc;
            desc = readQuotedString();
            token.quotedString()=desc;
            return token;

    }
}

bool Tokenizer::isASymbol(char c) {

    return c == '{' || c == ':' || c == '[' || c == ']' || c == ',' || c == '}';

}

// if token gets stuck where it shouldn't use this to reassess it
void Tokenizer::ungetToken() {

    char c;
    inputStream >> c;

    if(c=='[') {
        lastToken.symbol() = '[';
    } else if(c==']') {
        lastToken.symbol() = ']';
    } else if (c==','){
        lastToken.symbol() = ',';
    } else if (c=='{') {
        lastToken.symbol() = '{';
    } else if (c == '}') {
        lastToken.symbol() = '}';
    } else {
        std::cerr << "(Tokenizer::ungetToken())" <<errorMessages[3]

        << "Unexpected character in Tokenizer::getToken ->" <<
                  c << "<-" << std::endl;
        exit(E_BAD_TOKEN);
    }

    _hasUngottenToken = true;
}

// reads quoted string and also handles characters
// that get stuck at the end, by using lastToken
// and reorganizing the chars/strings piece by piece

std::string Tokenizer::readQuotedString() {

    std::string empty= "";
    std::string quote,number;
    std::string q = "";

    inputStream >> quote;
    //std::cout << "->" << quote << "<-" << std::endl;
    inputStream >> number;
    //std::cout <<"->" << number << "<-" << std::endl;

    size_t qSize = quote.size();
    size_t nSize = number.size();

    for(size_t c = 0; c < qSize; c++) {
        if (quote.at(0) != '"') {
            return empty;
        }
        if(quote.at(c)!= '"') {
            q.push_back(quote.at(c));
        }
    }

    q.push_back(' ');

    std::string ss1;

    for(int b = 0; b < nSize; b++){
        if(number.at(b)!= '"' && number.at(b)!=']' && number.at(b)!=':' && number.at(b)!= ','){
            q.push_back(number.at(b));
        }

        if(ss1 == "],"){
            if(number.at(b)!=','){
                exit(1);
            }
            lastToken.quotedString()=ss1;
        } else if(number.at(b)==']'){
            ss1 = "],";

        } else if (number.at(b)== ':'){
            lastToken.symbol() = ':';
            //std::cout << "occurred: :\n";

            _hasUngottenToken=true;
        } else if (number.at(b) == ','){
            lastToken.symbol() = ',';
            //std::cout << "occurred: ,\n";

            _hasUngottenToken=true;
        }  else if (number.at(b) == '}'){
            lastToken.symbol() = '}';
            //std::cout << "occurred: }\n";

            _hasUngottenToken=true;
        }
    }

    return q;
}

/*if(number.at(nSize-1)!='"'){
    std::cerr << "(Tokenizer::readQuotedString())" << errorMessages[3]
    << number.at(nSize-1)<<std::endl;
    exit(E_BAD_TOKEN);
}*/