class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int length = nums.size();
        if(k <= 0 || length == 0 || k == length)
            return;
        k %= length;
        reverse(nums, 0, length - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, length - 1);
    }
    void reverse(vector<int>& nums, int start, int end){
        if(start >= end)
            return;
        while(start < end){
            swap(nums[start++], nums[end--]);
        }
    }
};