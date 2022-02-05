# 图的最短路——Dijkstra

```c++
#include <bits/stdc++.h>
using namespace std;

struct node
{
    int data,w;
};//u->v的长度为w  【node[u].data=v,node[u].w=w】


#define MAXN 10010
vector<node> G[MAXN];
int nv,ne,s;

int dist[MAXN];//到s点的距离
int collected[MAXN];//是否被收录

```

```c++
//每次找未被收录的dist最小
//①遍历找法
int findMin(){
    int minDist=INT_MAX,minId=-1;
    for(int i=0;i<nv;i++){
        if(!collected[i] && dist[i]<minDist){//未收录的dist最小
            minDist=dist[i];
            minId=i;
        }
    }
    return minId;
}

void Dijstra(){
    //dist[]初始化为极大值,dist[s]=0
    fill(dist,dist+MAXN,INT_MAX);
    dist[s]=0;

    while(1){
        int minId=findMin();
        if(minId==-1) return;//找不到最小->返回
        collected[minId]=1;
        for(int i=0;i<G[minId].size();i++){
            int v=G[minId][i].data;
            if(!collected[v]){//未被收录的邻接点
                if(dist[minId]+G[minId][i].w<dist[v])//注意dist[]和G[][]的索引不同
                    dist[v]=dist[minId]+G[minId][i].w;
            }
        }
    }

}
```

```c++
//②堆优化
struct node
{
    int data,w;
    //运算符重构->与sort()的cmp函数作用正好“相反”->cmp:从大到小,bool:w小的优先级高
    friend bool operator < (const node &n1,const node &n2){
        return n1.w>n2.w;
    }
};

priority_queue<node> h;//dist优先队列

void Dijstra(){
    //dist[]初始化为极大值,dist[s]=0
    fill(dist,dist+MAXN,INT_MAX);
    dist[s]=0;
    h.push(node{s,0});
    while(!h.empty()){
        node minNode=h.top();
        h.pop();
        if(collected[minNode.data]) continue;//一个结点可能更新多次,也就被push多次
        collected[minNode.data]=1;
        
        for(int i=0;i<G[minNode.data].size();i++){
            int v=G[minNode.data][i].data;
            int w=G[minNode.data][i].w;
            if(!collected[v]){//未被收录的邻接点
                if(dist[v]>minNode.w+w){
                    dist[v]=minNode.w+w;
                    h.push(node{v,minNode.w+w});//每次push的就是未被收录且已更新的邻接点
                }
            }
        }
    }
}

```

