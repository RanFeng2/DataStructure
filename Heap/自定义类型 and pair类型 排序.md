# 自定义类型/pair类型 排序

最优路径不唯一时，如何判断第二标尺？

1. **自定义类型——运算符重载**

```c++
struct node{
    int data,w,t;
    friend bool operator < (const node &a,const node &b){//小根堆
        if(a.w!=b.w) return a.w>b.w;
        else         return a.t>b.t;
    }
};
priority_queue<node> min_heap;
```

2. **pair类型——仿函数**

==比较一个key的大小==【一个标尺】

```c++
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >min_heap;
//greater<> ,less<> 是std中实现的两个仿函数
```

==比较两个key的大小==【两个标尺】

```c++
struct cmp{
    bool operator () (pair<int,int> a, pair<int,int> b){
        //假设first存的是距离,second存的是id,t[]里存的是时间
        if(a.first!=b.first) return a.first>b.first;
        else                 return t[a.second]>t[b.second];
    }
};
priority_queue<pair<int,int>,vector<pair<int,int> >,cmp> min_heap;
```



参考文献：https://blog.csdn.net/weixin_36888577/article/details/79937886