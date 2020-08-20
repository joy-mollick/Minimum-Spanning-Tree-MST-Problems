///Tarjan Algorithm + MST
///By using Tarjan,we can find critical bridges which will be found in every MST.
///By using MST,we can find minimum cost and replacable edge also.


#include<bits/stdc++.h>

using namespace std;

const int mx=1000001;

#define pii pair<int,int>

vector<pii>adj[mx];/// adjacency matrix
bool visited[mx]={false};/// visited or not ??
int disc[mx]={0};/// dfs time finding,dfs number of a node
int low[mx]={0};/// low dfs time for purpose to find a cycle
int par[mx]={-1};/// -1 holds for Null
int id;

map<pii,int>extra;
map<int,string>ans;

struct Edge
{
    int u, v;
    int weight;
    int id;
};
vector<Edge>edges;
vector<Edge>graph_edge[mx];
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

void apu_finding(int u)
{
    ///this parameter will be used for counting discovery time of a node
    static int time=0;
    ///for marking a node
    visited[u]=true;
    ///keeping dfs(discovery) time and low discovery time
    disc[u]=low[u]=time++;
    vector<pii>::iterator it;
    ///iterator to iterate adjacency matrix of graph
    for(it=adj[u].begin();it!=adj[u].end();it++)
    {
    ///neighbour's node of v from u, u->v
        int v=(*it).first;
    ///if not visited ,then proceed apu_finding for new node(v)
        if(!visited[v])
        {
            par[v]=u;
            apu_finding(v);
    ///this is for finding low dfs number of a node
        low[u]=min(low[u],low[v]);
  /// when low[v]>disc[u] ,this u-v is the critical edges
        if(low[v]>disc[u])
        {
            id=(*it).second;
            if(extra[make_pair(u,v)]==1)
            ans[id]="any";
        }

        }
/// this means that, visited[v] is true i.e. already v is visited
/// if u's parent is not v,then this is a back edge , u-v .so we will take low[] time from disc[] time of v
        else if(v!=par[u])
        {
            low[u]=min(low[u],disc[v]);
        }
    }

}

  int main()
 {
    int tc,E,cst,t=0;
    int n,V,u,v,K,M;

    cin>>V>>E;
    int tot=0;
    n=V;
    for(int i=1;i<=E;i++)
    {
        scanf("%d%d%d",&u,&v,&cst);
        /// we will store edges according to its weight
        Edge e;
        e.u=u;
        e.v=v;
        e.weight=cst;
        e.id=i;
        edges.push_back(e);
        graph_edge[cst].push_back(e);
    }

    initialize(V);
   for(int w=1;w<mx;w++)
   {
       for(int j=0;j<graph_edge[w].size();j++)
       {
           u=graph_edge[w][j].u;
           v=graph_edge[w][j].v;
           int id=graph_edge[w][j].id;
           int a=find_set(u);
           int b=find_set(v);
           /// it is a edge to form cycle.
           /// so,it will not be in mst ever.
           if(a==b)
           {
               ans[id]="none";
           }
           /// different set,so take it.
           /// these all edges will be used to make all mst,if mst is not unique
           /// these edges will be available into different mst.
           else
           {

               if(extra.find(make_pair(a,b))==extra.end())
               {
                   ans[id]="at least one";
                   extra[make_pair(a,b)]=1;
                   extra[make_pair(b,a)]=1;
               }
               else
               {
                   ans[id]="at least one";
                   extra[make_pair(a,b)]=2;
                   extra[make_pair(b,a)]=2;
               }
               adj[a].push_back(make_pair(b,id));
               adj[b].push_back(make_pair(a,id));
           }
       }
       /// merge all edges with the same weight.
       for(int k=0;k<graph_edge[w].size();k++)
       {
           u=graph_edge[w][k].u;
           v=graph_edge[w][k].v;
           int a=find_set(u);
           int b=find_set(v);
           union_sets(a,b);
       }
   }

   for(int x=1;x<=V;x++)
   {
       if(!visited[x]) apu_finding(x);
   }

   for(int i=0;i<E;i++)
   {
      cout<<ans[edges[i].id]<<endl;
   }
 return 0;
}
