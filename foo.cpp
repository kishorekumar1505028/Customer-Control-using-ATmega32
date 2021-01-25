# include <bits/stdc++.h>

using namespace std;

int main ()
{
    int i, sum = 0;

    for (i = 2 ; i<=20 ; i+=2)
        sum = sum + i;

    printf("answer is %d", sum);
    return 0;
}
