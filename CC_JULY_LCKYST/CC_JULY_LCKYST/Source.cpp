#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

int main(){
	int size;
	cin >> size;
	vector<int>input(size);
	for (int i = 0; i < size; i++)
		cin >> input[i];
	int count = 0;
	long long int temp = 0;
	for (int i = 0; i < size; i++){
		count = 0;
		temp = input[i];
		while (temp % 10 == 0)
			temp = temp / 10;
		while(temp % 5 == 0){
			count++;
			temp /= 5;
		}
		
		count = ceil(double(count)/2);
		temp = input[i];
		while (count-- != 0)
			temp = temp * 4;
					
		cout << temp << endl;
	}
	return 0;
}