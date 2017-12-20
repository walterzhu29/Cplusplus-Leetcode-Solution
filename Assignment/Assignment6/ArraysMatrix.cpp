//Q1
int findMin(vector<int>& nums) {
	int len = nums.size();
	if(nums[0] <= nums[len - 1])
		return nums[0];
	int start = 0, end = len - 1;
	while(start + 1 < end) {
		int mid = start + (end - start) / 2;
		if(nums[mid] > nums[end])
			start = mid;
		else
			end = mid;
	}
	if(nums[start] < nums[end]) 
		return nums[start];
	else
        return nums[end];
}

//Q2
//because of this is not a rotated sorted array, 
//we need to find out the minimum number in this array,
//then we use binary search twice.
bool search(vector<int>& nums, int target) {
	int len = nums.size();
	if(len == 1)
		return 0;
	int start = 0, end = len - 1;
	while(start + 1 < end) {
		int mid = start + (end - start) / 2;
		if(nums[mid] == target)
			return mid;
		if(nums[mid] > nums[mid + 1]) {
			start = mid;
		}
		else if(nums[mid] > nums[mid - 1]) {
			end = mid;
		}
		else {
			start = mid;
			break;
		}
	}
	//find the minimun number's index 
	int pivot = nums[start] < nums[end] ? start : end;
	//use binary search in left part
	start = 0;
	end = pivot;
	while(start + 1 < end) {
		int mid = start + (end - start) / 2;
		if(nums[mid] == target)
			return mid;
		if(nums[mid] < target)
			end = mid;
		else
			start = mid;
	}
	if(nums[start] == target)
		return start;
	if(nums[end] == target)
		return end;
	//use binary search in right part
	start = pivot;
	end = len - 1;
	while(start + 1 < end) {
		int mid = start + (end - start) / 2;
		if(nums[mid] == target)
			return mid;
		if(nums[mid] < target)
			start = mid;
		else
			end = mid;
	}
	if(nums[start] == target)
		return start;
	return end;
}

//Q3
vector<int> findThreeNums(vector<int>& nums, int target) {
	vector<int> result;
	int len = nums.size();
	if(len < 3)
		return result;
	sort(nums.begin(), nums.end());
	for(int i = 0; i < len - 1; i++) {
		int start = i + 1, end = len - 1;
		while(start < end) {
			int sum = nums[i] + nums[start] + nums[end];
			if(sum == target) {
				result.push_back(nums[i]);
				result.push_back(nums[start]);
				result.push_back(nums[end]);
				return result;
			}
			if(sum < target)
				start++;
			else 
				end--;
		}
	}
	return result;
}

//Q4
//because of the start index of subarray (left) increase and wouldn't be reset to 0,
//the total run time of outter loop + inner loop is O(n). 
//so this is not a O(n^2) time algorithm, it is a O(n) time algorithm.
int minSubArrayLen(int s, vector<int>& nums) {
	int sum = 0;
	int left = 0;
	int minLen = INT_MAX;
	for(int i = 0; i < nums.size(); i++) {
		sum += nums[i];
		while(sum >= s) {
			minLen = min(minLen, (i - left + 1));
			sum -= nums[left++];
		}
	}
	return minLen == INT_MAX ? 0 : minLen;
}

//Q5
//let's say we get a new number nums[i] from this array,
//1) if our previous sum + nums[i] < nums[i], which mean previous sum < 0, 
//then we don't need to keep it, just let sum = nums[i];
//2) otherwise, sum >= 0, then let sum += nums[i],
//because even this nums[i] < 0, maybe there are more positive number after it.
//we just keep add it into our previous sum,
//if the previous sum is < 0, then it will be abandoned by the setp of 1),  
//otherwise, the previous will be increase.
int maxSubArray(vector<int>& nums) {
	if(nums.size() == 0)
		return 0;
	int sum = nums[0];
	int maxSum = sum;
	for(int i = 1; i < nums.size(); i++) {
		if(nums[i] + sum < nums[i])
			sum = nums[i];
		else
			sum += nums[i];
		maxSum = max(sum, maxSum);
	}
	return maxSum;
}


//Q6
//dp
int maxProduct(vector<int>& nums) {
	if(nums.size() == 0)
		return 0;
	int lastMin = 1; 
	int lastMax = 1;
	int prodMax = INT_MIN;
	for(int i = 0; i < nums.size(); i++) {
		int temp1 = nums[i] * lastMin;
		int temp2 = nums[i] * lastMax;
		lastMin = min(nums[i], min(temp1, temp2));
		lastMax = max(nums[i], max(temp1, temp2));
		prodMax = max(prodMax, lastMax);
	}
	return prodMax;
}

