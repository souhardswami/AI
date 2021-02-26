#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fast ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define f(i,a,b) for(ll i=a; i<b; i++)
#define WIN 100
#define DRAW 0
#define LOSS -100
#define vt vector
#define mp make_pair
#define F first
#define S second
#define INITIAL_DEPTH 0
#define PLAYER_MARKER 'X'
#define AI_MARKER 'O'

//  Counter to calculate the no. of nodes evaluated so far
ll counter = 0;

//  Returns maximum of the two numbers
ll max(ll a,ll b)
{
    return a>b?a:b;
}

//  Returns minimum of the two numbers
ll min(ll a,ll b)
{
    return a>b?b:a;
}

//  Print game state
void print_game_state(ll x)
{
    if(x == WIN)
    {
        cout<<"WON THE GAME"<<endl;
    }
    if(x == LOSS)
    {
        cout<<"LOST THE GAME"<<endl;
    }
    if(x == DRAW)
    {
        cout<<"DRAWN THE GAME"<<endl;
    }
}

//  All winning possible configurations
vt<vt<pair<ll,ll>>> win_states
{
    //  Row wins
    {   mp(0,0),mp(0,1),mp(0,2)    },
    {   mp(1,0),mp(1,1),mp(1,2)    },
    {   mp(2,0),mp(2,1),mp(2,2)    },

    //  Column wins
    {   mp(0,0),mp(1,0),mp(2,0)    },
    {   mp(0,1),mp(1,1),mp(2,1)    },
    {   mp(0,2),mp(1,2),mp(2,2)    },

    //  Diagonal wins
    {   mp(0,0),mp(1,1),mp(2,2)    },
    {   mp(2,0),mp(1,1),mp(0,2)    }
};

//  Initializing Board with '-' (empty spaces)
void initialize(char board[3][3])
{
    f(i,0,3)
    {
        f(j,0,3)
            board[i][j] = '-';
    }
}

//  Print current state of board
void print(char board[3][3])
{
    cout<<"---------------"<<endl;
    f(i,0,3)
    {
        f(j,0,3)
            cout<<"| "<<board[i][j]<<" |";
        cout<<endl<<"---------------"<<endl;
    }
}

//  Find available valid moves
vt<pair<ll,ll>> get_valid_moves(char board[3][3])
{
    vt<pair<ll,ll>> v;
    f(i,0,3)
    {
        f(j,0,3)
        {
            //  If pos[i][j] is empty
            if(board[i][j] == '-')
            {
                v.push_back(mp(i,j));
            }
        }
    }
    return v;
}

//  Check if position is filled already
bool pos_filled(char board[3][3],pair<ll,ll> ps)
{
    vt<pair<ll,ll>> v = get_valid_moves(board);
    f(i,0,v.size())
    {
        //  If position is present in valid moves, return false
        if(ps.F == v[i].F && ps.S == v[i].S)
        {
            return false;
        }
    }
    return true;
}

//  Find all places filled by current marker (X or O)
vt<pair<ll,ll>> get_filled_places(char board[3][3],char marker)
{
    vt<pair<ll,ll>> v;
    f(i,0,3)
    {
        f(j,0,3)
        {
            if(board[i][j] == marker)
            {
                v.push_back(mp(i,j));
            }
        }
    }
    return v;
}

//  If no empty spaces are left, return true
bool game_over(char board[3][3])
{
    f(i,0,3)
    {
        f(j,0,3)
        {
            //  If empty space is found, return false
            if(board[i][j] == '-')
            {
                return false;
            }
        }
    }
    return true;
}

//  Check if the game is already won
bool game_status(vt<pair<ll,ll>> v)
{
    bool game_won;
    f(i,0,win_states.size())
    {
        game_won = true;
        vt<pair<ll,ll>> c = win_states[i];
        f(j,0,3)
        {
            if(!(find(begin(v),end(v),c[j]) != end(v)))
            {
                game_won = false;
                break;
            }
        }
        if(game_won)
        {
            break;
        }
    }
    return game_won;
}

ll get_board_state(char board[3][3],char marker)
{
    char opponent_marker;

    //  Finding opponent marker
    if(marker == AI_MARKER)
    {
        opponent_marker = PLAYER_MARKER;
    }
    else
    {
        opponent_marker = AI_MARKER;
    }

    //  Finding the filled places of marker
    vt<pair<ll,ll>> filled_places = get_filled_places(board,marker);

    //  Returns true if filled places satisfy one of the winning configurations
    bool is_won = game_status(filled_places);

    //  Player won
    if(is_won)
    {
        return WIN;
    }

    //  Finding the filled places of opponent marker
    filled_places = get_filled_places(board,opponent_marker);
    bool is_lost = game_status(filled_places);

    //  Player lost
    if(is_lost)
    {
        return LOSS;
    }

    //  If no empty spaces are left
    bool is_draw = game_over(board);
    if(is_draw)
    {
        return DRAW;
    }
    return DRAW;
}

