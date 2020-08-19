/// Number Theory + MST - Minimum Spanning Tree (MST) -Kruskal's Algorithm.
/// It is better when the number of edges are comparatively less.
/// It is also mandatory algorithm regarding MST for disconnected graph as in that case prim's algo will not work.
/// Time-0.130s

#include<bits/stdc++.h>

using namespace std;

const int mx=1000001;

struct Edge
{
    int u, v;
    double weight;
};
vector<Edge>edges;
/// custom sort.
bool comp(Edge a,Edge b)
{
    return (a.weight<b.weight);
}
/// keeping each set_union's rank.
int parent[mx];
int ranks[mx];

void make_set(int v)
{
    parent[v] = v;
    ranks[v] = 0;
}
/// path compression and finding ultimate root node of the one
int find_set(int v)
{
    if (v != parent[v])
        (parent[v]=find_set(parent[v]));

    return parent[v];
}

/// merge two different set of nodes together.
void union_sets(int a, int b)
{
     int x,y;
     x=find_set(a);
     y=find_set(b);
     /// going to higher rank alltime.
    if(ranks[x]<ranks[y])
     {
        parent[x]=y;
     }
     else if(ranks[x]>ranks[y])
     {
        parent[y]=x;
     }
     /// same rank ,goes towards any side x or y.
   else
    {
     ranks[x]++;/// or ranks[y]++ and parent[x]=y.
     parent[y]=x;
    }
}

/// initialize
void initialize(int n)
{
    for (int j=0; j<=n; j++)
    {
    make_set(j);
    }
}

  int main()
 {
     int tc,E,cst,t=0;
     int n,V,u,v,K,M;

     while(scanf("%d",&V)!=EOF)
     {
    edges.clear();
    int tot=0,mn_cst=0;
    n=V;
    for(int i=0;i<V-1;i++)
    {
        scanf("%d%d%d",&u,&v,&cst);
        tot+=cst;
    }
    scanf("%d",&K);
    while(K--)
    {
        scanf("%d%d%d",&u,&v,&cst);
        Edge e;
        e.u=u;
        e.v=v;
        e.weight=cst;
        edges.push_back(e);
    }
    scanf("%d",&M);
    while(M--)
    {
        scanf("%d%d%d",&u,&v,&cst);
        Edge e;
        e.u=u;
        e.v=v;
        e.weight=cst;
        edges.push_back(e);
    }
    int m=(int) edges.size();
    sort(edges.begin(),edges.end(),comp);

    initialize(n);
    int i=0,c=0;
    while( i<m && c<=n-1 )
    {
     int a=find_set(edges[i].u);
     int b=find_set(edges[i].v);
     if(a!=b)
        {
      union_sets(a,b);
      c++;
      mn_cst+=edges[i].weight;
        }
     i++;
    }
    if(t!=0) printf("\n");
    printf("%d\n",tot);
    printf("%d\n",mn_cst);
    t++;
     }
 return 0;
}
