#include <utility>

#include "Eigen/Dense"

struct MLP {
public:
    MLP(std::vector<std::vector<std::vector<double>>> W, std::vector<int> npl,
        std::vector<std::vector<double>> X, std::vector<std::vector<double>> deltas, int L)
        : W(std::move(W)), npl(std::move(npl)), X(std::move(X)), deltas(std::move(deltas)), L(L){}

    std::vector<std::vector<std::vector<double>>> W;
    std::vector<int> npl;
    std::vector<std::vector<double>> X;
    std::vector<std::vector<double>> deltas;
    int L;
};

extern "C" {
    __declspec(dllexport) double *predictLinearModelRegression(double sampleInputs[],
               double sampleExpectedOutputs[], int sampleCount, int inputDim, int outputDim) {
        double *result = new double[inputDim + 1];

        Eigen::MatrixXd X(inputDim, sampleCount);
        Eigen::MatrixXd Y(inputDim, sampleCount);
        for (int i = 0; i < sampleCount; ++i) {
            for (int j = 0; j < inputDim; ++j) {
                X(i, j) = sampleInputs[i * inputDim + j];
            }
        }
        for (int i = 0; i < sampleCount; ++i) {
            for (int j = 0; j < outputDim; ++j) {
                Y(i, j) = sampleExpectedOutputs[i * outputDim + j];
            }
        }
        Eigen::MatrixXd W = ((X.transpose() * X).inverse() * X.transpose()) * Y;    // vector
        for (int i = 0; i < inputDim + 1; ++i) {
            result[i] = W(i, 0);
        }
        return result;
    }

    __declspec(dllexport) MLP *createMlpModel(int npl[], int nplSize) {
        int L = nplSize - 1;

        std::vector<std::vector<std::vector<double>>> W;
        for(int l = 0; l < L+1; ++l){
            W.emplace_back();
            if(l == 0)
                continue;

            for(int i = 0; i < npl[l - 1] + 1; ++i){
                W[l].emplace_back();
                for(int j = 0; j < npl[l] + 1; ++j){
                    double r = ((double) rand() / (RAND_MAX));
                    W[l][i].push_back(j != 0 ? r * 2.0 - 1.0 : 0.0);
                }
            }
        }

        std::vector<std::vector<double>> X;
        for(int l = 0; l < L + 1; ++l){
            X.emplace_back();
            for(int j = 0; j < npl[l] + 1; ++j){
                X[l].push_back(j == 0 ? 1.0 : 0.0);
            }
        }
        std::vector<std::vector<double>> deltas;
        for(int l = 0; l < L + 1; ++l){
            deltas.emplace_back();
            for(int j = 0; j < npl[l] + 1; ++j){
                deltas[l].push_back(0.0);
            }
        }

        std::vector<int> nplVec;
        nplVec.reserve(nplSize);
        for(int i = 0; i < nplSize; ++i){
            nplVec.push_back(npl[i]);
        }
        auto model = new MLP(W, nplVec, X, deltas, L);
        return model;
    }

    __declspec(dllexport) void destroyMlpModel(MLP *model) {
        delete model;
    }

    __declspec(dllexport) void destroyMlpResult(const double *result) {
        delete[] result;
    }

    _declspec(dllexport) void forwardPassMlpRegression(MLP *model, double sampleInputs[], int sampleInputsSize) {
        assert(sampleInputsSize == model->npl[0]);

        for(int j = 1; j < model->npl[0] + 1; ++j){
            model->X[0][j] = sampleInputs[j - 1];
        }

        for(int l = 1; l < model->L + 1; ++l){
            for(int j = 1; j < model->npl[l] + 1; ++j){
                double total = 0.0;
                for(int i = 0; i < model->npl[l - 1] + 1; ++i){
                    total += model->W[l][i][j] * model->X[l-1][i];
                }

                if(l != model->L){
                    total = tanh(total);
                }

                model->X[l][j] = total;
            }
        }
    }

    __declspec(dllexport) double *predictMlpModelRegression(MLP *model, double sampleInputs[], int inputDim) {
        forwardPassMlpRegression(model, sampleInputs, inputDim);
        auto resultVec = model->X[model->L];
        auto result = new double[resultVec.size()];
        for(int i = 1; i < resultVec.size(); ++i){
            result[i-1] = resultVec[i];
        }
        return result;
    }

    _declspec(dllexport) void trainMlpModelRegression(MLP *model, double samplesInputs[], double samplesExpectedOutputs[],
                     int sampleCount, int inputDim, int outputDim, double alpha, int nbIter) {
        for(int it = 0; it < nbIter; ++it){
            int randInt = rand()%(sampleCount);
            int k = randInt;
            auto sampleInputs = samplesInputs + k;
            auto sampleExpectedOutput = samplesExpectedOutputs + k;

            forwardPassMlpRegression(model, sampleInputs, inputDim);

            for(int j = 1; j < model->npl[model->L] + 1; ++j){
                model->deltas[model->L][j] = (model->X[model->L][j] - sampleExpectedOutput[j - 1]);

                model->deltas[model->L][j] *= (pow(1 - model->X[model->L][j], 2));
            }

            // changer ici si l index passe pas
            for(int l = model->L; l >= 2; --l){
                for(int i = 1; i < model->npl[l - 1] + 1; ++i){
                    double total = 0.0;
                    for(int j = 1; j < model->npl[l] + 1; ++j){
                        total += model->W[l][i][j] * model->deltas[l][j];
                    }
                    total *= (1 - pow(model->X[l-1][i], 2));
                    model->deltas[l-1][i] = total;
                }
            }

            for(int l = 1; l < model->L + 1; ++l){
                for(int i = 0; i < model->npl[l - 1] + 1; ++i){
                    for(int j = 1; j < model->npl[l] + 1; ++j){
                        model->W[l][i][j] -= alpha * model->X[l-1][i] * model->deltas[l][j];
                    }
                }
            }
        }
    }

    double evaluateModelAccuracy(MLP* model, double samplesInputs[], double samplesExpectedOutputs[],
                                 int sampleCount, int inputDim, int outputDim){
        double totalGoodPredictions = 0.0;
        for(int i = 0; i < sampleCount; ++i){
            auto sampleInputs = samplesInputs + i;
            auto sampleExpectedOutputs = samplesExpectedOutputs + i;
            double* v = predictMlpModelRegression(model, sampleInputs, inputDim);
            if(v[0] * sampleExpectedOutputs[0] >= 0){
                totalGoodPredictions += 1;
            }
        }
        return totalGoodPredictions / sampleCount;
    }
}