#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fast ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define f(i,a,b) for(ll i=a; i<b; i++)

//  If there are stones in any pile, return true
bool isPlayable(ll piles[],ll n)
{
    f(i,0,n)
    {
        if(piles[i] != 0)
            return true;
    }
    return false;
}

void play(ll piles[],ll n,ll turn)
{
    if(isPlayable(piles,n))
    {
        if(turn == 1)
        {
            cout<<endl<<"Your turn..."<<endl;
            cout<<endl<<"Pick the index from 1 to N and remove some valid no. of stones"<<endl;
            cout<<endl;
            f(i,0,n)
            {
                cout<<"Index    No. of stones"<<endl;
                cout<<i+1<<"        "<<piles[i]<<endl;
            }
            ll index,rem;
            abc:
            cin>>index>>rem;
            if(index > 0 && index <= n)
            {
                if(piles[index - 1] >= rem)
                {
                    cout<<endl<<"You removed "<<rem<<" stones from pile "<<index<<endl;
                    piles[index - 1] -= rem;
                }
                else                            //  no. exceeds the limit of selected pile
                {
                    cout<<endl<<"Invalid number, choose again..."<<endl;
                    goto abc;
                }
            }
            else                                //  no. out of index
            {
                cout<<endl<<"Invalid number, choose again..."<<endl;
                goto abc;
            }
            turn = 2;                           //  Now bot's turn
            play(piles,n,turn);
        }
        else
        {
            cout<<endl<<"Bot is thinking..."<<endl;
            ll nim_sum = 0;
            f(i,0,n)
            {
                nim_sum ^= piles[i];
            }
            //  If nim_sum is 0, bot is losing and can't do anything
            if(nim_sum == 0)
            {
                f(i,0,n)
                {
                    if(piles[i] > 0)
                    {
                        //  Removing 1 stone from the first non zero pile
                        cout<<endl<<"Bot removed 1 stone from pile "<<i+1<<endl;
                        piles[i]--;
                        break;
                    }
                }
            }
            else
            {
                //  Nim_sum is non zero, bot has to select such that the resulting sequence has nim_sum as 0
                f(i,0,n)
                {
                    ll p = piles[i]^nim_sum;
                    if(p < piles[i])
                    {
                        cout<<endl<<"Bot removed "<<piles[i] - p<<" stones from pile "<<i+1<<endl;
                        piles[i] = p;
                        break;
                    }
                }
            }
            turn = 1;                           //  Now player's turn
            play(piles,n,turn);
        }
    }
    else
    {
        if(turn == 1)                           //  Player's turn, no possible moves left
        {
            cout<<endl<<"I told you I will win, it's easy to defeat a human..."<<endl;
        }
        else                                    //  Bot's turn, no possible moves left
        {
            cout<<endl<<"You win, well played..."<<endl;
        }
        cout<<endl<<"********************************************************"<<endl;
        cout<<endl<<"Game Over..."<<endl;
        cout<<endl<<"********************************************************"<<endl;
    }
}

int main()
{
    fast;
    cout<<endl<<"********************************************************"<<endl;
    cout<<endl<<"Nim Game AI..."<<endl;
    cout<<endl<<"********************************************************"<<endl;
    ll n,choice,nim_sum = 0;
    cout<<endl<<"Enter the no. of piles..."<<endl;
    cin>>n;
    cout<<endl<<"Enter the values of "<<n<<" piles..."<<endl;
    ll piles[n];
    f(i,0,n)
    {
        cin>>piles[i];
    }

    cout<<endl<<"Who will make the first move ??"<<endl;
    cout<<"1. You"<<endl<<"2. Bot"<<endl;
    cin>>choice;

    f(i,0,n)
    {
        nim_sum ^= piles[i];
    }
    cout<<endl;
    if(choice == 1)                 //  Player is making the first move
    {
        if(nim_sum)                 //  nim_sum is non zero
        {
            cout<<"Odds are in favor of you, let's play..."<<endl;
        }
        else
        {
            cout<<"I know I will win, let's play..."<<endl;
        }
    }
    else                            //  Bot is making the first move
    {
        if(nim_sum)                 //  nim_sum is non zero
        {
            cout<<"I know I will win, let's play..."<<endl;
        }
        else
        {
            cout<<"Odds are in favor of you, let's play..."<<endl;
        }
    }
    play(piles,n,choice);
    return 0;
}
