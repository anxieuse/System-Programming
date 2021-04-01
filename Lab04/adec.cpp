
//               adec.cpp
#include "fsm.h"
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
    tFSM Adec;

    ///////////////////////
    addstr(Adec, 0, "+-", 1);
    addrange(Adec, 1, '0', '9', 2);
    addrange(Adec, 2, '0', '9', 2);
      addstr(Adec, 2, ".", 6);
      addrange(Adec, 6, '0', '9', 7);
      addrange(Adec, 7, '0', '9', 7);
      addstr(Adec, 7, "eE", 3);
    addstr(Adec, 2, "eE", 3);
    addstr(Adec, 3, "+-", 4);
    addrange(Adec, 4, '0', '9', 5);
    addrange(Adec, 5, '0', '9', 5);
    Adec.final(5);
    ///////////////////////

    cout << "Number of states = " << Adec.size() << "\n";

    while (true) {
        char input[81];
        cout << ">";
        cin.getline(input, 81);
        if (!*input)
            break;
        int res = Adec.apply(input);
        cout << setw(res ? res + 1 : 0) << "^"
             << endl;
    }
    return 0;
}
