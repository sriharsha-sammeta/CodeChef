#include<iostream>

using namespace std;


bool isPowerOf2(int num){
	while (num % 2 == 0){
		num /= 2;
	}
	if (num == 1)
		return true;
	return false;
}

int solve(int x, const int& y){
	if (x == y){
		return 0;
	}
	else if (x < y  && isPowerOf2(x)){		
		return 1 + solve(x * 2, y);		
	}
	else{
		if (x % 2 == 0)
			x = x / 2;
		else {
			x -= 1;
			x /= 2;
		}
		return 1 + solve(x, y);
	}	
}



int main(){
	int T, A, B;
	cin >> T;
	while (T-- != 0){
		cin >> A >> B;
		cout << solve(A, B)<<endl;
	}
	return 0;
}