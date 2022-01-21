#include <iostream>
#include <queue>
using namespace std;

//定义线性结点
#define MAXN 7
struct node
{
    int data;
    int lchild;
    int rchild;
}Node[MAXN];

//新建结点
int index=0;
int newNode(int v){
    Node[index].data=v;
    Node[index].lchild=-1;
    Node[index].rchild=-1;
    return index++;
}

//插入结点(静态二叉搜索树)[无返回,根结点位置root已经修改了]
void Insert(int &root,int x){
    if(root==-1){
        root=newNode(x);
    }else{
        if(Node[root].data>x){
            Insert(Node[root].lchild,x);
        }else{
            Insert(Node[root].rchild,x);
        }
    }
}
//插入结点(静态二叉搜索树)[返回根结点位置root]
int InsertT(int root,int x){
    if(root==-1){
        root=newNode(x);
    }else{
        if(Node[root].data>x){
            Node[root].lchild=InsertT(Node[root].lchild,x);
        }else{
            Node[root].rchild=InsertT(Node[root].rchild,x);
        }
    }
    return root;
}

//建树
int CreateT(int data[],int n){
    int root=-1;
    for(int i=0;i<n;i++){
        //Insert(root,data[i]);
        root=InsertT(root,data[i]);
    }
    return root;
}

//先序遍历,中序后序类似
void PrintT(int root){
    if(root==-1){
        return;
    }
    printf("%d",Node[root].data);
    PrintT(Node[root].lchild);
    PrintT(Node[root].rchild);
}

//层序遍历
void LevelOrderTraversal(int root){
    if(root==-1) return;
    queue<int> q;
    q.push(root);
    while(!q.empty()){
        int tmp=q.front();
        q.pop();
        printf("%d",Node[tmp].data);
        if(Node[tmp].lchild!=-1) q.push(Node[tmp].lchild);
        if(Node[tmp].rchild!=-1) q.push(Node[tmp].rchild);
    }
}

//查找(递归式有返回)[尾递归]
int Search(int root,int x){
    if(root==-1) return -1;
    if(Node[root].data==x){
        return root;
    }else if(Node[root].data>x){
        return Search(Node[root].lchild,x);
    }else{
        return Search(Node[root].rchild,x);
    }
}
//查找(循环式有返回)
int SearchT(int root,int x){
    while(root!=-1){
        if(Node[root].data==x){
            return root;
        }else if(Node[root].data>x){
            root=Node[root].lchild;
        }else{
            root=Node[root].rchild;
        }
    }
    return root;//没找到返回-1
}

int main(){
    //1:建树
    int data[7]={9,3,7,6,4,8,2};
    int root=CreateT(data,7);
    //2:遍历
    PrintT(root);                 printf("\n");
    LevelOrderTraversal(root);    printf("\n");
    //3:查找
    int pos=Search(root,4);       printf("4 is in the pos of %d\n",pos);
    int pos1=SearchT(root,6);     printf("6 is in the pos of %d\n",pos1);
    return 0;
}
