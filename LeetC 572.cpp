#include<iostream>
#include<cstdlib>
#include<cstdio> 
using namespace std;

typedef struct BiNode{
	char data;
	struct BiNode *Lchild,*Rchild;
}BiNode,*BiTree;

void Creat_Tree(BiTree *root){
	char ch;
	scanf("%c",&ch);
	if(ch == '#')
		*root = NULL;
	else{
		*root = (BiTree)malloc(sizeof(BiNode));
		(*root)->data = ch;
		Creat_Tree(&(*root)->Lchild);
		Creat_Tree(&(*root)->Rchild);
	}
}
bool Same_Tree( BiTree p,BiTree q){
	if(p == NULL&&q == NULL)
		return true;
	if(p == NULL&&q != NULL)
		return false;
    if(p != NULL&&q == NULL)
        return false;
	if(p->data != q->data)
		return false;
	return Same_Tree(p->Lchild,q->Lchild)&&Same_Tree(p->Rchild,q->Rchild);
}
bool Sub_Tree(BiTree p, BiTree q){
	if(p == NULL&&q == NULL)
		return true;
	if(p == NULL&&q != NULL)
		return false;
    if(p != NULL&&q == NULL)
        return false;
	return Same_Tree(p,q)||Sub_Tree(p->Lchild,q)||Sub_Tree(p->Rchild,q); 

}
int main(){
	BiTree root;
	BiTree root1; 
	printf("请输入主树：\n");
	Creat_Tree(&root);
	printf("请输入要判断的子树：\n");
	getchar(); 
	Creat_Tree(&root1);
	cout<<boolalpha<<Sub_Tree(root,root1);
	return 0;
}
