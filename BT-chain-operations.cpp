#include <iostream>
#include <queue>
#include <stack>
using namespace std;
//定义
struct node
{
    int data;
    node* lchild;
    node* rchild;
};

//新建结点
node* newNode(int v){
    node* t=new node;
    t->data=v;
    t->lchild=NULL;
    t->rchild=NULL;
    return t;
}

//插入结点(二叉搜索树)
node* Insert(node* root,int x){
    if(root==NULL){
        root=newNode(x);
    }else{
        if(root->data>x){
            root->lchild=Insert(root->lchild,x);
        }else{
            root->rchild=Insert(root->rchild,x);
        }
    }
    return root;
}

//建树
node* CreateT(int data[],int n){
    node* root=NULL;
    for(int i=0;i<n;i++){
        root=Insert(root,data[i]);
    }
    return root;
}

//递归前序
void prePrintT(node* root){

    if(root){
        printf("%d",root->data);
        prePrintT(root->lchild);
        prePrintT(root->rchild);
    }
}

//递归中序
void inPrintT(node* root){

    if(root){
        inPrintT(root->lchild);
        printf("%d",root->data);
        inPrintT(root->rchild);
    }
}

//层序
void LevelOrderTraversal(node* root){
    if(!root) return;
    queue<node*> q;
    q.push(root);
    while(!q.empty()){
        node* tmp=q.front();
        q.pop();
        printf("%d",tmp->data);
        if(tmp->lchild) q.push(tmp->lchild);
        if(tmp->rchild) q.push(tmp->rchild);
    }
}

//非递归中序
void inOrderTraversal(node* root){
    node* t=root;
    stack<node*> s;
    while(t || !s.empty()){
        while(t){
            s.push(t);
            t=t->lchild;
        }
        if(!s.empty()){
            t=s.top();
            s.pop();
            printf("%d",t->data);//左子树,自己,右子树
            t=t->rchild;
        }
    }
}

//非递归前序
void preOrderTraversal(node* root){
    node* t=root;
    stack<node*> s;
    while(!s.empty() || t){
        while(t){
            printf("%d",t->data);
            s.push(t);
            t=t->lchild;
        }
        if(!s.empty()){
            t=s.top();
            s.pop();
            t=t->rchild;
        }
    }
}

//求二叉树高度
int GetHeight(node* root){
    if(!root) return 0;
    else{
        int LH=GetHeight(root->lchild);
        int RH=GetHeight(root->rchild);
        return max(LH,RH)+1;
    }
}

//由先序(后序,层序)和中序建树
node* BuildT(int*pre,int*in,int preL,int preR,int inL,int inR){
    if(preL>preR){
        return NULL;
    }
    node* root=new node;
    root->data=pre[preL];
    //因为只有中序是左右子树分开的,通过中序知道左子树有多少个结点[左-结点-右]
    //但如果只有中序,不知道哪个是根结点
    int k;
    for(k=inL;k<=inR;k++){
        if(in[k]==pre[preL]) break;
    }
    int numLeft=k-inL;//左子树结点个数(不含根结点)

    //通过先序知道左右子树分别是哪些结点[结点-左-右]
    root->lchild=BuildT(pre,in,preL+1,preL+numLeft,inL,k-1);
    root->rchild=BuildT(pre,in,preL+numLeft+1,preR,k+1,inR);
    //pre:左子树[preL+1,preL+numLeft],共numLeft个结点
    //pre:右子树[preL+numLeft+1,preR]
    return root;
}

//查找结点(递归式无返回)
void SearchT(node* root,int x){
    if(root==NULL){
        return;
    }
    if(root->data==x){
        printf("%d is Found\n",root->data);
    }
    SearchT(root->lchild,x);
    SearchT(root->rchild,x);   
}

//查找结点(递归式有返回)(二叉搜索树)
node* SearchBT(node* root,int x){
    if(root==NULL){
        return NULL;
    }
    if(root->data==x){
        return root;
    }else if(root->data>x){
        return SearchBT(root->lchild,x);//每次return保证找到之后不再递归
    }else{
        return SearchBT(root->rchild,x);
    }   
}

//查找结点(循环式有返回)(二叉搜索树)
node* SearchTBT(node* root,int x){
   node* Troot=root;//函数内部可以修改指针的指向
   while(Troot){
       if(Troot->data==x){
           return Troot;
       }else if(Troot->data>x){
           Troot=Troot->lchild;
       }else{
           Troot=Troot->rchild;
       }
   }
}

node* FindMax(node* root){
    while(!root->rchild){
        root=root->rchild;
    }
    return root;
}
node* deleteT(node* root,int x){
    if(root->data>x){
            root->lchild=deleteT(root->lchild,x);
    }else if(root->data<x){
            root->rchild=deleteT(root->rchild,x);
    }else{
        if(root->lchild && root->rchild){
            //两个孩子
            node* tmp=FindMax(root->lchild);
            root->data=tmp->data;
            root->lchild=deleteT(root->lchild,tmp->data);
        }else{
            //一个孩子或无孩子
            node* tmp=root;
            if(!root->lchild)      root=root->rchild;
            else if(!root->rchild) root=root->lchild;
            delete tmp;
        }
    }
    return root;
}

int main(){
    //1:建树
    int n=7;
    int data[7];//9 3 7 6 4 8 2
    for(int i=0;i<n;i++){
        cin>>data[i];
    }
    node* T=CreateT(data,n);
    //2:遍历
    inPrintT(T);               printf("\n");
    inOrderTraversal(T);       printf("\n");
    prePrintT(T);              printf("\n");
    preOrderTraversal(T);      printf("\n");
    LevelOrderTraversal(T);    printf("\n");
    //3:求树高
    int height=GetHeight(T);   printf("%d\n",height);//5
    //4:前序中序还原树
    int pre[]={9,3,2,7,6,4,8};int in[]={2,3,4,6,7,8,9};
    node* T1=BuildT(pre,in,0,6,0,6);
    LevelOrderTraversal(T1);   printf("\n");
    //5:查找树
    SearchT(T,6);
    node* SBT=SearchBT(T,6);   printf("%d is Found.\n",SBT->data);
    node* STBT=SearchTBT(T,6); printf("%d is Found.\n",STBT->data);
    //6:删除树结点
    node* DT=deleteT(T,6);
    LevelOrderTraversal(DT);   printf("\n");
return 0;
}
