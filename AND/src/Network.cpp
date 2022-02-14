//
// Created by rdher on 09/02/2022.
//

#include "Network.h"
#include "random"

static void linear(std::vector<float> &values) {
    for (float &value: values) {
        value = value;
    }
}

static void sigmoid(std::vector<float> &values) {
    for (float &value: values) {
        value = tanh(value);
    }
}

void Network::addLayer(int nbNeuron) {
    sizes.push_back(nbNeuron);

    //Pas besoin de ca pour le 1er
    if (sizes.size() == 1)
        return;

    int matWidth = sizes[sizes.size() - 2] + 1;
    int matHeight = nbNeuron;
    //add Construct get ref
    Matrix<float> &mat = matrix.emplace_back(matWidth, matHeight);
    for (int i = 0; i < matWidth; ++i) {
        for (int j = 0; j < matHeight; ++j) {
            //TODO: Add du rdm a la place du 0
            mat(i, j) = 0;
        }
    }
}

void Network::train(DataSet &dataset, int nbLoop, float learningRate) {
    std::random_device rdmD;
    std::mt19937 seed(rdmD());
    std::uniform_int_distribution<> dist(0, dataset.Inputs().size() - 1);

    std::vector<std::vector<float>> deltasVector;
    deltasVector.reserve(sizes.size() + 1);//on alloue la place requise
    for (int i = 0; i < sizes.size(); ++i) {
        {
            deltasVector.emplace_back(sizes[i]);
        }

        for (int i = 0; i < nbLoop; ++i) {
            int index = dist(seed);
            compute(dataset.Inputs()[index], dataset.Output()[index], index != 0);
            backpropagate(dataset.ExpectedOutput()[index], dataset.Output()[index], deltasVector, learningRate, index != 0);
        }
    }
}

void Network::compute(const std::vector<float> &input, const std::vector<float> &output, bool isSig) {
    //Copy la list
    std::vector<float> vals(input.begin(), input.end());

    for (int i = 0; i < sizes.size(); ++i) {
        if (i > 0) {
            vals = matrix[i - 1] * vals;
        }

        if (isSig)
            sigmoid(vals);
        else
            linear(vals);
        treatedVals.push_back(vals); // Stockage pour le backpropagate
        vals.emplace_back(1.f);//ajoute le bias a la fin
    }
    //Met le contenu dans output
    std::copy(vals.begin(), vals.end() - 1, output.begin());
}


float Network::evaluate(const DataSet& dataset,float threshold, int nbLoop) {
    std::vector<float> deltaVec;
    for (int i = 0; i < sizes.size(); ++i) {
        deltaVec.push_back((float)sizes[i]);
    }
    int goodResult=0;
    for (int i = 0; i < nbLoop; ++i) {
        std::vector<float>& in = dataset.Inputs()[i];
        compute(in,dataset.Output()[i]);
        treatedVals.clear();
        bool error = false;
        for (int j = 0; j < dataset.Output().size(); ++j) {
            float diff = abs(dataset.Output()[i][j] - dataset.ExpectedOutput()[i][j]);
            if(diff > threshold){
                error = true;
                break;
            }
        }
        if(!error){
            goodResult++;
        }
    }

    return goodResult/static_cast<float>(dataset.Inputs().size());
}


void Network::backpropagate(const std::vector<float> &expectedOut,
                            const std::vector<float> &output,
                            const std::vector<std::vector<float>> &deltasVector, float learningRate, bool isSig) {
    std::vector<float> &outputLayerDeltas = deltasVector.back();
    std::vector<float> &outputLayerValues = treatedVals.back();
    for (int j = 0; j < outputLayerValues.size(); ++j) {
        //on calcule la diff entre la valeur et celle attendue pour le Jeme neurone
        outputLayerDeltas[j] = outputLayerValues[j] - expectedOut[j];

        //si on est en retropropagation : on s'arrete là
        //sinon on rajoute ca :
        if (isSig)
            outputLayerDeltas[j] *= 1 - std::powf(outputLayerValues[j], 2);
    }

    for (int l = sizes.size(); l >= 2; --l)//l = la couche
    {
        std::vector<float> &currentDeltas = deltasVector[l];
        std::vector<float> &previousDeltas = deltasVector[l - 1];
        std::vector<float> &previousValues = treatedVals[l - 1];
        Matrix<float> &currentMatrix = matrix[l - 1];

        //on parcours autant de fois que le layer précédent est grand
        for (int i = 0; i < sizes[l - 1]; i++)//i = l'input TODO: peut etre retirer - 1
        {
            float total = 0;

            //on parcours chaque neurone
            for (int j = 0; j < sizes[l]; j++)// j = au neurone
            {
                total += currentMatrix(i, j) * currentDeltas[j];//TODO: attention peut etre inverser j et i
            }

            total *= (1 - powf(previousValues[i], 2));
            previousDeltas[i] = total;
        }
        for (int l = 1; l <= sizes.size(); ++l)//pour toutes les couches sauf input
        {
            Matrix<float> &mat = matrix[l - 1];
            std::vector<float> &currentDeltas = deltasVector[l];
            std::vector<float> &previousValues = treatedVals[l - 1];

            for (int i = 0; i < sizes[l - 1] + 1; i++) {
                float val = i < sizes[l - 1] ? previousValues[i] : 1;//permet de gérer le cas du biais
                for (int j = 0; j < sizes[l]; j++) {
                    mat(i, j) -= learningRate * val * currentDeltas[j];
                }
            }
        }
    }
}

