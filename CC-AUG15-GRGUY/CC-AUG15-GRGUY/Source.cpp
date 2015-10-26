#include<iostream>
#include<string>


using namespace std;

string solve(const string &L1, const string &L2, const int &initialLane, int &gravityCount){
	gravityCount = 0;	
	int current = initialLane;
	for (auto it1 = L1.begin(), it2 = L2.begin(); it1 != L1.end() && it2 != L2.end(); it1++, it2++){
		if (*it1 == *it2 && *it1 == '#'){
			// game over scenario			
			return "No";
		}
		else{
			//if game is running 

			if (it1 == L1.begin()){
				//journey not yet started

				if (*it1 == '.' && *it2=='#')
					current = 1;
				else if (*it1 == '#' && *it2 == '.')
					current = 2;				
			}
			else{
				if (*it1 == '.' && *it2 == '#'){
					if (current == 2){
						current = 1;
						gravityCount++;
					}
				}
				else if (*it1 == '#' && *it2 == '.'){
					if (current == 1){
						current = 2;
						gravityCount++;
					}
				}
			}
		}
	}
	return "Yes";
}

int main(){
	int T;
	string L1, L2;
	cin >> T;	
	int gravityCount = 0;
	string res;
	while (T-- != 0){
		cin >> L1 >> L2;
		if (*(L1.begin()) == *(L2.begin()) && *(L1.begin()) == '.'){
			res = solve(L1, L2, 1, gravityCount);
			int min = gravityCount;
			if (res == "Yes"){
				solve(L1, L2, 2, gravityCount);
				if (min < gravityCount)
					gravityCount = min;
			}			
		}
		else{			
			res = solve(L1, L2, 1, gravityCount);
		}
		cout << res << endl;
		if (res != "No")
			cout << gravityCount << endl;
	}
	
	return 0;
}