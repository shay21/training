#include <iostream>
#include <vector>
#include <algorithm>

void rotate(std::vector<int>& nums, int k)
{
    reverse(nums.begin(), nums.end()); 
    reverse(nums.begin(), nums.begin()+k);   
    reverse(nums.begin()+k, nums.end()); 
}
int main()
{
    int k = 3;
    std::vector<int> nums = {1,2,3,4,5,6,7};
    std::cout << "nums before : ";
    for (int i = 0; i < nums.size(); i++)
    {
        std::cout << nums[i] << " ";
    }
    std::cout << std::endl;
    rotate(nums, k);
    std::cout << "nums after " << k << ": ";
    for (int i = 0; i < nums.size(); i++)
    {
        std::cout << nums[i] << " ";
    }

    
}