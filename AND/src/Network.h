//
// Created by rdher on 09/02/2022.
//

#ifndef AND_NETWORK_H
#define AND_NETWORK_H
#include "DataSet.h"
#include "vector"
#include "Matrix.h"
class Network {
private :
    std::vector<int> sizes;
    std::vector<Matrix<float>> matrix;
    std::vector<std::vector<float>> treatedVals;
    void backpropagate(const std::vector<float>& expectedOut,
                       std::vector<float>& output,
                       std::vector<std::vector<float>>& deltasVector,
                       float learningRate,bool isSig);

public:
    Network() = default;
    void addLayer(int nbNeuron);
    void compute(const std::vector<float>& input, std::vector<float>& output, bool isSig = true);
    void train(DataSet& dataSet, int nbLoop=1000, float learningRate =0.01f);
    float evaluate(DataSet& dataset, float threshold, int nbLoop = 1000);

};


#endif //AND_NETWORK_H
