#include <bits/stdc++.h>

using namespace std;
void fmtstr ()
{
    char input [10];

    int var = 0x11223344 ;
    printf ("address %x\n", (unsigned) &var) ;
    printf ("data 0x%x\n",var );
    printf ("enter a string: ") ;
    fgets(input, sizeof (input)-1, stdin);
    printf (input);
    printf ("data at target address : 0x%x\n", var);
}
int main ()
{
    int a, b, r;
    fmtstr ();
}
