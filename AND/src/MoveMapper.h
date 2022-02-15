// Created by Quentin Pamart on 15/02/2022.

#pragma once

#include <map>
#include <string>
#include "DataSet.h"

class MoveMapper {
public:
    MoveMapper();
    float registerMove(const std::string& move);
    std::string getMove(float value);
    float valueCount() const;
private:
    std::map<std::string, float> movesToValues;
    std::map<float, std::string> valuesToMoves;

    float currentValue;
};



