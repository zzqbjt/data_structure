#include<iostream>
#include<cstdio>
using namespace std;
template <class Elem>
class Alist
{
	int maxSize,listSize;
	Elem *listArray;
	public:
		Alist(int size=0)
		{
			maxSize=size;
			listArray=new Elem[maxSize];
			listSize=0;	
		}
		~Alist()
		{
			delete [] listArray;
		}
		bool insert(int index,Elem it)
		{
			if(listSize==maxSize)
				return false;				
			if(index<0||index>listSize)
				return false;				
			for(int i=listSize;i>index;i--)
				listArray[i]=listArray[i-1];
			listArray[index]=it;
			listSize++;
			return true;
		}
		bool init(int num)
		{
			if(num>maxSize)
				return false;
			Elem x;			
			for(int i=0;i<num;i++)
			{
				cin>>x;
				insert(i,x);
			}
			return true;
		}
		bool remove(int index)
		{
			if(listSize==0)
				return false; 
			if(index<0||index>listSize)
				return false;	
			for(int i=index;i<listSize;i++)
				listArray[i]=listArray[i+1];
			listSize--;
			return true;
		}
		Elem find(int i)
		{
			return listArray[i];
		}
		bool search(Elem it,int *p)
		{
			int judge=0;
			for(int i=0;i<listSize;i++)
			{
				if(listArray[i]==it)
				{
					*p=i;
					return true;
				}
				judge++;
			}
			if(judge==listSize)
				return false; 
		}
		bool append(Elem it)
		{
			if(insert(listSize,it))
				return true;
			else
				return false;
		}
		bool change(int index, Elem it)
		{
			if(index>=listSize)
				return false;
			listArray[index]=it;
			return true; 
		} 
		Elem findmin(int& index)
		{
			Elem min=listArray[0];
			int j=0; 
			for(int i=1;i<listSize;i++)
			{
				if(listArray[i]<min)
				{
					min=listArray[i];
					j=i;
				}
			}
			index=j;
			return min;
		}
		void print()
		{
			for(int i=0;i<listSize;i++)
				cout<<listArray[i]<<" ";
			cout<<endl;
		}
		int len()
		{
			return listSize;
		}
};
template <class Elem>
class Node
{
	public:
		Elem data;
		Node* next;
		Node(Elem Data, Node* p=NULL)
		{
			data=Data;
			next=p;
		}
		Node(Node* p=NULL){next=p;}
};
template <class Elem>
class Llist:public Node<Elem>
{
	private:
		Node<Elem>* head;
		Node<Elem>* curr;
		void init()
		{
			head=new Node<Elem>;
			head->next=NULL; 
			curr=head;
		}
		void removeall()
		{
			while(!head)
			{
				curr=head;
				head=head->next;
				delete curr;	
			}	
		} 
	public:
		Llist(){init();}
		~Llist(){removeall();}
		void append(Elem it){setPos(len()-1);InsertCurr(it);}
		bool change(int index,Elem it)
		{
			if(remove(index)&&insert(index,it))
				return true;			
			else
				return false;
		}
		void clear(){removeall();init();}
		bool find(int index, Elem& p)
		{
			if(head->next==NULL)
				return false;
			if(index<0)
				return false;
			curr=head->next;
			for(int i=0;i<index;i++)
			{
				curr=curr->next;
				if(!curr)
					return false;
			}	
			p=curr->data;
			return true;
		}
		bool getValue(Elem &e)
		{
			if(head->next==NULL)
				return false;
			e=curr->data;
			return true;
		}
		Node<Elem>* Head(){return head;}
		bool InsertCurr(Elem x)
		{	
			Node<Elem>* p=new Node<Elem>;
			if(!p)
				return false;
			p->data=x;
			p->next=curr->next;
			curr->next=p;
			curr=curr->next;
			return true;
		}
		bool IsEnd(){return (curr->next==NULL);}
		bool IsEmpty(){return !(head->next);}
		bool insert(int index, Elem it)
		{
			if(index<0)
				return false;
			curr=head;
			for(int i=0;i<index;i++)
			{
				curr=curr->next;
				if(!curr)
					return false;
			}	
			Node<Elem>* p=new Node<Elem>;
			p->data=it;
			p->next=curr->next;
			curr->next=p;
			curr=curr->next;
			return true;
		}
		void init(int num)
		{
			if(num<0)
				return;
			head=new Node<Elem>;
			curr=head;
			Elem x;
			for(int i=0;i<num;i++)
			{
				Node<Elem> *p=new Node<Elem>;
				cin>>x;
				p->data=x;
				curr->next=p;
				curr=curr->next;
			}
			curr->next=NULL;
		}
		Node<Elem>* Locate(Elem e)
		{
			curr=head;
			while(curr->next)
			{
				curr=curr->next;
				if(curr->data==e)
					return curr;
			}
			return NULL;
		}
		int len()
		{
			curr=head->next;
			int length=0;
			while(curr)
			{
				length++;
				curr=curr->next;
			}	
			return length;
		}
		void Next(){curr=curr->next;}
		void Prev()
		{
			Node<Elem>* p=curr;
			curr=head;
			while(curr->next!=p)
				curr=curr->next;
		}
		bool Removecurr() 
		{
			if(curr->next==NULL)
				return false;
			Node<Elem>* p=curr->next;
			curr->next=curr->next->next; 
			delete p;
			return true;
		}
		bool remove(int index)
		{
			curr=head;
			if(head->next==NULL)
				return false;
			if(index<0)
				return false;
			for(int i=0;i<index;i++)
			{
				curr=curr->next;
				if(!curr)
					return false;
			}
			Node<Elem>* p=curr->next;
			curr->next=curr->next->next; 
			delete p;
			return true;
		}
		
