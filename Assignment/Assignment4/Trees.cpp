//Q1
bool isBST(TreeNode* root, int& minValue, int& maxValue, int& size) {
	if(!root)
		return true;
    size++;
	if(!root->left && !root->right) {
		minValue = root->val;
		maxValue = root->val;
	    return true;
	}
	int lminV, lmaxV, rminV, rmaxV; 
	bool lR = isBST(root->left, lminV, lmaxV, size);
	bool rR = isBST(root->right, rminV, rmaxV, size);
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
int largestBSTSubtree(TreeNode* root) {
	if(!root)
		return 0;
	int selfSize = 0, minV, maxV;
	if(isBST(root, minV, maxV, selfSize))
		return selfSize;
	int leftSize = 0, rightSize = 0;
	return max(largestBSTSubtree(root->left), largestBSTSubtree(root->right));
}

//Q2
