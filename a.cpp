#include <bits\stdc++.h>
#define llf long long


using namespace std;
llf max_val (llf x, llf y)
{
    if (x > y) return x;
    return y;
}

llf min_val (llf x, llf y)
{
    if (x < y) return x;
    return y;
}

llf gcd (llf a , llf b)
{
    if (a==0)
        return b;
    return gcd (b%a , a) ;
}
llf lcm_ (llf a , llf b)
{
    return (a*b) / gcd (a , b) ;
}

int main ()
{
    llf  t, n, a, b, x, y,i, c, d, m, temp, l, r, q;
    cin >> t ;
    while (t--)
    {
        cin >> a >> b >> q ;
        cout << a << b << q << endl;
        //cout << 994974874371859201 - 994974874422476798 << endl ;

        llf mn = min_val(a, b) ;
        llf mx= max_val(a, b) ;
        llf lcm = lcm_(b , a) ;
        llf ans[q] = {0} ;
        llf tt = q ;
        llf cn = 0;
        while (q--)
        {
            cin >> l >> r ;
            cout << lcm << "; " << r << endl ;

            llf lb = floor((float)l/lcm) ;
            llf ub = floor ((float)r/lcm);
            llf n_lcm = ub-lb + 1 ;
            cout << lb << " ; " << ub << ";" << n_lcm << endl;
            llf rd= (n_lcm==1) * (min_val(r, lb + mx -1) - l + 1) +
                     (n_lcm>1) * ((l<=lb+mx-1)*(lb+mx-1-l + 1)+ (n_lcm-2)*mx  + (min_val(r, ub + mx-1) - ub + 1) );
            ans[cn] = r - l + 1 - rd  ;
            cn++;
            cout << "rd->"<< rd << "//////ans->" << ans[cn-1] << "///////////" << endl ;


        }

        for (i = 0 ; i < tt-1 ; i++)
        {
            cout << ans[i] << " " ;
        }
        cout << ans[tt-1] << endl;
    }

}
