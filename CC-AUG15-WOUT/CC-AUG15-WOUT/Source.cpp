#include<iostream>
#include<vector>

using namespace std;


typedef vector<long long int> vlli;



long long int minimumEnergy(int &N, int&H, vlli &C){
	vlli R(N, 0);
	long long int current = N;
	for (int i = 0; i < N; i++){
		R[i] = current + C[i];
		current = R[i];
	}
	
	vlli S(N, 0);
	current = 0;
	for (int i = 0; i < N; i++){		
		S[i] = current + R[i];
		current = S[i];
	}

	long long int minEnergy = -1;
	current = 0;
	for (int j=H-1; j<N; j++){
		current = S[j] - current;
		if (current < minEnergy || minEnergy==-1)
			minEnergy = current;
		current=S[j-H+1];
	}
	return minEnergy;
}
int main(){
	int T;
	int N;
	int H;	

	cin >> T;
	while (T--){
		cin >> N >> H;
		vlli C(N, 0);
		int li, hi;
		for (int i = 0; i < N;i++){
			cin >> li >> hi;
			C[li] -= 1;
			if (hi + 1 < N)
				C[hi + 1] += 1;			
			
		}
		cout << minimumEnergy(N, H, C) << endl;				
	}
	return 0;
}