//Q1
//and here are two test case
//the first case is the input case on geeks4geeks
//second case is the corner case which the input graph is not a connected graph
/*
vector<vector<int>> graph = {{INT_MAX, 4, INT_MAX, INT_MAX, INT_MAX, INT_MAX,INT_MAX, 8, INT_MAX}, 
                             {4, INT_MAX, 8, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 11, INT_MAX},
                             {INT_MAX, 8, INT_MAX, 7, INT_MAX, 4, INT_MAX, INT_MAX, 2},
                             {INT_MAX, INT_MAX, 7, INT_MAX, 9, 14, INT_MAX, INT_MAX, INT_MAX},
                             {INT_MAX, INT_MAX, INT_MAX, 9, INT_MAX, 10, INT_MAX, INT_MAX, INT_MAX},
                             {INT_MAX, INT_MAX, 4, 14, 10, INT_MAX, 2, INT_MAX, INT_MAX},
                             {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 2, INT_MAX, 1, 6},
                             {8, 11, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 1, INT_MAX, 7},
                             {INT_MAX, INT_MAX, 2, INT_MAX, INT_MAX, INT_MAX, 6, 7, INT_MAX}};

vector<vector<int>> graph = {{INT_MAX, INT_MAX, 5},
                             {INT_MAX, INT_MAX, INT_MAX},
                             {5, INT_MAX, INT_MAX}};
*/
//this function will return the total weight for MST, and print MST
//if return -1, which means this graph cannot generate MST
struct cmp {
  bool operator()(vector<int> a, vector<int> b) {
      return a[2] > b[2];
  }  
};

int prim(int n, vector<vector<int>>& graph) {
    if(n < 2)
        return -1;
    unordered_set<int> visited;
    priority_queue<vector<int>, vector<vector<int>>, cmp> dis;
    visited.insert(0);
    for(int i = 1; i < n; i++) {
        if(graph[0][i] == INT_MAX)
            continue;
        vector<int> temp = {0, i, graph[0][i]};
        dis.push(temp);
    }
    if(dis.empty())
        return -1;
    int totalWeight = 0;
    for(int i = 1; i < n; i++) {
        while(visited.find(dis.top()[0]) != visited.end() 
              && visited.find(dis.top()[1]) != visited.end()) {
            dis.pop();
        }
        if(dis.empty())
            return -1;
        vector<int> miniDis = dis.top();
        cout<<miniDis[0]<<" --> "<<miniDis[1]<<endl;
        dis.pop();
        totalWeight += miniDis[2];
        visited.insert(miniDis[1]);
        for(int i = 0; i < n; i++) {
            if(visited.find(i) != visited.end() 
               || graph[miniDis[1]][i] == INT_MAX) {
                continue;
            }
            vector<int> temp = {miniDis[1], i, graph[miniDis[1]][i]};
            dis.push(temp);
        }
    }
    return totalWeight;
}

//Q2
//this function will return the total weight for MST, and print MST
//if return -1, which means this graph cannot generate MST
//test cases:
//1.
// vector<vector<int>> edges = {
//     {0, 1, 4},
//     {0, 7, 8},
//     {1, 7, 11},
//     {1, 2, 8},
//     {2, 8, 2},
//     {7, 8, 7},
//     {6, 8, 6},
//     {6, 7, 1},
//     {2, 3, 7},
//     {3, 4, 9},
//     {4, 5, 10},
//     {5, 6, 2},
//     {2, 5, 4},
//     {3, 5, 14}
// };
// n = 9
//
//2.
// vector<vector<int>> edges = {
//     {1, 2, 10}
// };
// n = 3
//we can use union find to achieve Kruskal algorithm
int findParent(int node, vector<int>& parent) {
    if(parent[node] == node)
        return node;
    return findParent(parent[node], parent);
}
int kruskal(int n, vector<vector<int>> edges) {
    vector<int> parent;
    vector<int> rank(n, 0);
    for(int i = 0; i < n; i++) 
        parent.push_back(i);
    sort(edges.begin(), edges.end(), [](vector<int> a, vector<int> b){
        return a[2] < b[2];
    });
    int totalWeight = 0;
    for(auto a: edges) {
        //find
        int root1 = findParent(a[0], parent);
        int root2 = findParent(a[1], parent);
        if(root1 == root2) 
            continue;
        //union
        if(rank[root1] > rank[root2]) {
            parent[root2] = root1;
        }
        else {
            if(rank[root1] == rank[root2])
                rank[root2]++;
            parent[root1] = root2;
        }
        //print MST & calculate weight;
        cout<<a[0]<<" --> "<<a[1]<<endl;
        totalWeight += a[2];
    }
    int count = 0;
    for(int i = 0; i < n; i++) {
        if(parent[i] == i)
            count++;
    }
    if(count == 1)
        return totalWeight;
    else
        return -1;
}

//Q3
int Dijkstra(int n, vector<vector<int>>& cost) {
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

//Q4
void floydWarshall(vector<vector<int>>& graph) {
    int n = graph.size();
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(graph[i][j] > graph[i][k] + graph[k][j])
                    graph[i][j] = graph[i][k] + graph[k][j];
            }
        }
    }
}
































