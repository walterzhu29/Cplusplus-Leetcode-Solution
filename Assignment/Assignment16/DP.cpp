//Q1
//we need another matrix DP
//DP[i][j] represent the size of the square which the right-bottom located at (i , j)
//the DP function will be DP[i][j] = min(DP[i - 1][j], DP[i][j - 1], DP[i - 1][j - 1]) + 1;
int maxSize(vector<vector<int>>& mat) {
	int rows = mat.size();
	if(!rows)
		return 0;
	int cols = mat[0].size();
	if(!cols)
		return 0;
	vector<vector<int>> DP(rows, vector<int>(cols, 0));
	//inits
	for(int i = 0; i < rows; i++) {
		DP[i][0] = mat[i][0];
	}
	for(int i = 0; i < cols; i++) {
		DP[0][i] = mat[0][i];
	}
	//
	int result = 0;
	for(int i = 1; i < rows; i++) {
		for(int j = 1; j < cols; j++) {
			if(mat[i][j] == 1)
				DP[i][j] = min(DP[i - 1][j], min(DP[i][j - 1], DP[i - 1][j - 1])) + 1;
			result = max(DP[i][j], result);
		}
	}
	return result;
}

//Q2
//this is the upgrade question of longest increasing subsequence
//we still need a helper array to save the position of each elements in its increasing subsequence
//so the result = max(sum[i + 1]); which 0 <= i < nums.size();
//so the running time will be O(NlogN)
int binarySearch(vector<int>& nums, int n) {
	int len = nums.size();
	if(!len || n <= nums[0])
		return 0;
	if(n > nums[len - 1])
		return len;
	int start = 0, end = len - 1;
	while(start + 1 < end) {
		int mid = start + (end - start) / 2;
		if(nums[mid] == n)
			return mid;
		else if(nums[mid] > n)
			end  = mid;
		else 
			start = mid;
	}
	if(nums[start] >= n)
		return start;
	return end;
}
int maxSumOfLIS(vector<int>& nums) {
	int len = nums.size();
	if(!len)
		return 0;
	vector<int> DP;
	vector<int> sum(1, 0);
	int result = 0;
	for(int i: nums) {
		int index = binarySearch(DP, i);
		if(index == DP.size())
			DP.push_back(i);
		else 
			DP[index] = i;
		if(index >= sum.size() - 1)
			sum.push_back(sum.back() + i);
		else
			sum[index + 1] = sum[index] + i;
		result = max(sum[index + 1], result);
	}
	return result;
}

//Q4
//say we have two arrays: f and g;
//f[i] represent the maximum sum if we select the element at position i
//g[i] represent the maximnm sum if we donot select the element at position i
//then f[i] = max(g[i - 2] + nums[i - 1] + nums[i], g[i - 1] + nums[i]);
//g[i] = max(f[i - 1], g[i - 1]);
int maxSum(vector<int>& nums) {
	int len = nums.size();
	if(len < 3) {
		int sum = 0;
		for(int i: nums)
			sum += i;
		return sum;
	}
	//init
	vector<int> f = {nums[0], nums[0] + nums[1]};
	vector<int> g = {0, nums[0]};
	//DP
	for(int i = 2; i < len; i++) {
		f[i] = max(g[i - 2] + nums[i - 1] + nums[i], g[i - 1] + nums[i]);
		g[i] = max(f[i - 1], g[i - 1]);
	}
	return g[len - 1] > f[len - 1] ? g[len - 1] : f[len - 1];
}

//Q5
//we need use a hash map to help us solve this question.
//hash[n] represent the size of the subsequence that we are looking for.
//for a giving number n, hash[n] = max(hash[n - 1], hash[n + 1]) + 1.
//g[i] = max(f[i - 1], g[i - 1]);
int maxSum(vector<int>& nums) {
	int len = nums.size();
	if(!len)
		return 0;
	unordered_map<int, int> hash;
	int result = 1;
	for(int i: nums)
	{
		int curr = 1;
		if(hash.find(i - 1) != hash.end() || hash.find(i + 1) != hash.end()) {
			if(hash.find(i - 1) != hash.end())
				curr = hash[i - 1] + 1;
			if(hash.find(i + 1) != hash.end())
				curr = max(curr, hash[i + 1] + 1);
		}
		hash[i] = max(curr, hash[i]);
		result = max(hash[i], result);
	}
	return result;
}

//Q6
//I take a lot of time on this question
//The first solution comes out from my brain is DFS or trie
//And I confirmed my method by check geeks4geeks
bool helper(string& str, unordered_set<string>& hash) {
	int len = str.size();
	if(!len || hash.find(str) != hash.end())
		return true;
	for(int i = 1; i < len; i++) {
		string prefix = str.substr(0, i);
		if(hash.find(prefix) != hash.end()) {
			string postfix = str.substr(i);
			if(helper(postfix, hash))
				return true;
		}	
	}
	return false;
}
bool wordBreak(string str, vector<string>& dictionary) {
	int len = str.size();
	if(!len)
		return true;
	unordered_set<string> hash;
	for(auto a: dictionary)
		hash.insert(a);
	return helper(str, hash);
}


//Q7
//DP[i] represent the decode ways at location i
//say giving a number nums[i] from array nums
//if nums[i] is valid, dp[i] += dp[i - 1]
//if nums[i - 1] nums[i] is valid (for example 12 represent L), dp[i] += dp[i - 2]
//and we dont even use a helper array, just use two values to instead of dp[i - 1] and dp[i - 2]
bool isValid(char cha) {
	return cha != '0';
}
bool isValid(char cha1, char cha2) {
	if(cha1 == '0') {
		return false;
	}
	string str = "";
	str += cha1;
	str += cha2;
	int num = atoi(str.c_str());
	if(num > 26)
		return false;
	return true;
}
int decodeWays(string str) {
	int len = str.size();
	if(!len)
		return 1;
	int dp1 = 1;
	int dp2 = 1;
	for(int i = 1; i < len; i++) {
		int curr = 0;
		if(isValid(str[i]))
			curr += dp1;
		if(isValid(str[i - 1], str[i]))
			curr += dp2;
		dp2 = dp1;
		dp1 = curr;
	}
	return dp1;
}

//Q8
//buy2 and sell2 depend on sell1
int maxProfit(vector<int>& prices) {
    int buy1 = INT_MIN, buy2 = INT_MIN, sell1 = 0, sell2 = 0;
    for(int i: prices) {
        buy1 = max(buy1, -i);
        sell1 = max(sell1, buy1 + i);
        buy2 = max(buy2, sell1 - i);
        sell2 = max(sell2, buy2 + i);
    }
    return sell2;
}













































































