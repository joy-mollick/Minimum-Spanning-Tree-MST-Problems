/// Number Theory + MST - Minimum Spanning Tree (MST) -Kruskal's Algorithm.
/// It is better when the number of edges are comparatively less.
/// It is also mandatory algorithm regarding MST for disconnected graph as in that case prim's algo will not work.
/// Time-0.190 s

#include<bits/stdc++.h>

using namespace std;

map<string,int>mapping;

const int mx=401;
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
     string str,str1,str2;
     int tc,E;
     int n,U,V,m;
     while(cin>>n>>E)
     {
     if((n==0&&E==0)) break;
     edges.clear();
     mapping.clear();
      m=n;
     int id=0;
     while(m--)
     {
         cin>>str;
         if(mapping[str]==0)
         {
             id++;
             mapping[str]=id;
         }
     }
    int cst,tot_cst=0;
    while(E--)
    {
        cin>>str1>>str2>>cst;
        U=mapping[str1];
        V=mapping[str2];
        Edge e;
        e.u=U;
        e.v=V;
        e.weight=(cst);
        edges.push_back(e);
    }
    cin>>str;
    int start=mapping[str];

    for (int j=1; j<=n; j++)
    {
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
      tot_cst+=edges[i].weight;
      c++;
        }
     i++;
    }

    if(c==n-1)
    cout<<(tot_cst)<<endl;
    else cout<<"Impossible"<<endl;
     }
return 0;

}