//Q7
//first we use hash map to save the number of the characters in t.
//then we scan s from start to the end, when we find a window contains all of the characters in t.
//we use an index from 0 to remove unnecessary or extra characters,
//untill the window cannot contains all of the characters in t
//then we expand windows again
string minWindow(string s, string t) {
	unordered_map<char, int> hash;
	for(auto cha: t)
		hash[cha]++;
	int count = t.size();
	int left = 0;
	int minLeft = INT_MIN;
	int minLen = INT_MAX;
	for(int i = 0; i < s.size(); i++) {
		if(hash.find(s[i]) != hash.end()) {
			if(hash[s[i]]-- > 0)
				count--;
		}
		while(count == 0) {
			if((i - left + 1) < minLen) {
				minLen = i - left + 1;
				minLeft = left;
			}
			if(hash.find(s[left]) != hash.end()) {
				hash[s[left]]++;
				if(hash[s[left]] > 0)
				count++;
			}
			left++;
		}
	}
	if(minLen == INT_MAX)
		return "";
	else
		return s.substr(minLeft, minLen);
}

//Q8
int majorityElement(vector<int>& nums) {
	int count = 0;
	int majority;
	for(int i: nums) {
	if(count == 0) {
		majority = i;
		count = 1;
		}
		else if(majority == i)
			count++;     
		else
			count--;
	}
	return majority;
}

//Q9
//tank = gas[i] - cost[i] means the gas left in the tank after a car pass station i,
//if the car start from a station A, after it pass the station B and find tank < 0, 
//which means this car cannot pass station B, 
//also means the car cannot pass B from all of the station between A and B,
//So we understand the start point must behind B.
//then we record how much gas the car lack to pass B, and reset tank to 0.
//after we traversal all of the gas station, if tank > lack, it means the car can travel around the circuit.
//otherwise it cannot. 
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
	int start = 0, tank = 0, lack = 0;
	for(int i = 0; i < gas.size(); i++) {
		tank += gas[i] - cost[i];
		if(tank < 0) {
			lack += tank;
			start = i + 1;
			tank = 0;
		}
	}
	return tank + lack >= 0 ? start : -1;
}


//Q10
vector<vector<string>> groupAnagrams(vector<string>& strs) {
	vector<vector<string>> result;
	if(strs.size() == 0)
		return result;
	unordered_map<string, vector<string>> hash;
	for(auto a: strs) {
		string temp = a;
		sort(temp.begin(), temp.end());
		hash[temp].push_back(a);
	}
	for(auto a: hash) {
		vector<string> builder;
		for(auto str: a.second)
			builder.push_back(str);
		result.push_back(builder);
	}
	return result;
}

//Q11
//we can use the first row to record which column should be set to 0
//and first column to record which row should be set to 0
void setZeroes(vector<vector<int>>& matrix) {
    int m = matrix.size();
    if(m == 0)
        return;
    int n = matrix[0].size();
    if(n == 0)
        return;
	//record if first row and column should be set to 0
    bool firstRowContainsZero = false;
    bool firstColContainsZero = false;
    for(int i = 0; i < n; i++) {
        if(matrix[0][i] == 0) {
            firstRowContainsZero = true;
            break;
        }
    }
    for(int i = 0; i < m; i++) {
        if(matrix[i][0] == 0) {
            firstColContainsZero = true;
            break;
        }
    }
	//record
    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++) {
            if(matrix[i][j] == 0) {
                matrix[0][j] = 0;
                matrix[i][0] = 0;
            }
        }
    }
	//reset matrix
    for(int i = 1; i < n; i++) {
        if(matrix[0][i] == 0) {
            for(int j = 1; j < m; j++)
                matrix[j][i] = 0;
        }
    }
    for(int i = 1; i < m; i++) {
        if(matrix[i][0] == 0) {
            for(int j = 1; j < n; j++) 
                matrix[i][j] = 0;
        }
    }
	//reset first row and column
    if(firstRowContainsZero) {
        for(int i = 0; i < n; i++) 
            matrix[0][i] = 0;
    }
    if(firstColContainsZero) {
        for(int i = 0; i < m; i++) 
            matrix[i][0] = 0;
    }
}

//Q12
//treat this 2D matrix as an array, binary search
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    if(!m)
        return false;
    int n = matrix[0].size();
    if(!n)
        return false;
    int start = 1, end = m * n;
    while(start + 1 < end) {
        int mid = start + (end - start) / 2;
        int curr = matrix[(mid - 1) / n][(mid - 1) % n];
        if(curr == target)
            return true;
        else if(curr > target)
            end = mid;
        else 
            start = mid;
    }
    if(matrix[(start - 1) / n][(start - 1) % n] == target || matrix[(end - 1) / n][(end - 1) % n] == target)
        return true;
    return false;
}

