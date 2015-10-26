#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<set>
using namespace std;


typedef pair<int, int>pii;

int N = 0;
int K = 0;
int M = 0;



long long int findMaxTotal2(set<pii,less<pii> >&input, vector<vector<int> >&price, set<pii>::iterator it, int amountLeft){
	if (it == input.end() || it->first >= 0 || amountLeft <= 0)
		return 0;
	long long int currentVal = 0;
	long long int max1 = 0;
	int bestMoney = amountLeft + 1;
	for (int i = 0; i < M; i++){
		if (it->second >= price[i][0] && it->second <= price[i][1] && price[i][2] < bestMoney){
			bestMoney = price[i][2];			
		}
	}
		
	if (bestMoney <= amountLeft){
		amountLeft -= bestMoney;
		currentVal = it->first;					
		it++;		
		while (it != input.end() && it->first < 0 && amountLeft >0){
			max1= min(max1,findMaxTotal2(input, price, it, amountLeft));
			it++;
		}
	}		
	return currentVal+max1;	
}



int main(){	
	int T = 0;		
	int temp = 0;
	cin >> T;	
	while (T-- != 0){
		cin >> N >> K >> M;				
		set<pii,less<pii> >input;
		vector<vector<int> >price(M,vector<int>(3));
		long long int total = 0;
		for (int i = 0; i < N; i++){			
			cin >> temp;
			input.insert(pair<int, int>(temp, (i + 1)));
			total += temp;			
		}
		
		for (int i = 0; i < M; i++){
			cin >> price[i][0] >> price[i][1] >> price[i][2];
		}		
		long long int max1 = 0; 
		for (auto it = input.begin(); it != input.end();it++){
			max1 = min(max1, findMaxTotal2(input, price, it, K));		
		}		
		total -= max1;
		cout << total << endl;
	}

	return 0;
}