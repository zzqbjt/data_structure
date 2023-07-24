#include<iostream>
#include<algorithm> 
using namespace std;
template <typename T>
int BinarySearch(T a[],int len,T it)
{
	sort(a,a+len);
	int left=0,right=len-1;
	int mid;
	while(left<=mid)
	{
		mid=(left+right)/2;
		if(a[mid]>it)
			right=mid-1;
		else if(a[mid]<it)
			left=mid+1;
		else
			return mid;
	}
	return -1;	
}
int main()
{
	int n;
	cin>>n;
	int* a=new int [n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	cout<<BinarySearch<int>(a,n,43);
	return 0;
}

