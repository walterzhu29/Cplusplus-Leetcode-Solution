//Q1
int searchInsert(vector<int>& nums, int target) {
    if(nums.size() == 0)
        return 0;
    int start = 0, end = nums.size() - 1;
    while(start + 1 < end) {
        int mid = start + (end - start) / 2;
        if(nums[mid] == target)
            return mid;
        else if(nums[mid] < target)
            start = mid;
        else 
            end = mid;
    }
    if(nums[start] >= target)
        return start;
    else if(nums[end] < target)
        return end + 1;
    else
        return end;  
}

//Q2
bool increasingTriplet(vector<int>& nums) {
    int n1 = INT_MAX, n2 = INT_MAX;
    for(int i: nums) {
        if(i <= n1)
            n1 = i;
        else if(i <= n2)
            n2 = i;
        else 
            return true;
    }
    return false;
}

//Q3
//this is the same question on leetcode:
//https://leetcode.com/problems/range-sum-query-2d-immutable/description/
//so you can run this code easier
class NumMatrix {
private:
    vector<vector<int>> sum;
public:
    NumMatrix(vector<vector<int>> matrix) {
        if(matrix.size() == 0 || matrix[0].size() == 0)
            return;
        for(int i = 0; i < matrix.size(); i++) {
            vector<int> builder;
            for(int j = 0; j < matrix[i].size(); j++) {
                int temp = matrix[i][j];
                if(i >= 1)
                    temp += sum[i - 1][j];
                if(j >= 1)
                    temp += builder[j - 1];
                if(i >= 1 && j >= 1)
                    temp -= sum[i - 1][j - 1];
                builder.push_back(temp);
            }
            sum.push_back(builder);
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int result = sum[row2][col2];
        if(row1 >= 1)
            result -= sum[row1 - 1][col2];
        if(col1 >= 1)
            result -= sum[row2][col1 - 1];
        if(row1 >= 1 && col1 >= 1)
            result += sum[row1 - 1][col1 - 1];
        return result;
    }
};

//Q4
//use dfs + memoization
int longestIncreasingPath(vector<vector<int>>& matrix) {
    if(matrix.size() == 0 || matrix[0].size() == 0)
        return 0;
    int result = INT_MIN;
    unordered_map<int, int> hash;
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[i].size(); j++) {
            result = max(result, dfs(matrix, i, j, hash, LONG_MIN));
        }
    }
    return result;
}
int dfs(vector<vector<int>>& matrix, int i, int j, unordered_map<int, int>& hash, long last) {
    int row = matrix.size(), col = matrix[0].size();
    if(i < 0 || j < 0 || i >= row || j >= col || matrix[i][j] <= last)
        return 0;
    if(hash[i * col + j])
        return hash[i * col + j];
    int result = dfs(matrix, i - 1, j, hash, matrix[i][j]);
    result = max(result, dfs(matrix, i + 1, j, hash, matrix[i][j]));
    result = max(result, dfs(matrix, i, j - 1, hash, matrix[i][j]));
    result = max(result, dfs(matrix, i, j + 1, hash, matrix[i][j]));
    hash[i * col + j] = result + 1;
    return hash[i * col + j];
}


//Q5
int minPathSum(vector<vector<int>>& grid) {
    int row = grid.size();
    if(!row)
        return 0;
    int col = grid[0].size();
    if(!col)
        return 0;
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if(!i && !j)
                continue;
            grid[i][j] += min( j == 0 ? INT_MAX : grid[i][j - 1], i == 0 ? INT_MAX : grid[i - 1][j]);
        }
    }
    return grid[row - 1][col - 1];
}

