/// MST - Minimum Spanning Tree (MST) -Kruskal's Algorithm.
/// Time-0.130s

#include<bits/stdc++.h>

using namespace std;

const int mx=101;
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

bool comp1(Edge a,Edge b)
{
    return (a.weight>b.weight);
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
     int tc;
     cin>>tc;
     for(int t=1;t<=tc;t++)
     {

    edges.clear();
    int n,U,V;

    cin>>n;

    long long mn_cost=0,mx_cost=0,cst;

    for (int j=0; j<=n; j++)
    {
    ///initially setting,node itself is its parent .
    make_set(j);
    }
    while(cin>>U>>V>>cst)
    {
        if(U==0 && V==0 && cst==0) break;
        Edge e;
        e.u=U;
        e.v=V;
        e.weight=cst;
        edges.push_back(e);
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
    for (int j=0; j<=n; j++)
    {
    ///initially setting,node itself is its parent .
    make_set(j);
    }
    sort(edges.begin(),edges.end(),comp1);
    c=0,i=0;
     while(c<=n-1 && i<m)
    {
     int a=find_set(edges[i].u);
     int b=find_set(edges[i].v);
     if(a!=b)
        {
      union_sets(a,b);
      c++;
      mx_cost+=edges[i].weight;
        }
     i++;
    }
    long long tot=mx_cost+mn_cost;
    cout<<"Case "<<t<<": ";
    if(tot%2==0)
    cout<<(tot/2)<<endl;
    else cout<<(tot)<<"/2"<<endl;
     }
return 0;

}
