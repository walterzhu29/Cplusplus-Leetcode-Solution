class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        if(tokens.size() == 0)
            return 0;
        stack<int> s;
        for(string str: tokens){
            if(str[0] >= '0' && str[0] <= '9' || str.size() > 1)
                s.push(std::atoi(str.c_str()));
            else
            {
                int b = s.top();
                s.pop();
                int a = s.top();
                s.pop();
                if(str[0] == '+')
                    a += b;
                else if(str[0] == '-')
                    a -= b;
                else if(str[0] == '*')
                    a *= b;
                else if(str[0] == '/')
                    a /= b;
                s.push(a);
            }
        }
        return s.top();
    }
};