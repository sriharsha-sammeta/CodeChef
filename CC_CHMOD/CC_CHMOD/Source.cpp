#include<iostream>
#include<vector>

#define fr(i,begin,end) for(int i=begin;i<end;i++)
#define sz(input) int(input.size())
#define tr(V,it) for(auto it=V.begin();it!=V.end();it++)
#define szA(arr) sizeof(arr)/sizeof(arr[0]) 

using namespace std;

typedef vector<int> vi;
typedef long long int lli;

/*
void caliculatePrimes(int upper,vi&primes){	
	upper++;
	vector<bool> temp(upper,true);
	
	fr(i, 2, upper){
		if (temp[i]){
			for (int j = i*i; j < upper;j+=i){
				temp[j] = false;
			}
		}
	}

	fr(i, 2, upper){
		if (temp[i])
			primes.push_back(i);
	}
	
}*/

int frequency(int& num, int prime){
	int count = 0;	
	while (num%prime==0){		
		num /= prime;
		count++;
	}
	return count;
}

void buildCF(vi&input, int primes[],vector<vi>&CF){
	
	CF = vector<vi>(sz(input), vi(25, 0));
	vector<vi>dp(101, vi(25, -1));

	fr(i, 0, sz(input)){
		int num = input[i];
		fr(j, 0, 25){
			if (dp[input[i]][j] == -1){				
				dp[input[i]][j] = frequency(num, primes[j]);				
			}
			
			CF[i][j] = dp[input[i]][j];			
			//CF[i][j] = frequency(num, primes[j]);
			if (i != 0){
				CF[i][j] += CF[i - 1][j];
			}			
		}
	}

}

lli fastPow(lli base, int exp, int M){
	lli res = 1;
	base %= M;
	while (exp > 0){
		if (exp % 2 == 1){
			res = res*base;
			res %= M;
		}
		base = base*base;
		base %= M;
		exp /= 2;
	}
	return res% M;
}

lli query(int L, int R, int& M, int primes[],vector<vi>&CF){
	
	lli res = 1;

	int pow;
	fr(j, 0, 25){
		pow = CF[R][j];
		if (L > 0)
			pow -= CF[L - 1][j];
		res*=fastPow(primes[j], pow, M);
		res %= M;
	}
	return res;
}

int main(){
	int N;
	scanf("%d",&N);
	
	vi input(N);

	fr (i,0,N){
		scanf("%d",&input[i]);
	}
	int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
	//vi primes;
	//caliculatePrimes(100,primes);

	vector<vi>CF;
	buildCF(input, primes, CF);	

	int T;
	scanf("%d",&T);

	int L, R,M;
	while (T--){
		scanf("%d %d %d",&L,&R,&M);
		printf("%I64d\n",query(L - 1, R - 1, M, primes, CF));
	}
	
	return 0;
}