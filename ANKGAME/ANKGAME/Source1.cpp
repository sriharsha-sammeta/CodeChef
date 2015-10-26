#include<iostream>
#include<algorithm>
#include<map>
#include<vector>
#define all(it) it.begin(),it.end()
#define tr(container,it) for(auto it=container.begin();it!=container.end();it++)
#define sz(c) ulli(c.size())

typedef unsigned long long int ulli;

const ulli mod = 1000000007;

using namespace std;
map<ulli, ulli> factMap;
ulli fact(long long int x){
	
	if (x <= 1){
		return 1;
	}
	if (factMap.find(x)!=factMap.end()){
		return factMap[x];
	}
	ulli res = x * fact(x - 1);
	res = res %mod;
	factMap[x] = res;
	return res;
}

long long fast_pow(long long base, long long n, long long M)
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
long long  findMMI_fermat(long long n, long long  M)
{
	return fast_pow(n, M - 2, M);
}

ulli W(ulli x,ulli M, ulli N, ulli K){
	if (x <= M){
		ulli num = fact(N - x - 1);
		num = num * (N - M);
		num = num % mod;
		ulli denom = fact(M - x - 1);
		denom = denom*K;
		denom = denom%mod;
		if ((M - x) != 0){
			denom = denom * (M - x);
		}
		denom = denom % mod;
		ulli  MMI = findMMI_fermat(denom, mod);

		ulli res = (num * MMI);
		res = res % mod;
		return (res);	
	}
	return 0;
}

ulli caliculateK(map<ulli,ulli> & source){
	
	ulli pro = 1;	
	ulli temp = 1;
	tr(source, it){
		if (it->first != 1){
			temp= fact(it->second) ;	
			temp = temp%mod;
			pro *= temp;
			pro = pro%mod;
		}		
	}	
	return pro;
}


ulli perform(map<ulli,ulli> &source,ulli N){
	ulli K = caliculateK(source);
	ulli M = 0;
	if (source.find(1) != source.end()){
		M = source[1];
	}
	if (N == M){
		if (M % 2 == 0){
			return 0;
		}
		else{
			return 1;
		}
	}
	ulli sum = 0;
	ulli temp = 0;
	for (ulli r = 0; r <= M; r += 2){
		temp = W(r, M, N, K);			
		sum = sum + temp;
		sum = sum % mod;
	}
	return sum;
}

int main5(){
	ulli T;
	cin >> T;
	map<ulli, ulli>mp;
	while (T != 0){
		ulli n;
		ulli size;
		cin >> n;
		size = n;
		ulli temp;			
		while (n != 0){
			cin >> temp;
			mp[temp]++;
			n--;
		}
		cout << perform(mp,size) << endl;
		mp.clear();
		T--;
	}	
	return 0;
}
//1 1 1 1 1 2 