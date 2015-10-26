#include<iostream>
#include<algorithm>
using namespace std;
typedef long long int uli;

const uli mod = 1e9 + 7;
const int mx = 1e5 + 10;
uli fa[mx], fi[mx], d[mx];
int n, n1;
uli ivs;
uli fxp(uli b, uli x, uli m){
	uli a = 1;
	for (; x != 0; b = b*b%m, x >>= 1)
		if (x & 1ll)a = a*b%m;
	return a;
}
inline uli solve(int u){
	uli cmb = fa[n - u] * fi[n1 - u] % mod*ivs%mod;
	if (u == n1){
		if (n == u)return 0;
		return cmb;
	}
	return (cmb - solve(u + 1) + mod) % mod;
}
int main2(){
	fa[0] = fi[0] = 1;
	for (int i = 1; i<mx; i++){
		fa[i] = fa[i - 1] * uli(i) % mod;
		fi[i] = fxp(fa[i], mod - 2, mod);
	}
	int t;
	scanf("%d", &t);
	while (t--){
		scanf("%d", &n);
		n1 = 0;
		for (int i = 0; i<n; i++){
			scanf("%lld", d + i);
			if (d[i] == 1)n1++;
		}
		sort(d, d + n);
		ivs = 1;
		for (int i = 0; i<n;){
			uli v = d[i];
			int qv = 0;
			while (i<n && d[i] == v) i++, qv++;
			if (v != 1)ivs = ivs*fi[qv] % mod;
		}
		uli ans = solve(0);
		printf("%lld\n", ans);
	}
	return 0;
}

// 1 1 1 1 1 2 2 2 2 2 3 3 3 3 3 