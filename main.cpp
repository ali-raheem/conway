#include <iostream>
#include <chrono>
#include <thread>

#include "conway.h"

using namespace std;



int main() {
    uint32_t state[35];
    Conway<uint32_t> gol(state, 35);
    gol.clear();
    state[0] = 0x2;
    state[1] = 0x1;
    state[2] = 0x7;
    state[7] = 0x20;
    state[8] = 0x10;
    state[9] = 0x70;

    while (true) {
        gol.next();
        uint8_t i, j;
        for(i = 0; i < 32; i++) {
            for(j = 0; j < 32; j++) {
                bool s = (gol.*(gol.getCellState))(i, j);
                cout << (s ? " # " : " - ");
            };
            cout << endl;
        };
        cout << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
