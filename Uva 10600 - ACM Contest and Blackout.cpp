/// Number Theory + MST - Minimum Spanning Tree (MST) -Kruskal's Algorithm.
/// It is better when the number of edges are comparatively less.
/// It is also mandatory algorithm regarding MST for disconnected graph as in that case prim's algo will not work.
/// Time-0.190 s

#include<bits/stdc++.h>

using namespace std;

const int mx=101;
/// a structure of an edge u-v and its weight.

struct Edge
{
    int u, v;
    int weight;
};
vector<Edge>edges;
vector<Edge>mst;
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
     int tc,E;
     cin>>tc;
     int n,U,V,m;
     while(tc--)
     {
     cin>>n>>E;
     edges.clear();
     mst.clear();
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

    int c=0,i=0;
    while(c<=n-1 && i<m)
    {
     int a=find_set(edges[i].u);
     int b=find_set(edges[i].v);
     if(a!=b)
        {
      union_sets(a,b);
      tot_cst+=edges[i].weight;
      mst.push_back(edges[i]);
      c++;
        }
     i++;
    }

///the edges of mst tree has been stored.
///second mst and mst will differ by only one edge.
///iterate over all mst tree edges and skip each edge.
///And check the minimum one.

         int second_mst=INT_MAX;
        ///iterate over each edge of mst.
        for(int i=0;i<mst.size();i++)
        {
            initialize(n);
            int cnt=0;
            int sec_mst=0;
            for(int j=0;j<m;j++)
            {
                ///ignore each ith edge and check.
                if(mst[i].u==edges[j].u&&mst[i].v==edges[j].v) continue;
                int u=edges[j].u,v=edges[j].v;
                int a=find_set(u);
                int b=find_set(v);
                if(a!=b)
                {  /// acyclic
                    sec_mst+=edges[j].weight;
                    union_sets(a,b);
                    cnt++;
                }
                ///this is that one.
                ///when n-1 edges have been added.
                if(cnt==n-1)
                {
                    second_mst =min(sec_mst,second_mst);
                    break;
                }
            }
        }

        cout<<tot_cst<<" "<<second_mst<<endl;

     }
return 0;

}
