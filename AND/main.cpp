#include <iostream>
#include "src/Network.h"
#include "src/DataSet.h"
#include "src/MoveParser.h"
#include "src/MoveMapper.h"
int main() {
    Network net;
    net.addLayer(10);
    net.addLayer(5);
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



    net.train(set);

    DataSet set2;
    // data 1
    moves = parseMoves("c4 c6 e4 e6 Nf3 d5 cxd5 cxd5 e5 Nc6 d4 Qb6 Be3 Nge7 b3 Nf5 Bg5 Bb4+ Nfd2 Ncxd4 a3 Bxd2+ Nxd2 Bd7 Bd3 O-O O-O h6 Bf6 Kh7 Nf3 gxf6 exf6 Bb5 Ng5+ hxg5 Qh5+ Kg8 Qxg5+ Kh7 Qg7#");
    for(auto& move : moves){
        float value = mapper.registerMove(move);
        inData.push_back(value);
    }
    set2.addData(inData, {1});   // white, 0 si black
    // fin data
    // data 2
    moves = parseMoves("e4 c6 d4 d5 Nc3 dxe4 Nxe4 Bf5 Bd3 Nd7 Nc3 Bxd3 Qxd3 e6 Nf3 Ngf6 Bg5 h6 Bh4 Be7 Bg3 a5 O-O a4 Ne5 O-O a3 c5 Rad1 Nb6 Qb5 cxd4 Nxa4 Nxa4 Qxb7 Nc5 Qf3 Na4 Nc6 Qd7 Rxd4 Nd5 Ne5 Qb5 Rfd1 Nxb2 Rb1 Bc5 Rh4 Rxa3 Qg4 Nc3 Re1 Nbd1 Qxg7+ Kxg7 Rg4+ Kh7 Rh4 Ne2+ Kf1 Nxg3+");
    for(auto& move : moves){
        float value = mapper.registerMove(move);
        inData.push_back(value);
    }
    set2.addData(inData, {0});   // white, 0 si black
    // fin data
    float error = net.evaluate(set2,0.25);
    std::cout << set.Inputs().size() <<std::endl;
    std::cout << set.ExpectedOutput().size() <<std::endl;
    std::cout << set.Output().size() <<std::endl;



    return 0;
}

//d4 d5 c4 c6 cxd5 e6 dxe6 fxe6 Nf3 Bb4+ Nc3 Ba5 Bf4
//