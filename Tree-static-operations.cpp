#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//定义线性结点[需要数据域]
#define MAXN 7
struct node
{
    int data;
    vector<int> child;
    int layer;//需要知道层号才定义
}Node[MAXN];

//定义线性结点[不需要数据域,可简化]
vector<int> child1[MAXN];

int index=0;
int newNode(int v){
    Node[index].data=v;
    Node[index].child.clear();
    return index++;
}

//先序遍历
void preOrder(int root){
    if(root==-1) return;
    printf("%d",Node[root].data);
    for(int i=0;i<Node[root].child.size();i++){
        preOrder(Node[root].child[i]);
    }
}

//层序遍历
void levelOrderTraversal(int root){
    if(root==-1) return;
    queue<int> q;
    q.push(root);
    while(!q.empty()){
        int tmp=q.front();
        q.pop();
        printf("%d",Node[tmp].data);
        for(int i=0;i<Node[tmp].child.size();i++){
            q.push(Node[tmp].child[i]);
        }
    }
}

//层序遍历[需要知道层号]
void levelOrderTraversal1(int root){
    if(root==-1) return;
    queue<int> q;
    q.push(root);
    Node[root].layer=0;//根结点是第0层
    while(!q.empty()){
        int tmp=q.front();
        q.pop();
        printf("data:%d layer:%d\n",Node[tmp].data,Node[tmp].layer);
        for(int i=0;i<Node[tmp].child.size();i++){
            int tmpChild=Node[tmp].child[i];
            q.push(tmpChild);
            Node[tmpChild].layer=Node[tmp].layer+1;//子结点层号为父结点+1
        }
    }
}

int main(){
    //1:建树
    int n=7;
    int data[7]={9,3,7,6,4,8,2};
    for(int i=0;i<n;i++){
        newNode(data[i]);//更新数据域
    }
    //更新子树
    Node[0].child.push_back(1);Node[0].child.push_back(2);Node[0].child.push_back(3);
    Node[1].child.push_back(4);Node[1].child.push_back(5);
    Node[3].child.push_back(6);

    //2:遍历
    preOrder(0);                        printf("\n");
    levelOrderTraversal(0);             printf("\n");
    levelOrderTraversal1(0);            printf("\n");

    return 0;
}
