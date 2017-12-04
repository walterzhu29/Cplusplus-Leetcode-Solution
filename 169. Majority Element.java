class Solution {
    public int majorityElement(int[] nums) {
        if(nums.length == 1)
            return nums[0];
        int majority = nums[0];
        int time = 1;
        for(int i = 1; i < nums.length; i++){
            if(time == 0){
                majority = nums[i];
                time = 1;
                continue;
            }
            if(nums[i] == majority)
                time++;
            else
                time--;
        }
        return majority;
    }
}