#include <iostream>
#include <chrono>
#include <thread>
#include <random>

#include "conway.h"

using namespace std;

int main() {
    uint32_t state[35];
    Conway<uint32_t> gol(state, 35);

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed);
    uniform_int_distribution<uint32_t> distribution(0, UINT32_MAX);

    // Initialize the game state with random values
    for (uint8_t i = 0; i < gol.rows; i++) {
        state[i] = distribution(generator);
    }

    for (uint8_t i = gol.rows; i < gol.rows + 3; i++) {
        state[i] = 0;
    }

    while (true) {
        cout << "\033[2J\033[H";

        gol.next();
        uint8_t i, j;
        for (i = 0; i < gol.rows; i++) {
            for (j = 0; j < gol.cols; j++) {
                bool s = gol.getCellState(i, j);
                cout << (s ? "<>" : "  ");
            }
            cout << endl;
        }
        cout << endl;

        // Sleep to slow animation 200 gives 5fps
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}
