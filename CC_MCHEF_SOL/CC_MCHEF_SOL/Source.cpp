#include <stdio.h>
#include <climits>
#include <bits/stdc++.h>
using namespace std;
 
struct ele
{
	int l;
	int r;
	int c;
};
int rating[100010];
struct ele arr[100010];
int cost[100010];
long long int knap[100010][510];
 
long long int max(long long int a,long long int b)
{
	if(a>b)
		return a;
	return b;
}
 
int main() {
	// your code goes here
	int t;
	scanf(" %d ",&t);
	
	while(t--)
	{
		int n,k,m;
		scanf(" %d %d %d ",&n,&k,&m);
		long long int sum=0;
		
		for(int i=1;i<=n;i++)
		{
			scanf(" %d ",&rating[i]);
			sum+=rating[i];
			cost[i]=INT_MAX;
		}
		
		int l,r,c;
		vector<int> left[n+10];
		vector<int> right[n+10];
		for(int i=1;i<=m;i++)
		{
			scanf(" %d %d %d ",&l,&r,&c);
			arr[i].l=l;
			arr[i].r=r;
			arr[i].c=c;
			
			left[l].push_back(i);
			right[r].push_back(i);
		}
		
		set< pair < int , int > > se;
		
		// int j=1;
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<left[i].size();j++)
			{
				se.insert(make_pair(arr[left[i][j]].c,left[i][j]));
			}
			
			if(!se.empty())
				cost[i]=se.begin()->first;
			
			for(int j=0;j<right[i].size();j++)
			{
				se.erase(make_pair(arr[right[i][j]].c,right[i][j]));
			}
		}
		
		
		int newN=0;
		for(int i=1;i<=n;i++)
		{
			if(rating[i]<0)
			{
				newN++;
				rating[newN]=(-rating[i]);
				cost[newN]=cost[i];
				// printf("%d %d\n",arr[newN],cost[newN]);
			}
		}
		
		// for(int i=1;i<=newN;i++)
		// {
		// 	printf("%d %d\n",rating[i],cost[i]);
		// }
 
		// printf("%d",k);
		// printf.flush();
		for(int i=0;i<=k;i++)
			knap[0][i]=0;
		for(int i=0;i<=newN;i++)
			knap[i][0]=0;
			
		for(int i=1;i<=newN;i++)
		{
			for(int j=1;j<=k;j++)
			{
				if(cost[i]<=j)
				{
					knap[i][j]=max(knap[i-1][j],(long long int)(rating[i]+knap[i-1][j-cost[i]]));
				}
				else knap[i][j]=knap[i-1][j];
				
			}
		}
		
		sum+=knap[newN][k];
		printf("%lld\n",sum);
	}
	return 0;
}  