# 最短路Dijkstra算法——pair+堆优化

```c++
//基本逻辑
#include <bits/stdc++.h>
using namespace std;
int n,m;
int s1,s2;        //起点、终点
#define maxn 520
int s[maxn][maxn];//距离s【边权】

int main(){
    cin>>n>>m;
//1.初始化距离s为INT_MAX
    int v1,v2,v_length;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) s[i][j]=INT_MAX;
    }
//2.读入边和边权
    for(int i=0;i<m;i++){
        cin>>v1>>v2>>v_length;
        s[v1][v2]=v_length,s[v2][v1]=v_length;
    }

    cin>>s1>>s2;
    s_dijkstra();
    sPrintL(s2);

    return 0;
}
```

```c++
//pair+堆优化的dijkstra算法
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >min_heap;
////greater<>:小根堆,less<>:大根堆
////pair优先比较first
int s_dist[maxn],s_path[maxn],collected[maxn];
void s_dijkstra(){
    fill(s_dist,s_dist+n,INT_MAX);
    fill(collected,collected+n,0);
    s_dist[s1]=0,s_path[s1]=-1;
    min_heap.push(make_pair(0,s1));
    while(!min_heap.empty()){
        int minId=min_heap.top().second;
        int minS=min_heap.top().first;
        min_heap.pop();
        if(collected[minId]) continue;//在被收录前可能被进堆两次
        collected[minId]=1;
        for(int i=0;i<n;i++){
            if(collected[i]==0 && s[minId][i]!=INT_MAX){//未访问的邻接点
                if(s_dist[i]>minS+s[minId][i]){//更新距离
                    s_dist[i] = minS + s[minId][i];
                    s_path[i] = minId;
                    min_heap.push(make_pair(s_dist[i],i));
                }
            }
        }
    }
}
```

```c++
//打印最短路径:递归出的是逆序,要正向打印用个容器存一下
vector<int> res_Spath;
void sPrintL(int root){
    if(root==-1) return;
    res_Spath.push_back(root);
    sPrintL(s_path[root]);
}
```

