class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, int> hash1, hash2;
        for(int i = 0; i < s.size(); i++){
            if(hash1[s[i]] != hash2[t[i]])
                return false;
            hash1[s[i]] = i + 1;
            hahs2[t[i]] = i + 1;
        }
        return true;
    }
};