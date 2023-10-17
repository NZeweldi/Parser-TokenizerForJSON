/** ***************************************************************************
 * @remark CS 315: Main function to test the tokenizer and parser
 *
 * @author Ali Kooshesh and Suzanne Rivoire (Assignment Completed by Natnael Zeweldi)
 * @file  main_phase1.cpp
 * @date  Fall 2023
 *
 * @remark This main function tests only the tokenizer and parser.
 *         It takes the name of the .json file as a command-line input,
 *         instantiates a parser for that file, and prints the resulting map
 *         of { course names -> vectors of their prerequisites }.
 * 
 *         Optionally, you can set the PRINT_TOKENS constant to true
 *         to create a separate tokenizer so that you can print the individual 
 *         tokens in the .json file.
 **************************************************************************** */

#include <iostream>
#include <fstream>
#include "constants.hpp"
#include "Parser.hpp"

// Token and Tokenizer: only needed for testTokenizer
#include "Token.hpp"
#include "Tokenizer.hpp"

const bool PRINT_TOKENS = false; // set this to true to debug tokenizer
const bool PRINT_PARSER_MAP = true; // set this to true to test your parser

void verifyReadableInputFile(char* jsonFileName);
void testTokenizer(char* jsonFileName);

/** ***************************************************************************
 * Main function. Pass it the name of the JSON file as a command-line argument.
 * 
 * For example:
 * ./parser.x csbs.json
 * 
 * @param argc: number of command-line arguments (should be 2)
 * @param argv: array of command-line arguments as C-style strings.
 *              argv[0] is always name of executable file; 
 *              for this program, argv[1] should be name of JSON input file
 **************************************************************************** */
int main(int argc, char *argv[]) {

    // Make sure that the executable was given exactly 1 command-line argument
    if (argc != 2) {
        std::cerr << errorMessages[E_WRONG_NUMBER_ARGS] << std::endl;
        exit(E_WRONG_NUMBER_ARGS);
    }

    // Verify that the command-line argument is a legitimate, readable file
    // Exit with error if not.
    verifyReadableInputFile(argv[1]);

    // Optionally, print all tokens. Only do this when writing and debugging
    // your tokenizer. Once you're confident in your tokenizer and have moved
    // on to the parser, set PRINT_TOKENS at the top of this file back to false.
    if (PRINT_TOKENS) {
        testTokenizer(argv[1]);
    }

    if(PRINT_PARSER_MAP) {
        // Create Parser object for the JSON file and get the map it returns.
        Parser parser(argv[1]);
        std::map<std::string, std::vector<std::string>> requisiteMap = parser.parseJSONObject();

        // Iterate over the (key, value) pairs in the map that was created.
        // This loop inserts formatting to make it look like the original JSON file.
        std::cout << "\nThe parser created this prerequisite map:" << std::endl;
        for (auto &[key, value]: requisiteMap) {
            std::cout << key << ": ";
            for (int i = 0; i < value.size(); i++) {
                std::cout << value.at(i);
                if (i != value.size() - 1)
                    std::cout << ", ";
            }
            std::cout << std::endl;
        }
    }
    return 0;
}

/** ***************************************************************************
 * Make sure that the filename passed as a command-line argument is a valid,
 * readable file. This does not necessarily mean that it is a correctly
 * formatted JSON file.
 * 
 * Will exit the program with error if the file cannot be opened or cannot
 * be read.
 * 
 * This is also an example of a function that uses the provided error
 * messages but extends them with additional, situation-specific information.
 * 
 * @param jsonFileName: the command-line argument, which should be the name
 *          of a valid, readable file
 **************************************************************************** */
void verifyReadableInputFile(char* jsonFileName) {
    std::fstream inputStream;
    inputStream.open(jsonFileName, std::ios::in);

    if (!inputStream.is_open()) {
        std::cerr << errorMessages[E_BAD_INPUT_FILE] << jsonFileName << std::endl;
        exit(E_BAD_INPUT_FILE);
    }
    inputStream.close(); // close file! Parser will reopen it later.
}

/** ***************************************************************************
* Isolate the tokenizer for testing -- creates a tokenizer without a parser.
* Grabs each token and prints it.
* 
* Your parser will need to instantiate a tokenizer and read successive tokens
* from it too, so this code may help you.
*
* @param jsonFileName: the command-line argument (the name of the JSON file)
* 
* @pre Before calling this function, you should have verified that
*      jsonFileName is the name of a valid, readable file.
**************************************************************************** */

void testTokenizer(char* jsonFileName) {

    Tokenizer tokenizer = Tokenizer(jsonFileName);

    Token token = tokenizer.getToken(); // get the first token

    // Keep reading and printing tokens until you hit the special 
    // "End of file" symbol
    while( !token.eof() ) {
        std::cout << token.toString() << std::endl;
        token = tokenizer.getToken();
    }

    std::cout << token.toString() << std::endl; // print EOF token

}