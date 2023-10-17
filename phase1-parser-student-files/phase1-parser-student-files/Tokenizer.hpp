/** ***************************************************************************
 * @remark CS 315: Definition of Tokenizer class
 *
 * @author Ali Kooshesh and Suzanne Rivoire
 * @file  Tokenizer.hpp
 * @date  Fall 2023
 *
 * @remark You create a Tokenizer object by passing a filename to the 
 *     constructor. The object's job is then to move through the file,
 *     finding and returning one token at a time.
 * 
 * @remark If you've never had to really think about input streams as...well...
 *     streams, you may want to reinforce those concepts. Here are two
 *     good resources -- they contain more info than you need, so just read
 *     enough to have a good mental picture of how to process input,
 *     piece by piece:
 *     https://www.cprogramming.com/tutorial/c++-iostreams.html
 *     http://websites.umich.edu/~eecs381/handouts/filestreams.pdf
 **************************************************************************** */

#ifndef CANBETAKENTOGETHER_TOKENIZER_HPP
#define CANBETAKENTOGETHER_TOKENIZER_HPP

#include <string>
#include <fstream>
#include "Token.hpp"

class Tokenizer {
public:
    // Constructor: open the input file for reading
    // (OK to assume it's been validated) and hook it up to your inputStream
    Tokenizer(std::string inputFileName);

    // Return the next token in the input file
    // If you keep calling getToken() until you hit EOF, it should return 
    // all the tokens in the file, in order.
    // If you hit something that is not a valid token, you should:
    //    1. print the appropriate error message from constants.hpp,
    //    2. print the offending character you saw, and
    //    3. exit using the appropriate error code from constants.hpp.
    Token getToken();

    // Sometimes the parser will want to put a token back ("unget" it)
    // so that the **next** call to getToken() will return that same token
    // again, presumably in a more convenient context.
    // When ungetToken() is called, the Tokenizer should make a note of it
    // and return the current token again the next time getToken() is called.
    void ungetToken();

private:
    std::fstream inputStream;
    Token lastToken;
    bool _hasUngottenToken = false;

    // Private member functions

    // Return true if the character c is one of our single-character tokens
    bool isASymbol(char c);

    // Read a quoted string, character by character.
    // Return the empty string if the first character is not a "
    // Otherwise, return what's between the initial " and the next " you see.
    // You do not need to worry about escaped quotes -- we promise not to do \"
    // within a quoted string.
    // If you hit the end of the file without ever seeing a closing ",
    // follow the procedure for invalid token described above for getToken,
    // and use the quoted string you've read so far for #2 in that list.
    std::string readQuotedString();
};

#endif //CANBETAKENTOGETHER_TOKENIZER_HPP
