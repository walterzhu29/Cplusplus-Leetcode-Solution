struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//Q1
void levelOrder(TreeNode* root){
	if(!root)
		return NULL:
	queue<TreeNode*> Q;
	Q.push(root);
	while(!Q.empty()){
		int len = Q.size();
		for(int i = 0; i < len; i++){
			TreeNode* curr = Q.front();
			Q.pop();
			cout<<curr->val<<" ";
			if(curr->left)
				Q.push(curr->left);
			if(curr->right)
				Q.push(curr->right);
		}
		cout<<endl;
	}
}

//Q2
void spiralOrder(TreeNode* root){
	if(!root)
		return NULL;
	queue<TreeNode*> Q;
	Q.push(root);
	//true = from left to end, otherwise false;
	bool order = false;
	while(!Q.empty()){
		int len = Q.size();
		vector<int> printer;
		for(int i = 0; i < len; i++){
			TreeNode* curr = Q.front();
			Q.pop();			
			printer.push_back(curr->val);
			if(curr->left)
				Q.push(curr->left);
			if(curr->right)
				Q.push(curr->right);
		}
		if(order)
		{
			for(int i: printer)
				cout<<i<<" ";
			cout<<endl;
		}
		else{
			for(int i = printer.size() - 1; i >= 0; i--)
				cout<<printer[i]<<" ";
			cout<<endl;
		}
		order = !order;
	}
}

//Q3
void preorderTraversal(TreeNode* root){
	stack<TreeNode*> S;
	S.push(root);
	while(!S.empty()){
		TreeNode* curr = S.top();
		S.pop();
		cout<<curr->val<<endl;
		if(curr->right)
			S.push(curr->right);
		if(curr->left)
			S.push(curr->left);
	}
}

void inorderTraversal(TreeNode* root){
	if(!root)
		return;
	stack<TreeNode*> S;
	TreeNode* curr = root;
	while(curr || !S.empty()){
		while(curr){
			S.push(curr);
			curr = curr->left;
		}
		curr = S.top();
		S.pop();
		cout<<curr->val<<endl;
		curr = curr->right;
	}
}

void postorderTraversal(TreeNode* root){
	if(!root)
		return;
	stack<TreeNode*> S;
	TreeNode* curr = root, *prev = NULL;
	while(curr){
		S.push(curr);
		curr = curr->left;
	}
	while(!S.empty()){
		curr = S.top();
		S.pop();
		if(!curr->right || prev == curr->right){
			cout<<curr->val<<endl;
			prev = curr;
		}
		else{
			S.push(curr);
			curr = curr->right;
			while(curr){
				S.push(curr);
				curr = curr->left;
			}
		}
	}
}

//Q4
int findHeight(TreeNode* root){
	if(!root)
		return 0;
	int l = findHeight(root->left);
	int r = findHeight(root->right);
	return l > r ? l + 1 : r + 1;
}

//Q5
TreeNode* findLCA(TreeNode* root, int n1, int n2){
	if(!root)
		return NULL;
	TreeNode* lResult = findLCA(root->left, n1, n2);
	TreeNode* rResult = findLCA(root->right, n1, n2);
	if(root->val == n1 || root->val == n2 || (lResult && rResult))	
		return root;
	return lResult ? lResult : rResult;
}




















