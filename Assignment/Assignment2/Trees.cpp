struct TreeNode{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int v): val(v), left(NULL), right(NULL) {}
};
//Q1
bool isBST(TreeNode* root, int& minValue, int& maxValue){
	if(!root)
		return true;
	//in some case a node->val = INT_MIN or INT_MAX
	if(!root->left && !root->right) {
		minValue = root->val;
		maxValue = root->val;
	    return true;
	}
	int lminV, lmaxV, rminV, rmaxV; 
	bool lR = isBST(root->left, lminV, lmaxV);
	bool rR = isBST(root->right, rminV, rmaxV);
	bool cR = false;
	if(!root->left && rR && root->val < rminV) {
		minValue = root->val;
		maxValue = rmaxV;
		cR = true;
	}
	else if(!root->right && lR && root->val > lmaxV) {
		maxValue = root->val;
		minValue = lminV;
		cR = true;
	}
	else if(lR && rR && root->val < rminV && root->val > lmaxV) {
		minValue = lminV;
		maxValue = rmaxV;
		cR = true;
	}
	return cR;
}

//Q2
bool isBalanced(TreeNode* root, int& depth){
	if(!root)
		return true;
	int lDepth = 0, rDepth = 0;
	bool lB = isBalanced(root->left, lDepth);
	bool rB = isBalanced(root->right, rDepth);
	++depth += lDepth > rDepth ? lDepth : rDepth;
	return abs(lDepth - rDepth) < 2 && lB && rB;
}

//Q3
int diameterOfBinaryTree(TreeNode* root, int& depth){
	if(!root)
		return 0;
	int lDepth = 0, rDepth = 0;
	int lResult = diameterOfBinaryTree(root->left, lDepth);
	int rResult = diameterOfBinaryTree(root->right, rDepth);
	++depth += lDepth > rDepth ? lDepth : rDepth;
	return max(lDepth + rDepth, max(lResult, rResult)) + 1;
}

//Q4
void helper(TreeNode* root, int num, int& sum){
	if(!root)
		return;
	num += root->val;
	if(!root->left && !root->right){
		sum += num;
		return;
	}
	helper(root->left, num * 10, sum);
	helper(root->right, num * 10, sum);
}
int sumNumbers(TreeNode* root){
	if(!root)
		return 0;
	int sum = 0;
	helper(root, 0, sum);
	return sum;
}

//Q5
TreeNode* mostLeftLeaf(TreeNode* root){
	if(!root)
		return NULL;
	while(root->left){
		root = root->left;
	}
	return root;
}
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p){
	if(!root)
		return NULL;
	if(root == p)
		return mostLeftLeaf(root->right);
	if(p->right)
		return mostLeftLeaf(p->right);
	//return NULL if p is the most right leaf
	TreeNode* parent = NULL;
	while(root->left != p && root->right != p){
		if(root->val < p->val)
			root = root->right;
		else{
			parent = root;
			root = root->left;
		}
	}
	if(root->left == p){
		return root;
	}
	return parent;
}

//Q6
bool isSameTree(TreeNode* p, TreeNode* q){
	if(!p && !q)
		return true;
	if(!p || !q)
		return false;
	return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

//Q7
void helper(TreeNode* root, TreeNode* p, TreeNode** result, int& signal){
	if(signal == 2)
		return;
	if(!root)
		return;
	helper(root->left, p, result, signal);
	if(signal == 1){
		signal = 2;
		*result = root;
	}
	if(root == p)
		signal = 1;
	helper(root->right, p, result, signal);
}
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p){
	TreeNode* store = NULL;
	TreeNode** result = &store;
	int signal = 0;
	helper(root, p, result, signal);
	return *result;
}
























