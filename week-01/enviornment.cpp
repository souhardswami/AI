#include<bits/stdc++.h>
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


