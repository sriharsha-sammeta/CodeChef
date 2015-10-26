#include<iostream>
#include<vector>
using namespace std;
int main(){
	int T=0;
	cin >> T;
	int N = 0;
	long long int K = 0;
	long long int count = 0;
	long long int balance = 0;
	int temp = 0;
	while (T-- != 0){
		cin >> N;
		cin >> K;
		count = 0;
		balance = 0;
		vector<int>input(N);
		for (int i = 0; i < N; i++)
			cin >> input[i];
		for (int i = 0; i < N; i++){
			temp = input[i];
			if (balance > 0){
				if (temp >= balance){
					temp -= balance;
					balance = 0;
				}
				else{
					balance -= temp;
					balance--;
					temp = 0;
				}

			}
			if (temp == 0)
				continue;
			else if (temp == K){
				count++;
			}
			else if (temp < K){								
				count++;
				balance = (K - (temp + 1));								
			}
			else{
				count += (temp / K); 
				temp = temp % K;
				if (temp == 0)
					continue;
				count++;
				balance = (K - (temp + 1));				
			}
		}		
		cout << count << endl;		
	}
	return 0;
}