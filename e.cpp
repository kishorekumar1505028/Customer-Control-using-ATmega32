#include <bits\stdc++.h>
#define llf long long
#define mod 1000000007

using namespace std;



inline void normal(llf& a)
{
    a %= mod;
    (a < 0) && (a += mod);
}

inline llf mul(llf a, llf b)
{
    a %= mod, b %= mod;
    normal(a), normal(b);
    return (a * b) % mod;
}

inline llf add(llf a, llf b)
{
    a %= mod, b %= mod;
    normal(a), normal(b);
    return (a + b) % mod;
}

inline llf sub(llf a, llf b)
{
    a %= mod, b %= mod;
    normal(a), normal(b);
    a -= b;
    normal(a);
    return a;
}

inline llf cal_sum(llf n)
{
    return mul(mul(n, n + 1), (mod + 1) / 2);
}
inline llf cal_sum(llf lf, llf rg)
{
    return sub(cal_sum(rg), cal_sum(lf - 1));    // [lf, rg]
}



int main ()
{
    //freopen("output.txt", "wt", stdout);

    llf n, m, i= 0, sum = 0, lf = 0, rg = 0, t = 0, tt;
    cin >> n >> m ;
    llf om = m ;
    llf sq= sqrt(n) ;

    m = min (m, n) ;
    llf ub = min (sq, m) ;

    for (i = 1 ; i<=ub ; i++)
    {
        llf d = floor (n/i);
        sum = add(sum, mul(i, d));
        //cout << "sum-> " << sum << endl ;

        lf = floor (n/(i+1)) ;
        rg = min (m,d);
        //cout << "lf " << lf << "rg " << rg << endl ;

        if (lf < rg)
        {
            llf sub_rg_lf = sub(rg,lf);
            if ((i!=sq) || !((i==sq) && (d==i) && (sub_rg_lf==1)&&(rg==i)))
            {
                t = mul(i,cal_sum(lf + 1, rg));
                sum = add(sum, t);
                //cout << i << ";" <<  t << endl ;

            }

        }

    }
    //cout << "total-> " << sum << endl ;
    sum = sub (mul (om, n), sum) ;
    cout << sum;

    return 0;
}
