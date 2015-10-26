#include<iostream>
#include<vector>
#include "math.h"

#define sz(A) int(A.size())
#define sieveK 10000000
using namespace std;

typedef vector<int> vi;
vi arr(sieveK,1);

bool isPrime(int &num){
	return ((arr[num] >= 1 ) ? true : false);
}
void dfs(vector<vi>&input, int i, int j, bool isEven){

	if (i < 0 || j < 0 || i >= sz(input) || j >= sz(input))
		return;
	if (input[i][j] == -1)
		return;
	else if (isEven && input[i][j] % 2 == 0 && input[i][j] != 2){
			input[i][j] = -1;			
			dfs(input, i, j - 1,isEven);
			dfs(input, i + 1, j,isEven);
			dfs(input, i, j + 1,isEven);
			dfs(input, i - 1, j, isEven);
		
	}
	else if (!isEven && !isPrime(input[i][j]) && input[i][j]%2!=0){
		input[i][j] = -1;
		dfs(input, i, j - 1, isEven);
		dfs(input, i + 1, j, isEven);
		dfs(input, i, j + 1, isEven);
		dfs(input, i - 1, j, isEven);
	}
}

int countOfSieves(int &primeNum){
	return arr[primeNum];
}
void runSieve(){
	arr[0] = 0;
	arr[1] = 0;
	for (int i = 2; i <= sqrt(sz(arr)); i++){
		if (arr[i] == 1){
			for (int j = i * i; j < sz(arr); j += i){
				arr[j] = 0;
			}
		}
	}
	long long int count = 1;
	for (int i = 2; i < sz(arr); i++){
		if (arr[i] == 1){
			arr[i] = count;
			count++;
		}
	}
}
int main(){
	
	int T;
	scanf("%d", &T);
	runSieve();
	while (T--){

		int N;
		scanf("%d", &N);
		vector<vi>input(N,vi(N));
		
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				scanf("%d", &input[i][j]);
			}
		}
		
		long long int numberOfTries = 0;
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				switch (input[i][j]%2)
				{
				case -1:
					break;
				case 0:
					if (input[i][j] != 2){
						numberOfTries += (input[i][j] / 2);		
						dfs(input, i, j,true);									
						break;
					}
				default:			
					if (isPrime(input[i][j])){
						numberOfTries += (countOfSieves(input[i][j]) - 1);
					}
					else{						
						numberOfTries += ((input[i][j] + 3) / 2);
						dfs(input, i, j,false);												
					}
					break; 
				}
			}
		}
		cout << numberOfTries << endl;
	}
	return 0;
}