//Q1
//use a hash map to save the count of each integer
//use a hash set to save all unique integers of every window
vector<vector<int>> findAllUnique(vector<int>& nums, int k) {
	int len = nums.size();
	unordered_map<int, int> hash1;
	unordered_set<int> hash2;
	vector<vector<int>> result;
	if(k >= len) {
		for(int i: nums)
			hash2.insert(i);
		vector<int> builder;
		for(int i: hash2)
			builder.push_back(i);
		result.push_back(builder);
		return result;
	}
	for(int i = 0; i < len; i++) {
		hash1[nums[i]]++;
		hash2.insert(nums[i]);
		if(hash1[nums[i]] > 1)
			hash2.erase(nums[i]);
		if(i > k - 1) {
			hash1[nums[i - k]]--;
			if(hash1[nums[i - k]] == 1)
				hash2.insert(nums[i - k]);
			if(hash1[nums[i - k]] == 0)
				hash2.erase(nums[i - k]);
		}
		if(i >= k - 1) {
			vector<int> builder;
			for(auto i: hash2)
				builder.push_back(i);
			result.push_back(builder);
		}
	}
	return result;
}

//Q2
//use stack to identify if a substring is valid
//we use hash table to record the pair which key is the size of the stack, and the value is the index of string
//let's say for index i and j, they have the same key
//which means the substring from i(not included) to j is valid
//we don't update value for the same key unless we get a new '('
int longestValidParenthesesSubstring(string& p) {
	int len = p.size();
	if(!len)
		return 0;
	int result = 0;
	stack<char> S;
	unordered_map<int, int> hash;
	hash[0] = -1;
	for(int i = 0; i < len; i++) {
		if(!S.empty() && p[i] == ')') {
			S.pop();
		}
		else {
			if(p[i] == '(') {
				S.push(p[i]);
			}
			//if p[i] == ')' which means this is a break point for a valid substring
			//we delete every record before this point
			//and this wouldn't be a O(n^2) because every element only in and out to stack at most once
			else {
				while(!S.empty())
					S.pop();
				hash.clear();
			}
		}
		int size = S.size();
		if(hash.find(size) == hash.end() || p[i] == '(') {
			hash[size] = i;
		}
		else {
			result = max(result, i - hash[size]);
		}
	}
	return result;
}

//Q3
//we scan array from left to right, for every child i;
//and record how many consecutive numbers increasing and smaller then children[i]
//and we scan array again from right to left, pick the greater counter which will be the candies
//we giving to the child
//in the end, we add candies array up, the sum is the result.
int minimumCandies(vector<int>& children) {
	int len = children.size();
	if(!len)
		return 0;
	vector<int> candies(len);
	int count = 0;
	for(int i = 0; i < len; i++) {
		if(i == 0 || children[i - 1] >= children[i])
			count = 0;
		else 
			count++;
		candies[i] = count + 1;
	}
	count = 0;
	for(int i = len - 1; i >= 0; i--) {
		if(i == len - 1 || children[i + 1] >= children[i])
			count = 0;
		else
			count++;
		candies[i] = max(count + 1, candies[i]);
	}
	int result = 0;
	for(int i: candies)
		result += i;
	return result;
}

//Q4
//the time complexity is still even we use heap, because of the heap part only cost O(klog26) for the worst case;
//so the total time complexity is O(n)
int minimumValue(string& s, int k) {
	int len = s.size();
	if(!len)
		return 0;
	vector<int> letter(26, 0);
	int count = 0;
	for(char cha: s) {
		letter[cha - 'a']++;
		count++;
	}
	if(k >= count)
		return 0;
	priority_queue<int> heap;
	for(int i: letter)
		heap.push(i);
	while(k--) {
		int temp = heap.top();
		heap.pop();
		temp--;
		heap.push(temp);
	}
	int result = 0;
	while(!heap.empty()) {
		result += heap.top() * heap.top();
		heap.pop();
	}
	return result;	
}

