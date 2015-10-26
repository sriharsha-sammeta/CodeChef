#include<iostream>
#include<algorithm>
#include<map>

#define sz(A) int(A.size())

using namespace std; 
typedef pair<int, int> pii;



pii getPoint(int centerX, int centerY, int point2X, int point2Y, int cosX, int sinX){
	int newX = centerX + (cosX * (point2X - centerX) + sinX * (point2Y - centerY));
	int newY = centerY + (-sinX * (point2X - centerX) + cosX * (point2Y - centerY));
	return make_pair(newX, newY);
}

int getCount(pii p1, pii p2,map<pii,int>&input){
	int count1 = 0;

	if (input.find(getPoint(p1.first, p1.second, p2.first, p2.second, 0, 1)) != input.end()){
		count1++;
	}
	if (input.find(getPoint(p2.first, p2.second, p1.first, p1.second, 0, 1)) != input.end()){
		count1++;
	}
	int count2 = 0;
	if (count1 < 2){
		
		if (input.find(getPoint(p1.first, p1.second, p2.first, p2.second, 0, 1)) != input.end()){
			count2++;
		}
		if (input.find(getPoint(p2.first, p2.second, p1.first, p1.second, 0, -1)) != input.end()){
			count2++;
		}
	}

	return max(count1,count2);
}


int main(){
	
	int N;
	scanf("%d", &N);	

	int A, B;	
	map<pii, int>input;
	int count = 4;
	while (N--){	
		scanf("%d %d", &A, &B);
		pii pr = make_pair(A, B);
		input[pr]++;
		count = min(count, 4 - input[pr]);
	}
	
	if (sz(input) <=2)
		count = 4-sz(input);
	else{
		for (auto it = input.begin(); it != input.end(); it++){
			auto it2 = it;
			for (it2++; it2 != input.end(); it2++){
				count = min(count, 2-getCount(it->first, it2->first, input));
			}
		}
	}
	cout << count << endl;

	return 0;
}