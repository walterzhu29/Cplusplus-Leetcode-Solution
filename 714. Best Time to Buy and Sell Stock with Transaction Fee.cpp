class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n=prices.size();
        if (prices.size()<2) {return 0;}
        vector<int> f(n,0),g(n,0); //f - max profit without a share; g - max profit with a share
        g[0]=-prices[0];
        
        for (int i=1; i<n; i++) {
            f[i]=max(f[i-1],prices[i]-fee+g[i-1]);
            g[i]=max(g[i-1],f[i-1]-prices[i]);
        }
        return f[n-1];
    }
};
