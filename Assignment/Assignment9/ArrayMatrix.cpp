//Q1
//DFS
bool reachable(vector<int>& nums, int target) {
	int len = nums.size();
	if(!len)
		return 0;
	unordered_map<int, int> hash;
	for(int i: nums) {
		hash[i]++;
	}
	for(int i = 0; i < len; i++) {
		hash[nums[i]]--;
		if(helper(nums, target, hash, nums[i]))
			return true;
		hash[nums[i]]++;
	}
	return false;
}
bool helper(vector<int>& nums, int target, unordered_map<int, int>& hash, int curr) {
	if(curr == target)
		return true;
	for(int i = 0; i< nums.size(); i++) {
		if(hash[nums[i]] == 0)
			continue;
		hash[nums[i]]--;
		if(helper(nums, target, hash, curr + nums[i]) ||
		   helper(nums, target, hash, curr - nums[i]) ||
		   helper(nums, target, hash, curr * nums[i]) ||
		   helper(nums, target, hash, curr / nums[i]))
		   return true;
		hash[nums[i]]++;
	}
	return false;
}

//Q2
int uniquePaths(int m, int n) {
    if(m == 0 || n == 0)
        return 0;
    if(m == 1 || n == 1)
        return 1;
    int a = (m + n - 2), b = n - 1;
    // result = C(a ,b)
    //        = A(a ,b) / b!
    //        = a * (a - 1) *...*(a - b + 1) / b!
    double result = 1;
    for(int i = 1; i <= b; i++)
        result = result * (a - b + i) / i;
    return result;
}

//Q3
int maxBitonicSubarrayLength(vector<int>& nums) {
	int len = nums.size();
	vector<int> left(len, 1);
	vector<int> right(len, 1);
	for(int i = 1; i < len; i++)
		if(nums[i] > nums[i - 1])
			left[i] += left[i - 1];
	for(int i = len - 2; i >= 0; i--)
		if(nums[i] > nums[i + 1])
			right[i] += right[i + 1];
	int result = 0; 
	for(int i = 0; i < len; i++)
		result = result < (left[i] + right[i] - 1) ? (left[i] + right[i] - 1) : result;
	return result;
}

//Q4
int maxSum(vector<int>& nums) {
	int len = nums.size();
	if(!len)
		return 0;
	sort(nums.begin(), nums.end());
	int result = 0;
	int last = nums[0];
	int left = 0, right = len - 1;
	bool lr = true;
	while(left <= right) {
		int curr;
		if(lr)
			curr = nums[left++];
		else
			curr = nums[right--];
		lr = !lr;
		result += abs(last - curr);
		last = curr;
	}
	result += abs(last - nums[0]);
	return result;
}

//Q5
void change(vector<int>& nums) {
	int len = nums.size();
	if(len < 3)
		return;
	for(int i = 0; i < len; i++)
		nums[i]++;
	for(int i = 0; i < len; i++) {
		if(nums[i] > 0) {
			int index = nums[i] - 1;
			int val = i + 1;
			while(nums[index] > 0) {
				int newIndex = nums[index] - 1;
				nums[index] = -val;
				val = index + 1;
				index = newIndex;
			}
		}
	}
	for(int i = 0; i < len; i++) {
		nums[i] = -(nums[i] + 1);
	}
}

//Q6
//if no such a pair of elements in this array, I think we can reuturn -1;
int maxDiff(vector<int>& nums) {
	int len = nums.size();
	int maxDiff = -1;
	int leftMin = INT_MAX;
	for(int i: nums) {
		if(i > leftMin)
			maxDiff = i - leftMin > maxDiff ? i - leftMin : maxDiff;
		leftMin = i < leftMin ? i : leftMin;
	}
	return maxDiff;
}

//Q7
vector<int> NGE(vector<int>& nums) {
	int len = nums.size();
	if(!len)
		return vector<int>();
	vector<int> result(len, 0);
	stack<int> S;
	for(int i = len - 1; i >= 0; i--) {
		if(S.empty() || nums[i] < S.top()) {
			if(S.empty())
				result[i] = -1;
			else
				result[i] = S.top();
		}
		else {
			while(!S.empty() && nums[i] >= S.top()) {
				S.pop();
			}
			if(S.empty())
				result[i] = -1;
			else
				result[i] = S.top();
		}
		S.push(nums[i]);
	}
	return result;
}

//Q8
int pathMaxSum(vector<int> nums1, vector<int> nums2) {
	int len1 = nums1.size();
	int len2 = nums2.size();
	//calculate maximum sum
	int index1 = 0, index2 = 0;
	int sum1 = 0, sum2 = 0;
	int result = 0;
	while(index1 < len1 && index2 < len2) {
		if(nums1[index1] < nums2[index2]) {
			sum1 += nums1[index1++];
		}
		else if(nums1[index1] > nums2[index2]) {
			sum2 += nums2[index2++];
		}
		else {
			result += max(sum1, sum2) + nums1[index1];
			sum1 = 0;
			sum2 = 0;
			index1++;
			index2++;
		}
	}
	result += max(sum1, sum2);
	while(index1 < len1)
		result += nums1[index1++];
	while(index2 < len2)
		result += nums2[index2++];
	return result;
}

//Q9
int findMax(vector<int>& nums) {
	int len = nums.size();
	int start = 0, end = len - 1;
	while(start + 1 < end) {
		int mid = start + (end - start) / 2;
		if(nums[mid - 1] < nums[mid] && nums[mid + 1] < nums[mid])
			return nums[mid];
		else if(nums[mid - 1] < nums[mid])
			start = mid;
		else if(nums[mid + 1] < nums[mid])
			end = mid;
	}
	return nums[start] > nums[end] ? nums[start] : nums[end];
}
































