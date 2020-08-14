/// MST - Minimum Spanning Tree (MST) -Kruskal's Algorithm.
/// It is better when the number of edges are comparatively less.
/// It is also mandatory algorithm regarding MST for disconnected graph as in that case prim's algo will not work.
/// O(ElogV) Time Complexity 

#include<bits/stdc++.h>

using namespace std;

const int mx=10001;

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
Edge result[mx];

  int main()
 {
    int n,m,U,V;

    cin>>n>>m;

    Edge edges[m];

    long long cost=0;

    for (int j=1; j<=n; j++)
    {
    ///initially setting,node itself is its parent .
    make_set(j);
    }
    for(int k=0;k<m;k++)
    {
       cin>>edges[k].u>>edges[k].v>>edges[k].weight;
    }
    sort(edges,edges+m,comp);
    int c=0,i=0;
    while(c<=n-1 && i<m)
    {
     int a=find_set(edges[i].u);
     int b=find_set(edges[i].v);
     if(a!=b)
        {
      union_sets(a,b);
      /// this holds the resultant edges
      /// at most n-1 edges can remain
      result[c]=edges[i];
      c++;
      cost+=edges[i].weight;
        }
     i++;
    }
    cout<<cost<<endl;

return 0;

}
