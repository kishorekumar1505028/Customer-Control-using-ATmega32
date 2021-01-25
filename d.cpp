#include <bits\stdc++.h>
#define llf long long
# define sz 4

using namespace std;

int main ()
{
    int a , c  , i , j;

    int A[sz] = {1 , 2 , 5 , 10};
    int C[sz] = {1 , 2 , 3, 6};
    for (i = 0 ; i < sz ; i++)
    {
        for (j = 0; j < sz ; j++)
        {
            a = A[i] ;
            c = C[j] ;
            float r = float((20*a - c - 48 + 6*a/c))/float(9) ;
            cout << r << endl ;
            if (int(r)==r){
                cout << "wooho"<< a << " " << c << endl ;
                //return 0;
            }

        }
    }
    return 0;
}
