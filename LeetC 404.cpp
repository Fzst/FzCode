/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


int sumOfLeftLeaves(struct TreeNode* root){
    int sum = 0;
    if(root == NULL) return 0;
    if(root->left){
        if(root->left->left == NULL && root->left->right == NULL)
            sum = root->left->val;
        else
            sum = sumOfLeftLeaves(root->left);
    }
    sum = sum+sumOfLeftLeaves(root->right);
    return sum;

    
    
}
