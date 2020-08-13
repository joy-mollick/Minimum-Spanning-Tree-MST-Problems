

/// MST - Minimum Spanning Tree (MST) -Prim's Algorithm.
/// Dijkstra Greedy Approach.
/// For disconnected graph, this algorithm will not work 
/// For graph with more edges , prim algo will be better.
/// Time Complexity- O((V + E)logV)

#include<bits/stdc++.h>

using namespace std;

const int mx=10001;

bool visited[mx]={false};

typedef pair<long long,int> pii;

long long mst_cost=0ll;

vector<pii>adj[mx];

priority_queue< pii,vector<pii>,greater<pii> >pq;

/// from x node ,we will start run over the tree 

void prim(int x)
{
    int y;
    pii p;
    pq.push(make_pair(0ll, x));
    while(!Q.empty())
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
            if(marked[y] == false)
                pq.push(adj[x][i]);
        }
        
    }
    
}
   
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n,m,u,v;
    cin>>n>>m;
    long long cst;
    
    while(m--)
    {
        cin>>u>>v>>cst;
        adj[u].push_back(make_pair(cst,v));
        adj[v].push_back(make_pair(cst,u));
    }
    
    prim(1);
    cout<<(mst_cost)<<endl;
    
}
