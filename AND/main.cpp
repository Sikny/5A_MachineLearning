#include <iostream>
#include "src/Network.h"
#include "src/DataSet.h"
int main() {
    Network net;
    net.addLayer(2);
    net.addLayer(1);

    DataSet set;
    //And dataset
    // in : {d4,d5, c4, c6}, {0}

    // in : {0, 5, 9, 12}, {0}
    //
    //in : {d4,d5, c4, c6}
    set.addData({0, 0}, {0});
    set.addData({1, 0}, {0});
    set.addData({0, 1}, {0});
    set.addData({1, 1}, {1});

    net.train(set);

    DataSet set2;
    //other dataset
    set2.addData({0.8, 0.9}, {1});
    set2.addData({0, 0.5}, {0});
    set2.addData({0.7, 0}, {0});
    set2.addData({0, 0}, {0});

    float error = net.evaluate(set2,0.25);
    std::cout << set.Inputs().size() <<std::endl;
    std::cout << set.ExpectedOutput().size() <<std::endl;
    std::cout << set.Output().size() <<std::endl;


    return 0;
}

//d4 d5 c4 c6 cxd5 e6 dxe6 fxe6 Nf3 Bb4+ Nc3 Ba5 Bf4
//