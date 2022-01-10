#include "Eigen/Dense"

extern "C"{
    __declspec(dllexport) double* predictLinearModelRegression(double sampleInputs[],
               double sampleExpectedOutputs[], int sampleCount, int inputDim,
               int outputDim){
        double* result = new double[inputDim*sampleCount];

        Eigen::MatrixXd X(inputDim, sampleCount);
        Eigen::MatrixXd Y(inputDim, sampleCount);
        for(int i = 0; i < sampleCount; ++i){
            for(int j = 0; j < inputDim; ++j){
                X(i, j) = sampleInputs[i * inputDim + j];
            }
        }
        for(int i = 0; i < sampleCount; ++i){
            for(int j = 0; j < outputDim; ++j){
                Y(i, j) = sampleExpectedOutputs[i * outputDim + j];
            }
        }
        Eigen::MatrixXd W = ((X.transpose() * X).inverse() * X.transpose()) * Y;    // vector
        for(int i = 0; i < sampleCount; ++i){
            result[i] = W(i, 0);
        }
        return result;
    }
}