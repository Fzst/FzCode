class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> st;
        int ans = 1;    
        while(root != nullptr || !st.empty()){
            while(root != nullptr){
            st.push(root);
            root = root->left;
            }
            
            root = st.top();
            st.pop();
            if(ans++ == k)
                return root->val;
    
            root = root->right;
        }
        return -1;
    }
};