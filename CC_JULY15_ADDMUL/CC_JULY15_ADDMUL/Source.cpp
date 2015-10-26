#include<iostream>
#include<vector>
#include<math.h>
#define sz(A) int(A.size())
const long long int M = 1e9 + 7;

using namespace std;
typedef vector<int>vi;

struct Node{
	long long int sum = 0;
	int mul = 1;
	int add = 0;
};

vector<Node> segmentTree;
vi A;


void  buildSegmentTree(int i, int start, int end){	
	if (i<0 || i>sz(segmentTree) || start > end)
		return;
	int mid = (start + end) / 2;
	if (start == end)
		segmentTree[i].sum = A[start];
	else{
		buildSegmentTree((2 * i) + 1, start, mid);
		buildSegmentTree((2 * i) + 2, mid + 1, end);
		segmentTree[i].sum = segmentTree[(2 * i) + 1].sum + segmentTree[(2 * i) + 2].sum;
		segmentTree[i].sum %= M;
	}		
}

void recomputeSegmentTreeAt(int i,int start, int mid ,int end){
	long long int res1 = 0, res2 = 0;
	res1 = segmentTree[(2 * i) + 1].sum *segmentTree[(2 * i) + 1].mul;
	res1 %= M;
	long long int temp = (segmentTree[(2 * i) + 1].add *(mid - start + 1));
	temp %= M;
	res1 += temp;
	res1%= M;

	res2 = segmentTree[(2 * i) + 2].sum *segmentTree[(2 * i) + 2].mul;
	res2 %= M;
	temp = (segmentTree[(2 * i) + 2].add *(end - mid));
	temp %= M;
	res2 += temp;
	res2 %= M;
	
	segmentTree[i].sum = res1+res2;
	segmentTree[i].sum %= M;

}
void update(int QN, int x, int y, int v, int i, int start, int end){
	if (x > y || start > end || end < x || y < start)
		return;
	if (QN != 4){
		if (start ==x  && y==end){
			switch (QN){
			case 1:
				segmentTree[i].add += v;				
				break;
			case 2:
				segmentTree[i].mul *= v;
				segmentTree[i].add *= v;
				break;
			case 3:
				segmentTree[i].mul = 1;
				segmentTree[i].add = 0;
				segmentTree[i].sum = (end - start + 1)*v;
				segmentTree[i].sum %= M;
				break;
			}
			
		}
		else {
			int mid = (start + end) / 2;
			if (y <= mid)
				update(QN, x, y, v, (2 * i) + 1, start, mid);
			else if (x >= mid + 1)
				update(QN, x, y, v, (2 * i) + 2, mid + 1, end);
			else {
				update(QN, x, mid, v, (2 * i) + 1, start, mid);
				update(QN, mid + 1, y, v, (2 * i) + 2, mid + 1, end);
			}
			recomputeSegmentTreeAt(i, start, mid, end);
		}
		
	}
}
long long int query(int i, int x, int y, int start, int end){
	if (x > end || y < start || x >y || start > end)
		return 0;
	if (start == x && y == end){
		long long int res = 0;
		res = segmentTree[i].sum * segmentTree[i].mul;
		res %= M;
		long long int temp = segmentTree[i].add*(end - start + 1);
		temp %= M;
		res += temp;
		res %= M;
		return res;
	}
		
	int mid = (start + end) / 2;
	if (y <= mid)
		return query((2 * i) + 1, x, y, start, mid);
	else if (x >= (mid + 1))
		return query((2 * i) + 2, x, y, mid + 1, end);
	else {
		return ((query((2 * i) + 1, x, mid, start, mid) + query((2 * i) + 2, mid+1, y, mid + 1, end)) % M);
	}
		
}

int main(){
	int N, Q,x,y,v;
	int queryType;
	cin >> N >> Q;
	A = vi(N + 1);
	
	for (int i = 1; i <= N; i++)
		cin >> A[i];

	int size = (2 * pow(2, ceil(log2(N)))) - 1;
	segmentTree = vector<Node>(size);
	buildSegmentTree(0, 1, N);


	while (Q-- != 0){
		cin >> queryType >> x >> y;
		if (queryType != 4)
			cin >> v;
		else
			v = 0;

		if (queryType == 4){
			cout << query(0, x, y, 1, N) << endl;			
		}
		else{
			update(queryType, x, y, v, 0, 1, N);
		}
	}
	

	return 0;
}