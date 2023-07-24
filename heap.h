template <class Elem>
class MaxHeap
{
	Elem* Heap;
	int n;
	int maxsize;
	public:
		MaxHeap(int size)
		{
			Heap=new Elem [size+1];
			maxsize=size;
			n=0;
			Heap[0]=2147483647;
		}
		bool IsFull(){return (n==maxsize);}
		bool IsEmpty(){return (n==0);}
		bool Insert(Elem e)
		{
			if(IsFull())
				return false;
			else
			{
				int i;
				for(i=n+1;Heap[i/2]<=e;i/=2)
					Heap[i]=Heap[i/2];
				Heap[i]=e;
				n++;
				return true;
			}
		}
		Elem RemoveMax()
		{
			if(IsEmpty())
				return 0;
			else
			{
				int parent,child;
				Elem max,temp;
				max=Heap[1];
				temp=Heap[n];
				n--;
				for(parent=1;parent*2<=n;parent=child)
				{
					child=2*parent;
					if(child!=n&&Heap[child]<Heap[child+1])
						child++;
					if(temp>=Heap[child])
						break;
					else
						Heap[parent]=Heap[child];
				}
				Heap[parent]=temp;
				return max;
			}
		}
		void SiftDown(int pos)
		{
			int parent,child;
			Elem temp;
			temp=Heap[pos];
			for(parent=pos;parent*2<=n;parent=child)
			{
				child=2*parent;
				if(child!=n&&Heap[child]<Heap[child+1])
					child++;
				if(temp>=Heap[child])
					break;
				else
					Heap[parent]=Heap[child];
			}
			Heap[parent]=temp;
		}
		bool BuildHeap(Elem* &a,int len)
		{
			if(len>maxsize)
				return false;
			else
			{
				for(int i=0;i<len;i++)
					Heap[i+1]=a[i];
				n=len;
				for(int i=n/2;i>0;i--)
					SiftDown(i); 
				return true; 
			}
		}
		void print()
		{
			for(int i=1;i<=n;i++)
				cout<<Heap[i]<<" ";
		}
};
template <class Elem>
class MinHeap
{
	Elem* Heap;
	int n;
	int maxsize;
	public:
		MinHeap(int size)
		{
			Heap=new Elem [size+1];
			maxsize=size;
			n=0;
			Heap[0]=-2147483647;
		}
		bool IsFull(){return (n==maxsize);}
		bool IsEmpty(){return (n==0);}
		bool Insert(Elem e)
		{
			if(IsFull())
				return false;
			else
			{
				int i;
				for(i=n+1;Heap[i/2]>=e;i/=2)
					Heap[i]=Heap[i/2];
				Heap[i]=e;
				n++;
				return true;
			}
		}
		Elem RemoveMin()
		{
			if(IsEmpty())
				return 0;
			else
			{
				int parent,child;
				Elem min,temp;
				min=Heap[1];
				temp=Heap[n];
				n--;
				for(parent=1;parent*2<=n;parent=child)
				{
					child=2*parent;
					if(child!=n&&Heap[child]>Heap[child+1])
						child++;
					if(temp<=Heap[child])
						break;
					else
						Heap[parent]=Heap[child];
				}
				Heap[parent]=temp;
				return min;
			}
		}
		void SiftDown(int pos)
		{
			int parent,child;
			Elem temp;
			temp=Heap[pos];
			for(parent=pos;parent*2<=n;parent=child)
			{
				child=2*parent;
				if(child!=n&&Heap[child]>Heap[child+1])
					child++;
				if(temp<=Heap[child])
					break;
				else
					Heap[parent]=Heap[child];
			}
			Heap[parent]=temp;
		}
		bool BuildHeap(Elem* &a,int len)
		{
			if(len>maxsize)
				return false;
			else
			{
				for(int i=0;i<len;i++)
					Heap[i+1]=a[i];
				n=len;
				for(int i=n/2;i>0;i--)
					SiftDown(i); 
				return true; 
			}
		}
		void print()
		{
			for(int i=1;i<=n;i++)
				cout<<Heap[i]<<" ";
		}
};
