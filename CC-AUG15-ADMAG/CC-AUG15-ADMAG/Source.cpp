#include<iostream>
#include<vector>

#define sz(A) int(A.size())
using namespace std;
vector<long long int>dp;
long long int fib(long long int N){
	if (N >= 0){
		if (N + 1 <= sz(dp)){
			return dp[N];
		}
		else{
			dp.push_back(fib(N - 1) + fib(N - 2));
			return dp[N];
		}
	}
}



int main(){
	int T;
	cin >> T;
	long long int N;
	dp.push_back(1);
	dp.push_back(2);

	while (T-- != 0){
		cin >> N;
		for (long long int i = 1;; i++){
			if (fib(i) > N){
				cout << i << endl;
				break;
			}
		}
	}
	return 0;
}