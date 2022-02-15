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
    static float meanAbsoluteError(DataSet& dataset)
    {
        float sum = 0;
        for (int j = 0; j < dataset.Output().size(); ++j) {
            float dataSum = 0;
            for (int i = 0; i < dataset.Output()[j].size() ; i++){
                float outputVal = dataset.Output()[j][i];
                float expectedVal = dataset.ExpectedOutput()[j][i];
                dataSum += std::abs(outputVal-expectedVal);
            }
            sum += dataSum / (float)dataset.Output()[j].size();
        }
        return sum/(float)dataset.Output().size();
    }
};


#endif //AND_NETWORK_H
