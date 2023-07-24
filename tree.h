#include<iostream>
#include<string>
#include "List.h"
#include "heap.h" 
using namespace std;
template <class Elem>
class BTN
{
	public:
		Elem data;
		BTN* left;
		BTN* right;
};
template <class Elem>
class BT
{
	protected:
		BTN<Elem>* root;
	public:
		BT(){root=NULL;}
		~BT()
		{
			DeleteBT(root);
		}
		void DeleteBT(BTN<Elem> *r)
		{
			if(r)
			{
				DeleteBT(r->left);
				DeleteBT(r->right);
				delete r;
			}
		}
		BTN<Elem>* &Root()
		{
			return root;
		}
		bool IsEmpty()
		{
			if(root==NULL)
				return true;
			else
				return false;
		}
		void PreOrder(BTN<Elem>* Root)
		{
			if(Root)
			{
				cout<<Root->data<<" ";
				PreOrder(Root->left);
				PreOrder(Root->right);
			}	
		}
		void PreOrderWR()
		{
			BTN<Elem>* curr=root;
			LinkStack<BTN<Elem>*> S;
			while(curr||!S.IsEmpty())
			{
				while(curr)
				{
					S.push(curr);
					cout<<curr->data<<" ";
					curr=curr->left;
				}
				if(!S.IsEmpty())
				{
					S.pop(curr);
					curr=curr->right;
				}
			}
		}
		void InOrder(BTN<Elem>* Root)
		{
			if(Root)
			{
				InOrder(Root->left);
				cout<<Root->data<<" ";
				InOrder(Root->right);
			}	
		}
		void InOrderWR()
		{
			BTN<Elem>* curr=root;
			LinkStack<BTN<Elem>*> S;
			while(curr||!S.IsEmpty())
			{
				while(curr)
				{
					S.push(curr);
					curr=curr->left;
				}
				if(!S.IsEmpty())
				{
					S.pop(curr);
					cout<<curr->data<<" ";
					curr=curr->right;
				}
			}
		}
		void PostOrder(BTN<Elem>* Root)
		{
			if(Root)
			{
				PostOrder(Root->left);
				PostOrder(Root->right);
				cout<<Root->data<<" ";
			}
		}
		void LevelOrder()
		{
			LinkQueue<BTN<Elem>*> Q;
			BTN<Elem>* curr=root;
			BTN<Elem>* p;
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
		void CreateTree(BTN<Elem>* &r)//PreOrder 
		{
			Elem ch;
			cin>>ch;
			if(ch=='#')
				r=NULL;
			else
			{
				r=new BTN<Elem>;
				r->data=ch;
				CreateTree(r->left);
				CreateTree(r->right);
			}
		}
		int Height(BTN<Elem>* Root)//PostOrder
		{
			int HL,HR,H;
			if(Root)
			{
				HL=Height(Root->left);
				HR=Height(Root->right);
				H=(HL>HR)?HL:HR;
				return H+1;
			}	
			else
				return 0;
		}
};
template <class Elem>
class htn
{
	public:
		Elem data;
		int w;
		int left;
		int right;
		htn()
		{
			data='#';
			w=0;
			left=-1;
			right=-1;
		}
		htn(Elem d,int weight,int l,int r)
		{
			data=d;w=weight;left=l;right=r;
		}
};
template<class Elem>
class HTN
{
	public:
		Elem data;
		string code;
		HTN* left;
		HTN* right;
};
template<class Elem>
class HT
{
	protected:
		HTN<Elem>* root;
	public:
		HT(){root=NULL;}
		void Create(htn<Elem>* a, int n)
		{
			int len=n;
			htn<Elem>* b=new htn<Elem> [2*n];
			int min1,i1,min2,i2;
			int count=0,count1,count2;
			while(len>1)
			{
				min1=a[0].w;
				i1=0;
				for(int i=1;i<len;i++)
				{
					if(a[i].w<min1)
					{
						min1=a[i].w;
						i1=i;
					}
				}
				b[count]=a[i1];
				count1=count;
				count++;
				for(int i=i1;i<len-1;i++)
					a[i]=a[i+1];
				len--;
				min2=a[0].w;
				i2=0;
				for(int i=1;i<len;i++)
				{
					if(a[i].w<min2)
					{
						min2=a[i].w;
						i2=i;
					}
				}
				b[count]=a[i2];
				count2=count;
				count++;
				for(int i=i2;i<len-1;i++)
					a[i]=a[i+1];
				len--;
				a[len].w=min1+min2;
				a[len].left=count1;
				a[len].right=count2;
				a[len].data='#'; 
				len++;
			}
			b[count]=a[0];
			count++;
			int index=count-1;
			cout<<endl;
			LinkStack<htn<Elem>> S1;
			LinkStack<HTN<Elem>*> S2;
			root=new HTN<Elem>;
			HTN<Elem>* curr=this->root;
			htn<Elem> node;
			while(true)
			{
				curr->data=b[index].data;
				if(b[index].left<0)
				{
					curr->left=NULL;
					curr->right=NULL;
					if(S1.IsEmpty())
						break;
					S1.pop(node);
					S2.pop(curr);
					index=node.right;
					curr=curr->right;
				}
				else
				{
					HTN<Elem>* l=new HTN<Elem>;
					HTN<Elem>* r=new HTN<Elem>;
					curr->left=l;
					curr->right=r;
					S1.push(b[index]);
					S2.push(curr);
					curr=curr->left;
					index=b[index].left;
				}		
			}
		}
		void HuffmanCode(htn<Elem>* a, int n)
		{
			if(root==NULL)
				Create(a,n);
			HTN<Elem>* curr=root;
			curr->code="";
			LinkStack<HTN<Elem>*> S;
			while(curr||!S.IsEmpty())
			{
				while(curr)
				{
					S.push(curr);
					if(curr->left==NULL&&curr->right==NULL)
						cout<<curr->data<<":"<<curr->code<<endl;
					if(curr->left)
						curr->left->code=curr->code+"0";
					curr=curr->left;
				}
				if(!S.IsEmpty())
				{
					S.pop(curr);
					if(curr->right)
						curr->right->code=curr->code+"1";
					curr=curr->right;
				}
			}
			
		}	
};
template<class Elem>
class BST:public BT<Elem>
{
	public:
		BST():BT<Elem>(){}
		void Insert(Elem e,BTN<Elem>* &r)
		{
			if(!r)
			{
				r=new BTN<Elem>;
				r->left=NULL;
				r->right=NULL;
				r->data=e;
			}
			else	
			{
				if(e<r->data)
					Insert(e,r->left);
				else if(e>r->data)
					Insert(e,r->right);
			}
		}
		void Remove(Elem e, BTN<Elem>* &r)
		{
			if(e>r->data)
				Remove(e,r->right);
			else if(e<r->data)
				Remove(e,r->left);
			else
			{
				if(r->left&&r->right)
				{
					BTN<Elem>* curr=r->right;
					while(curr->left)
						curr=curr->left;
					r->data=curr->data;
					Remove(curr->data,r->right);
				}
				else
				{
					if(!r->left)
						r=r->right;
					else if(!r->right)
						r=r->left;
				}
			}			
		} 
		void Create(Elem* a,int n)
		{			
			for(int i=0;i<n;i++)
				Insert(a[i],this->root);
		}
		BTN<Elem>* find(Elem e,BTN<Elem>* r)
		{
			if(!r)
				return NULL;
			if(e>r->data)
				return find(e,r->right);
			else if(e<r->data)
				return find(e,r->left);
			else
				return r;
		}
		BTN<Elem>* findmin()
		{
			BTN<Elem>* curr=this->root;
			if(!curr)
				return NULL;
			else
			{
				while(curr->left)
					curr=curr->left;
				return curr;
			}
		}
		BTN<Elem>* findmax()
		{
			BTN<Elem>* curr=this->root;
			if(!curr)
				return NULL;
			else
			{
				while(curr->right)
					curr=curr->right;
				return curr;
			}
		}
		
}; 

