#include <iostream>
#include <vector>

int removeDuplicates(std::vector<int>& nums)
{
    int prev = nums[0];
    int count = 1;
    int countErased = 0;
    for (int i = 1;i < nums.size() ;i++)
    {
        int current = nums[i];
        if (current == prev)
        {
            count++;
            if (count > 2)
            {
                countErased += 1;
                
            }
        }
        else
        {
            count = 1;
        }
        nums[i - countErased] = current;
        prev = current;
    }
    return nums.size() - countErased;
}

int main()
{
    std::vector<int> nums = {1, 1, 1, 2, 2, 3};
    int k = removeDuplicates(nums);
    std::cout << "k: " << k << std::endl;
     // print nums
    for (int i = 0; i < nums.size(); i++)
    {
        
        if (k - 1 < i)
        {
            std::cout << "x ";
        }
        else
        {
            std::cout << nums[i] << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}