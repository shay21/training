#include <iostream>
#include <vector>
int majorityElement(std::vector<int>& nums) {
    int count = 0;
    int most = 0;
    
    for (int num : nums) {
        if (count == 0) {
            most = num;
        }
        
        if (num == most) {
            count++;
        } else {
            count--;
        }
    }
    
    return most;
}

int main()
{
    std::vector<int> nums = {1, 2, 1, 2, 1, 2, 1};
    int k = majorityElement(nums);
    std::cout << "majorityElement" << std::endl;
    std::cout << "k: " << k << std::endl;
    return 0;
}