//Q13
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> result;
    int m = matrix.size();
    if(!m)
        return result;
    int n = matrix[0].size();
    if(!n)
        return result;
    int top = 0, left = 0, right = n - 1, bottom = m - 1;
    while(true) {
        for(int i = left; i <= right; i++)
            result.push_back(matrix[top][i]);
        if(++top > bottom)
           break;
        for(int i = top; i <= bottom; i++)
            result.push_back(matrix[i][right]);
        if(--right < left)
           break;
        for(int i = right; i >= left; i--)
            result.push_back(matrix[bottom][i]);
        if(--bottom < top)
           break;
        for(int i = bottom; i >= top; i--)
            result.push_back(matrix[i][left]);
        if(++left > right)
           break;   
    }
    return result;
}

//Q14
//this question may have other O(n) solutions,
//like: scan the array twice, record the min and max bar for every position, then calculate the total water
//I solve this question by my solution, which is also O(n) time complexity:
//we use a stack to record the every bar we meet, 
//1. while the stack is not empty and the last bar we met lower then the curr bar,
//we pop our stack and increase the sum, we also need a value to save the height of last bar we pop
//because of this situation: [423]
//2. then we calculate the water between the new bar and the bar at Stack top
//3. repeat step 2 until we finish scan.
//this solution is O(n) because each bar will be read only twice.
int trap(vector<int>& height) {
    stack<pair<int,int>> S;
    int sum = 0;
    for(int i = 0; i < height.size(); i++) {
        if(!S.empty() && height[i] >= S.top().second) {
            int lastHeight = 0;
            while(!S.empty() && S.top().second <= height[i]) {
                pair<int, int> last = S.top();
                S.pop();
                sum += (last.second - lastHeight) * (i - last.first - 1);
                lastHeight = last.second;
            }
            if(!S.empty()) {
                pair<int, int> last = S.top();
                sum += (height[i] - lastHeight) * (i - last.first - 1);
                lastHeight = last.second;
            }
        }
        S.push(pair<int, int>(i, height[i]));
    }
    return sum;
}

//Q15
bool ZeroSum(vector<int>& nums) {
	int sum = 0;
	unordered_set<int> hash;
	for(auto i: nums) {
		sum += i;
		if(sum == 0 || hash.find(sum) != hash.end())
			return true;
		hash.insert(sum);
	}
	return false;
}

//Q16
//find median of two sorted arrays is like find kth smallest element from these arrays
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int size1 = nums1.size(), size2 = nums2.size();
    if((size1 + size2) % 2 == 0)
        return (findKth(nums1, nums2, (size1 + size2) / 2, 0, 0) + findKth(nums1, nums2, (size1 + size2) / 2 + 1, 0, 0)) / 2.0;
    else
        return findKth(nums1, nums2, (size1 + size2) / 2 + 1, 0, 0);
}
int findKth(vector<int>& nums1, vector<int>& nums2, int k, int start1, int start2) {
    if(start1 == nums1.size())
        return nums2[start2 + k - 1];
    if(start2 == nums2.size())
        return nums1[start1 + k - 1];
    if(k == 1)
        return nums1[start1] < nums2[start2] ? nums1[start1] : nums2[start2]; 
    int index = k / 2 - 1;
    if(start1 + index >= nums1.size() || start2 + index >= nums2.size())
        index = min(nums1.size() - start1, nums2.size() - start2) - 1;
    if(nums1[start1 + index] < nums2[start2 + index])
        return findKth(nums1, nums2, k - index - 1, start1 + index + 1, start2);
    else
        return findKth(nums1, nums2, k - index - 1, start1, start2 + index + 1);
}

//Q17
bool findPair(vector<int>& nums, int diff) {
	unordered_set<int> hash;
	for(auto i: nums) {
		if(hash.find(i) != hash.end())
			return true;
		hash.insert(i - diff);
		hash.insert(i + diff);
	}
	return false;
}

//Q18
void sortArr(vector<int>& nums) {
	if(nums.size() < 2)
		return;
	int left = 0, right = nums.size() - 1;
	int i = 0;
	while(i <= right) {
		if(nums[i] == 1) {
			i++;
		}
		else if(nums[i] == 0) {
			swap(nums[i++], nums[left++]);
		}
		else {
			swap(nums[i], nums[right--]);
		}
	}
}



































