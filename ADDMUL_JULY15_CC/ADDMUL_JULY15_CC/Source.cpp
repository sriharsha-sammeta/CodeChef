#include<iostream>
#include<vector>
#include<map>
using namespace std;

#define M 1000000007
vector<int>A;
int N;
int Q;
int realN=0;
struct Node{

	long long int totalSum;
	long long int add;
	long long int mul;

};

vector<Node*> result;

void buildTree(int i, int startIndex, int endIndex){
	if (startIndex > endIndex)
		return;
	if (startIndex == endIndex){			
		result[i]->totalSum = A[startIndex];
		result[i]->mul = 1;
		result[i]->add = 0;		
		return;
	}
	int midIndex = (startIndex + endIndex) / 2;
	buildTree((2 * i) + 1, startIndex, midIndex);
	buildTree((2 * i) + 2, midIndex + 1, endIndex);
			
	result[i]->totalSum = result[(2 * i) + 1]->totalSum + result[(2 * i) + 2]->totalSum;
	result[i]->totalSum %= M;
	result[i]->add = 0;
	result[i]->mul = 1;	
}

void lazilyPropogate(int i){
	
	if (((2 * i) + 1) < realN && ((2 * i) + 1) < realN){

		if (result[i]->mul != 1){
			result[(2 * i) + 1]->mul *= result[i]->mul;
			result[(2 * i) + 1]->mul %= M;
			result[(2 * i) + 1]->add *= result[i]->mul;
			result[(2 * i) + 1]->add %= M;

			result[(2 * i) + 2]->mul *= result[i]->mul;
			result[(2 * i) + 2]->mul %= M;
			result[(2 * i) + 2]->add *= result[i]->mul;
			result[(2 * i) + 2]->add %= M;

			result[i]->mul = 1;
		}

		if (result[i]->add != 0){
			result[(2 * i) + 1]->add += result[i]->add;
			result[(2 * i) + 1]->add %= M;

			result[(2 * i) + 2]->add += result[i]->add;
			result[(2 * i) + 2]->add %= M;
			result[i]->add = 0;
		}
	}
}

int queryTree(int queryType, int i, int startIndex, int endIndex, int queryStart, int queryEnd, int v){
	if (startIndex <= queryStart && queryEnd <= endIndex && queryStart <= queryEnd && startIndex <= endIndex){
		if (startIndex == queryStart && endIndex == queryEnd){
			switch (queryType){
			case 1:
				result[i]->add += v;
				result[i]->add %= M;
				return 0;
			case 2:
				result[i]->mul *= v;
				result[i]->mul %= M;

				result[i]->add *= v;
				result[i]->add %= M;
				return 0;
			case 3:
				result[i]->mul = 0;

				result[i]->add = v;

				return 0;
			case 4:
				long long int sum = result[i]->totalSum;
				sum *= result[i]->mul;
				sum %= M;

				long long int tempSum = (endIndex - startIndex + 1)*result[i]->add;
				tempSum %= M;

				sum += tempSum;
				sum %= M;

				return sum;
			}
		}
		else{
			int sum1 = 0, sum2 = 0;
			int midIndex = (startIndex + endIndex) / 2;
			int shouldUpdateParentNode = true;
			if (result[i]->add == 0 && result[i]->mul == 1 && queryType == 4){
				shouldUpdateParentNode = false;
			}
			if (shouldUpdateParentNode){
				lazilyPropogate(i);
			}
			if (startIndex <= queryStart && queryEnd <= midIndex){
				sum1 = queryTree(queryType, (2 * i) + 1, startIndex, midIndex, queryStart, queryEnd, v);
			}
			else if ((midIndex + 1) <= queryStart && queryEnd <= endIndex){
				sum2 = queryTree(queryType, (2 * i) + 2, midIndex + 1, endIndex, queryStart, queryEnd, v);
			}
			else{
				sum1 = queryTree(queryType, (2 * i) + 1, startIndex, midIndex, queryStart, midIndex, v);
				sum2 = queryTree(queryType, (2 * i) + 2, midIndex + 1, endIndex, midIndex + 1, queryEnd, v);
			}
			if (shouldUpdateParentNode){
				result[i]->totalSum = queryTree(4, (2 * i) + 1, startIndex, midIndex, startIndex, midIndex, v);

				result[i]->totalSum += queryTree(4, (2 * i) + 2, midIndex + 1, endIndex, midIndex + 1, endIndex, v);
				result[i]->totalSum %= M;
			}
			return (sum1 + sum2) % M;			
		}		
	}
	return 0;
}


int main(){

	cin >> N;
	cin >> Q;
	A.resize(N);


	for (int i = 0; i < N; i++)
		cin >> A[i];
	/*
	realN = 1;
	while (realN < N){
		realN *= 2;
	}
	realN *= 2;
	*/

	realN = N;
	realN=realN << 2;
	result.reserve(realN);
	
	for (int i = 0; i < realN; i++){
		struct Node *tempNode= new Node();
		tempNode->totalSum = 0;
		tempNode->add = 0;
		tempNode->mul = 1;
		result.push_back(tempNode);
	}
	
	buildTree(0, 0, N - 1);


	int queryType = 0, startQuery = 0, endQuery = 0, v = 0;

	for (int i = 0; i < Q; i++){
		cin >> queryType;
		cin >> startQuery >> endQuery;
		if (queryType == 4){
			cout << queryTree(queryType, 0, 0, N - 1, startQuery - 1, endQuery - 1, v) << endl;
		}
		else{
			cin >> v;
			queryTree(queryType, 0, 0, N - 1, startQuery - 1, endQuery - 1, v);
		}
	}

	return 0;
}