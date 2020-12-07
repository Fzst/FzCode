/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool isPD(struct TreeNode *root1,struct TreeNode *root2){
    if(root1 == NULL && root2 == NULL)
        return true;
    if(root1 == NULL || root2 == NULL)
        return false;
    return isPD(root1->left,root2->right) && (root1->val == root2->val) && isPD(root1->right,root2->left);
}
bool isSymmetric(struct TreeNode* root){
    if(root == NULL)
        return true;
    return isPD(root->left,root->right);
}