#include <iostream>
#include "src/Network.h"
#include "src/DataSet.h"
#include "src/MoveParser.h"
#include "src/MoveMapper.h"
int main() {
    Network net;
    net.addLayer(2);
    net.addLayer(1);

    DataSet set;
    MoveMapper mapper;

    std::vector<float> inData;
    // data 1
    auto moves = parseMoves("d4 d5 c4 c6 cxd5 e6 dxe6 fxe6 Nf3 Bb4+ Nc3 Ba5 Bf4");
    for(auto& move : moves){
        float value = mapper.registerMove(move);
        inData.push_back(value);
    }
    set.addData(inData, {1});   // white, 0 si black
    // fin data

    // data 2
    inData.clear();
    moves = parseMoves("d4 Nc6 e4 e5 f4 f6 dxe5 fxe5 fxe5 Nxe5 Qd4 Nc6 Qe5+ Nxe5 c4 Bb4+");
    for(auto& move : moves){
        float value = mapper.registerMove(move);
        inData.push_back(value);
    }
    set.addData(inData, {0});   // black
    // fin data

    // data 3
    inData.clear();
    moves = parseMoves("e4 e5 d3 d6 Be3 c6 Be2 b5 Nd2 a5 a4 c5 axb5 Nc6 bxc6 Ra6 Nc4 a4 c3 a3 Nxa3 Rxa3 Rxa3 c4 dxc4 d5 cxd5 Qxd5 exd5 Be6 Ra8+ Ke7 Bc5+ Kf6 Bxf8 Kg6 Bxg7 Kxg7 dxe6 Kh6 exf7 Nf6 Rxh8 Nh5 Bxh5 Kg5 Rxh7 Kf5 Qf3+ Ke6 Bg4+ Kd6 Rh6+ Kc5 Qe3+ Kb5 c4+ Kb4 Qc3+ Ka4 Bd1#");
    for(auto& move : moves){
        float value = mapper.registerMove(move);
        inData.push_back(value);
    }
    set.addData(inData, {1});   // white
    // fin data


    //And dataset
    /*set.addData({0, 0}, {0});
    set.addData({1, 0}, {0});
    set.addData({0, 1}, {0});
    set.addData({1, 1}, {1});*/

    net.train(set);

    //other dataset
    /*set.addData({0.8, 0.9}, {1});
    set.addData({0, 0.5}, {0});
    set.addData({0.7, 0}, {0});
    set.addData({0, 0}, {0});*/


    return 0;
}
