/// MST
/// Time-0.427s

#include<bits/stdc++.h>

using namespace std;

const int mx=201;

struct Edge
{
    int u, v;
    int weight;
};

bool comp(Edge a,Edge b)
{
    return (a.weight<b.weight);
}
vector<Edge>edges;
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

int kruskal(int n)
{
     sort(edges.begin(),edges.end(),comp);
     vector<Edge>mst;
     int i=0,c=0,u,v,m;
     int cst=0;
     m=(int)edges.size();
     while(i<m)
    {
        u=edges[i].u;
        v=edges[i].v;
        int a=find_set(u);
        int b=find_set(v);
        if(a!=b)
        {
            union_sets(a,b);
            c++;
            cst+=edges[i].weight;
            mst.push_back(edges[i]);
            if(c==n-1) break;
        }
        i++;
    }
    edges.clear();
    /// taking those edge only for mst
    edges=mst;
    if(c==n-1) return cst;
    else return -1;
}

  int main()
 {
    int tc,E,cst,t;
    int n,V,u,v,K,M;
    scanf("%d",&tc);
    for(t=1;t<=tc;t++)
    {
    scanf("%d%d",&V,&E);
    n=V;
    printf("Case %d:\n",t);
    for(int i=1;i<=E;i++)
    {
        scanf("%d%d%d",&u,&v,&cst);
        Edge e;
        e.u=u;
        e.v=v;
        e.weight=cst;
        edges.push_back(e);
        initialize(n);
        printf("%d\n",kruskal(n));
    }
    edges.clear();
    }

 return 0;
}
