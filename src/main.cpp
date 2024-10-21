/*
Conway is a library for running John Conway's Game of Life
Copyright Ali Raheem 2022 - 2024 - https://github.com/ali-raheem/conway
MIT Licensed
File version: 2024-10-21 19:29 GMT
*/
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <string>
#include <cstdlib>

#include "conway.h"

using namespace std;

int main(int argc, char* argv[]) {
    uint32_t state[35];
    Conway<uint32_t> gol(state, 35);

    int max_staleness = -1;
    string alive_str = " # ";
    string dead_str = "   ";
    int pause_duration = 200;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if ((arg == "-s" || arg == "--staleness") && i + 1 < argc) {
            max_staleness = stoi(argv[++i]);
        }
        else if ((arg == "-a" || arg == "--alive") && i + 1 < argc) {
            alive_str = argv[++i];
        }
        else if ((arg == "-d" || arg == "--dead") && i + 1 < argc) {
            dead_str = argv[++i];
        }
        else if ((arg == "-p" || arg == "--pause") && i + 1 < argc) {
            pause_duration = stoi(argv[++i]);
        }
        else {
            cerr << "Unknown argument: " << arg << endl;
            return 1;
        }
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed);
    uniform_int_distribution<uint32_t> distribution(0, UINT32_MAX);

    for (uint8_t i = 0; i < gol.rows; i++) {
        state[i] = distribution(generator);
    }

    for (uint8_t i = gol.rows; i < gol.rows + 3; i++) {
        state[i] = 0;
    }

    while (true) {
        cout << "\033[2J\033[H";

        gol.next();

        for (uint8_t i = 0; i < gol.rows; i++) {
            for (uint8_t j = 0; j < gol.cols; j++) {
                bool s = gol.getCellState(i, j);
                cout << (s ? alive_str : dead_str);
            }
            cout << endl;
        }
        cout << endl;

        if (max_staleness >= 0 && gol.staleness > max_staleness)
            break;


        this_thread::sleep_for(chrono::milliseconds(pause_duration));
    }

    return 0;
}
