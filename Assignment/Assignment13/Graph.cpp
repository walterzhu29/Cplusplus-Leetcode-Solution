//DFS
vector<vector<int>> allPaths(int source, int destination, vector<vector<int>>& edges) {
	unordered_map<int, vector<int>> graph;
	for(auto a: edges) {
		graph[a[0]].push_back(a[1]);
	}
	unordered_set<int> visited;
	vector<vector<int>> result;
	visited.insert(source);
	dfs(source, destination, visited, graph, result);
	return result;
}

void dfs(int curr, int dest, unordered_set<int>& visited, unordered_map<int, vector<int>>& graph, vector<vector<int>>& result) {
	if(curr == dest) {
		vector<int> path;
		for(auto i: visited)
			path.push_back(i);
		reverse(path.begin(), path.end());
		result.push_back(path);
		return;
	}
	for(auto i: graph[curr]) {
		if(visited.find(i) != visited.end())
			continue;
		visited.insert(i);
		dfs(i, dest, visited, graph, result);
		visited.erase(i);
	}
}

//Q2
//BFS
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> words;
    for(auto a: wordList)
        words.insert(a);
    int step = 0;
    queue<string> Q;
    Q.push(beginWord);
    while(!Q.empty()) {
        int len = Q.size();
        step++;
        for(int a = 0; a < len; a++) {
            string curr = Q.front();
            Q.pop();
            if(curr == endWord)
                return step;
            for(int i = 0; i < curr.size(); i++) {
                for(int j = 0; j < 26; j++) {
                    string temp = curr;
                    temp[i] = 'a' + j;
                    if(words.find(temp) != words.end()) {
                        Q.push(temp);
                        words.erase(temp);
                    }
                }
            }
        }
    }
    return -1;
}

//Q3
//DFS
int numIslands(vector<vector<char>>& grid) {
    int rows = grid.size();
    if(!rows)
        return 0;
    int cols = grid[0].size();
    if(!cols)
        return 0;
    int count = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(grid[i][j] == '1') {
                count++;
                dfs(rows, cols, i, j, grid);
            }

        }
    }
    return count;
}
void dfs(int rows, int cols, int i, int j, vector<vector<char>>& grid) {
    if(i < 0 || j < 0 || i >= rows || j >= cols || grid[i][j] != '1')
        return;
    grid[i][j] = '0';
    dfs(rows, cols, i - 1, j, grid);
    dfs(rows, cols, i + 1, j, grid);
    dfs(rows, cols, i, j - 1, grid);
    dfs(rows, cols, i, j + 1, grid);
}

//Q5
//BFS
int rotAll(vector<vector<int>>& grid) {
	int rows = grid.size();
    if(!rows)
        return 0;
    int cols = grid[0].size();
    if(!cols)
        return 0;
	queue<pair<int, int>> Q;
	int count = 0;
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			if(grid[i][j] == 2)
				Q.push(pair<int, int>(i, j));
			else if(grid[i][j] == 1)
				count++;
		}
	}
	int step = 0;
	int dirX[4] = {-1, 1, 0, 0};
	int dirY[4] = {0, 0, -1, 1};
	while(!Q.empty()) {
		if(count == 0)
			return step;
		step++;
		int len = Q.size();
		for(int i = 0; i < len; i++) {
			pair<int, int> curr = Q.front();
			Q.pop();
			for(int j = 0; j < 4; j++) {
				int x = curr.first + dirX[j];
				int y = curr.second + dirY[j];
				if(x >= 0 && y >= 0 && x < rows && y < cols && grid[x][y] == 1) {
					grid[x][y] = 2;
					count--;
					Q.push(pair<int, int> (x, y));
				}
			}
		}
	}
	return -1;
}







































