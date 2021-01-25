#include <bits\stdc++.h>
#define llf long long
# define sz 9

using namespace std;

void printa (llf n )
{
    for (llf i = 0 ; i < n ; i++)
        cout <<'a';

}

llf max_val (llf m, llf n)
{
    if (m < n) return n;
    return m;
}

llf min_val (llf m, llf n)
{
    if (m < n) return m;
    return n;
}

int main ()
{
    llf  t, n, a, b, x, i, j;
    cin >> t ;
    while (t--)
    {

        llf ara [sz][sz]  = {0};

        for (i = 0 ; i < sz; i++)
        {
            for (j = 0 ; j < sz ; j++)

                cin >> ara [i] [j] ;


        }

        ara [0] [4] = (ara [0] [4] + 1) % 9;
        ara [1] [1] = (ara [1] [1] + 1) % 9;
        ara [2] [7] = (ara [2] [7] + 1) % 9;
        ara [3] [0] = (ara [3] [0] + 1) % 9;
        ara [4] [3] = (ara [4] [3] + 1) % 9;
        ara [5] [6] = (ara [5] [6] + 1) % 9;
        ara [6] [2] = (ara [6] [2] + 1) % 9;
        ara [7] [5] = (ara [7] [5] + 1) % 9;
        ara [8] [8] = (ara [8] [8] + 1) % 9;
        for (i = 0 ; i < sz; i++)
        {
            for (j = 0 ; j < sz ; j++)

                cout <<  ara [i] [j] ;
            cout << endl ;

        }

        cout << endl ;


    }
}


// 1 2 3 4 5 6 7 8 9
