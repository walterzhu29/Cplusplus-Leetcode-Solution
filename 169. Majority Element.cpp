class Solution {
public:
    int majorityElement(vector<int>& nums) {
        if(nums.size() == 1)
            return nums[0];
        int num = nums[0];
        int time = 1;
        for(int i = 1; i < nums.size(); i++){
            if(time == 0){
                time = 1;
                num = nums[i];
                continue;
            }
            if(nums[i] != num)
                time--;
            else
                time++;
        }
        return num;
    }
};