//Q5
//we count the frequency of each character, 
//and save these character to frequency pair into an array: frequency
//sort frequency by the frequency of every element
//pick up the most high frequency characters (maybe more than one), make them to be the head of each string
//add rest chareacters to the end of each string (exclude the last one)
//put these string together, which is the result

//another solution is use heap sort for these frequency
//every time we pick the most frequency character from heap and make its frequency--
string rearrangeString(string s, int k) {
    if(!k || s == "" || s.size() == 1 || k == 1)
        return s;
    unordered_map<char, int> hash;
    for(char cha: s) {
        if(hash.find(cha) != hash.end())
            hash[cha]++;
        else
            hash[cha] = 1;
    }
    vector<pair<string, int>> frequency;
    for(auto a: hash) {
        frequency.push_back(pair<string, int>(string(1, a.first), a.second));
    }
    sort(frequency.begin(), frequency.end(), [](pair<string, int> a, pair<string, int> b) {
        return a.second > b.second;
    });
    vector<string> builder(frequency[0].second, frequency[0].first);
    int index = 1;
    while(index < frequency.size() && frequency[index].second == frequency[index - 1].second) {
        for(int i = 0; i < builder.size(); i++) {
            builder[i] += frequency[index].first;
        }
        index++;
    }
    while(index < frequency.size()) {
        for(int i = 0; i < builder.size() - 1; i++) {
            builder[i] += frequency[index].first;
            frequency[index].second--;
            if(frequency[index].second == 0)
                index++;
            if(index >= frequency.size())
                break;
        }
    }
    string result;
    for(int i = 0; i < builder.size(); i++) {
        if(builder[i].size() < k && i < builder.size() - 1)
            return "";
        result += builder[i];
    }
    return result;
}

//Q6
//this is a graph question, but the input still will be O(N = total number of characters of input words)
//First: Find out rules (order infos) from the giving input
//we compare two consecutive words, 
//bacause of this is sorted dictionary, so we wouldn't miss any infos for unconsecutive words pair
//Second: the rules we find out, actually are the infos that can help to us build graph
//Third: we find out if there are circles in the graph by dfs(bfs also work and a little bit faster, but the total time complexity are determine by the process we fetch rules from input), if there are, which means, there is no valid order
//then we return empty string
//otherwise, we count how many characters after curr characters, then we can find out correct order
//There may be multiple valid order of letters(the input may not include all of the infos we need), return any one of them.
string alienOrder(vector<string>& words) {
    int len = words.size();
    if(!len)
        return "";
    if(len == 1)
        return words[0];
    //get rules between two characters (build Graph)
    unordered_map<char, unordered_set<char>> characters;
    for(int i = len - 1; i > 0; i--) {
        string str2 = words[i];
        string str1 = words[i - 1];
        for(char cha: str1)
            if(characters.find(cha) == characters.end())
                characters[cha] = unordered_set<char>();
        for(char cha: str2)
            if(characters.find(cha) == characters.end())
                characters[cha] = unordered_set<char>();
        for(int i = 0; i < str1.size() && i < str2.size(); i++) {
            if(str1[i] != str2[i]) {
                characters[str1[i]].insert(str2[i]);
                break;
            }
        }
    }
    //DFS
    vector<pair<char, int>> order;
    for(auto a: characters) {
        bool valid = true;
        unordered_set<char> visited;
		//hash set will count the number of characters after current one
        unordered_set<char> count;
        visited.insert(a.first);
        dfs(a.first, characters, valid, visited, count);
        order.push_back(pair<char, int>(a.first, count.size()));
        if(!valid)
            return "";
    }        
    //sort
    sort(order.begin(), order.end(), [](pair<char, int> a, pair<char, int> b){
        return a.second > b.second;
    });

    //build result
    string result = "";
    for(auto a: order) {
        result += a.first;
    }
    return result;
}
void dfs(char curr, unordered_map<char, unordered_set<char>>& characters, bool& valid, unordered_set<char>& visited, unordered_set<char>& count) {
    count.insert(curr);
    if(!valid || characters[curr].empty())
        return;
    for(auto a: characters[curr]) {
        if(visited.find(a) != visited.end()) {
            valid = false;
            return;
        }
        visited.insert(a);
        dfs(a, characters, valid, visited, count);
        visited.erase(a);
    }
}

