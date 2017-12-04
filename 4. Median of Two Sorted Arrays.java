class Solution {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        int m = nums1.length, n = nums2.length;
        if((m + n) % 2 == 0)
            return (getKth(0, 0, (m + n) / 2, nums1, nums2) + getKth(0, 0, (m + n) / 2 + 1, nums1, nums2)) / 2.0;
        else
            return (double)getKth(0, 0, (m + n) / 2 + 1, nums1, nums2);
    }
    int getKth(int start1, int start2, int k, int[] nums1, int[] nums2){
        if(start1 >= nums1.length)
            return nums2[start2 + k - 1];
        if(start2 >= nums2.length)
            return nums1[start1 + k - 1];
        if(k == 1)
            return nums1[start1] > nums2[start2] ? nums2[start2] : nums1[start1];
        int half = k / 2;
        int i = Math.min(half, nums1.length);
        int j = Math.min(half, nums2.length);
        if(nums1[start1 + i - 1] > nums2[start2 + j - 1])
            return getKth(start1, start2 + j, k - j, nums1, nums2);
        else
            return getKth(start1 + i, start2, k - i, nums1, nums2);
    }
}