/// Number Theory + MST - Minimum Spanning Tree (MST) -Kruskal's Algorithm.
/// It is better when the number of edges are comparatively less.
/// It is also mandatory algorithm regarding MST for disconnected graph as in that case prim's algo will not work.
/// Time-0.150s

#include<bits/stdc++.h>

using namespace std;

const int mx=200001;
/// a structure of an edge u-v and its weight.

struct Edge
{
    int u, v;
    int weight;
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
    for (int j=1; j<=n; j++)
    {
    make_set(j);
    }
}

  int main()
 {
     ios_base::sync_with_stdio(false);
     int tc,E,airport_cst,t=1;
     int n,U,V,m;
     while(cin>>n>>E)
     {
     if(n==0&&E==0) break;
     edges.clear();
     int cst,tot_cst=0,min_cst=0;
     while(E--)
     {
        cin>>U>>V>>cst;
        tot_cst+=cst;
        U++;
        V++;
        Edge e;
        e.u=U;
        e.v=V;
        e.weight=(cst);
        edges.push_back(e);
    }

    int m=(int) edges.size();
    sort(edges.begin(),edges.end(),comp);

    initialize(n);
    int i=0,c=0;
    /// if road cost is bigger than an airportcost
    /// then, it is better to build an airport to u or v.
    /// so,we will proceed till edge[i].weight is below airport_cst.Other towns will be treated as airport
    while( i<m && c<=n-1)
    {
     int a=find_set(edges[i].u);
     int b=find_set(edges[i].v);
     if(a!=b)
        {
      union_sets(a,b);
      min_cst+=edges[i].weight;
      c++;
        }
     i++;
    }
    cout<<(tot_cst-min_cst)<<endl;
     }
return 0;

}
