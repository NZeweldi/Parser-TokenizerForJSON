/** ***************************************************************************
 * @remark CS 315: Definition of Parser class
 *
 * @author Ali Kooshesh and Suzanne Rivoire
 * @file  Parser.hpp
 * @date  Fall 2023
 *
 * @remark You create a Tokenizer object by passing a filename to the 
 *     constructor. The parser's job is to read in all the key-value pairs
 *     of (coursename, listOfPrereqs) from the JSON file and, upon request,
 *     populate an STL map with those contents.
 **************************************************************************** */

#ifndef CANBETAKENTOGETHER_PARSER_HPP
#define CANBETAKENTOGETHER_PARSER_HPP

#include <map>
#include <vector>
#include <utility>

#include "Tokenizer.hpp"

class Parser {
public:
    // This is a fancy constructor for Parser that uses an initialization list
    // to ensure that the tokenizer member variable is built with the correct
    // input file name.
    // If we don't do it this way, the tokenizer will be created with the
    // default constructor, and we have no way to give it the file name once that
    // happens.
    // For more on initialization lists:
    // https://www.cprogramming.com/tutorial/initialization-lists-c++.html
    Parser(std::string inputFileName): tokenizer{std::move(inputFileName)} {}

    // This is where the magic happens!
    // Repeatedly ask the tokenizer to give you tokens, one at a time, and
    // compare them to what you are expecting at this point in the file.

    // Whenever you expect the next group of tokens to be a key-value pair like
    // "MATH 431": ["MATH 241", "MATH 180"],
    // call the parseKeyValuePair helper function to handle that for you.
    // Then, insert the key-value pair that parseKeyValuePair returns into the map.

    // If you get something you don't expect, you need to:
    // 1. Print the name of this function (Parser::parseJSONObject), then a space
    // 2. Print the appropriate error message from constants.hpp
    // 3. Print the specific unexpected token you found
    // 4. Exit with the appropriate error code from constants.hpp

    // If you get a duplicate key, you should follow the above steps,
    // but in step 3 you should print that key.
    std::map<std::string, std::vector<std::string>> parseJSONObject();

private:
    Tokenizer tokenizer;
    std::map<std::string, std::vector<std::string>> jsonObject;

    // Read and return a key-value pair like
    // "MATH 431": ["MATH 241", "MATH 180"],
    // Note that the final key-value pair in the file won't end with a comma,
    // but the others all should.

    // You can expect the first token this function encounters to be a
    // quoted string; if not, raise an error as described next.

    // If you get something you don't expect, you need to:
    // 1. Print the name of this function (Parser::parseKeyValuePair), then a space
    // 2. Print the appropriate error message from constants.hpp
    // 3. Print the specific unexpected token you found
    // 4. Exit with the appropriate error code from constants.hpp
    std::tuple<std::string, std::vector<std::string>> parseKeyValuePair();
};


#endif //CANBETAKENTOGETHER_PARSER_HPP
