/*struct TreeNode* Mirror_Tree(struct TreeNode* root){
    if(root == NULL)
        return NULL;
    else{
        struct TreeNode*  temp;
        temp = root->left;
        root->left = Mirror_Tree(root->right);
        root->right = Mirror_Tree(temp);
    }
    return root;
}*/
bool Same_Tree(struct TreeNode* p,struct TreeNode*  q){
	if(p == NULL&&q == NULL)
		return true;
	if(p == NULL&&q != NULL)
		return false;
    if(p != NULL&&q == NULL)
        return false;
	if(p->val != q->val)
		return false;
	return Same_Tree(p->left,q->right)&&Same_Tree(p->right,q->left);
}
bool isSymmetric(struct TreeNode* root){
    struct TreeNode* p,*q;
    p=q=root;
    //root1 = Mirror_Tree(root);
    if(Same_Tree(p,q))
        return true;
    else
        return false;
}
