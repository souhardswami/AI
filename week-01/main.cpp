#include<bits/stdc++.h>
#include<time.h>

using namespace std;

 

typedef struct State {
    char action;          
    char Matrix[3][3];     
};

State* genState(State *state, char move) {

    State *newState;
    int i, j, row, col; 

    for(i = 0;i<3; ++i) {
        for(j = 0;j < 3; ++j) {
            if(state->Matrix[i][j] == 0) {
                row = i;
                col = j;
            }
            newState->Matrix[i][j] = state->Matrix[i][j];
        }
    }

    if(move == 'U' && row - 1 >= 0) {
        char temp = newState->Matrix[row - 1][col];
        newState->Matrix[row - 1][col] = 0;
        newState->Matrix[row][col] = temp;
        newState->action = 'U';
        return newState;
    }
    else if(move == 'D'  && row + 1 < 3) {
        char temp = newState->Matrix[row + 1][col];
        newState->Matrix[row + 1][col] = 0;
        newState->Matrix[row][col] = temp;
        newState->action = 'D';
        return newState;
    }
    else if(move == 'L'  && col - 1 >= 0) {
        char temp = newState->Matrix[row][col - 1];
        newState->Matrix[row][col - 1] = 0;
        newState->Matrix[row][col] = temp;
        newState->action = 'L';
        return newState;
    }
    else if(move == 'R' && col + 1 < 3) {
        char temp = newState->Matrix[row][col + 1];
        newState->Matrix[row][col + 1] = 0;
        newState->Matrix[row][col] = temp;
        newState->action = 'R';
        return newState;
    }

    return NULL;
}
bool checkState(State const *testState, State const *goalState) {
    char row = 3, col;
    while(row--) {
        col = 3;
        while(col--) {
            if(testState->Matrix[row][col] != goalState->Matrix[row][col])
                return 0;
        }
    }
    return 1;
}
void inputState(State * const state) {
    state->action = NULL;
    int x;
    for(int row = 0; row < 3; ++row) {
        for(int col = 0; col < 3; ++col) {
            scanf("%d", x);
            state->Matrix[row][col] = x;
        }
    }
}

struct Node {
    unsigned int depth;              
    unsigned int heuristic; 
    State *state;       
    Node *parent;       
    vector<Node> *children; 
};


Node* genNode(unsigned int d, unsigned int h, State *s, Node *p) {
    Node *newNode;
    if(newNode) {
        newNode->depth = d;
        newNode->heuristic = h;
        newNode->state = s;
        newNode->parent = p;
        newNode->children = NULL;
        total_nodes ++ ; 
    }
    return newNode;
}

vector<Node>* g_child(Node *parent, State *goalState) {
    vector<Node> *c_point = NULL;
    State *testState = NULL;
    Node *child = NULL;

    if(parent->state->action != 'D' && (testState = genState(parent->state, 'U'))) {
        child = genNode(parent->depth + 1, 0, testState, parent);
        c_point->push_back(*child);
    }
    if(parent->state->action != 'U' && (testState = genState(parent->state, 'D'))) {
        child = genNode(parent->depth + 1, 0, testState, parent);
        c_point->push_back(*child);
        
    }
    if(parent->state->action != 'R' && (testState = genState(parent->state, 'L'))) {
        child = genNode(parent->depth + 1, 0, testState, parent);
        c_point->push_back(*child);
        
    }
    if(parent->state->action != 'L' && (testState = genState(parent->state, 'R'))) {
        child = genNode(parent->depth + 1, 0, testState, parent);
        c_point->push_back(*child);
    }

    return c_point;
}

int totalCost(Node * const node) {
    return node->depth + node->heuristic;
}
State BFS_search(State *source, State *goal) {
    Node *node = NULL;

    //start timer
    clock_t start = clock();

    
    node = genNode(0, 0, source, NULL);
    que.push(*node);
    

    //while there is a node in the queue to expand
    while(que.size() > 0) {
        //pop the last node 

        *node = que.front();
        que.pop();
        //if the state of the node is the goal state
        if(checkState(node->state, goal))
            break;
        auto children = g_child(node, goal);
        auto child = children->begin();
        while(child!= children->end()){
            que.push(*child);
        }
    }
    // final time
    runtime = (double)(clock() - start) / CLOCKS_PER_SEC;

    return *node->state;
}
void back_track(State* final_state){
    while(final_state->action != NULL){
        cout<<final_state->action<<"->";
        if(final_state->action=='R'){
            genState(final_state,'L');
        }
         if(final_state->action=='U'){
            genState(final_state,'D');
        }
         if(final_state->action=='L'){
            genState(final_state,'R');
        }
         if(final_state->action=='D'){
            genState(final_state,'U');
        } 
    }

}
// Global Variables
int total_nodes; 
int depth; 
double runtime;
queue<Node> que;


void solve(){
    State source;           
    State goalState;         

    inputState(&source);

    inputState(&goalState);

    // cout<<source.Matrix<<"\n";
    // cout<<goalState.Matrix<<"\n";

   
    total_nodes = 0;
    depth = 0;
    runtime = 0;

    State final_state = BFS_search(&source, &goalState);
    back_track(&final_state);

    // cout<<"Runtime --"<<runtime<<"\n";
    // cout<<"Total_nodes --"<<total_nodes<<"\n";
    // cout<<"size --"<<total_nodes*21<<"\n";
    // cout<<"depth --"<<depth<<"\n";

}

int main() {
    int t=1;
    cin>>t;  // number of test cased to solve;
    while (t--)
    {
        solve();
    }
    
}
