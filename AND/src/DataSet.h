//
// Created by rdher on 09/02/2022.
//

#ifndef AND_DATASET_H
#define AND_DATASET_H
#include "vector"
#include "Matrix.h"
class DataSet {
    std::vector<std::vector<float>> inputs;
    std::vector<std::vector<float>> expectedOutput;
    std::vector<std::vector<float>> output;
public:
    DataSet();
    void addData(const std::vector<float>& in, const std::vector<float>& expectedOut){
        inputs.push_back(in);
        expectedOutput.push_back(expectedOut);
        output.push_back({0});
    }
    const std::vector<std::vector<float>>& Inputs()const{
        return inputs;
    }
    const std::vector<std::vector<float>>& Output() const{
        return output;
    }
    const std::vector<std::vector<float>>& ExpectedOutput() const{
        return expectedOutput;
    }

};


#endif //AND_DATASET_H
