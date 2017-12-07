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
void printKdistance(Node *root, int k) {
	if(!k) {
		cout<<root->val;
	}
	
	
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



















