#include <iostream>
#include <chrono>
#include <thread>

// Include necessary headers
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
      cout << "\033[2J\033[H"; // Clear screen

        gol.next();
        uint8_t i, j;
        for (i = 0; i < gol.rows; i++) {
            for (j = 0; j < gol.cols; j++) {
                bool s = gol.getCellState(i, j);
                cout << (s ? " # " : " - ");
            }
            cout << endl;
        }
        cout << endl;

	// Slow output
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}
