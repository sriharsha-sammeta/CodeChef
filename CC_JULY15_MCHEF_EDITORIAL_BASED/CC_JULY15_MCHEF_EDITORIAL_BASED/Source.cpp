#include<iostream>
#include<vector>
#include<fstream>
#include<set>

#define max(a,b) (a>=b)? a:b
#define sz(A) int(A.size())
using namespace std;

typedef vector<int> vi;
vector<long long int> A(100010);
vi cost(100010);
vector<vi> L(100010);
vector<vi> R(100010);
vector<vector<long long int> >dp(100010);
vector<vi> price(100010, vi(3));


void caliculateCost(const int &N,const int &M, const int &C){	

	set<pair<int, int> >myset;

	for (int i = 0; i < M; i++){
		L[price[i][0]-1].push_back(i);
		R[price[i][1]-1].push_back(i);
	}
	
	for (int i = 0; i < N; i++){
		for (int j = 0; j < sz(L[i]); j++){
			myset.insert(pair<int, int>(price[L[i][j]][2], L[i][j]));
		}
		if (myset.begin() != myset.end())
			cost[i] = myset.begin()->first;
		else
			cost[i] = C + 1;
		for (int j = 0; j < sz(R[i]); j++){
			myset.erase(pair<int, int>(price[R[i][j]][2], R[i][j]));
		}
	}
}



long long int solve(int n, int C){
	if (n< 0)
		return 0;
	if (dp[n][C] != -123456)
		return dp[n][C];
	if (C == 0 || cost[n]>C || A[n] >= 0)
		dp[n][C] = A[n] + solve(n - 1, C);
	else
		dp[n][C] = max(solve(n - 1, C - cost[n]), A[n] + solve(n - 1, C));
	return dp[n][C];
}
//10 -2 -5 7 -10
int main(){
	
	int T;
	int N, K, M;
	int newN=0;
	long long int result = 0;	
	
	ifstream cin2("C:\\Users\\srihars\\Desktop\\input5.txt");
	if (!cin2.is_open()){
		cout << "Unable to open file" << endl;
		return -1;
	}
	
	cin2 >> T;
	while (T-- != 0){
		cin2 >> N >> K >> M;		
		result = 0;

		for (int i = 0; i < N; i++){
			cin2 >> A[i];
			if (A[i] >= 0)
				result += A[i];
		}
		for (int i = 0; i < N; i++){					
			cost[i] = K + 1;
			L[i] = vi();
			R[i] = vi();		
		}
		
		for (int i = 0; i < M; i++){
			cin2 >> price[i][0] >> price[i][1] >> price[i][2];
		}
		caliculateCost(N,M, K);		
		newN = 0;
		for (int i = 0; i < N; i++){
			if (A[i] < 0){
				A[newN] = A[i];				
				cost[newN] = cost[i];
				dp[newN] = vector<long long int>(K + 1, -123456);
				newN++;
			}
		}
		long long int temp = 0;
		result+= solve(newN - 1, K);		
		cout << (T+1)<<" -> "<<result << endl;
	}
	return 0;
}

/*
int main2(){
	ifstream cin2("C:\\Users\\srihars\\Desktop\\input.txt");	
	if (!cin2.is_open()){
		cout << "Unable to open file" << endl;
		return -1;
	}
	int T;
	cin2 >> T;
	int N, K, M;	
	while (T-- != 0){
		cin2 >> N>>K>>M;
		A = vi(N);		
		for (int i = 0; i < N; i++){
			cin2 >> A[i];
		}
		vector<vi> price(M, vi(3));
		for (int i = 0; i < M; i++){
			cin2 >> price[i][0] >> price[i][1] >> price[i][2];
		}
		caliculateCost(price,K);
		dp = vector<vi>(A.size(), vi(K + 1, -1));
		int result = solve(A.size() - 1, K);
		int result2 = 0;
		cin3 >> result2;
		if (result == result2)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << " -- T--" << (T+1) << endl;
	}
	return 0;
}


/*vi segmentTree;
int min(int a, int b){
return (a <= b) ? a : b;
}
void insertMinCost(int L,int R, int ql,int qr,int i,int value){
if (L <= R){
int mid = (L + R) / 2;
if (L == ql && R == qr){
if (value < segmentTree[i])
segmentTree[i] = value;
}
else if (L<=ql && qr<=mid){
insertMinCost(L, mid, ql, qr, ((2*i) + 1), value);
}
else if (mid<ql && qr<=R){
insertMinCost(mid+1, R, ql, qr, ((2 * i) + 2), value);
}
else{
insertMinCost(L, mid, ql, mid, ((2 * i) + 1), value);
insertMinCost(mid + 1, R, mid+1, qr, ((2 * i) + 2), value);
}
}
}

int getMinCost(int L,int R, int q, int i){
if (L <= R){
int mid = (L + R) / 2;
if (L == q && R == q)
return segmentTree[i];
else if (L <= q && q <= mid)
return min(segmentTree[i],getMinCost(L, mid, q, ((2 * i) + 1)));
else if (mid < q && q <= R)
return min(segmentTree[i],getMinCost(mid+1, R, q, ((2 * i) + 2)));
}
}


void caliculateCost(const vector<vi> &price, const int &C){
cost=vi(A.size(),C+1);
segmentTree= vi((2 * pow(2, ceil(log2(A.size())))) - 1, C + 1); // 2*2^log(n) - 1
for (int i = 0; i < price.size(); i++){
insertMinCost(1, A.size(), price[i][0], price[i][1], 0, price[i][2]);
}
for (int i = 0; i < A.size(); i++){
cost[i] = getMinCost(1, A.size(), i + 1, 0);
}
}
*/