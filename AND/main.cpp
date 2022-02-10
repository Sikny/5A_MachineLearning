#include <iostream>
#include "src/Network.h"
#include "src/DataSet.h"
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
