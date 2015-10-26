#include<iostream>
#include<vector>
#include<set>
#define tr(V,it) for(auto it=V.begin();it!=V.end();it++)

using namespace std;
typedef pair<int, int> pii;
int main(){
	int N;
	cin >> N;
	int x, y;
	int Q;
	int K;
	int num;
	vector<pii> input(N);

	for (int i = 0; i < N; i++){
		cin >> x >> y;
		input[i] = make_pair(x, y);
	}
	cin >> Q;
	set<pii> myset;
	while (Q--){
		cin >> K;
		int count = 0;
		while (K--){
			cin >> num;
	
			tr(input, it){
				if (it->first <= num && num <= it->second && myset.find(*it)==myset.end()){
					myset.insert(*it);
					count++;
				}
			}				
		}
		myset.clear();
		cout << count << endl;
	}

	return 0;
}