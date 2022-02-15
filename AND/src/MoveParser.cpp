// Created by Quentin Pamart on 15/02/2022.

#include "MoveParser.h"

#include <sstream>

std::vector<std::string> parseMoves(const std::string& moveList){
    std::vector<std::string> moves;
    std::stringstream stream(moveList);
    std::string word;

    while(std::getline(stream, word, ' ')){
        moves.emplace_back(word);
        if(moves.size() == 10) break;
    }

    return moves;
}