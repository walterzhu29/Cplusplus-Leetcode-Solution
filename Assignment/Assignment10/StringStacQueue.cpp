//Q1
//DP
bool wordBreak(string s, vector<string>& wordDict) {
    int len = s.size();
    if(len == 0 || wordDict.size() == 0)
        return false;
    unordered_set<string> hash;
    for(auto str: wordDict)
        hash.insert(str);
    vector<bool> dp(len, false);
    for(int i = 0; i < len; i++) {
        for(int j = i; j >= 0; j--) {
            if((j == 0|| dp[j - 1]) && hash.find(s.substr(j, i - j + 1)) != hash.end()) {
                dp[i] = true;
                break;
            }
        }
        if(dp[i])
            cout<<"true"<<endl;
        else
            cout<<"false"<<endl;
    }
    return dp[len - 1];
}

//Q2
//DFS
vector<vector<string>> partition(string s) {
    vector<vector<string>> result;
    if(s.size() == 0)
        return result;
    vector<string> builder;
    dfs(0, 0, s, builder, result);
    return result;
}
void dfs(int start, int end, string& s, vector<string>& builder, vector<vector<string>>& result) {
    string curr = s.substr(start, end - start + 1);
    if(isPld(curr)) {
        builder.push_back(curr);
        if(end == s.size() - 1) {
            result.push_back(builder);
            builder.pop_back();
            return;
        }
        else {
            dfs(end + 1, end + 1, s, builder, result);
            builder.pop_back();
        }
    }
    else {
        if(end == s.size() - 1)
            return;
    }
    dfs(start, end + 1, s, builder, result);
}
bool isPld(string& s) {
    int len = s.size();
    int start = 0, end = len - 1;
    while(start < end) {
        if(s[start++] != s[end--])
            return false;
    }
    return true;
}

//Q3
//dp[i] means the number of the way decode from index 0 to i;
//when s[i] is valid (which means s[i] != 0) dp[i] += dp[i - 1]
//when string s[i - 1]s[i] is valid (which means s[i-1]s[i] could be decode to a letter)
//then dp[i] += dp[i - 2]
//actually we don't need extra space, we just need to use two values to record dp[i - 1] and dp[i - 2]
int numDecodings(string s) {
    int len = s.size();
    if(!len || s[0] == '0')
        return 0;
    if(len == 1)
        return 1;
    int dp1 = 1, dp2 = 1;
    for(int i = 1; i < len; i++) {
        int curr = 0;
        if(isValid(s[i]))
            curr += dp2;
        if(isValid(s[i - 1], s[i]))
            curr += dp1;
        if(!curr)
            return 0;
        dp1 = dp2;
        dp2 = curr;
    }
    return dp2;
}
bool isValid(char c) {
    return c != '0';
}
bool isValid(char c1, char c2) {
    if(c1 == '0')
        return false;
    string s;
    s += c1;
    s += c2;
    int val = atoi(s.c_str());
    if(val > 26)
        return false;
    return true;
}

//Q4
//this is a methematical problem, let's say if string s is palindrome
//which means for every i (0<= i < len), s[i] = s[len - 1 - i]
//If we remove the last number, if it still is a palindrome, 
//which means for every i (0<= i < len), s[i] = s[len - 2 - i]
//it comes out s[len - 1 - i] = s[len - 2 - i]
//which means all of the number in this string is the same
//so we can check the whole string first, if it is a palindrome, we check it again but ignore the last number, 
//if it still a palindrome, we return 0;
int maxLengthNonPalindrome(string& s) {
	int len = s.size();
	if(len < 2)
		return 0;
	if(len == 2)
		return s[0] == s[1] ? 0 : 2;
	int start = 0, end = len - 1;
	while(start < end) {
		if(s[start++] != s[end--])
			return len;
	}
	start = 0, end = len - 2;
	while(start < end) {
		if(s[start++] != s[end--])
			return len - 1;
	}
	return 0;
}

