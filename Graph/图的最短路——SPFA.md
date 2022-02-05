# 图的最短路——SPFA算法

```c++
#include <bits/stdc++.h>
using namespace std;

struct node
{
    int v,w;
};
int nv,ne,s;
#define maxn 100010
vector<node> G[maxn];

queue<int> q;
int dist[maxn];//到源点距离
int inq[maxn];//是否在队中,肯定不能搜索,直接打表
int num[maxn];//入队几次,判断是否有负值圈

```

每次更新结点的路径长度，就**可能影响其邻接点的路径长度**，

因此**每更新一次就必须保证其邻接点之后也会被判断一次**

```c++
bool SPFA(int s){
    fill(dist,dist+maxn,INT_MAX);
    dist[s]=0;
    q.push(s),inq[s]=1,num[s]++;
    while(!q.empty()){
        int u=q.front();
        q.pop(),inq[u]=0;
        for(int j=0;j<G[u].size();j++){//所有边
            int v=G[u][j].v;
            int w=G[u][j].w;
            if(dist[v]>dist[u]+w){
                dist[v]=dist[u]+w;
                //更新了v,则v的邻接点也有更新的可能,如不在队中,则重新入队
                if(inq[v]==0){
                    q.push(v),inq[v]=1,num[v]++;
                    //重新入队后,num[v]++,可能超过nv
                    if(num[v] >= nv) return false;
                }
            }
        }
    }
    return true;//无负值圈
}
```

