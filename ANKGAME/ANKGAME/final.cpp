#include<iostream>
#include<map>
#define tr(container,it) for(auto it = container.begin();it!=container.end();it++)
typedef long long ll;

const ll mod = 1000000007;

using namespace std;
map<ll, ll>factTable;
ll fact(ll x){
	if (x <= 1){
		return 1;
	}
	else if (factTable.find(x) != factTable.end()){
		return factTable[x];
	}
	else{
		ll res = x * fact(x - 1);
		res = res % mod;
		factTable[x] = res;
		return res;
	}
}

ll getK(map<ll,ll> &source){
	ll K = 1;
	tr(source, it){
		if (it->first != 1){
			K = K * fact(it->second);
			K = K % mod;
		}
	}
	return K;
}

ll fast_pow(ll base, ll n, ll M)
{
	if (n == 0)
		return 1;
	if (n == 1)
		return base;
	long long halfn = fast_pow(base, n / 2, M);
	if (n % 2 == 0)
		return (halfn * halfn) % M;
	else
		return (((halfn * halfn) % M) * base) % M;
}
ll  findMMI_fermat(ll n, ll  M)
{
	return fast_pow(n, M - 2, M);
}


ll W(ll x, ll N, ll M, ll K){
	ll num = 0;
	ll denom = 1;
	ll res = 0;
	num = num * fact(N - x - 1);
	num = num % mod;
	num = num * (N - M);
	num = num % mod;

	denom = K;
	denom = denom * fact(M - x - 1);
	denom = denom % mod;
	if ((M - x) != 0){
		denom = denom * (M - x);
		denom = denom % mod;
	}
	ll MMI = findMMI_fermat(denom, mod);
	res = (num * denom);
	res = res % mod;
	return res;
}

ll TimesAnkitWillWin(map<ll, ll>&source, int N){
	ll M = source[1];
	ll K = getK(source);
	ll sum = 0;
	for (ll x = 0; x <= M; x+=2){
		sum = sum + W(x, N, M, K);
		sum = sum % mod;
	}
	return sum;
}

int main(){
	int T = 0;
	cin >> T;
	map<ll, ll>source;
	ll N = 0;
	ll size = 0;
	ll temp = 0;
	while (T != 0){
		cin >> N;
		size = N;
		while (N != 0){
			cin >> temp;
			source[temp]++;
			N--;
		}



		source.clear();
		T--;
	}
	
	return 0;
}