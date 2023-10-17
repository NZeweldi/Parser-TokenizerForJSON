/** ***************************************************************************
 * @remark CS 315: Constants and error message strings for parser
 *
 * @author Ali Kooshesh and Suzanne Rivoire
 * @file  constants.hpp
 * @date  Fall 2023
 *
 * @remark Use the constants in this header file rather than hard-coding
 *         your exit codes (e.g. exit(5)) or your error messages.
 * ************************************************************************* */

#ifndef CANBETAKENTOGETHER_CONSTANTS_HPP
#define CANBETAKENTOGETHER_CONSTANTS_HPP

#include <string>

/* ****************************************************************************
 * Enum for error codes
 *
 * Rather than hard-coding your exit codes, use this enum.
 * 
 * For example, instead of exit(1), use exit(E_WRONG_NUMBER_ARGS), which is
 * longer but clearer.
 * 
 * The "= 0", "= 1", etc. are unnecessary, since that's the default behavior
 * of enum; we're just making it explicit.
 * 
 * --- ONLY READ THE REST OF THIS COMMENT IF YOU'RE CURIOUS: ---
 * 
 * If you're new to enums and want to learn more, read the first section here:
 * https://learnmoderncpp.com/enums-and-structs/
 * 
 * If you're NOT new to enums and want to know why we didn't use the more
 * modern "enum class" construct, there are pros and cons!
 * 
 *     Pro of "enum class" vs. "enum": you don't "pollute the namespace" -- 
 *     that is, you're less likely to accidentally use one of the enum
 *     names in a totally different context in some other part of the program.
 * 
 *     Con of "enum class"": it's super annoying to use the enum like an int.
 * 
 * Since we're going to be using these enums as ints a LOT, we chose the
 * old way (traditional "enum") to avoid complicating your life.
 * ************************************************************************* */
enum Errors {
    E_OK = 0,
    // errors in main
    E_WRONG_NUMBER_ARGS = 1,  // wrong number of command-line args
    E_BAD_INPUT_FILE = 2, // provided input .json file can't be opened/read
    // tokenizer errors
    E_BAD_TOKEN = 3, // non-tokenizable character found in input

    // parser errors
    E_EXPECTED_OPEN_BRACKET = 4,  // parser expected [ and got something else
    E_EXPECTED_CLOSE_BRACKET = 5, // parser expected ] and got something else
    E_EXPECTED_OPEN_BRACE = 6, // parser expected { and got something else
    E_EXPECTED_CLOSE_BRACE = 7, // parser expected } and got something else
    E_EXPECTED_COMMA = 8, // parser expected , and got something else
    E_EXPECTED_COLON = 9, // parser expected : and got something else
    E_EXPECTED_EOF = 10, // parser expected end of file but there was more!
    E_EXPECTED_KEY = 11, // expected a quoted string as the key of a k-v pair
    E_EXPECTED_VALUE = 12, // expected quoted string in values of a k-v pair
    // shouldn't have comma after last item in a value vector or
    // after the last k-v pair
    E_COMMA_AFTER_LAST_ITEM = 13,
    E_DUPLICATE_KEYS = 14
};

/* ****************************************************************************
 * Array of error messages
 *
 * Instead of having string literals all over your code, use these instead.
 * They work together with the enums above: you can use the enum to index
 * into this array.
 *
 * For example, instead of
 * std::cerr << "Usage: ./parser.x name-of-json-file\n"
 * do
 * std::cerr << errorMessages[E_WRONG_NUMBER_ARGS];
 *
 * This is the same thing as
 * std::cerr << errorMessages[1];
 * but easier to understand.
 *
 * Why do this instead of interspersing error messages throughout the code?
 * 1. You can see all the error messages at once.
 * 2. It makes it easier to change the look of all of the error messages.
 *    For example, if you decide you want them all to start with "!!ERROR!!!",
 *    it's easy to make that change in one place.
 * 3. It's a baby step toward the professional software engineering practice
 *    of localization, a.k.a. internationalization. Imagine that we wanted to
 *    make (for example) a Spanish-language version of this program. We'd
 *    want all of these strings in one place so we could easily swap them out
 *    for their Spanish equivalents.
 *
 * In industry, there are more full-featured tools and practices for this than
 * what we're doing here -- this is just to give you the general idea
 * and hopefully make your code a little easier to read and write.
 * ************************************************************************* */
const std::string ERROR_MSG_EXPECTED_TOKEN = "Error: Expected token ";
const std::string ERROR_MSG_GOT_TOKEN = " but got ";

const std::string errorMessages[] = {
        "", // no error
        "Usage: ./parser.x name-of-json-file",
        "Error: Unable to open the input file: ",

        "Error: Tokenizer found unexpected character in input file: ",

        // Parser errors
        ERROR_MSG_EXPECTED_TOKEN + "[" + ERROR_MSG_GOT_TOKEN,
        ERROR_MSG_EXPECTED_TOKEN + "]" + ERROR_MSG_GOT_TOKEN,
        ERROR_MSG_EXPECTED_TOKEN + "{" + ERROR_MSG_GOT_TOKEN,
        ERROR_MSG_EXPECTED_TOKEN + "}" + ERROR_MSG_GOT_TOKEN,
        ERROR_MSG_EXPECTED_TOKEN + "," + ERROR_MSG_GOT_TOKEN,
        ERROR_MSG_EXPECTED_TOKEN + ":" + ERROR_MSG_GOT_TOKEN,
        "Error: Expected end of file, but there was more file! Specifically: ",
        "Error: Expected quoted string for a key" + ERROR_MSG_GOT_TOKEN,
        "Error: Expected quoted string for the value vector" + ERROR_MSG_GOT_TOKEN,
        "Error: Unexpected comma after ",
        "Error: Duplicate key: "
};

#endif
