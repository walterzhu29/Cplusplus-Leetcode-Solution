class Solution {
    public boolean isIsomorphic(String s, String t) {
        if(s == null || t == null)
            return false;
        if(s.length() != t.length())
            return false;
        Map<Character, Character> hash = new HashMap<Character, Character>();
        for(int i = 0; i < s.length(); i++){
            if(hash.containsKey(s.charAt(i))){
                if(hash.get(s.charAt(i)) != t.charAt(i))
                    return false;
            }
            else{
                if(hash.containsValue(t.charAt(i)))
                    return false;
                hash.put(s.charAt(i), t.charAt(i));
            }
        }
        return true;
    }
}