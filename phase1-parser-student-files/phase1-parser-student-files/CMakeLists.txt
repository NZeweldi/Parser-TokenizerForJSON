cmake_minimum_required(VERSION 3.24)
project(CanBeTakenTogether)

set(CMAKE_CXX_STANDARD 20)

add_executable(parser.x main_phase1.cpp Token.cpp Token.hpp Tokenizer.cpp Tokenizer.hpp Parser.cpp Parser.hpp Parser.cpp Tokenizer.cpp)
