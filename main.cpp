#include <iostream>

#include "Langford.h"
#include "Langford_par.h"

using namespace std;

int main() {

    auto sbegings = chrono::system_clock::now();
    Langford seq;
    seq.run();

    cout << seqCount / 2 << endl;

    auto stimes = std::chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now() - sbegings).count();
    cout << "\nLangford Sequential: " << stimes << " ms" << endl;

    auto pbegings = chrono::system_clock::now();

    Langford_par par;
    par.run();

    cout << parCount / 2 << endl;

    auto ptimes = std::chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now() - pbegings).count();
    cout << "\nLangford Parallel: " << ptimes << " ms" << endl;

}
