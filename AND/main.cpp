#include <iostream>
#include "src/Network.h"
#include "src/DataSet.h"

void display(DataSet &set) {
    for (int i = 0; i < set.Inputs().size(); ++i) {
        std::cout << "-----Input-----" << std::endl;
        std::cout << "{";
        for (int j = 0; j < set.Inputs()[i].size(); ++j) {
            std::cout << set.Inputs()[i][j];
            if (j != set.Output()[i].size()) {
                std::cout << ", ";
            }
        }
        std::cout << "}";
        std::cout << std::endl;

        std::cout << "-----Expected Output-----" << std::endl;
        std::cout << "{";
        for (int j = 0; j < set.ExpectedOutput()[i].size(); ++j) {
            std::cout << set.ExpectedOutput()[i][j];
            if (j != set.ExpectedOutput()[i].size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "}";
        std::cout << std::endl;

        std::cout << "-----Output-----" << std::endl;
        std::cout << "{";
        for (int j = 0; j < set.Output()[i].size(); ++j) {
            std::cout << set.Output()[i][j];
            if (j != set.Output()[i].size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "}";
        std::cout << std::endl << std::endl;
    }
}

int main() {
    Network net;
    net.addLayer(2);
    net.addLayer(1);

    DataSet set;
    //And dataset
    set.addData({0, 0}, {0});
    set.addData({1, 0}, {0});
    set.addData({0, 1}, {0});
    set.addData({1, 1}, {1});

    net.train(set);

    //other dataset
    set.addData({0.8, 0.9}, {1});
    set.addData({0, 0.5}, {0});
    set.addData({0.7, 0}, {0});
    set.addData({0, 0}, {0});

    return 0;
}