//  Applying minimax game optimization algorithm
pair<ll,pair<ll,ll>> minimax_optimization(char board[3][3],char marker,ll depth,ll alpha,ll beta)
{
    counter++;
    //  Initialize best move
    pair<ll,ll> best_move = mp(-1,-1);

    //  If marker is AI, he tries to minimize the score
    ll best_score = (marker == AI_MARKER)?LOSS:WIN;

    //  If terminal state is reached, return best score and best move
    if(game_over(board) || DRAW != get_board_state(board,AI_MARKER))
	{
		best_score = get_board_state(board,AI_MARKER);
		return mp(best_score,best_move);
	}

	//  Collecting valid moves to mark the best out of it
    vt<pair<ll,ll>> valid_moves = get_valid_moves(board);
	f(i,0,valid_moves.size())
	{
	    pair<ll,ll> c = valid_moves[i];
		board[c.F][c.S] = marker;

		//  Maximizing player's turn
		if(marker == AI_MARKER)
		{
			ll score = minimax_optimization(board,PLAYER_MARKER,depth + 1,alpha,beta).F;

			// Get the best scoring move
			if(best_score < score)
			{
				best_score = score - depth*10;
				best_move = c;

				/* If this branch's best move is worse than the best
				   option of a previously search branch, skip it  */
				alpha = max(alpha,best_score);
				board[c.F][c.S] = '-';
				if(beta <= alpha)
				{
					break;
				}
			}
		}

		//  Minimizing opponent's turn
		else
		{
			ll score = minimax_optimization(board,AI_MARKER,depth + 1,alpha,beta).F;

			//  Get the worst scoring move
			if (best_score > score)
			{
				best_score = score + depth * 10;
				best_move = c;

				/* If this branch's best move is worse than the best
				   option of a previously search branch, skip it  */
				beta = min(beta,best_score);
				board[c.F][c.S] = '-';
				if(beta <= alpha)
				{
					break;
				}
			}
		}
		board[c.F][c.S] = '-';                      //  Undo move
	}
	return mp(best_score,best_move);
}

bool isPlayable(char board[3][3])
{
    //  Returns true if board has no empty spaces
    if(game_over(board))
    {
        return false;
    }

    //  Returns true if game is already drawn
    if(DRAW != get_board_state(board,AI_MARKER))
    {
        return false;
    }
    return true;
}

int main()
{
    fast;
    cout<<endl<<"********************************************************"<<endl;
    cout<<endl<<"Tic-tac-toe Game AI..."<<endl;
    cout<<endl<<"********************************************************"<<endl;
    char board[3][3];

    //  Initializing board with blank spaces '-'
    initialize(board);
    print(board);

    cout<<endl<<"You are 'X', make the first move"<<endl<<endl;

    //  Game is incomplete
    while(isPlayable(board))
    {
        ll row,col;

        //  (1,1) is top-left space, (3,3) is bottom-right space
        cout<<"Choose row index (1 to 3)"<<endl;
        cin>>row;
        cout<<"Choose column index (1 to 3)"<<endl;
        cin>>col;
        cout<<endl<<endl;

        //  If selected space is not empty
        if(pos_filled(board,mp(row - 1,col - 1)))
        {
            cout<<"The position is filled :(, please choose again..."<<endl;
            continue;
        }
        else
        {
            board[row - 1][col - 1] = PLAYER_MARKER;
        }

        //  Calculating best move for AI
        pair<ll,pair<ll,ll>> ai_move = minimax_optimization(board,AI_MARKER,INITIAL_DEPTH,LOSS,WIN);
        cout<<"No. of nodes evaluated so far : "<<counter<<endl;
        board[ai_move.S.F][ai_move.S.S] = AI_MARKER;
        print(board);
    }

    //  Finding if player has won or not
    ll x = get_board_state(board,PLAYER_MARKER);
    cout<<"YOU ";
    print_game_state(x);

    cout<<endl<<"********************************************************"<<endl;
    cout<<endl<<"Game Over..."<<endl;
    cout<<endl<<"********************************************************"<<endl;
    return 0;
}
