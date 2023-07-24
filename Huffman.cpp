#include<iostream>
#include "List.h"
using namespace std;
template <class Elem>
class HTN
{	
	public:
		HTN<Elem>* left;
		HTN<Elem>* right;
		int w;
		Elem data;
		HTN()
		{
			left=right=NULL;
			w=0;
			data='#';
		}
		bool IsLeaf()
		{
			return !left&&!right;
		}
}; 
template <class Elem>
class HT:public HTN<Elem>
{
	
	public:	
		HTN<Elem>* root;	
		HT()
		{
			root=NULL;
		}
		bool IsEmpty()
		{
			return !root;
		}
		void Build(Alist<Elem> E, Alist<int> W, int n)
		{
			Alist<HTN<Elem>*> Huffman(n);
			for(int i=0;i<n;i++)
			{
				HTN<Elem>* x=new HTN<Elem>;
				x->data=E.find(i);
				x->w=W.find(i);
				Huffman.append(x);
			}
			int min1,min2,i1,i2;
			while(Huffman.len()>1)
			{
				HTN<Elem> *H=new HTN<Elem>;
				min1=W.findmin(i1);
				W.remove(i1);
				H->left=Huffman.find(i1);
				Huffman.remove(i1);
				
				min2=W.findmin(i2);
				W.remove(i2);
				H->right=Huffman.find(i2);
				Huffman.remove(i2);
				
				
				H->w=min1+min2;
				Huffman.append(H);
				W.append(min1+min2);

			}
			root=new HTN<Elem>;
			root->left=Huffman.find(0)->left;
			root->right=Huffman.find(0)->right;
			root->w=Huffman.find(0)->w;
		}
		void LevelOrder()
		{
			LinkQueue<HTN<Elem>*> Q;
			HTN<Elem>* curr=root;
			HTN<Elem>* p;
			Q.InQueue(root);
			while(!Q.IsEmpty())
			{
				Q.OutQueue(curr);
				cout<<curr->data<<" ";
				if(curr->left)
					Q.InQueue(curr->left);
				if(curr->right)
					Q.InQueue(curr->right);				
			}
		}
		HTN<Elem>* &Root()
		{
			return root;
		}
};
int main()
{
	HT<char> A;
	Alist<char> a1(100);
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		char c;
		cin>>c;
		a1.append(c); 
	}
	Alist<int> a2(100);
	for(int i=0;i<n;i++)
	{
		int x;
		cin>>x;
		a2.append(x);
	}
	A.Build(a1,a2,n);
	A.LevelOrder();
	return 0;
}
//4
//a b c d
//1 2 3 4
