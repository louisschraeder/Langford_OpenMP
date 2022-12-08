//
// Created by louis on 12/7/22.
//
#include <iostream>
#include <bitset>
#include <utility>
#include <vector>
#include <oneapi/tbb.h>

using namespace std;

#ifndef LANGFORD_PAR_LANGFORD_H
#define LANGFORD_PAR_LANGFORD_H


static int const n_par = 12;
static int const bitLength_par = 2 * n_par;
static vector<vector<bitset<bitLength_par>>> posStep_par;
int parCount = 0;

class Langford_par {
    bitset<bitLength_par> bits;
    int stepCount;
    int trueAmount;
    bool right;

public:
    Langford_par() {
        right = false;
        this->stepCount = n_par;
        this->trueAmount = 2;
        bits.reset();
        posStep_par.clear();
        bitset<bitLength_par> tmp;
        vector<bitset<bitLength_par>> tmpVec;
        for (int i = 1; i <= n_par; i++) {
            for (int j = 0; j+i+1 < bitLength_par; j++) {
                tmp.reset();
                tmp[j] = true;
                tmp[j+i+1] = true;

                tmpVec.push_back(tmp);
            }
            posStep_par.push_back(tmpVec);
            tmpVec.clear();
        }
    }

    Langford_par(bitset<bitLength_par> &bits, int stepCount, int trueAmount, bool right) {
        this->bits = bits;
        this->stepCount = stepCount;
        this->trueAmount = trueAmount;
        this->right = right;
    }

    void run() {
        if (this->stepCount == 0) {
#pragma omp atomic
            parCount++;
            return;
        }

        auto step = posStep_par[this->stepCount - 1];

#pragma omp parallel for
        for (auto &state : step) {
            state |= this->bits;

            if (state.count() == this->trueAmount) {
                Langford_par nextStep_par(state, this->stepCount - 1, this->trueAmount + 2, false);
                nextStep_par.run();
            }
        }
    }


};

#endif //LANGFORD_PAR_LANGFORD_H
