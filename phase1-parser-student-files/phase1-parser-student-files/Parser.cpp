//
// Created by Ali Kooshesh on 10/4/23.
// Natnael Zeweldi
#include "Parser.hpp"
#include "constants.hpp"
#include <tuple>
#include <iostream>
#include <map>
#include <utility>

// parse a JSON object initially until you approach key value and vector values
std::map<std::string, std::vector<std::string>> Parser::parseJSONObject() {

    Token token = tokenizer.getToken();
    // Initial Brace : {
    if(!token.isOpenBrace()){
        std::cerr << "(Parser::parseJSONObject)" << " "<< errorMessages[6] << std::endl;
        exit(E_EXPECTED_OPEN_BRACE);
    }

    while(!token.isCloseBrace())
    {
            // convert a tuple to pair and insert into jsonObject map
            std::tuple<std::string, std::vector<std::string>> t2 = parseKeyValuePair();
            std::string s2 = std::get<0>(t2);
            std::vector<std::string> v2 = std::get<1>(t2);
            std::pair<std::string, std::vector<std::string>> p2=std::make_pair(s2,v2);

            if(jsonObject.count(s2)==0) {

                jsonObject.insert(p2);
            }
            else {

                std::cerr << "(Parser::parseJSONObject)" << " "<< errorMessages[14] << std::endl;
                exit(E_DUPLICATE_KEYS);
            }

        token = tokenizer.getToken(); // expecting either a comma or the closing brace
    }
    // expecting a close brace here
    if(!token.isCloseBrace()){
        std::cerr << "(Parser::parseJSONObject)" << " "<< errorMessages[7]
        << token.symbol() << std::endl;
        exit(E_EXPECTED_CLOSE_BRACE);
    }

    token = tokenizer.getToken();
// eof reached
    if(!token.eof()){
        std::cerr << "(Parser::parseJSONObject)" << " "<< errorMessages[10]
        << token.symbol() << std::endl;
        exit(E_EXPECTED_EOF);
    }

    return jsonObject;
// return map after parsing key value pairs
}

 // STEPS INDICATE PATH OF THE PARSER FROM INITIAL QUOTED STRING
 // THAT IS THE KEY, THROUGH THE VECTOR WHETHER IT BE EMPTY OR
 // HAVE ELEMENTS TO THE CLOSING SQUARE BRACKET

 // AS LONG AS THERE IS NO ERRORS FROM THE FILE IT SHOULD
 // BE ABLE TO PARSE A KEY VALUE PAIR (THAT WILL BE ADDED TO A MAP)

 // IF NOT AN ERROR WILL BE CALLED DEPENDING ON WHERE THE
 // ERROR OCCURS TO ALLOW FOR ACCURATE REPORT OF THE MISTAKE

std::tuple<std::string, std::vector<std::string>> Parser::parseKeyValuePair() {

    Token token;
    std::string s1,s2;
    std::vector<std::string> v1,v2;

    token = tokenizer.getToken();

    // key - "MATH 000"/"CS 000"
    if(token.isQuotedString()){

        s1=token.quotedString();
        token = tokenizer.getToken();
    }
    else {

        std::cerr << "(Parser::parseKeyValuePair)" << " " << errorMessages[11]
        << token.symbol() << std::endl;
        exit(E_EXPECTED_KEY);
    }
    // colon - :
    if(token.isColon()){

        token = tokenizer.getToken();
    }
    else {

        std::cerr << "(Parser::parseKeyValuePair)" << " "<< errorMessages[9]
        << token.symbol() << std::endl;
        exit(E_EXPECTED_COLON);
    }
    // Open Sq. Bracket - [
    if(token.isOpenSquareBracket()){

         token = tokenizer.getToken();
    }
    else {
        std::cerr << "(Parser::parseKeyValuePair)" << " "<< errorMessages[4]
        << token.symbol()<< std::endl;
        exit(E_EXPECTED_OPEN_BRACKET);
    }
    // value vector - "CS 000"/"MATH 000"
    if(token.isQuotedString()){

        while(!token.isCloseSquareBracket()){

            if(!token.isCloseSquareBracket()) {

                if (token.isQuotedString() && v1.size() != 3) {
                    v1.push_back(token.quotedString());
                }

                token = tokenizer.getToken();
            }
        }

        return std::make_tuple(s1,v1);

    } else if(token.isCloseSquareBracket()){
        // no vector values so, return the key with an empty vector
        return std::make_tuple(s1,v2);
    }
    else { // this might not be necessary

        std::cerr << "Incorrect symbol placement.\n";
        return std::make_tuple(s2,v2);
    }
}