struct node {
	int val;
	node* left;
	node* right;
	node(int v): val(v), left(NULL), right(NULL) {}	
};

//Q1
node* dummy = new node(0);
node* builder = dummy;
void helper(node* root) {
	if(root == NULL)
		return;
	helper(root->left);
	builder->right = root;
	root->left = builder;
	builder = root;
	helper(root->right);
}
node* convertBTtoDLL(node* root) {
	helper(root);
	return dummy->right;
}

//Q2
int treeSum(node* root) {
	if(!root)
		return 0;
	int self = root->val;
	int sum = treeSum(root->left) + treeSum(root->right);
	root->val = sum;
	return self + sum;
}

//Q3
void helper(node* root, int& sum) {
	if(!root)
		return;
	helper(root->right, sum);
	root->val += sum;
	sum = root->val;
	helper(root->left, sum);
}
void convertBST(node* root) {
	int sum = 0;
	helper(root, sum);
}


//Q4
int getDepth(node* root) {
	if(!root)
		return 0;
	int lD = getDepth(root->left);
	int rD = getDepth(root->right);
	return lD > rD ? lD + 1 : rD + 1;
}
void print2Array(node* root, vector<vector<string>>& result, int depth, int poi) {
	if(!root)
		return;
	result[depth][poi] = std::to_string(root->val);
	print2Array(root->left, result, depth + 1, poi - 1);
	print2Array(root->right, result, depth + 1, poi + 1);
}

void treeView(node* root) {
	if(!root)
		return;
	if(!root->left && !root->right){
		cout<<root->val<<endl;
		return;
	}
	
	//print this tree into a 2D array, which may takes O(D) space (D is the depth of the tree).
	int depth = getDepth(root);
	int num = depth * 2 - 1;
	vector<vector<string>> tree(depth, vector<string>(num, " "));
	print2Array(root, tree, 0, (num - 1) / 2);
	
	//print top view
	for(int j = 0; j < tree[0].size(); j++) {
		for(int i = 0; i < tree.size(); i++) {
			if(tree[i][j] != " ") {
				cout<<tree[i][j]<<" ";
				break;
			}
		}
	}
	cout<<endl;
	//print bottom view
	for(int j = 0; j < tree[0].size(); j++) {
		for(int i = tree.size() - 1; i >= 0; i--) {
			if(tree[i][j] != " ") {
				cout<<tree[i][j]<<" ";
				break;
			}
		}
	}
	cout<<endl;
	//print left view
	for(int i = 0; i < tree.size(); i++) {
		for(int j = 0; j < tree[0].size(); j++) {
			if(tree[i][j] != " ") {
				cout<<tree[i][j]<<" ";
				break;
			}
		}
	}
	cout<<endl;
	//print right view
	for(int i = 0; i < tree.size(); i++) {
		for(int j = tree[0].size() - 1; j >= 0; j--) {
			if(tree[i][j] != " ") {
				cout<<tree[i][j]<<" ";
				break;
			}
		}
	}
	cout<<endl;
}

//Q5
void kDistanceSet(TreeNode* root, int k, vector<int>& result) {
	if(!root)
		return;
	if(!k) {
		result.push_back(root->val);
		return;
	}
	kDistanceSet(root->left, k - 1, result);
	kDistanceSet(root->right, k - 1, result);
}
void printKdistance(TreeNode *root, int k) {
	if(!root || k <= 0)
		return;
	vector<int> fromRoot;
	//find out all child nodes which at k distance from current node;
	//if these child nodes exsit, print em.
	kDistanceSet(root, k, fromRoot);
	if(fromRoot.size() > 0) {
		for(auto i: fromRoot) {
			cout<<root->val<<" "<<i<<endl;
		}
	}
	//find out all note pairs at k distance and the paths between these pairs go through current node.
	for(int i = 1, j = k - 1; i < k && j > 0; i++, j--) {
		vector<int> leftSet;
		vector<int> rightSet;
		kDistanceSet(root->left, i - 1, leftSet);
		kDistanceSet(root->right, j - 1, rightSet);
		//print
		if(leftSet.size() > 0 && rightSet.size() > 0) {
			for(auto l: leftSet) {
				for(auto r: rightSet) {
					cout<<l<<" "<<r<<endl;
				}
			}
		}
	}
	printKdistance(root->left, k);
	printKdistance(root->right, k);
}

//Q6
void helper(node* root, vector<int> builder, vector<vector<int>>& result) {
	if(!root)
		return;
	builder.push_back(root->val);
	if(!root->left && !root->right) {
		result.push_back(builder);
		return;
	}
	helper(root->left, builder, result);
	helper(root->right, builder, result);
}
void printPath(node* root) {
	if(!root)
		return;
	vector<vector<int>> result;
	vector<int> builder;
	helper(root, builder, result);
	for(auto i: result) {
		for(auto j: i) {
			cout<<j<<" ";
		}
		cout<<endl;
	}
}

//Q7
void searchRange(node* root, int k1, int k2) {
	if(!root)
		return;
	searchRange(root->left, k1, k2);
	if(root->val >= k1 && root->val <= k2)
		cout<<root->val<<" ";
	searchRange(root->right, k1, k2);
}

//Q8
//the same question on leetcode required solving this in constant space and do not change the structure
//find out two nodes
TreeNode* prev = new TreeNode(INT_MIN);
void helper(TreeNode* root, vector<TreeNode*>& twoNodes) {
	if(!root)
		return;
	helper(root->left, twoNodes);
	if(twoNodes[0] == NULL && prev->val > root->val)
		twoNodes[0] = prev;
	if(twoNodes[0] != NULL && prev->val > root->val)
		twoNodes[1] = root;
	prev = root;
	helper(root->right, twoNodes);
}
void recoverTree(TreeNode* root) {
    if(!root)
        return;
    vector<TreeNode*> twoNodes(2, NULL);
	helper(root, twoNodes);
    if(twoNodes[0] == NULL)
        return;
    int temp = twoNodes[0]->val;
    twoNodes[0]->val = twoNodes[1]->val;
    twoNodes[1]->val = temp;
}















