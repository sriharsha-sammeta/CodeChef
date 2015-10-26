#include<iostream>
#include<string>
#include<vector>

using namespace std;
typedef vector<string> vs;
vs fb(2);
vs lr(2);
vs tb(2);
bool check(){
	for (int i = 0; i <= 1; i++){
		for (int j = 0; j <= 1; j++){
			for (int k = 0; k <= 1; k++){
				if (fb[i] == lr[j] && lr[j] == tb[k]){
					return true;
				}

			}
		}
	}
	return false;
}

int main(){
	int T;
	cin >> T;
	int flag = 0;
	while (T != 0){
		flag = true;
		cin >> fb[0];
		cin >> fb[1];
		cin >> lr[0];
		cin >> lr[1];
		cin >> tb[0];
		cin >> tb[1];
		cout << (check() ? "YES" : "NO") << endl;
		T--;
	}
	return 0;
}