//Q6
//DFS
bool exist(vector<vector<char>>& board, string word) {
    int row = board.size();
    if(!row || word.size() == 0)
        return false;
    int col = board[0].size();
    if(!col)
        return false;
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if(dfs(board, word, i, j, 0))
                return true;
        }
    }
    return false;
}
bool dfs(vector<vector<char>>& board, string& word, int i, int j, int poi) {
    int row = board.size();
    if(!row)
        return false;
    int col = board[0].size();
    if(!col)
        return false;
    if(i < 0 || j < 0 || i >= row || j >= col || board[i][j] != word[poi] || board[i][j] == '0')
        return false;
    if(poi == word.size() - 1)
        return true;
    char temp = board[i][j];
    board[i][j] = '0';
    if(dfs(board, word, i - 1, j, poi + 1) 
       || dfs(board, word, i + 1, j, poi + 1) 
       || dfs(board, word, i, j - 1, poi + 1) 
       || dfs(board, word, i, j + 1, poi + 1))
        return true;
    board[i][j] = temp;
    return false;
}

//Q7
//use dynamic programming to solve this problem
//dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1]));
//dp[i][j] represent the width of the largest square which the right bottom corner is at [i][j]
int maximalSquare(vector<vector<char>>& matrix) {
    int row = matrix.size();
    if(!row)
        return 0;
    int col = matrix[0].size();
    if(!col)
        return 0;
    int result = 0;
    vector<vector<int>> dp(row, vector<int>(col, 0));
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if(i != 0 && j != 0)
                dp[i][j] += min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1]));
            if(matrix[i][j] == '1')
                dp[i][j]++;
            else
                dp[i][j] = 0;
            result = max(result, dp[i][j]);
        }
    }
    return result * result;
}

//Q8
//this question is like the upgrade question of Largest Rectangle in Histogram
int maximalRectangle(vector<vector<char>>& matrix) {
    int row = matrix.size();
    if(!row)
        return 0;
    int col = matrix[0].size();
    if(!col)
        return 0;
    int result = INT_MIN;
    vector<vector<int>> h(row, vector<int>(col, 0));
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if(matrix[i][j] == '1') {
                h[i][j] = 1;
                if(i != 0)
                    h[i][j] += h[i - 1][j];
            }  
        }
        result = max(result, largestRectangleArea(h[i]));
    }
    return result;
}
int largestRectangleArea(vector<int>& heights) {
    int len = heights.size();
    stack<pair<int, int>> S;
    int result = INT_MIN;
    for(int i = 0; i <= len; i++) {
        int h = i == len ? -1 : heights[i];
        if(!S.empty() && S.top().second >= h) {
            pair<int, int> curr = S.top();
            S.pop();
            int start = S.empty() ? -1 : S.top().first;
            int area = (i - start - 1) * curr.second;
            result = area > result ? area : result;
            i--;
        }
        else
            S.push(pair<int, int>(i, h));
    }
    return result;
}

//Q9
//DFS
void solve(vector<vector<char>>& board) {
    int row = board.size();
    if(!row)
        return;
    int col = board[0].size();
    if(!col)
        return;
    for(int i = 0; i < col; i++) {
        dfs(board, 0, i);
        dfs(board, row - 1, i);
    }
    for(int i = 1; i < row - 1; i++) {
        dfs(board, i, 0);
        dfs(board, i, col - 1);
    }
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if(board[i][j] == 'O')
                board[i][j] = 'X';
            else if(board[i][j] == 'a')
                board[i][j] = 'O';
        }
    }
}
void dfs(vector<vector<char>>& board, int i, int j) {
    int row = board.size();
    if(!row)
        return;
    int col = board[0].size();
    if(!col)
        return;
    if(i < 0 || j < 0 || i >= row || j >= col || board[i][j] != 'O')
        return;
    board[i][j] = 'a';
    dfs(board, i - 1, j);
    dfs(board, i + 1, j);
    dfs(board, i, j - 1);
    dfs(board, i, j + 1);
}

