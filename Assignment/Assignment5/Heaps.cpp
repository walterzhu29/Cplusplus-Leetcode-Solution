//Q1
struct comLess {
	bool operator() (int a, int b) {
		return a > b;
	}
};
vector<int> mergeKSortedArrays(vector<vector<int>> arrays, int k, int n) {
	vector<int> result;
	if(k == 0 || n == 0)
		return result;
	//use hashmap to record the index of the number that will be put into the min heap
	unordered_map<int, int> hash;
	for(int i = 0; i < k; i++)
		hash[i] = 0;
	//merge, when the hash is empty, which means we pushed all the numbers into result 
	while(!hash.empty()) {
		int pick;
		priority_queue<int, vector<int>, comLess> minHeap;
		for(int i = 0; i < k; i++) {
			if(hash.find(i) == hash.end())
				continue;
			minHeap.push(arrays[i][hash[i]]);
			//record which array we will push result
			if(minHeap.top() == arrays[i][hash[i]])
				pick = i;
		}
		result.push_back(minHeap.top());
		hash[pick]++;
		if(hash[pick] >= k)
			hash.erase(pick);
	}
	//print the merged result and return
	for(int i = 0; i < result.size(); i++)
		cout<<result[i]<<" ";
	cout<<endl;
	return result;
}

//Q2
//let's say the input vector numbers is a stream of numbers
vector<int> findTop10Number(vector<int> numbers) {
	priority_queue<int, vector<int>, comLess> minHeap;
	int i = 0;
	//get the fisrt 10 number from stream
	for(; i < 10; i++) {
		minHeap.push(numbers[i]);
	}
	//every time get a number from stream, compare with the top number of the min heap
	for(; i < numbers.size(); i++) {
		if(numbers[i] > minHeap.top()) {
			minHeap.pop();
			minHeap.push(numbers[i]);
		}
	} 
	vector<int> result;
	while(!minHeap.empty()) {
		result.push_back(minHeap.top());
		minHeap.pop();
	}
	return result;
}

//Q3
//we can use two heaps to solve this problem, one min heap and one max heap.
//The max heap saves all of the number <= median, and the min heap saves all of the number > median
//we maintain these to heaps like: maxHeap.size() == minHeap.size() or maxHeap.size() = minHeap.size() + 1
//suppose the input vector numbers is the stream of numbers
double findMeidan(vector<int> numbers) {
	priority_queue<int, vector<int>, comLess> minHeap;
	priority_queue<int, vector<int>> maxHeap;
	//use this for loop to simulate fetch each number from stream
	for(int i = 0; i < numbers.size(); i++) {
		//if maxHeap.size() > minHeap.size(), add a number into minHeap
		if(maxHeap.size() > minHeap.size()) {
			if(numbers[i] < maxHeap.top()) {
				minHeap.push(maxHeap.top());
				maxHeap.pop();
				maxHeap.push(numbers[i]);
			}
			else
				minHeap.push(numbers[i]);
		}
		else {
			if(maxHeap.size() == 0)
				maxHeap.push(numbers[i]);
			else if(numbers[i] > minHeap.top()) {
				maxHeap.push(minHeap.top());
				minHeap.pop();
				minHeap.push(numbers[i]);
			}
			else
				maxHeap.push(numbers[i]);
		}
	}
	if(maxHeap.size() > minHeap.size())
		return maxHeap.top();
	else
		return (maxHeap.top() + minHeap.top()) / 2.0;
}

//Q4
//we go through the array from start to the end
//for each index i we get all of the number from i to i + k, and put em into a min heap
//then the top of the min heap is the number should be at index i 
void sortNearElements(vector<int>& nums, int k) {
	if(k >= nums.size()) {
		sort(nums.begin(), nums.end());
		return;
	}
	priority_queue<int, vector<int>, comLess> minHeap;
	for(int i = 0; i < k; i++) {
		minHeap.push(nums[i]);
	}
	
	for(int i = 0; i < nums.size(); i++) {
		if(i + k < nums.size())
			minHeap.push(nums[i + k]);
		nums[i] = minHeap.top();
		minHeap.pop();
	}
}

//Q5
int minimumCost(vector<int> ropes) {
	//if there no rope or only one rope, the result should be 0
	int cost = 0;
	priority_queue<int, vector<int>, comLess> minHeap;
	for(auto i: ropes)
		minHeap.push(i);
	while(minHeap.size() > 1) {
		int newRope = minHeap.top();
		minHeap.pop();
		newRope += minHeap.top();
		minHeap.pop();
		minHeap.push(newRope);
		cost += newRope;
	}
	return cost;
}




















