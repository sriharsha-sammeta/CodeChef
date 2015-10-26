#include<iostream>
#include<vector>
#include<map>
#include<stack>
#define sz(A) int(A.size())
#define tr(V,it) for(auto it = V.begin();it!=V.end();it++)

using namespace std;

typedef long long int lli;
typedef vector<int>vi;
typedef map<int, lli>mll;


char switchWinner(char &winner){
	return (winner == 'D') ? 'C' : 'D';
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

struct TreeNode{
	int left;
	int right;
	lli sum;
};
vector<pair<int, lli> > myperms;
vector<TreeNode*> mytree;
lli buildTree(int i,int left, int right){

	if (left < right){
		int mid = (left + right) / 2;
		lli leftSum = buildTree((2*i)+1,left, mid);
		lli rightSum = buildTree((2*i)+2,mid + 1, right);
		lli total = 0;

		if (leftSum != -1)
			total += leftSum;
		if (rightSum != -1)
			total += rightSum;

		TreeNode* tn = new TreeNode();
		tn->sum = total;
		tn->left = myperms[left].first;
		tn->right = myperms[right].first;
		mytree[i] = tn;

		return total;
	}
	else if (left == right){
		TreeNode* tn=new TreeNode();		
		tn->sum = myperms[left].second;
		tn->left = myperms[left].first;
		tn->right = myperms[left].first;
		mytree[i] = tn;
		return mytree[i]->sum;
	}
	return -1;

}


lli queryTree(int i,char &constraint,int &qvalue){
	lli total = 0;
	if (i >= 0 && i < mytree.size()){			
		switch (constraint)
		{
		case '>':
			if (qvalue < mytree[i]->left){
				return mytree[i]->sum;
			}
			else if (qvalue < mytree[i]->right){
				total = queryTree((2 * i) + 1, constraint, qvalue);
				total += queryTree((2 * i) + 2, constraint, qvalue);
				return total;
			}
			else{
				return 0;
			}
		case '<':
			if (qvalue > mytree[i]->right){
				return mytree[i]->sum;
			}
			else if (qvalue > mytree[i]->left){
				total = queryTree((2 * i) + 1, constraint, qvalue);
				total += queryTree((2 * i) + 2, constraint, qvalue);
				return total;
			}
			else{
				return 0;
			}
		case '=':
			if (mytree[i]->left == mytree[i]->right && mytree[i]->left == qvalue){
				return mytree[i]->sum;
			}
			else if ( mytree[i]->left<=qvalue && qvalue <= mytree[i]->right){
				total = queryTree((2 * i) + 1, constraint, qvalue);
				total += queryTree((2 * i) + 2, constraint, qvalue);
				return total;
			}
			else{
				return 0;
			}
		}
	}
	return 0;
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

	tr(perms, it){
		myperms.push_back(pair<int, lli>(it->first, it->second));			
	}

	mytree = vector<TreeNode*>(perms.size()<<2);

	buildTree(0,0,sz(myperms)-1);

	char constraint;
	int num;
	char person;
	while (M--){
		cin >> constraint >> num >> person;
		lli result = queryTree(0, constraint, num);		
		cout << ((result % 2 == 0) ? switchWinner(person): person);
	}
	cout << endl;
	return 0;
}