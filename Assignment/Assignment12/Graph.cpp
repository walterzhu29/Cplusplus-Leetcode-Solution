//Q1
//DFS
UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
   if(node == NULL)
       return NULL;
   unordered_map<int, UndirectedGraphNode*> hash;
   UndirectedGraphNode* result = clone(node, hash);
   return result;
}
UndirectedGraphNode *clone(UndirectedGraphNode *node, unordered_map<int, UndirectedGraphNode *>& hash) {
   if(hash.find(node->label) != hash.end())
       return hash[node->label];
   UndirectedGraphNode *node1 = new UndirectedGraphNode(node->label);
   hash[node1->label] = node1;
   for(auto a: node->neighbors)
       node1->neighbors.push_back(clone(a, hash));
   return node1;
}

//Q2
//BFS
//in this question, all of the edges are undirect, 
//but we can record an undirect edge as two direct edges
//for example: (0, 1) = 0->1 and 1->0
//that's the key we avoid duplicate way in BFS
//for example: (0, 1) (0, 2) (1, 2)
//when we have 0 at the front of the queue
//we push 1 and 2 into queue bacause edges: 0->1 and 0->2
//then we delete back ways: 1->0 and 2->0
//then 1 at the front of the queue
//but we will find a circle because of the edge: 1->2
//so this is not a vaild tree
bool validTree(int n, vector<pair<int, int>>& edges) {
    if(!n)
        return true;
    vector<unordered_set<int>> nodes(n);
    for(auto a: edges) {
        nodes[a.first].insert(a.second);
        nodes[a.second].insert(a.first);
    }
    unordered_set<int> visited;
    queue<int> Q;
    Q.push(0);
    while(!Q.empty()) {
        int curr = Q.front();
        cout<<curr<<endl;
        Q.pop();
        if(visited.find(curr) != visited.end())
            return false;
        for(auto a: nodes[curr]) {
            Q.push(a);
            nodes[a].erase(curr);
        }
        visited.insert(curr);
    }
    return n == visited.size();
}

//Q3
//In this question, BFS is totally faster than DFS
bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
    unordered_map<int, vector<int>> hash;
    vector<int> indegree(numCourses, 0);
    for(auto a: prerequisites) {
        hash[a.second].push_back(a.first);
        indegree[a.first]++;
    }
    queue<int> Q;
    //start BFS from these courses don't have any prerequisites
    for(int i = 0; i < indegree.size(); i++) {
        if(indegree[i] == 0)
            Q.push(i);
    }
    unordered_set<int> visited;
    while(!Q.empty()) {
        int curr = Q.front();
        Q.pop();
        if(visited.find(curr) != visited.end())
            return false;
        for(int i = 0; i < hash[curr].size(); i++) {
            int next = hash[curr][i];
            indegree[next]--;
            if(indegree[next] == 0) {
                Q.push(next);
            }
        }
        visited.insert(curr);
    }
    return visited.size() == numCourses;
}

//Q4
//I use BFS to solve this in Q2
//And we can also use Union Find to solve this problem
//so this algorithm can also be use to solve Q2
int find(int node, vector<int>& parent) {
    if(parent[node] == node)
        return node;
    return find(parent[node], parent);
}
bool haveCircle(int n, vector<pair<int, int>>& edges) {
    vector<int> parent;
    for(int i = 0; i < n; i++) {
        parent.push_back(i);
    }
    vector<int> rank(n, 0);
    for(auto a: edges) {
        int i = find(a.first, parent);
        int j = find(a.second, parent);
		//if have circle, return true
        if(i == j)
            return return;
        else {
            if(rank[i] > rank[j])
                parent[j] = i;
            else {
                if(rank[i] == rank[j])
                    rank[j]++;
                parent[i] = j;
            }
        }
    }
	//otherwise, return false
	return false;
}

//For directed graph, we can use both BFS and DFS
bool haveCircle(int n, vector<pair<int, int>>& edges) {
    unordered_map<int, vector<int>> hash;
    vector<int> indegree(n, 0);
    for(auto a: edges) {
        hash[a.second].push_back(a.first);
        indegree[a.first]++;
    }
    queue<int> Q;
    for(int i = 0; i < indegree.size(); i++) {
        if(indegree[i] == 0)
            Q.push(i);
    }
    unordered_set<int> visited;
    while(!Q.empty()) {
        int curr = Q.front();
        Q.pop();
        if(visited.find(curr) != visited.end())
            return false;
        for(int i = 0; i < hash[curr].size(); i++) {
            int next = hash[curr][i];
            indegree[next]--;
            if(indegree[next] == 0) {
                Q.push(next);
            }
        }
        visited.insert(curr);
    }
    return visited.size() == n;
}

//Q5
//we can use Dijkstra algorithm to solve this problem
//the time complexity will be O(N^2) where N is the number of stations
//if we can use Fibonacci heap in this case, the running time will be down to O(E + NlogN)
//but STL doesn't include any implementation for Fibonacci heap (boost may have)
//so we wouldn't use normal heap sort, otherwise the running time will up to O(N^2 * logN)
int minimumCost(int n, vector<vector<int>>& cost) {
	vector<int> weights;
	unordered_set<int> unCheck;
	for(int i = 0; i < n; i++) {
		if(i == 0)
			weights.push_back(0);
		else 
			weights.push_back(INT_MAX);
		unCheck.insert(i);
	}
	while(!unCheck.empty()) {
		//we use a scan to find out the heap top instead of use heap sort
		int minWeight = INT_MAX;
		int next;
		for(int i: unCheck) {
			if(weights[i] < minWeight) {
				minWeight = weights[i];
				next = i;
			}
		}
		//remove node from set
		unCheck.erase(next);
		//update weights
		for(int i = next; i < n; i++) {
			weights[i] = min(weights[i], weights[next] + cost[next][i]);
		}
	}
	return weights[n - 1];
}
























