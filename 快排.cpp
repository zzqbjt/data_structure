#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
void qsort(int a[],int l,int r)
{
	if(l>=r)
		return;
	int low=l;
	int high=r;
//	int len = r-l+1;
//	int x = l + rand()%len;
	int pivot=a[l];
	int temp;
	while(high>low)
	{
		while(a[high]>=pivot&&high>low)
			high--;
		temp=a[high];
		a[high]=a[low];
		a[low]=temp;
		while(a[low]<=pivot&&high>low)
			low++;	
		temp=a[high];
		a[high]=a[low];
		a[low]=temp;
	}
	qsort(a,l,low-1);
	qsort(a,low+1,r);
}
void Quick_Sort(int a[],int n)
{
	qsort(a,0,n-1);	
} 
int main()
{
	time_t t;
	clock_t start, end;
	srand((unsigned)time(&t));
	int N;
	cin>>N;
	int* a=new int [N];
	for(int i=0;i<N;i++)
	{
		a[i] = N-i;
	}
	start = clock(); //记录当前时间
	Quick_Sort(a,N);
//	for(int i=0;i<N-1;i++)
//		cout<<a[i]<<" ";
//	cout<<a[N-1];
    end = clock(); //记录结束时间   
    cout << double(end-start)<< "ms"; //输出运行时间
	return 0;
}

