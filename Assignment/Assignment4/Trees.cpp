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
TreeNode* helper(vector<int>& preorder, unordered_map<int, int>& inorderHash, int start1, int end1, int start2, int end2) {
	if(start1 > end1)
		return NULL;
	TreeNode* curr = new TreeNode(preorder[start1]);
	if(start1 == end1)
		return curr;
	int index = inorderHash[curr->val];
	curr->left = helper(preorder, inorderHash, start1 + 1, start1 + (index - start2), start2, index - 1);
	curr->right = helper(preorder, inorderHash, start1 + (index - start2) + 1, end1, index + 1, end2);
	return curr;
}
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
	int len = inorder.size();
	if(len == 0 || preorder.size() == 0)
		return NULL;
	unordered_map<int, int> inorderHash;
	for(int i = 0; i < len; i++) {
		inorderHash[inorder[i]] = i;
	}
	TreeNode* head = helper(preorder, inorderHash, 0, len - 1, 0, len - 1);
	return head;
}

//Q3
//for exapmle, a tree like:
/*
        1
	   / 
	  2   
	 / \
	4   5
*/
//will be serialized in a string by 
//level-order traversal and separated by a single space: [1 2 null 4 5]
//enserialize
string serialize(TreeNode* root) {
	if(!root)
		return "";
	vector<string> srlz;
	queue<TreeNode*> Q;
	Q.push(root);
	while(!Q.empty()) {
		TreeNode* curr = Q.front();
		Q.pop();
		if(!curr) {
			srlz.push_back("null");
			continue;
		}
		else {
			srlz.push_back(std::to_string(curr->val));
			Q.push(curr->left);
			Q.push(curr->right);
		}
	}
	//remove the extra nulls from srlz;
	while(srlz.back() == "null") {
		srlz.pop_back();
	}
	//build string 
	string result;
	for(auto str: srlz) {
		result += str + " ";
	}
	result.pop_back();
	return result;
}
//deserialize
TreeNode* deserialize(string data) {
	stringstream ss(data);
	string builder;
	vector<string> tree;
	//separate string 
	while(ss>>builder) {
		tree.push_back(builder);
	}
	if(tree.size() == 0 || tree[0] == "null")
		return NULL;
	TreeNode* root = new TreeNode(atoi(tree[0].c_str()));
	queue<TreeNode*> Q;
	Q.push(root);
	//indicate if curr node is the right child of its parent node
	bool isRight = false;
	for(int i = 1; i < tree.size(); i++) {
		//get a new string represent a node
		if(tree[i] != "null") {
			TreeNode* curr = new TreeNode(atoi(tree[i].c_str()));
			if(isRight) {
				Q.front()->right = curr;
			}
			else {
				Q.front()->left = curr;
			}
			Q.push(curr);
		}
		if(isRight)
			Q.pop();
		isRight = !isRight;
	}
	return root;
}

//Q4
//if a current node is smaller than lower boundry, return its right child part (maybe need modify)
//if a current node is greater than upper boundry, return its left child part (also this part may need modify)
//otherwise check both its left and right child
TreeNode* removeOutsideNodes(TreeNode* root, int min, int max) {
	if(!root)
		return NULL;
	if(root->val < min) {
		return removeOutsideNodes(root->right, min, max);
	}
	else if(root-val > max) {
		return removeOoutsideNodes(root->left, min, max);
	}
	else {
		root->left = removeOutsideNodes(root->left, min, max);
		root->right = removeOutsideNodes(root->right, min, max);
		return root;
	}
}

//Q5
void connect(TreeNode *root) {
	if(!root)
		return;
	TreeNode* nextLevelDummy = new TreeNode(0);
	TreeNode* cBuilder = root;
	TreeNode* nBuilder = nextLevelDummy;
	while(cBuilder) {
		if(cBuilder->left) {
			nBuilder->next = cBuilder->left;
			nBuilder = nBuilder->next;
		}
		if(cBuilder->right) {
			nBuilder->next = cBuilder->right;
			nBuilder = nBuilder->next;
		}
		cBuilder = cBuilder->next;
		if(!cBuilder) {
			cBuilder = nextLevelDummy->next;
			nBuilder = nextLevelDummy;
			nBuilder->next = NULL;
		}
	}
}



































