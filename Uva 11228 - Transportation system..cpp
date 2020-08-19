/// Number Theory + MST - Minimum Spanning Tree (MST) -Kruskal's Algorithm.
/// It is better when the number of edges are comparatively less.
/// It is also mandatory algorithm regarding MST for disconnected graph as in that case prim's algo will not work.
/// Time-0.130s

#include<bits/stdc++.h>

using namespace std;

const int mx=1001;
/// a structure of an edge u-v and its weight.
/// co-ordinates.
double x[mx];
double y[mx];

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
    for (int j=1; j<=n; j++)
    {
    make_set(j);
    }
}

double dis(int i,int j)
{
    return (sqrt((x[i-1]-x[j-1])*(x[i-1]-x[j-1])+(y[i-1]-y[j-1])*(y[i-1]-y[j-1])));
}

  int main()
 {
     ios_base::sync_with_stdio(false);
     int tc,E,airport_cst,t=1;
     int n,U,V;
     double r;
     cin>>tc;
     for(t=1;t<=tc;t++)
     {
     edges.clear();
     cin>>n>>r;
     int cst,tot_cst=0,min_cst=0;
     for(int k=0;k<n;k++)
     {
        cin>>x[k]>>y[k];
     }

     for(int i=1;i<=n;i++)
        {
            for(int j=i+1;j<=n;j++)
            {
                Edge e;
                e.u =i ;
                e.v = j ;
                e.weight = dis(i,j);
                edges.push_back(e);
            }
        }

    int m=(int) edges.size();
    sort(edges.begin(),edges.end(),comp);

    initialize(n);
    int i=0,state=0;
    double cst1=0.0,cst2=0.0;
    /// if road cost is bigger than an airportcost
    /// then, it is better to build an airport to u or v.
    /// so,we will proceed till edge[i].weight is below airport_cst.Other towns will be treated as airport
    while( i<m )
    {
     int a=find_set(edges[i].u);
     int b=find_set(edges[i].v);
     if(a!=b)
        {
      union_sets(a,b);
      if(edges[i].weight<=r)
      {
          cst1+=edges[i].weight;
      }
      /// another state  will be counted.
      else
      {
          cst2+=edges[i].weight;
          state++;
      }
        }
     i++;
    }
    ///base state is also counted.
    state++;
    int roads,railroads;
    roads=round(cst1);
    railroads=round(cst2);
    cout<<"Case #"<<t<<": ";
    cout<<state<<" "<<roads<<" "<<railroads<<endl;
     }
return 0;

}
