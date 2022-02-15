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

    ///LE TRAIN DE LA HYPE EST PASSER PAR LA
    net.train(set);


    DataSet set2;

    inData.clear();
    moves = parseMoves("d4 d5 Bf4 c5 e3 cxd4 exd4 e6 Nf3 Nc6 c3 h6 Qa4 Bd7 Bb5 g5 Bg3 g4 Ne5 Nxe5 Bxe5 a6 Bxd7+ Qxd7 Qxd7+ Kxd7 Bxh8 Ne7");
    for(auto& move : moves){
        float value = mapper.registerMove(move);
        inData.push_back(value);
    }
    set2.addData(inData, {1});   // white


    inData.clear();
    moves = parseMoves("d4 Nf6 Nf3 e6 e3 b6 Bd3 Bb7 c4 c5 Qc2 Bxf3 gxf3 cxd4 exd4 Nc6 d5 Nb4 Qc3 Rc8 a3 Nfxd5 Qb3 Nxd3+ Qxd3 Qc7 cxd5 Qxc1+ Qd1 Qxb2 dxe6 Rc1 exd7+ Kd8 Nd2 Rxa1 O-O Rxd1 Rxd1 Qc2");
    for(auto& move : moves){
        float value = mapper.registerMove(move);
        inData.push_back(value);
    }
    set2.addData(inData, {0});   // black

    inData.clear();
    moves = parseMoves("d4 d5 c4 e6 Nc3 Bb4 Bd2 dxc4 e3 Bxc3 Bxc3 Qd5 Qa4+ b5 Qb4 Nc6 Qc5 a5 Qxd5 exd5 a3 Nge7 Nf3 Ba6 Be2 b4 axb4 axb4 Bd2 b3 O-O O-O Ne5 Nxe5 dxe5 g6 Bf3 c3 Bxc3 Bxf1 Rxa8 Rxa8 Kxf1 Ra1+ Ke2 c6 e4 dxe4 Bxe4 Ra4 f4 Rxe4+");
    for(auto& move : moves){
        float value = mapper.registerMove(move);
        inData.push_back(value);
    }
    set2.addData(inData, {0});   // black


    inData.clear();
    moves = parseMoves("e3 e5 d4 Nc6 dxe5 Nxe5 Nf3 Bd6 Nxe5 Bxe5 Qf3 Qf6 Qd5 Ne7 Qd1 O-O h4 Bxb2 Bxb2 Qxb2 Nd2 Qb3 Nxb3");
    for(auto& move : moves){
        float value = mapper.registerMove(move);
        inData.push_back(value);
    }
    set2.addData(inData, {1});   // black



    float error = net.evaluate(set2,0.25);

    return 0;
}

//d4 d5 c4 c6 cxd5 e6 dxe6 fxe6 Nf3 Bb4+ Nc3 Ba5 Bf4
//