//Q7
//an slower method is to find next permutation many times, but the time complexity will be up to O(n!)
//so we need use mathematical method to solve this problem 
//for a string which the length is n; the total number of permutations is n!;
//if chatacter x is the kth in lexicographical order. And it is the start of a permutation
//there are at least (k - 1) * (n - 1)! permutations before this one.
//so we scan the string from the begin to the end, we could calculate how many permutation before the current one.
//which is the rank - 1;
int factorial(int n) {
	if(!n)
		return 1;
	int result = 1;
	while(n > 0) {
		result *= n--;
	}
	return result;
}
int findRank(string s) {
	int len = s.size();
	if(len < 2)
		return len;
	vector<char> characters;
	for(char cha: s)
		characters.push_back(cha);
	sort(characters.begin(), characters.end());
	int rank = 0;
	for(int i = 0; i < len; i++) {
		int j = 0;
		int temp = factorial(len - i - 1);
		for(int j = 0; j < characters.size(); j++) {
			if(characters[j] == ' ')
				continue;
			if(characters[j] < s[i])
				rank += temp;
			else {
				characters[j] = ' ';
				break;
			}
		}
	}
	return rank + 1;
}

//Q8
string runLengthEncoded(string s) {
	int len = s.size();
	if(len < 2)
		return s;
	string result = "";
    int count = 1;
    result += s[0];
    for(int i = 1; i < len; i++) {
        if(s[i] != s[i - 1]) {
            result += std::to_string(count);
            count = 1;
            result += s[i];
        }
        else {
            count++;
        }
    }
    if(count > 1)
        result += std::to_string(count);
	return result;
}

//Q9
//find out the next greater element for every element
//then find out the next smaller element for every element
//then we got result
vector<int> nextSmallerOfNextGreater(vector<int>& nums) {
	int len = nums.size();
	vector<int> result(len , -1);
	if(len < 3)
		return result;
	vector<int> ng(len, -1);
	stack<int> S1;
	for(int i = len - 1; i >= 0; i--) {
		if(S1.empty())
			S1.push(i);
		else {
			if(nums[S1.top()] > nums[i]) {
				ng[i] = S1.top();
			}
			else {
				while(!S1.empty() && nums[S1.top()] <= nums[i])
					S1.pop();
				if(!S1.empty())
					ng[i] = S1.top();
			}
			S1.push(i);
		}
	}
	vector<int> ns(len, - 1);
	stack<int> S2;
	for(int i = len - 1; i >= 0; i--) {
		if(S2.empty())
			S2.push(i);
		else {
			if(nums[S2.top()] < nums[i]) {
				ns[i] = S2.top();
			}
			else {
				while(!S2.empty() && nums[S2.top()] >= nums[i])
					S2.pop();
				if(!S2.empty())
					ns[i] = S2.top();
			}
			S2.push(i);
		}
	}
	for(int i = 0; i < len; i++) {
		if(ng[i] == -1 || ns[ng[i]] == -1)
			result[i] = -1;
		else
			result[i] = nums[ns[ng[i]]];
	}
	return result;
}

//Q10
vector<pair<int, int>> merge(vector<pair<int, int>>& intervals) {
    int len = intervals.size();
    if(len < 2)
        return intervals;
    sort(intervals.begin(), intervals.end(), [](pair<int, int> a, pair<int, int> b){
        return a.first < b.first;
    });
    vector<pair<int, int>> result;
    for(int i = 0; i < len; i++) {
        if(result.empty() || result.back().second < intervals[i].first)
            result.push_back(intervals[i]);
        else
            result.back().second = max(result.back().second, intervals[i].second);                   
    }
    return result;
}




















