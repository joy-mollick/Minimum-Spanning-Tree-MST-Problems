/// MST - Minimum Spanning Tree (MST) -Prim's Algorithm.
/// Classical MST Algorithm.

#include<bits/stdc++.h>

using namespace std;

const int mx=101;

bool visited[mx]={false};

typedef pair<double,int> pii;
typedef pair<double,double> PI;

map<PI,int>mapping;
map<int,PI>iddd;

double mst_cost=0.0;

vector<pii>adj[mx];

priority_queue< pii,vector<pii>,greater<pii> >pq;

/// from x node ,we will start run over the tree

void prim(int x)
{
    int y;
    pii p;
    pq.push(make_pair(0.0, x));
    while(!pq.empty())
    {
        ///Select the edge with minimum weight from minimum heap
        p = pq.top();
        pq.pop();
        x = p.second;

        ///Checking for cycle ,it means cycle.
        if(visited[x] == true)
            continue;

        mst_cost += p.first;
        visited[x] = true;

        for(int i=0; i<adj[x].size(); ++i)
        {
            y = adj[x][i].second;
            ///which has not been fixed yet,push them into queue.
            if(visited[y] == false)
                pq.push(adj[x][i]);
        }

    }

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int tc;
    cin>>tc;

    for(int t=1;t<=tc;t++){

    for(int j=0;j<mx;j++)
    {
        adj[j].clear();
        visited[j]=false;
    }
    mapping.clear();
    iddd.clear();
    mst_cost=0.0;

    int n;
    cin>>n;
    double cst,u,v;

    int id=1;

    while(n--)
    {
        cin>>u>>v;
        PI p=make_pair(u,v);
        if(mapping[p]==0)
        {
            mapping[p]=id;
            iddd[id]=p;
            id++;
        }
    }

    for(int i=1;i<id;i++)
    {
        for(int j=1;j<id;j++)
        {
            if(i!=j)
            {
                double x1=iddd[i].first;
                double x2=iddd[j].first;
                double y1=iddd[i].second;
                double y2=iddd[j].second;
                cst=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
                adj[i].push_back(make_pair(cst,j));
                adj[j].push_back(make_pair(cst,i));
            }
        }
    }

    prim(1);
    printf("%0.02f\n",mst_cost);
    if(t!=tc) printf("\n");

    }

}
