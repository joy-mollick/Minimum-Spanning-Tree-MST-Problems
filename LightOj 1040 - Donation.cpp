/// MST - Minimum Spanning Tree (MST) -Kruskal's Algorithm.
/// It is better when the number of edges are comparatively less.
/// It is also mandatory algorithm regarding MST for disconnected graph as in that case prim's algo will not work.

#include<bits/stdc++.h>

using namespace std;

const int mx=51;
bool visited[mx];
vector<int>adj[mx];
/// a structure of an edge u-v and its weight.
struct Edge
{
    int u, v;
    long long weight;
};
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

void dfs(int u)
{
    visited[u]=true;
    for(int k=0;k<adj[u].size();k++)
    {
        if(!visited[adj[u][k]])
        {
            dfs(adj[u][k]);
        }
    }
}

vector<Edge>edges;

  int main()
 {
     int tc,E,U,V;
     cin>>tc;
     for(int t=1;t<=tc;t++)
     {

     for(int j=0;j<mx;j++)
     {
         adj[j].clear();
         visited[j]=false;
     }

    edges.clear();
    int n,U,V;

    long long mn_cost=0,cst,tot_cst=0;
    cin>>n;
    for(int p=1;p<=n;p++)
    {
        for(int q=1;q<=n;q++)
        {
        cin>>cst;
        tot_cst+=cst;
        if(p!=q&&cst!=0)
        {
        U=p;
        V=q;
        Edge e;
        e.u=p;
        e.v=q;
        e.weight=cst;
        edges.push_back(e);
        adj[U].push_back(V);
        adj[V].push_back(U);
        }
        }
    }

    int cnnct_cmpnt=0;
    for (int j=1; j<=n; j++)
    {
    ///initially setting,node itself is its parent .
    make_set(j);
    if(!visited[j])
    {
        dfs(j);
        cnnct_cmpnt++;
    }

    }

    int m=(int) edges.size();
    sort(edges.begin(),edges.end(),comp);
    int c=0,i=0;
    while(c<=n-1 && i<m)
    {
     int a=find_set(edges[i].u);
     int b=find_set(edges[i].v);
     if(a!=b)
        {
      union_sets(a,b);
      c++;
      mn_cost+=edges[i].weight;
        }
     i++;
    }
    ///if connected component is more than 1 i.e. means it is not possible to rebuild.
    cout<<"Case "<<t<<": ";
    if(cnnct_cmpnt==1)
    cout<<(tot_cst-mn_cost)<<endl;
    else cout<<"-1"<<endl;

     }
return 0;

}
