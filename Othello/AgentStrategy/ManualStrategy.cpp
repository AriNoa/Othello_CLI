#include <iostream>
#include "ManualStrategy.h"


otl::Point ManualStrategy::answer(const otl::Othello& othello) {
    using namespace std;
    using namespace otl;

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
