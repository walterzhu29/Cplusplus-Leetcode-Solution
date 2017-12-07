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
	builder = root;
	helper(root->right);
}
node* convertBTtoDLL(node* root) {
	helper(root);
	node* move = dummy->right;
	while(move && move->right) {
		move->right->left = move;
		move = move->right;
	}
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
vector<vector<string>> tree22DArray(node* root) {
	if(!root)
		return vector<vector<string>>(); 
	int depth = getDepth(root);
	int num = depth * 2 - 1;
	vector<vector<string>> result(depth, vector<string>(num, " "));
	print2Array(root, result, 0, (num - 1) / 2);
	return result;
}
void treeView(node* root) {
	if(!root)
		return;
	if(!root->left && !root->right){
		cout<<root->val<<endl;
		return;
	}
	vector<vector<string>> tree = tree22DArray(root);
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
	kDistanceSet(root, k, fromRoot);
	if(fromRoot.size() > 0) {
		for(auto i: fromRoot) {
			cout<<root->val<<" "<<i<<endl;
		}
	}
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
//return the smallest node which val < v
TreeNode* searchGreater(TreeNode* root, int v) {
	if (!root)
		return NULL;
	TreeNode* lR = searchGreater(root->left, v);
	TreeNode* rR = searchGreater(root->right, v);
	TreeNode* result = NULL;
	if (root->val > v)
		result = root;
	if ((lR && result && lR->val > result->val) || !result)
		result = lR;
	if ((rR && result && rR->val > result->val) || !result)
		result = rR;
	return result;
}
//return the greatest node which val > v
TreeNode* searchSmaller(TreeNode* root, int v) {
	if (!root)
		return NULL;
	TreeNode* lR = searchSmaller(root->left, v);
	TreeNode* rR = searchSmaller(root->right, v);
	TreeNode* result = NULL;
	if (root->val < v)
		result = root;
	if ((lR && result && lR->val < result->val) || !result)
		result = lR;
	if ((rR && result && rR->val < result->val) || !result)
		result = rR;
	return result;
}
//find out two nodes
vector<TreeNode*> helper(TreeNode* root) {
    vector<TreeNode*> result;
    if(!root)
        return result;
    TreeNode* lR = searchGreater(root->left, root->val);
    TreeNode* rR = searchSmaller(root->right, root->val);
    if(lR || rR) {
        if(lR) {
            result.push_back(lR);
            if(!rR)
                result.push_back(root);
        }
        if(rR) {
            result.push_back(rR);
            if(!lR)
                result.push_back(root);
        }
        return result;
    }
    result = helper(root->left);
    if(result.size() > 0)
        return result;
    return helper(root->right);
}
void recoverTree(TreeNode* root) {
    if(!root)
        return;
    vector<TreeNode*> twoNodes = helper(root);
    if(twoNodes.size() < 2)
        return;
    int temp = twoNodes[0]->val;
    twoNodes[0]->val = twoNodes[1]->val;
    twoNodes[1]->val = temp;
}















