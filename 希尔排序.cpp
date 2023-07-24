#include<iostream>
using namespace std;
void Insert_Sort(int a[],int n,int start,int gap)
{
	for(int i=start+gap;i<n;i+=gap)
	{
		int temp=a[i];
		int j;
		for(j=i-gap;j>=start;j-=gap)
		{
			if(a[j]>temp)
				a[j+gap]=a[j];
			else
				break;
		}	
		a[j+gap]=temp;	
	}
}
void Shell_Sort(int a[],int n)
{
	for(int gap=n/2;gap>2;gap/=2)
	{
		for(int j=0;j<gap;j++)
			Insert_Sort(a,n,j,gap);
	}
	Insert_Sort(a,n,0,1); 
}
int main()
{
	int N;
	cin>>N;
	int* a=new int [N];
	for(int i=0;i<N;i++)
		cin>>a[i];
	Shell_Sort(a,N);
	for(int i=0;i<N-1;i++)
		cout<<a[i]<<" ";
	cout<<a[N-1];
	return 0;
}

