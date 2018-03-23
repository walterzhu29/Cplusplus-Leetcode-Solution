class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int n=s1.length(),m=s2.length();
        vector<vector<int>> f(n+1,vector<int> (m+1,0)); // f[i][j] means minimum ascii sum to match s1[1..i] to s2[1..j]
        for (int j=1; j<=m; j++) {
            f[0][j]=f[0][j-1]+int(s2[j-1]);
        }
        for (int i=1; i<=n; i++) {
            f[i][0]=f[i-1][0]+int(s1[i-1]);
            for (int j=1; j<=m; j++) {
                f[i][j]=min(f[i-1][j]+int(s1[i-1]),f[i][j-1]+int(s2[j-1]));
                if (s1[i-1]==s2[j-1]) {
                    f[i][j]=min(f[i][j],f[i-1][j-1]);
                }
            }
        }
        return (f[n][m]);
        
    }
};
