/// Number Theory + MST - Minimum Spanning Tree (MST) -Kruskal's Algorithm.
/// It is better when the number of edges are comparatively less.
/// It is also mandatory algorithm regarding MST for disconnected graph as in that case prim's algo will not work.
/// Time-0.110 s

/// Classical Problem 

#include<bits/stdc++.h>

using namespace std;

const int mx=10001;
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
     cin>>tc;
     int n,U,V,m;
     for(t=1;t<=tc;t++)
     {
     cin>>n>>E>>airport_cst;
     edges.clear();
      m=n;
     int id=0;
    int cst,tot_cst=0;
    while(E--)
    {
        cin>>U>>V>>cst;
        Edge e;
        e.u=U;
        e.v=V;
        e.weight=(cst);
        edges.push_back(e);
    }

    int m=(int) edges.size();
    sort(edges.begin(),edges.end(),comp);

    initialize(n);
    int i=0;
    /// if road cost is bigger than an airportcost
    /// then, it is better to build an airport to u or v.
    /// so,we will proceed till edge[i].weight is below airport_cst.Other towns will be treated as airport
    while( i<m && edges[i].weight<airport_cst)
    {
     int a=find_set(edges[i].u);
     int b=find_set(edges[i].v);
     if(a!=b)
        {
      union_sets(a,b);
      tot_cst+=edges[i].weight;
        }
     i++;
    }
     int cnnctd_cmpnt=0;
    for(i=1; i<=n; i++)
    {
        if(parent[i]==i) cnnctd_cmpnt++;
    }
    /// cnnctd_cmpnt , hold different airports
    int total_min_cst=(cnnctd_cmpnt*airport_cst)+tot_cst;
    /// tot_cst for making roads and (cnnctd_cmpnt*airport_cst) for building airports.
    cout<<"Case #"<<t<<": ";
    cout<<total_min_cst<<" "<<cnnctd_cmpnt<<endl;
     }
return 0;

}
