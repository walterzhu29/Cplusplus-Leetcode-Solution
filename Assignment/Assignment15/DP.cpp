//Q1
//mat[i][j] += max(mat[i][j - 1], mat[i - 1][j - 1], mat[i + 1][j - 1]);
int maxAmountOfGold(vector<vector<int>>& mat) {
	int row = mat.size();
	if(!row)
		return 0;
	int col = mat[0].size();
	if(!col)
		return 0;
	int result = 0;
	for(int j = 0; j < col; j++) {
		for(int i = 0; i < row; i++) {
			int left, leftUp, leftDown;
			if(j == 0) {
				left = 0;
				leftUp = 0;
				leftDown = 0;
			}
			else {
				left = mat[i][j - 1];
				leftUp = i == 0 ? 0 : mat[i - 1][j - 1];
				leftDown = i == row - 1 ? 0 : mat[i + 1][j - 1];
			}
			mat[i][j] += max(left, max(leftUp, leftDown));
			result = mat[i][j] > result ? mat[i][j] : result;
		}
	}
	return result;
}

//Q2
int maxSum(vector<vector<int>>& mat) {
	int row = mat.size();
	if(!row)
		return 0;
	int col = mat[0].size();
	if(!col)
		return 0;
	int result = 0;
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			int up, upLeft, upRight;
			if(i == 0) {
				up = 0; 
				upLeft = 0;
				upRight = 0;
			}
			else {
				up = mat[i - 1][j];
				upLeft = j == 0 ? 0 : mat[i - 1][j - 1];
				upRight = j == col - 1 ? 0 : mat[i - 1][j + 1];
			}
			mat[i][j] += max(up, max(upLeft, upRight));
			result = mat[i][j] > result ? mat[i][j] : result;
		}
	}
	return result;
}

//Q3
//when string1[x-1] == string2[y-1] == string3[z-1]， DP[x][y][z] = DP[x - 1][y - 1][z - 1] + 1；
//otherwise, DP[x][y][z] = max(DP[x - 1][y][z], DP[x][y - 1][z], DP[x][y][z - 1]);
int longestSubSequence(string& str1, string& str2, string& str3) {
	int size1 = str1.size(), size2 = str2.size(), size3 = str3.size();
	vector<vector<vector<int>>> DP(size1 + 1, vector<vector<int>>(size2 + 1, vector<int>(size3 + 1, 0)));
	for(int x = 1; x <= size1; x++) {
		for(int y = 1; y <= size2; y++) {
			for(int z = 1; z <= size3; z++) {
				if(str1[x - 1] == str2[y - 1] && str2[y - 1] == str3[z - 1]) {
                    cout<<str1[x]<<endl;
                    DP[x][y][z] = DP[x - 1][y - 1][z - 1] + 1;
                }   
            else
				    DP[x][y][z] = max(DP[x - 1][y][z], max(DP[x][y -1][z], DP[x][y][z - 1]));
			}
		}
	}
	return DP[size1][size2][size3];
}

//Q4
int maxSumOfPair(int k, vector<int>& nums) {
	int len = nums.size();
	if(!len)
		return 0;
	//first we sort this array to descending 
	sort(nums.begin(), nums.end(), [](int a, int b){
		return a > b;
	});
	//traversal array
	int result = 0;
	for(int i = 0; i < len - 1; i++) {
		if(nums[i] - nums[i + 1] < k) {
			result += nums[i] + nums[i++ + 1];
		}
	}
	return result;
}

//Q5
//downgrade version of Q3
int longestCommonSubstring(string str1, string str2) {
	int len1 = str1.size(), len2 = str2.size();
	if(!len1 || !len2)
		return 0;
	vector<vector<int>> DP(len1 + 1, vector<int>(len2 + 1, 0));
	int result = 0;
	for(int i = 1; i <= len1; i++) {
		for(int j = 1; j <= len2; j++) {
			if(str1[i  - 1] == str2[j - 1])
				DP[i][j] = DP[i - 1][j - 1] + 1;
			result = max(DP[i][j], result);
		}
	}
	return result;
}

//Q6
//I solve this problem after I solve Q10, because I think they are similar.
int maxPrice(vector<int>& nums) {
	int len = nums.size();
	if(!len)
		return 0;
	vector<int> DP(len + 1, 0);
	for(int i = 1; i < len; i++) {
		for(int j = i; j <= len; j++) {   
			DP[j] = max(DP[j - i] + nums[i - 1], DP[j]);
		}
	}
	return DP[len];
}

//Q7
//DP[i] represents the minimun steps cost from 0 to position i
//DP[i] = min(DP[j]) + 1, where j = from 0 to i - 1 and nums[j] + j >= i;
int minSteps(vector<int>& nums) {
	int len = nums.size();
	if(!len)
		return -1;
	vector<int> DP(len, INT_MAX);
	DP[0] = 0;
	for(int i = 1; i < len; i++) {
		if(nums[i] != 0) {
			for(int j = i - 1; j >= 0; j--) {
				if(nums[j] + j >= i) {
					DP[i] = min(DP[i], DP[j] + 1);
				}
			}
		}	
	}
	if(DP[len - 1] == INT_MAX)
		return -1;
	else
		return DP[len - 1];
}

//Q8
//DP[i] represents the largest sum of subarray which end by number nums[i];
//if we have new number from array, let's say nums[i]
//and we have an other value prevSum = DP[i - 1] represents the previous sum of the prefix before position i;
//if nums[i] + prevSum < nums[i], which means we don't need previous prefix, so that DP[i] = nums[i]
//otherwise, DP[i] = nums[i] + prevSum;
//during the process, we can just use a single value currSum to instead of DP[i]
int maxSumOfSubarray(vector<int>& nums) {
	int len = nums.size();
	if(!len)
		return 0;
	int prevSum = 0, currSum = 0, result = INT_MIN;
	for(int i: nums) {
		if(prevSum + i < i) {
			currSum = i;
		}
		else {
			currSum = prevSum + i;
		}
		result = max(currSum, result);
		prevSum = currSum;
	}
	return result;
}

//Q9
//we can solve this problem by dynamic programming in O(N^2) time
//and also we can improve this algorithm to O(NlogN) with binary seach
int bs(vector<int>& nums, int n) {
	int len = nums.size();
	if(!len || n < nums[0])
		return 0;
	if(n > nums[len - 1])
		return len;
	int start = 0, end = len - 1;
	while(start + 1 < end) {
		int mid = start + (end - start) / 2;
		if(nums[mid] == n)
			return mid;
		else if(nums[mid] > n)
			end = mid;
		else 
			start = mid;
	}
	if(nums[start] == n)
		return start;
	if(nums[end] == n)
		return end;
	if(nums[start] > n)
		return start;	
	else 
		return end;
}
int LIS(vector<int>& nums) {
	int len = nums.size();
	if(len < 2)
		return len;
	vector<int> DP;
	for(int i: nums) {
		int index = bs(DP, i);
		if(index == DP.size())
			DP.push_back(i);
		else 
			DP[index] = i;
	}
	return DP.size();
}

//Q10
//this is an package problem, I solve this before, but I forget the solution.
int wayMakeChange(vector<int>& coins, int change) {
	if(!change)
		return 1;
	int len = coins.size();
	if(!len)
		return 0;
	vector<int> DP(0, change + 1);
	DP[0] = 1;
	for(int i: coins) {
		for(int j = i; j <= change; j++)
			DP[j] += DP[j - i];
	}
	return DP[change];
}
























