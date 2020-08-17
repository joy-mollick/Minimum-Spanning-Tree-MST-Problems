/// Number Theory + MST - Minimum Spanning Tree (MST) -Kruskal's Algorithm.
/// It is better when the number of edges are comparatively less.
/// It is also mandatory algorithm regarding MST for disconnected graph as in that case prim's algo will not work.
/// 2^p number has p+1 dividor,after multiplying the cost will have log2(num)+1 divisors.
/// Time-80ms

#include<bits/stdc++.h>

using namespace std;

const int mx=100001;
/// a structure of an edge u-v and its weight.
struct Edge
{
    int u, v;
    int weight;
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


vector<Edge>edges;

  int main()
 {
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);
     cout.tie(NULL);

     int tc,E;
     cin>>tc;
     for(int t=1;t<=tc;t++)
     {

    edges.clear();
    int n,U,V;
    int ans=0;
    long long cst;
    cin>>n>>E;

    while(E--)
    {
        cin>>U>>V>>cst;
        Edge e;
        e.u=U;
        e.v=V;
        e.weight=(int)log2(cst);
        edges.push_back(e);
    }

    for (int j=1; j<=n; j++)
    {
    ///initially setting,node itself is its parent .
    make_set(j);
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
      ans+=edges[i].weight;
        }
     i++;
    }
    ans++;/// extra for divisor 1.
    cout<<(ans)<<'\n';
     }
return 0;

}
