#include<bits/stdc++.h>
using namespace std;
long long a,b,q,l,r,t;
int main(){
	cin>>t;
	while(t--){
		cin>>a>>b>>q;
		long long mcm=a*b/__gcd(a,b),blo=mcm-max(a,b),rr,ll;
		while(q--){cin>>l>>r;rr=r%mcm;ll=l%mcm;
		rr=rr>=max(a,b)?rr-max(a,b)+1:0;
		ll=ll>=max(a,b)?ll-max(a,b):0;
		cout<<r/mcm*blo-l/mcm*blo+blo/mcm+rr-ll<<" ";}cout<<endl;
	}
}
