#include <iostream>
#include "ManualStrategy.h"


Point ManualStrategy::answer(const Othello& othello) {
    using namespace std;
    Point putPos;

    do {
        cout << "Please enter the answer." << endl;
        cout << "X << ";
        cin >> putPos.x;
        cout << "Y << ";
        cin >> putPos.y;
    } while (!othello.canPutStone(putPos));

    return putPos;
}
