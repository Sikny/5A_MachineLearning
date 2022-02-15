// Created by Quentin Pamart on 15/02/2022.

#include "MoveMapper.h"

MoveMapper::MoveMapper() : currentValue(0){
}

float MoveMapper::registerMove(const std::string& move) {
    if(movesToValues.count(move)){
        return movesToValues[move];
    } else {
        movesToValues[move] = currentValue;
        valuesToMoves[currentValue] = move;
        currentValue++;
        return movesToValues[move];
    }
}

std::string MoveMapper::getMove(float value) {
    return valuesToMoves[value];
}

float MoveMapper::valueCount() const {
    return currentValue - 1;
}