//Q10
//do two time find length of longest increasing subsquence
//first from 0 to n - 1, second from n - 1 to 0
//we use a nlogn algorithm (binary search and dp) to find out length of LIS
int binarySearch(int target, vector<int>& nums) {
    int len = nums.size();
    if(!len || target <= nums[0])
        return 0;
    if(target > nums[len - 1])
        return len;
    int start = 0, end = len - 1;
    while(start + 1 < end) {
        int mid = start + (end - start) / 2;
        if(nums[mid] == target)
            return mid;
        else if(nums[mid] > target)
            end = mid;
        else
            start = mid;
    }
    if(nums[start] == target)
        return start;
    return end;
}
int lengthOfLBS(vector<int>& nums) {
	int len = nums.size();
	if(!len)
		return 0;
	vector<int> fromLeft(len, 0);
	vector<int> fromRight(len, 0);
	vector<int> dp;
	//fill fromLeft
	for(int i = 0; i < len; i++) {
        int index = binarySearch(nums[i], dp);
        if(index >= (int) dp.size())
            dp.push_back(nums[i]);
        else
            dp[index] = nums[i];
		fromLeft[i] = index + 1;
    }
	//fill fromRight
	dp.clear();
	for(int i = len - 1; i >= 0; i--) {
		int index = binarySearch(nums[i], dp);
		if(index >= (int) dp.size())
            dp.push_back(nums[i]);
        else
            dp[index] = nums[i];
		fromRight[i] = index + 1;
	}
	//calculate result
	int result = INT_MIN;
	for(int i = 0; i < len; i++) {
		result = max(result, fromLeft[i] + fromRight[i] + 1);
	}
	return result;
}


//Q11
//do traversal, we use a value ones record how many times 1 appear before current position
//for example if ones = -1 at position i, which means times(0) = times(1) + 1 before i;
//if then we use hash map record (ones, index) pair, if the key already exist in hash map
//which mean the subarray between this two index is exactly what we want.
int findMaxLength(vector<int>& nums) {
    int len = nums.size();
    if(!len)
        return 0;
    unordered_map<int, int> hash;
    hash[0] = 0;
    int last = 0;
    int ones = 0;
    int result = 0;
    for(int i = 0; i <= len; i++) {
        ones += last;
        if(hash.find(ones) != hash.end()) {
            result = max(result, i - hash[ones]);
        }
        else {
            hash[ones] = i;
        }
        if(i == len)
            break;
        else {
            last = nums[i] == 0 ? -1 : 1;
        }
    }
    return result;
}

//Q12
//this is a really hard question, I read the solution on geeks4geeks and understand it now
//but seriously I'm not sure if I can solve its variations
int maxIndexDiff(vector<int>& nums) {
	int len = nums.size();
	if(len == 0)
		return 0;
	int min = INT_MAX;
	vector<int> ls;
	vector<int> rg(len, 0);
	for(int i: nums) {
		min = min > i ? i : min;
		ls.push_back(min);
	}
	int max = INT_MIN;
	for(int i = len - 1; i >= 0; i--) {
		max = max < nums[i] ? nums[i] : max;
		rg[i] = max;
	}
	int i = 0, j = 0;
	int result = -1;
	while(i < len && j < len) {
		if(ls[i] < rg[j]) {
			result = j - i > result ? j - i : result;
			j++;
		}
		else
			i++;
	}
	return result;
}

//Q13
//O(n) time O(n) space
int maxProfit(vector<int>& prices) {
    int len = prices.size();
    if(!len)
        return 0;
    vector<int> leftMax(len, 0);
    vector<int> rightMax(len, 0);
    int lMin = prices[0];
    for(int i = 1; i < len; i++) {
        if(lMin > prices[i])
            lMin = prices[i];
        leftMax[i] = max(leftMax[i - 1], prices[i] - lMin);
        cout<<leftMax[i]<<" ";
    }
    cout<<endl;
    int rMax = prices[len - 1];
    for(int i = len - 2; i >= 0; i--) {
        if(rMax < prices[i])
            rMax = prices[i];
        rightMax[i] = max(rightMax[i + 1], rMax - prices[i]);
        cout<<rightMax[i]<<" ";
    }
    cout<<endl;
    int maxProfit = INT_MIN;
    for(int i = 0; i < len; i++) {
        maxProfit = max(leftMax[i] + rightMax[i], maxProfit);
    }
    return maxProfit;
}
//O(n) time O(1) space
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

























































