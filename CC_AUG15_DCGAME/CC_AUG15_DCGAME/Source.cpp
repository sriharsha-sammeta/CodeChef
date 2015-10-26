#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<stack>
#define sz(A) int(A.size())
#define tr(V,it) for(auto it = V.begin();it!=V.end();it++)

using namespace std;

typedef long long int lli;
typedef vector<int>vi;
typedef map<int, lli>mll;


void switchWinner(char &winner){
	winner = (winner == 'D') ? 'C' : 'D';
}

void findAllPerms(vi & A, mll & perms){
	for (int i = 0; i < sz(A); i++){
		perms[A[i]] = sz(A) - i;
	}
}
struct node{
	int index;
	int value;
};
void findPerms(vi & A, mll &perms){
	stack<node>Lstack;
	stack<node>Rstack;
	vi tempRVect(A.size());
	for (int i = sz(A) - 1; i >= 0; i--){
		while (!Rstack.empty() && Rstack.top().value <= A[i]){
			Rstack.pop();
		}
		if (!Rstack.empty()){
			tempRVect[i] = Rstack.top().index;
		}
		else{
			tempRVect[i] = A.size();
		}
		node n;
		n.value = A[i];
		n.index = i;
		Rstack.push(n);
	}
	int Li = 0, Ri = 0;
	for (int i = 0; i < sz(A); i++){
		Ri = tempRVect[i];
		while (!Lstack.empty() && Lstack.top().value < A[i]){
			Lstack.pop();
		}
		if (!Lstack.empty()){
			Li = Lstack.top().index;
		}
		else{
			Li = -1;
		}
		node n;
		n.value = A[i];
		n.index = i;
		Lstack.push(n);
		perms[A[i]] += (Ri - i)*(i - Li);
	}
}


int bs(vi &A, int val, int left, int right, char constraint){

	if (left <= right){
		int mid = (left + right) / 2;

		if (A[mid] == val){
			switch (constraint){
			case '<':
			case '=':
				if (mid - 1 >= 0)
					return A[mid - 1];
				break;
			case '>':
				return A[mid];
			}

		}
		else if (A[mid] < val){
			switch (constraint){
			case '<':
			case '>':
				if (mid + 1 <sz(A) && A[mid + 1] > val)
					return A[mid];
				break;
			}
			return bs(A, val, mid + 1, right, constraint);
		}
		else if (A[mid]> val){
			switch (constraint){
			case '<':
			case '>':
				if (mid - 1 >= 0 && A[mid - 1] <val)
					return A[mid - 1];
				break;
			}
			return bs(A, val, left, mid - 1, constraint);
		}
	}

	return -1;
}

char work(mll &S, vi &A, char &constraint, int &num, char &person){
	char winner = person;

	lli count = 0;

	if (constraint == '='){
		int index = bs(A, num, 0, sz(A) - 1, constraint);
		auto valIt = S.find(num);
		if (valIt != S.end()){
			count = valIt->second;
			if (valIt->first != index)
				count -= S[index];
		}

	}
	else if (constraint == '<'){
		int index = bs(A, num, 0, sz(A) - 1, constraint);
		if (index != -1)
			count = S[index];
	}
	else if (constraint == '>'){
		int index = bs(A, num, 0, sz(A) - 1, constraint);
		count = S[A[sz(A) - 1]];
		if (index != -1)
			count = count - S[index];
	}

	if (count % 2 == 0){
		switchWinner(winner);
	}
	return winner;
}


int main(){

	vector<int>demo;

	int N, M;
	cin >> N >> M;
	vi A(N);
	for (int i = 0; i < N; i++){
		cin >> A[i];
	}
	mll perms;
	findPerms(A, perms);

	A = vi();
	A.reserve(N);

	tr(perms, it){
		A.push_back(it->first);
	}	
	
	lli sum = 0;
	mll S;
	tr(perms, it){
		sum += it->second;
		S[it->first] = sum;
	}
	char constraint;
	int num;
	char person;
	while (M--){
		cin >> constraint >> num >> person;
		cout << work(S, A, constraint, num, person);
	}
	cout << endl;
	return 0;
}