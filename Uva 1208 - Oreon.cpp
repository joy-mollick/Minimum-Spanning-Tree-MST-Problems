/// Number Theory + MST - Minimum Spanning Tree (MST) -Kruskal's Algorithm.
/// It is better when the number of edges are comparatively less.
/// It is also mandatory algorithm regarding MST for disconnected graph as in that case prim's algo will not work.
/// Time-0.130s

#include<bits/stdc++.h>

using namespace std;

const int mx=130;
/// a structure of an edge u-v and its weight.
/// co-ordinates.
int dist[mx][mx];

struct Edge
{
    int u, v;
    double weight;
};
vector<Edge>edges;
vector<Edge>ans;
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
     ios_base::sync_with_stdio(false);
     int tc,E,airport_cst,t=1;
     int n,U,V;
     double r;
     cin>>tc;
     for(t=1;t<=tc;t++)
     {
     edges.clear();
     ans.clear();
     cin>>n;
     int min_cst=0;
     char dummy;
     for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(j==n-1)
                    cin>>dist[i][j];
                else
               cin>>dist[i][j]>>dummy;
              /// an edge will be counted once.
               if (i<j && dist[i][j] != 0)
               {
                   Edge e;
                   e.u=i;
                   e.v=j;
                   e.weight=dist[i][j];
                   edges.push_back(e);
               }
            }
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
      ans.push_back(edges[i]);
        }
     i++;
    }

    cout<<"Case "<<t<<":"<<endl;
    for(int l=0;l<(int)ans.size();l++)
    {
      cout<<(char)(ans[l].u+'A')<<"-"<<(char)(ans[l].v+'A')<<" "<<ans[l].weight<<endl;
    }

     }
return 0;

}
