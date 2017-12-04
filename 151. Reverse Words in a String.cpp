class Solution {
public:
    void reverseWords(string &s) {
        //solve it in-place
        int index = 0;
        while(s[index] == ' ')
            index++;
        int rebuild = 0;
        while(index < s.size()){
            s[rebuild++] = s[index];
            if(s[index] == ' '){           
                while(index < s.size() && s[index] == ' ')
                    index++;
            }
            else
                index++;
        }
        for(int i = s.size() - 1; i >= rebuild; i--){
            s.pop_back();
        }
        while(s[s.size() - 1] == ' ')
            s.pop_back();
        reverse(s, 0, s.size() - 1);
        for(int i = 0, j = 0; i <= s.size(); i++){
            if(s[i] == ' ' || i == s.size()){
                reverse(s, j, i - 1);
                j = i + 1;
            }
            else
                continue;
        }
    }
    void reverse(string &s, int start, int end){
        if(start >= end)
            return;
        while(start < end){
            swap(s[start++], s[end--]);
        }
    }
};