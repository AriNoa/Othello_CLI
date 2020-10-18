#include <iostream>
#include "Othello/Controller/OthelloController.h"
#include "Othello/AgentStrategy/ManualStrategy.h"
#include "Othello/AgentStrategy/RandomBot.h"
#include "Othello/AgentStrategy/ScoreBot.h"


int main() {
    using namespace std;
    using namespace otl;


    cout << endl;
    cout << "Othello_CLI";
    cout << endl;

    shared_ptr<IAgentStrategy> scoreAgent(new ScoreBot());
    shared_ptr<IAgentStrategy> randomAgent(new RandomBot());
    map<Team, shared_ptr<IAgentStrategy>> agents = {
        { Team::First,  scoreAgent },
        { Team::Second, randomAgent }
    };

    OthelloController controller(agents);

    controller.run();
    
    return 0;
}
