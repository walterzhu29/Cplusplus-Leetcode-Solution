class Solution {
    public int evalRPN(String[] tokens) {
        if(tokens.length == 0)
            return 0;
        Stack<Integer> s = new Stack<Integer>();
        for(String str: tokens){
            if(str.equals("+"))
                s.push(s.pop() + s.pop());
            else if(str.equals("*"))
                s.push(s.pop() * s.pop());
            else if(str.equals("-")){
                int b = s.pop();
                int a = s.pop();
                s.push(a - b);
            }
            else if(str.equals("/")){
                int b = s.pop();
                int a = s.pop();
                s.push(a / b);
            }
            else
                s.push(Integer.parseInt(str));
        }
        return s.peek();
    }
}