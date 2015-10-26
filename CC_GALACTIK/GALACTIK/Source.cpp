#include<iostream>
#include<vector>
#include<set>


#define sz(A) int(A.size())
#define tr(V,it) for(auto it=V.begin();it!=V.end();it++)
#define ALREADY_ENCOUNTERED -10001
#define MAX_CI 10000

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int>pii;


void dfs(vvi &input,int indexNum,set<pii>&result,vi &values){
		
	if (values[indexNum] != ALREADY_ENCOUNTERED){
		
		result.insert(make_pair(values[indexNum], indexNum));
		values[indexNum] = ALREADY_ENCOUNTERED;
		for (int i = 0; i < sz(input[indexNum]); i++){
			dfs(input, input[indexNum][i], result, values);
		}
	}		
}

void preProcess(vvi &input, vector<set<pii> > &disjointSets, vi &values){	

	for (int i = 1; i < sz(input); i++){
		set<pii>tempSet;
		dfs(input, i, tempSet, values);
		if (sz(tempSet)>0)
			disjointSets.push_back(tempSet);
	}

}

long long int caliculateTotalCost(vector<set<pii> > &disjointSets,int N){
	int min = MAX_CI + 1;
	long long int totalCost = 0;
	if (sz(disjointSets) == 1 && sz(disjointSets[0]) == N)
		return 0;

	for (int i = 0; i < sz(disjointSets); i++){	
		auto it = disjointSets[i].upper_bound(make_pair(-1, MAX_CI));
		if (it == disjointSets[i].end()){
			return -1;
		}
		else{
			if (it->first < min)
				min = it->first;

			totalCost += it->first;
		}
	}
	totalCost += ((sz(disjointSets) - 2)*min);
	return totalCost;
}

int main(){	
	
	int N, M;	
	scanf("%d %d", &N, &M);

	vvi input(N+1,vi());
	vector<set<pii> > disjointSets;
	
	vi values(N + 1);
	
	int A, B;
	while (M--){
		scanf("%d %d", &A, &B);		
		input[A].push_back(B);
		input[B].push_back(A);
	}

	for(int i=1;i<=N;i++){
		scanf("%d", &values[i]);
	}

	preProcess(input, disjointSets, values);
	cout<<caliculateTotalCost(disjointSets,N)<<endl;

	return 0;
}