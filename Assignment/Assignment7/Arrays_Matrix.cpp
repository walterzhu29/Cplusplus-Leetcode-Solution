//Q1
//for every element in the given matrix, we search its 8 directions.
vector<pair<int, int>> searchWord(vector<string>& matrix, string word) {
	vector<pair<int, int>> result;
	if(matrix.size() == 0 || word.size() == 0)
		return result;
	for(int i = 0; i < matrix.size(); i++) {
		for(int j = 0; j < matrix[i].size(); j++) {
			if(match(matrix, i, j, word))
				result.push_back(pair<int, int>(i, j));
		}
	}
}
bool match(vector<string>& matrix, int row, int col, string word) {
	if(matrix[row][col] != word[0])
		return false;
	int dirR[] = {-1, 1, 0, 0, -1, -1, 1, 1};
	int dirC[] = {0, 0, -1, 1, -1, 1, -1, 1};
	for(int i = 0; i < 8; i++) {
		int r = row, c = col;
		for(int j = 0; j < word.size() - 1; j++) {
			r += dirR[i];
			c += dirC[i];
			if(r >= matrix.size() || r < 0 || c >= matrix[0].size() || c < 0 || matrix[r][c] != word[j + 1])
				break;
			if(j == word.size() - 2)
				return true;
		}
	}
	return false;
}
//Q2
//brute force will take O(N^2)
//so I use sliding window to solve this problem, may take O(N) time
//Solved this problem with my code first, then I changed my code because the code in geeks4geeks looks better and simplified
vector<int> findZeroes(vector<int>& arr, int m) {
	int start = 0, end = 0;
	int zeros = 0;
	int len = arr.size();
	int maxS = 0, maxE = 0;
	int maxSize = 0;
	while(end < m) {
		if(zeros <= m) {
			if(arr[end] == 0)
				zeros++;
			end++;
		}
		if(zeros > m) {
			if(arr[start] == 0)
				zeros--;
			start++;
		}
		if(end - start > maxSize) {
			maxS = start;
			maxE = end;
			maxSize = end - start;
		}
	}
	vector<int> result;
	for(int i = maxS; i < maxE; i++)
		if(arr[i] == 0)
			result.push_back(i);
	return result;
}

//Q3 
//if this is a rotated sorted array, we can use binary search;
//if it isnot a sorted array before rotated, use brute force which is O(N) time method.
//Guess you want me to search an element in a rotated sorted array. 
int search(vector<int>& nums, int target) {
    int start = 0, end = nums.size() - 1;
    int len = nums.size();
    if(len == 0)
        return -1;
    while(start + 1 < end) {
        int mid = start + (end - start) / 2;
        if(nums[mid] == target)
            return mid;
		//if mid and target locate in different parts
        if((nums[mid] > nums[len - 1] && target <= nums[len - 1]) || (nums[mid] <= nums[len - 1] && target > nums[len - 1])) {
            if(nums[mid] > target)
                start = mid;
            else
                end = mid;
        }
		//if mid and target locate in the same part
        else {
            if(nums[mid] > target)
                end = mid;
            else
                start = mid;
        }
    }
    if(nums[start] == target)
        return start;
    if(nums[end] == target)
        return end;
    return -1;
}

//Q4
//we use a deque to store these indexes that maybe the maximum element in a sliding window, 
//and keep this queue in descending order
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> result;
    deque<int> Q;
    for(int i = 0; i < nums.size(); i++) {
        while(!Q.empty() && i - k >= Q.front())
            Q.pop_front();
        while(!Q.empty() && nums[i] > nums[Q.back()])
            Q.pop_back();
        Q.push_back(i);
        if(i >= k - 1)
        	result.push_back(nums[Q.front()]);
    }
    return result;
}

//Q5
//let's say we have a function bool fetch(int& num); 
//which will return true (otherwise false) if there is next number available in the stream, 
//and also pass the value.
vector<double> movingAverage(int size) {
	vector<int> result;
	if(size == 0)
		return result;
	list<int> L;
	int val;
	double sum = 0;
	while(fetch(val)) {
		if(L.size() <= size) {
			L.push_back(val);
			sum += val;
		}
		if(L.size() > size) {
			sum -= L.front();
			L.pop_front();
		}
		result.push_back(sum / L.size());
	}
	return result;
}

//Q6
//just use binary search twice for left bound and right bound;
vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> result(2, -1);
    if(nums.size() == 0)
        return result;
    int start = 0, end = nums.size() - 1;
    while(start + 1 < end) {
        int mid = start + (end - start) / 2;
        if(nums[mid] > target)
            end = mid;
        else 
            start = mid;
    }
    int right = -1;
    if(nums[start] == target)
        right = start;
    if(nums[end] == target)
        right = end;
    start = 0;
    end = nums.size() - 1;
    while(start + 1 < end) {
        int mid = start + (end - start) / 2;
        if(nums[mid] >= target)
            end = mid;
        else 
            start = mid;
    }
    int left = -1;
    if(nums[end] == target)
        left = end;
    if(nums[start] == target)
        left = start;
    result[0] = left;
    result[1] = right;
    return result;
}

//Q7
//sliding window
string LongestSubstringTwoUnique(string s) {
    int start = 0, end = 0;
    int maxLen = 0, maxStart, maxEnd;
    unordered_map<char, int> hash;
    int size = 0;
    while(end < s.size()) {
        if(size <= 2 && end < s.size()) {
            if(hash.find(s[end]) == hash.end() || hash[s[end]] == 0)
                size++;
            hash[s[end++]]++;
        }
        if(size > 2) {
            hash[s[start]]--;
            if(hash[s[start++]] == 0)
                size--;
        }
        if(end - start > maxLen && size == 2) {
            maxLen = end - start;
            maxStart = start;
            maxEnd = end - 1;
        }
    }
    return s.substr(maxStart, maxLen);
}

//Q8
//actually we don't even need extra space
//if change the origin map is not allowed, we can use a vector to record values of dp, that will cost O(n) extra space
//because for the last row of the triangle, the number of elements is equal to the number of rows in the triangle.
int minimumTotal(vector<vector<int>>& triangle) {
    if(triangle.size() == 1)
        return triangle[0][0];
    int minSum;
    for(int i = 1; i < triangle.size(); i++) {
        minSum = INT_MAX;
        for(int  j = 0; j < triangle[i].size(); j++) {
            triangle[i][j] += min((j == 0 ? INT_MAX : triangle[i - 1][j - 1]), 
								  (j == triangle[i].size() - 1 ? INT_MAX : triangle[i - 1][j]));
            if(triangle[i][j] < minSum)
                minSum = triangle[i][j];
        }
    }
    return minSum;
}

//Q9
//this question is similar to the questio Trapping rain water
//the runing time is O(N) because of every element only get push in and pop out stack once.
int largestRectangleArea(vector<int>& heights) {
    int len = heights.size();
    if(len == 0)
        return 0;
    int maxArea = INT_MIN;
    stack<pair<int, int>> S;
    for(int i = 0; i <= len; i++) {  
        int h = i == len ? -1 : heights[i];
        if(!S.empty() && h <= S.top().second) {
            pair<int, int> curr = S.top();
            S.pop();
            int start;
            if(S.empty())
                start = -1;
            else
                start = S.top().first;
            int area = (i - start - 1) * curr.second;
            cout<<area<<endl;
            if(area > maxArea)
                maxArea = area;
            i--;
        }
        else {
            S.push(pair<int, int>(i, heights[i]));
        }

    }
    return maxArea;
}

























