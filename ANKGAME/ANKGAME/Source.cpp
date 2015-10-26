#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#define all(it) it.begin(),it.end()
#define tr(container,it) for(auto it=container.begin();it!=container.end();it++)
#define sz(c) int(c.size())

using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;



void display(vvi &result){
	tr(result, it){
		tr((*it) , it2){
			cout << *it2<<"\t";
		}
		cout << endl;
	}
}
void generatePermutations(vi &source, vvi&result){
	sort(all(source));
	do{
		result.push_back(source);
	} while (next_permutation(all(source)));
}

bool canAnkitWin2(vi source, bool isAnkitChance, int pileNumber){
	if (pileNumber < sz(source)){
		bool pileChanged = false;
		for (int i = 1; i <= source[pileNumber]; i++){
			source[pileNumber] -= i;
			if (source[pileNumber] == 0){
				pileChanged = true;
				pileNumber++;
			}
			bool res = canAnkitWin2(source, !isAnkitChance, pileNumber);
			if (res == isAnkitChance){
				return res;
			}
			if (pileChanged){
				pileChanged = false;
				pileNumber--;
			}
			source[pileNumber] += i;			
		}
	}
		return !isAnkitChance;
}

bool canAnkitWin(vi source, bool isAnkitChance, int pileNumber){
	if (isAnkitChance){
		if (source.size() == pileNumber){
			return false;
		}
		else{
			bool pileChanged = false;
			for (int i = 1; i <= source[pileNumber]; i++){
				source[pileNumber] -= i;
				if (source[pileNumber] == 0){
					pileChanged = true;
					pileNumber++;
				}	
				bool res = canAnkitWin(source, false, pileNumber);
				if (res == true)
					return res;
				else{
					if (pileChanged){
						pileChanged = false;
						pileNumber--;
					}
					source[pileNumber] += i;
				}
			}
			return false;
		}
	}
	else{
		if (source.size() == pileNumber){
			return true;
		}
		else{
			bool pileChanged = false;
			for (int i = 1; i <= source[pileNumber]; i++){
				source[pileNumber] -= i;
				if (source[pileNumber] == 0){
					pileChanged = true;
					pileNumber++;
				}
				bool res = canAnkitWin(source, true, pileNumber);
				if (res == false)
					return res;
				else{
					if (pileChanged){
						pileChanged = false;
						pileNumber--;
					}
					source[pileNumber] += i;
				}
			}
			return true;
		}
	}
}


int main2(){
	int T;
	cin >> T;
	vi source;
	vvi perms;

	while (T != 0){
		int n;
		cin >> n;
		
		int temp;
		
		while (n != 0){
			cin >> temp;
			source.push_back(temp);
			n--;
		}
		generatePermutations(source, perms);
		int count = 0;
		tr(perms, it){
			count+=canAnkitWin2(*it, true, 0);
		}
		cout << count << endl;
		source.clear();
		perms.clear();
		T--;
	}

	return 0;
}