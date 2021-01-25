#include <bits\stdc++.h>
#define llf long long


using namespace std;

void printa (llf n )
{
    for (llf i = 0 ; i < n ; i++)
        cout <<'a';

}

llf max_val (llf n)
{
    if (n < 0) return 0;
    return n;
}

int ara [26] = {0};

void init_ara ()
{
    int i ;
    for (i = 0 ; i < 26; i++)
        ara [i] = 0 ;
}

llf min_val (llf m, llf n)
{
    if (m < n) return m;
    return n;
}
llf max_val (llf m, llf n)
{
    if (m > n) return m;
    return n;
}

int main ()
{
    llf  t, n, a, b, x, i, c, d, m, temp;
    cin >> t ;
    while (t--)
    {
        cin >> n ;
        llf ara [n]= {0} ;
        for (i = 0 ; i  < n ; i++)
            cin >> ara[i] ;
        llf mx = ara [0], sum = 0, flag = 1;
        for (i = 0 ; i  < n-1 ; i++)
        {
            if ((ara[i]<0) == (ara[i+1]<0))
            {
                mx = max_val(mx, ara[i+1]);
                flag = 1;
            }
            else
            {

                // cout << mx << " " ;
                sum += mx ;
                if (i==n-2)
                {
                    sum+=ara[n-1] ;
                }
                mx = ara [i+1] ;
                flag = 0;
            }
        }

        if (flag) sum += mx ;
        cout << sum <<  endl ;
    }
}
