#include <iostream>
#include "ManualStrategy.h"


Point ManualStrategy::answer(const Othello& othello) {
    using namespace std;
    Point putPos;
    do {
        cout << endl << "入力してください！" << endl;
        cout << "X << ";
        cin >> putPos.x;
        cout << "Y << ";
        cin >> putPos.y;
    } while (!othello.canPutStone(putPos));

    return putPos;
}