		bool search(Elem it ,int& p)
		{
			int index=0;
			curr=head->next;
			while(curr)
			{
				if(curr->data==it)
				{
					p=index;
					return true;
				}
				index++;
				curr=curr->next;
			}
			if(index==this->len())
				return false;
		}
		bool setPos(int pos)
		{
			curr=head;
			for(int i=0;i<=pos;i++)
			{
				if(curr->next==NULL)
					return false; 
				Next();
			}
			return true;
		}
		void print()
		{
			curr=head;
			while(curr->next)
			{
				curr=curr->next;
				cout<<curr->data<<" ";
			}
		}
};
template <class Elem>
class DNode
{
	public:
		Elem data;
		DNode* next;
		DNode* prev;
		DNode(Elem Data, DNode* p=NULL)
		{
			data=Data;
			next=p;
		}
		DNode(DNode* p=NULL){next=p;}
};
template <class Elem>
class Dlist:public DNode<Elem>
{
	private:
		DNode<Elem>* head;
		DNode<Elem>* tail;
		DNode<Elem>* curr;
	public:
		Dlist()
		{
			head=new DNode<Elem>;
			tail=new DNode<Elem>;
			curr=head;
		}
		~Dlist()
		{
			while(remove(0));
		}
		bool find(int index, Elem& p)
		{
			if(head->next==NULL)
				return false;
			if(index<0)
				return false;
			curr=head->next;
			for(int i=0;i<index;i++)
			{
				curr=curr->next;
				if(!curr)
					return false;
			}	
			p=curr->data;
			return true;
		}
		bool insert(int index, Elem it)
		{
			if(index<0)
				return false;
			curr=head;
			for(int i=0;i<index;i++)
			{
				curr=curr->next;
				if(!(curr->next))
					return false;
			}	
			DNode<Elem>* p=new DNode<Elem>;
			p->data=it;
			p->next=curr->next;
			p->prev=curr;
			curr->next->prev=p;
			curr->next=p;
			curr=curr->next;
			return true;
		}
		bool remove(int index)
		{
			curr=head;
			if(head->next==NULL)
				return false;
			if(index<0)
				return false;
			for(int i=0;i<index;i++)
			{
				curr=curr->next;
				if(!(curr->next))
					return false;
			}
			DNode<Elem>* p=curr->next;
			curr->next=curr->next->next;
			curr->next->prev=curr;
			delete p;
			return true;
		}
		bool search(Elem it ,int& p)
		{
			int index=0;
			curr=head->next;
			while(curr)
			{
				if(curr->data==it)
				{
					p=index;
					return true;
				}
				index++;
				curr=curr->next;
			}
			if(index==this->len())
				return false;
		}
		bool change(int index,Elem it)
		{
			if(remove(index)&&insert(index,it))
				return true;			
			else
				return false;
		}
		void init(int num)
		{
			if(num<0)
				return;
			head=new DNode<Elem>;
			tail=new DNode<Elem>;
			curr=head;
			head->prev=NULL;
			Elem x;
			for(int i=0;i<num;i++)
			{
				DNode<Elem> *p=new DNode<Elem>;
				cin>>x;
				p->data=x;
				curr->next=p;
				p->prev=curr;
				curr=curr->next;
			}
			curr->next=tail;
			tail->prev=curr;
			tail->next=NULL;			
		}
		void append(Elem it){setPos(len()-1);InsertCurr(it);}
		int len()
		{
			curr=head->next;
			int length=0;
			while(curr->next)
			{
				length++;
				curr=curr->next;
			}	
			return length;
		}
		void Next(){curr=curr->next;}
		void Prev(){curr=curr->prev;}
		bool getValue(Elem &e)
		{
			if(head->next==NULL)
				return false;
			e=curr->data;
			return true;
		}
		bool IsEnd(){return (curr->next==NULL);} 
		void RemoveCurr()
		{
			if(curr->next==NULL)
				return false;
			DNode<Elem>* p=curr->next;
			curr->next=curr->next->next;
			curr->next->prev=curr;
			delete p;
			return true;
		}
		bool InsertCurr(Elem e)
		{
			DNode<Elem>* p=new DNode<Elem>;
			if(!p)
				return false;
			p->data=e;
			p->next=curr->next;
			p->prev=curr;
			curr->next->prev=p;
			curr->next=p;
			curr=curr->next;
			return true;
		}
		bool setPos(int pos)
		{
			curr=head;
			for(int i=0;i<=pos;i++)
			{
				if(curr->next==NULL)
					return false; 
				Next();
			}
			return true;
		}
		void print(bool i=1)
		{
			if(i)
			{
				curr=head->next;
				while(curr->next)
				{
					cout<<curr->data<<" ";
					curr=curr->next;
				}
			}
			else
			{
				curr=tail->prev;
				while(curr->prev)
				{
					cout<<curr->data<<" ";
					curr=curr->prev;
				}
			}	
		}
}; 
template <class Elem>
class Clist:public Node<Elem>
{
	private:
		Node<Elem>* head;
		Node<Elem>* curr;
	public:
		Clist()
		{
			head=new Node<Elem>;
			head->next=head;
			curr=head;
		}
		~Clist()
		{
			while(remove(0));
		}
		bool find(int index, Elem& p)
		{
			if(head->next==head)
				return false;
			if(index<0)
				return false;
			curr=head->next;
			for(int i=0;i<index;i++)
			{
				curr=curr->next;
				if(curr==head)
					return false;
			}	
			p=curr->data;
			return true;
		}
		bool insert(int index, Elem it)
		{
			if(index<0)
				return false;
			curr=head;
			for(int i=0;i<index;i++)
			{
				curr=curr->next;
				if(curr==head)
					return false;
			}	
			Node<Elem>* p=new Node<Elem>;
			p->data=it;
			p->next=curr->next;
			curr->next=p;
			curr=curr->next;
			return true;
		}
		bool remove(int index)
		{
			curr=head;
			if(head->next==head)
				return false;
			if(index<0)
				return false;
			for(int i=0;i<index;i++)
			{
				curr=curr->next;
				if(curr==head)
					return false;
			}
			Node<Elem>* p=curr->next;
			curr->next=curr->next->next;
			delete p;
			return true;
		}
		bool search(Elem it ,int& p)
		{
			int index=0;
			curr=head->next;
			while(curr!=head)
			{
				if(curr->data==it)
				{
					p=index;
					return true;
				}
				index++;
				curr=curr->next;
			}
			if(index==len())
				return false;
		}
		bool change(int index,Elem it)
		{
			if(remove(index)&&insert(index,it))
				return true;			
			else
				return false;
		}
		void init(int num)
		{
			if(num<0)
				return;
			head=new Node<Elem>;
			curr=head;
			Elem x;
			for(int i=0;i<num;i++)
			{
				Node<Elem> *p=new Node<Elem>;
				cin>>x;
				p->data=x;
				curr->next=p;
				curr=curr->next;
			}
			curr->next=head;
		}
		void append(Elem it){setPos(len()-1);InsertCurr(it);}
		int len()
		{
			curr=head->next;
			int length=0;
			while(curr!=head)
			{
				length++;
				curr=curr->next;
			}	
			return length;
		}
		void Next(){curr=curr->next;}
		void Prev()
		{
			Node<Elem>* p=curr;
			curr=head;
			while(curr->next!=p)
				curr=curr->next;
		}
		bool getValue(Elem &e)
		{
			if(head->next==NULL)
				return false;
			e=curr->data;
			return true;
		}
		bool IsEnd(){return (curr->next==head);}
		bool RemoveCurr()
		{
			if(curr->next==NULL)
				return false;
			Node<Elem>* p=curr->next;
			curr->next=curr->next->next;
			delete p;
			return true;
		}
		bool InsertCurr(Elem e)
		{
			Node<Elem>* p=new Node<Elem>;
			if(!p)
				return false;
			p->data=e;
			p->next=curr->next;
			curr->next=p;
			curr=curr->next;
			return true;
		}
		bool setPos(int pos)
		{
			curr=head;
			for(int i=0;i<=pos;i++)
			{
				if(curr->next==NULL)
					return false; 
				Next();
			}
			return true;
		}
		void print()
		{
			curr=head->next;
			while(curr!=head)
			{
				cout<<curr->data<<" ";
				curr=curr->next;
			}
		}
};
template <class Elem>
class SeqStack
{
	int maxSize;
	int top;
	Elem* base;
	public:
		SeqStack(int size)
		{
			maxSize=size;
			base=new Elem [maxSize];
			top=0;	
		}
		~SeqStack()
		{
			delete [] base;
		}
		bool IsFull()
		{
			if(top==maxSize)
				return true;
			else
				return false;	
		}
		bool IsEmpty()
		{
			if(top==0)
				return true;
			else
				return false;	
		}
		bool push(Elem it)
		{
			if(IsFull())
				return false;
			else
			{
				base[top]=it;
				top++;
				return true;
			}
		}
		bool pop(Elem& p)
		{
			if(IsEmpty())
				return false;
			else
			{
				top--;
				p=base[top];
				return true;	
			}	
		}
		int len()
		{
			return top;	
		}	
};
template <class Elem>
class LinkStack:public Node<Elem> 
{
	Node<Elem>* top;
	public:
		LinkStack()
		{
			top=new Node<Elem>;
			top->next=NULL;
		}
		~LinkStack()
		{
			Elem p;
			while(pop(p));
		}
		bool IsEmpty()
		{
			if(top->next)
				return false;
			else
				return true;
		}
		void push(Elem it)
		{
			Node<Elem>* p=new Node<Elem>;
			p->data=it;
			p->next=top->next;
			top->next=p;
		}
		bool pop(Elem& q)
		{
			if(IsEmpty())
				return false;	
			q=top->next->data;
			Node<Elem> *p=top->next;
			top->next=top->next->next;
			delete p;
			return true;
		}
		int len()
		{
			int len=0;
			Node<Elem> *p=top;
			while(p->next)
			{
				len++;
				p=p->next;
			}
			return len;
		}
};
template <class Elem>
class SeqQueue
{
	int maxsize;
	int front,rear;
	Elem* queue;
	public:
		SeqQueue(int size)
		{
			maxsize=size+1;
			front=0;
			rear=0;
			queue=new Elem[maxsize];
		}
		~SeqQueue()
		{
			delete [] queue;
		}
		bool IsFull()
		{
			if((rear+1)%maxsize==front)
				return true;
			else
				return false;
		}
		bool IsEmpty()
		{
			if(front==rear)
				return true;
			else
				return false;
		}
		bool InQueue(Elem e)
		{
			if(IsFull())
				return false;
			queue[rear]=e;
			rear=(rear+1)%maxsize;
			return true;
		}
		bool OutQueue(Elem& p)
		{
			if(IsEmpty())
				return false;
			p=queue[front];
			front=(front+1)%maxsize;
			return true;
		}
};
template <class Elem>
class LinkQueue:public Node<Elem>
{
	
	public:
		Node<Elem>* front;
		Node<Elem>* rear;
		LinkQueue()
		{
			front=new Node<Elem>;
			rear=front;
			front->next=NULL;
		}
		~LinkQueue()
		{
			Elem x;
			while(OutQueue(x));
		}
		bool IsEmpty()
		{
			if(front->next)
				return false;
			else
				return true;
		}
		void InQueue(Elem e)
		{
			Node<Elem>* p=new Node<Elem>;
			p->data=e;
			p->next=NULL;
			rear->next=p;
			rear=p;
		}
		bool OutQueue(Elem& p)
		{
			if(IsEmpty())
				return false;
			p=front->next->data;
			Node<Elem>* q=front->next;
			front->next=front->next->next;
			if(front->next==NULL)
				rear=front;
			delete q;
			return true;
		}
		int len()
		{
			int len=0;
			Node<Elem>* p=front;
			while(p->next)
			{
				len++;
				p=p->next;
			}
			return len;
		}
}; 