//Q5
//BFS
int rotAllOranges(vector<vector<int>>& matrix) {
    int row = matrix.size();
    if(!row)
        return 0;
    int col = matrix[0].size();
    if(!col)
        return 0;
    queue<pair<int, int>> Q;
    int fresh = 0;
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if(matrix[i][j] == 1)
                fresh++;
            else if(matrix[i][j] == 2) {
                Q.push(pair<int, int>(i, j));
            }
        }
    }
    if(!fresh)
        return 0;
    int dirX[4] = {-1, 1, 0, 0};
    int dirY[4] = {0, 0, -1, 1};
    int step = 0;
    while(!Q.empty()) {
        int len = Q.size();
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++)
                cout<<matrix[i][j]<<" ";
            cout<<endl;
        }
        cout<<endl;
        int lastFreshNum = fresh;
        for(int i = 0; i < len; i++) {
            pair<int, int> curr = Q.front();
            Q.pop();
            for(int j = 0; j < 4; j++) {
                int x = curr.first + dirX[j];
                int y = curr.second + dirY[j];
                pair<int, int> temp(x, y);
                if(x < 0 || y < 0 || x >= row || y >= col || matrix[x][y] != 1)
                    continue;
                fresh--;
                matrix[x][y] = 2;
                Q.push(temp);
            }
        }
        if(lastFreshNum == fresh)
            break;
        step++;
    }
    if(fresh != 0)
        return -1;
    return step;  
}

//Q6
//we use two lists to store all elements
//each list save half of these elements
//so that middle element is always the last element of left list
class Stack{
private: 
	list<int> left;
	list<int> right;
public:
	void push(int num) {
		if(left.size() == right.size()) {
			if(right.size() == 0) {
				left.push_back(num);
			}
			else {
				left.push_back(right.front());
				right.pop_front();
				right.push_back(num);
			}
		}
		else
			right.push_back(num);
	}
	
	void pop() {
		if(left.size() == right.size()) {
			if(left.size() == 0)
				return;
		}
		else {
			right.push_front(left.back());
			left.pop_back();
		}
		right.pop_back();
	}
	
	int findMiddle() {
		return left.back();
	}
	
	void deleteMiddle() {
		if(left.size() == 0)
			return;
		left.pop_back();
		if(left.size() < right.size()) {
			left.push_back(right.front());
			right.pop_front();
		}
	}
};


//Q7
class MinStack {
private:
    stack<int> s;
    vector<int> mins;
public:
    bool isEmpty() {
		return s.empty();
	}
    
    void push(int x) {
        s.push(x);
        if(mins.empty() || mins.back() >= x)
            mins.push_back(x);
    }
    
    void pop() {
        if(s.empty())
            return;
        if(mins.back() == s.top())
            mins.pop_back();
        s.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int getMin() {
        return mins.back();
    }
};

//Q8
//let's say we have a function: bool AKnowB(int a, int b);
//if a know b, it return true, otherwise return false;
//input is an array, every people is represented by an unique number.
int findStranger(vector<int>& person) {
	stack<int> S;
	for(auto i: person)
		S.push(i);
	while(S.size() > 1) {
		int a = person.top();
		person.pop();
		int b = person.top();
		person.pop();
		if(AKnowB(a, b))
			person.push(b);
		else
			person.push(a);
	}
	int rest = S.top();
	for(auto i: person) {
		if(AKnowB(rest, i) || !AKnowB(i, rest))
			return -1;
	}
	return rest;
}

//Q9
//use insert sort for every last element during recursion
void sortStack(stack<int>& S) {
	if(S.empty())
		return;
	int temp = S.top();
	S.pop();
	sortStack(S);
	insertSort(S, temp);
}

void insertSort(stack<int>& S, int num) {
	if(S.empty() || num >= S.top())
		S.push(num);
	else {
		int temp = S.top();
		S.pop();
		insertSort(S, num);
		S.push(temp);
	}
}

//Q10
void reverse(stack<int>& S) {
	if(S.empty())
		return;
	int temp = S.top();
	S.pop();
	reverse(S);
	addToBottom(S, temp);
}

void addToBottom(stack<int>&S, int num) {
	if(S.empty()) 
		S.push(num);
	else {
		int temp = S.top();
		S.pop();
		addToBottom(S, num);
		S.push(temp);
	}
}























