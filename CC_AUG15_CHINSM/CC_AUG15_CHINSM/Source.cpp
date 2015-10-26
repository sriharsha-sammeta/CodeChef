#include<iostream>
#include<vector>

using namespace std;

int main(){
	int N, K;
	cin >> N >> K;
	vector<int>A(N);
	
	for (int i = 0; i < N; i++){
		cin >> A[i];
	}

	vector<int>mods(N,N);

	for (int i = N-1; i >= 0; i--){
		for (int j = i + 1; j < mods[i]; j++){
			if (A[i] % A[j] == K && j<mods[i]){
				mods[i] = j;
				break;
			}
			else if(mods[j]<mods[i]){
				mods[i] = mods[j];
			}			
		}
	}

	long long int count = 0;

	for (int i = 0; i < N; i++){
		count += (mods[i] - i);
	}

	cout << count << endl;
	
	return 0;
}