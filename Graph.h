#include<iostream>
#include "List.h"
#include<algorithm>
#define infty 1000000000
using namespace std;
class Graph
{
	public:
		int numVertex;
		int numEdge;
		bool* Visited;
		int *InDegree;
		Graph(int n)
		{
			numVertex=n;
			InDegree=new int [n];
			Visited=new bool [n];
		}
		~Graph()
		{
			delete [] InDegree;
			delete [] Visited;
		}
		virtual int FirstAdj(int n)=0;
		virtual int NextAdj(int n,int pre)=0;
		int VerticesNum(){return numVertex;}
		int EdgesNum(){return numEdge;}
		virtual int weight(int from,int to)=0;
		virtual void setEdge(int from,int to,int weight=1)=0;
		virtual void delEdge(int from,int to)=0;
};
class Graphm:public Graph
{
	int** AdjMatrix;
	public:
		Graphm(int n):Graph(n)
		{
			AdjMatrix=new int* [n];
			for(int i=0;i<n;i++)
				AdjMatrix[i]=new int [n];
			for(int i=0;i<n;i++)
			{
				InDegree[i]=0;
				Visited[i]=false;
				for(int j=0;j<n;j++)
					AdjMatrix[i][j]=0;
			}
		}
		~Graphm()
		{
			for(int i=0;i<numVertex;i++)
				delete [] AdjMatrix[i];
			delete [] AdjMatrix;
		}
		int weight(int from,int to){return AdjMatrix[from][to];}
		void setEdge(int from,int to,int weight=1)
		{
			if(AdjMatrix[from][to]==0)
			{
				numEdge++;
				InDegree[to]++;
			}
			AdjMatrix[from][to]=weight;
		}
		void delEdge(int from,int to)
		{
			if(AdjMatrix[from][to]!=0)
			{
				numEdge--;
				InDegree[to]--;
			}
			AdjMatrix[from][to]=0;
		}
		int FirstAdj(int n)
		{
			for(int i=0;i<numVertex;i++)
			{
				if(AdjMatrix[n][i]!=0)
					return i;
			}
			return -1;
		}
		int NextAdj(int n,int pre)
		{
			for(int i=pre+1;i<numVertex;i++)
			{
				if(AdjMatrix[n][i]!=0)
					return i;
			}
			return -1;
		}
};
struct listUnit
{
	int vertex;
	int weight;
};
class Graphl:public Graph
{
	Llist<listUnit>* vexList;
	public:
		Graphl(int n):Graph(n){vexList=new Llist<listUnit> [n];}
		~Graphl(){delete [] vexList;}
		int weight(int from,int to)
		{
			Node<listUnit>* curr=vexList[from].Head();
			while(curr->next!=NULL&&curr->next->data.vertex!=to)
				curr=curr->next;
			return curr->next->data.weight;
		}
		int FirstAdj(int n)
		{
			Node<listUnit>* curr=vexList[n].Head();
			if(curr->next!=NULL)
				return curr->next->data.vertex;
			return -1;
		}
		int NextAdj(int n,int pre)
		{
			Node<listUnit>* curr=vexList[n].Head();
			while(curr->next!=NULL&&curr->next->data.vertex<=pre)
				curr=curr->next;
			if(curr->next!=NULL)
				return curr->next->data.vertex;
			return -1;
		}
		void setEdge(int from,int to,int weight=1)
		{
			Node<listUnit>* curr=vexList[from].Head();
			while(curr->next!=NULL&&curr->next->data.vertex<to)
				curr=curr->next;
			if(curr->next==NULL)
			{
				curr->next=new Node<listUnit>;
				curr->next->data.vertex=to;
				curr->next->data.weight=weight;
				InDegree[to]++;
				numEdge++;
				return;
			}
			if(curr->next->data.vertex==to)
			{
				curr->next->data.weight=weight;
				return;
			}
			if(curr->next->data.vertex>to)
			{
				Node<listUnit>* p=new Node<listUnit>;
				p->next=curr->next;
				curr->next=p;
				p->data.vertex=to;
				p->data.weight=weight;
				InDegree[to]++;
				numEdge++;
			}
		}
		void delEdge(int from,int to)
		{
			Node<listUnit>* curr=vexList[from].Head();
			while(curr->next!=NULL&&curr->next->data.vertex<to)
				curr=curr->next;
			if(curr->next==NULL)
				return;
			if(curr->next->data.vertex==to)
			{
				Node<listUnit>* p=curr->next;
				curr->next=curr->next->next;
				delete p;
				numEdge--;
				InDegree[to]--;
			}
		}
};
void DFS(Graph& G,int V)
{
	G.Visited[V]=true;
	cout<<V<<" ";
	for(int w=G.FirstAdj(V);w!=-1;w=G.NextAdj(V,w))
	{
		if(!G.Visited[w])
			DFS(G,w);	
	}	
}
void BFS(Graph& G, int V)
{
	SeqQueue<int> Q(G.VerticesNum());
	G.Visited[V]=true;
	cout<<V<<" ";
	Q.InQueue(V);
	while(!Q.IsEmpty())
	{
		int W;
		Q.OutQueue(W);
		for(int w=G.FirstAdj(W);w!=-1;w=G.NextAdj(W,w))
		{
			if(!G.Visited[w])
			{
				cout<<w<<" ";
				G.Visited[w]=true;
				Q.InQueue(w);
			}
		}	
	}	
} 
void Dijkstra(Graph &G,int* dist,int* pre,int s)
{
	int n=G.VerticesNum();
	bool* S=new bool [n];
	for(int i=0;i<n;i++)
	{
		S[i]=false;
		if(i!=s&&G.weight(s,i)==0)
			dist[i]=infty;
		else
			dist[i]=G.weight(s,i);
		if(i!=s&&dist[i]<infty)
			pre[i]=s;
		else
			pre[i]=-1;
	}
	S[s]=true;
	int Min,v;
	for(int i=0;i<n-1;i++)
	{
		Min=infty;
		v=s;
		for(int j=0;j<n;j++)
		{
			if(!S[j]&&dist[j]<Min)
			{
				Min=dist[j];
				v=j;
			}
		}
		S[v]=true;
		for(int j=0;j<n;j++)
		{
			if(!S[j]&&G.weight(v,j)!=0&&G.weight(v,j)+dist[v]<dist[j])
			{
				dist[j]=G.weight(v,j)+dist[v];
				pre[j]=v;
			}
		}
	}
	delete [] S;
}
void MidNode(int i,int j,int** path)
{
	if(path[i][j]!=-1&&i!=path[i][j])
	{
		MidNode(i,path[i][j],path);
		cout<<path[i][j]<<"->";
		MidNode(path[i][j],j,path);
	}
}
void Output_Allpaths(int n,int** path,int** dist)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i!=j&&path[i][j]!=-1)
			{
				cout<<i<<"->";
				MidNode(i,j,path);
				cout<<j<<":"<<dist[i][j]<<endl;
			}
			else if(i!=j)
				cout<<"There is no path from "<<i<<" to "<<j<<"!"<<endl;
		}
	}	
} 
void Floyd(Graph& G,int** dist,int** path)
{
	int n=G.VerticesNum();
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i!=j&&G.weight(i,j)==0)
				dist[i][j]=infty;
			else
				dist[i][j]=G.weight(i,j);
			if(i!=j&&dist[i][j]<infty)
				path[i][j]=i;
			else
				path[i][j]=-1;		
		}
	}
	for(int k=0;k<n;k++)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(dist[i][k]+dist[k][j]<dist[i][j])
				{
					dist[i][j]=dist[i][k]+dist[k][j];
					path[i][j]=k;
				}
			}
		}
	}
	Output_Allpaths(n,path,dist);
}
struct Edge
{
	int from;
	int to;
	int weight;
};
void Prim(Graph& G,int s,Edge* MST)
{
	int i,j;
	int n=G.VerticesNum();
	Edge* MST_Edge=new Edge [n];
	for(i=0;i<n;i++)
	{
		MST_Edge[i].from=i;
		MST_Edge[i].to=s;
		if(i!=s&&G.weight(i,s)==0)
			MST_Edge[i].weight=infty;
		else
			MST_Edge[i].weight=G.weight(i,s);
	}
	int v,Min;
	for(i=0;i<n-1;i++)
	{
		v=0;
		Min=infty;
		for(j=0;j<n;j++)
		{
			if(MST_Edge[j].weight!=0&&MST_Edge[j].weight<Min)
			{
				Min=MST_Edge[j].weight;
				v=j;
			}
		}
		MST[i].from=v;
		MST[i].to=MST_Edge[v].to;
		MST[i].weight=Min;
		MST_Edge[v].weight=0;
		for(j=0;j<n;j++)
		{
			if(G.weight(j,v)!=0&&G.weight(j,v)<MST_Edge[j].weight)
			{
				MST_Edge[j].to=v;
				MST_Edge[j].weight=G.weight(j,v);	
			}	
		}	
	}
	delete [] MST_Edge;
}
bool cmp(Edge a,Edge b)
{
	return (a.weight<b.weight);
}
void Kruskal(Graph& G,Edge* MST)
{
	int n=G.VerticesNum();
	int* Vset=new int [n];
	Edge* E=new Edge [G.EdgesNum()];
	int Enum=0;
	for(int i=0;i<n;i++)
	{
		for(int j=G.FirstAdj(i);j!=-1;j=G.NextAdj(i,j))
		{
			if(i<j)
			{
				E[Enum].from=i;
				E[Enum].to=j;
				E[Enum].weight=G.weight(i,j);
				Enum++;
			}
		}
		Vset[i]=i;
	}
	sort(E,E+Enum,cmp);
	int count=0;
	int i=0;
	while(count<n-1)
	{
		int x=Vset[E[i].from];
		int y=Vset[E[i].to];
		if(x!=y)
		{
			MST[count]=E[i];
			count++;
			for(int j=0;j<n;j++)
			{
				if(Vset[j]==y)
					Vset[j]=x;
			}
		}
		i++;
	}
	delete [] Vset;
	delete [] E;		
}
void Do_TopoSort(Graph& G,int V)
{
	G.Visited[V]=true;
	for(int w=G.FirstAdj(V);w!=-1;w=G.NextAdj(V,w))
	{
		if(!G.Visited[w])
			Do_TopoSort(G,w);
	}
	cout<<V<<" ";	
} 
void TopoSort_DFS(Graph &G)
{
	int n=G.VerticesNum();
	for(int i=0;i<n;i++)
		G.Visited[i]=false;
	for(int i=0;i<n;i++)
	{
		if(!G.Visited[i])
			Do_TopoSort(G,i);
	}
}
void TopoSort_BFS(Graph &G)
{
	int n=G.VerticesNum();
	int* indegree=new int [n];
	for(int i=0;i<n;i++)
	{
		indegree[i]=G.InDegree[i];
		G.Visited[i]=false;
	}
	SeqQueue<int> Q(n);
	for(int i=0;i<n;i++)
	{
		if(indegree[i]==0)
			Q.InQueue(i);	
	}
	while(!Q.IsEmpty())
	{
		int V;
		Q.OutQueue(V);
		cout<<V<<" ";
		G.Visited[V]=true;
		for(int w=G.FirstAdj(V);w!=-1;w=G.NextAdj(V,w))
		{
			indegree[w]--;
			if(indegree[w]==0)
				Q.InQueue(w);
		}	
	}
	for(int i=0;i<n;i++)
	{
		if(!G.Visited[i])
		{
			cout<<"Error: There is a circle in the graph!"<<endl;
			break;
		}		
	}
	delete [] indegree;	
}
bool CriticalPath(Graph& G)
{
	int n=G.VerticesNum();
	int* ES=new int [n];
	int* LF=new int [n];
	int* indegree=new int [n];
	int e,l;
	int count=0;
	SeqQueue<int> Q(n);
	SeqStack<int> S(n);
	for(int i=0;i<n;i++)
	{
		indegree[i]=G.InDegree[i];
		ES[i]=0;
	}
	for(int i=0;i<n;i++)
	{
		if(indegree[i]==0)
			Q.InQueue(i);	
	}
	while(!Q.IsEmpty())
	{
		int V;
		Q.OutQueue(V);
		S.push(V);
		count++;
		for(int w=G.FirstAdj(V);w!=-1;w=G.NextAdj(V,w))
		{
			indegree[w]--;
			if(indegree[w]==0)
				Q.InQueue(w);
			if(ES[V]+G.weight(V,w)>ES[w])
				ES[w]=ES[V]+G.weight(V,w);
		}	
	}
	if(count<n)
	{
		cout<<"Error: There is a circle in the graph!"<<endl;
		delete [] ES;
		delete [] LF;
		delete [] indegree;
		return false;
	}
	for(int i=0;i<n;i++)
		LF[i]=ES[i];
	while(!S.IsEmpty())
	{
		int V;
		S.pop(V);
		for(int w=G.FirstAdj(V);w!=-1;w=G.NextAdj(V,w))
		{
			if(LF[w]-G.weight(V,w)<LF[V])
				LF[V]=LF[w]-G.weight(V,w);	
		}	
	}
	for(int v=0;v<n;v++)
	{
		for(int w=G.FirstAdj(v);w!=-1;w=G.NextAdj(v,w))
		{
			e=ES[v];
			l=LF[w]-G.weight(v,w);
			if(e==l)
				cout<<"<"<<v<<","<<w<<">";
		}	
	}
	delete [] ES;
	delete [] LF;
	delete [] indegree;	
	return true;	
}
