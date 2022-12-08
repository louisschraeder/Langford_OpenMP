//
// Created by louis on 12/7/22.
//
#include <iostream>
#include <bitset>
#include <utility>
#include <vector>

using namespace std;

#ifndef LANGFORD_LANGFORD_H
#define LANGFORD_LANGFORD_H


static int const n = 12;
static int const bitLength = 2 * n;
static vector<vector<bitset<bitLength>>> posStep;
int seqCount = 0;


class Langford {
    bitset<bitLength> bits;
    int stepCount;
    unsigned trueAmount;
    bool right;

public:
    Langford() {
        right = false;
        this->stepCount = n;
        this->trueAmount = 2;
        bits.reset();
        posStep.clear();
        bitset<bitLength> tmp;
        vector<bitset<bitLength>> tmpVec;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j+i+1 < bitLength; j++) {
                tmp.reset();
                tmp[j] = true;
                tmp[j+i+1] = true;

                tmpVec.push_back(tmp);
            }
            posStep.push_back(tmpVec);
            tmpVec.clear();
        }
    }

    Langford(bitset<bitLength> &bits, int stepCount, int trueAmount, bool right) {
        this->bits = bits;
        this->stepCount = stepCount;
        this->trueAmount = trueAmount;
        this->right = right;
    }

    void run() {
        if (this->stepCount == 0) {
            seqCount++;
            return;
        }

        auto step = posStep[this->stepCount - 1];

        for (auto &state : step) {
            state |= this->bits;

            if (state.count() == this->trueAmount) {
                Langford nextStep(state, this->stepCount - 1, this->trueAmount + 2, false);
                nextStep.run();
            }
        }
    }


};

#endif //LANGFORD_LANGFORD_H
