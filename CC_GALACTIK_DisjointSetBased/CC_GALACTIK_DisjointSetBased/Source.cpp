#include<iostream>
#include<vector>

#define sz(A) int(A.size())
#define tr(V,it) for(auto it=V.begin();it!=V.end();it++)
#define MAX_CI 10001
#define MAX_N 100001

using namespace std;

vector<int>Parent(MAX_N);
vector<int>Rank(MAX_N);
vector<int>value(MAX_N);

// disjoint sets data structure 


void init(const int &N){
	for (int i = 1; i <= N; i++){
		Parent[i] = i;
		Rank[i] = 0;
	}
}

//along with path compression
int find_set(int num){
	if (num != Parent[num]){
		Parent[num] = find_set(Parent[num]);		
	}
	return Parent[num];
}

//union by rank
void union_set(int n1, int n2){
	int p1 = find_set(n1);
	int p2 = find_set(n2);
	if (p1 == p2)
		return;
	if (Rank[p1] > Rank[p2])
		Parent[p2] = p1;
	else{
		Parent[p1] = p2;
		if (Rank[p1] == Rank[p2])
			Rank[p2]++;
	}	
}


int main(){
	
	int N, M;
	scanf("%d %d", &N, &M);
	init(N);

	int A, B;
	while (M--){
		scanf("%d %d", &A, &B);
		union_set(A, B);
	}

	for (int i = 1; i <= N; i++){
		scanf("%d", &value[i]);
		if (value[i] < 0)
			value[i] = MAX_CI;
	}

	for (int i = 1; i <= N; i++){

		if (value[i] < value[find_set(i)])
			value[find_set(i)] = value[i];
	}

	long long int sum = 0;
	int min = MAX_CI;
	int K = 0;
	bool badFlag = false;

	for (int i = 1; i <= N;i++){
		if (i == Parent[i]){
			if (value[i] < MAX_CI)
			{
				sum += value[i];
				if (value[i] < min)
					min = value[i];				
			}
			else{
				badFlag = true;
			}
			K++;
		}
	}

	if (K == 1)
		sum = 0;
	else{
		if (badFlag)
			sum = -1;
		else
			sum += ((K - 2)*min);
	}

	cout << sum << endl;
	return 0;
}