#ifndef ARRAY_H_
#define ARRAY_H_

#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>

using namespace std;

class ALGArray
{
public:
    ALGArray() = default;
    virtual ~ALGArray() = default;

    //找出数组的最大子串和
    //{1,5,-3,7,2,-7,9,3,2,6,-5,8}
    int maxSubNum(vector<int> values)
    {
        size_t size = values.size();
        if(0 == size)
        {
            return 0;
        }

        //假设第一个元素为最大子串和
        int maxNums = values.at(0);
        int nums = 0;

        for (auto element : values)
        {
            //当前元素的累加和
            nums += element;

            //累加和大于最大子串和，更新最大字串和
            if(maxNums < nums)
            {
                maxNums = nums;
            }

            //当前元素累加和小于0，更新累加和为0
            if(nums < 0)
            {
                nums = 0;
            }
        }
    }

    //find数组和等于0的子串
    //{1,2,3,-5,2,4,6,-10}
    pair<int,int> specialSub(vector<int> values)
    {
        size_t size = values.size();
        if(0 == size)
        {
            return make_pair(-1, -1);
        }

        //hash table 存储当前位置的累计和
        unordered_map<int, int> nums_index;
        int numsTmp = 0;

        for (size_t i = 0; i < size; i++)
        {
            numsTmp += values[i];

            //如果累加和已在hash table，说明存在子串和为0
            if(nums_index.count(numsTmp) > 0)
            {
                int firstTmp = nums_index.at(numsTmp);
                int secondTmp = i;
                return make_pair(firstTmp, secondTmp);
            }

            nums_index[numsTmp] = i + 1;
        }

        return make_pair(-1, -1);
    }

    //find数组和等于special num的子串
    //{1,2,3,-5,2,4,6,-10}
    pair<int, int> specialSub(vector<int> values, int specialNum)
    {
        size_t size = values.size();
        if (0 == size)
        {
            return make_pair(-1, -1);
        }

        //hash table 存储当前位置的累计和
        unordered_map<int, int> nums_index;
        int numsTmp = 0;

        for (size_t i = 0; i < size; i++)
        {
            numsTmp += values[i];

            //如果累加和已在hash table，说明存在子串和为0
            if (nums_index.count(numsTmp - specialNum) > 0)
            {
                int firstTmp = nums_index.at(numsTmp - specialNum);
                int secondTmp = i;
                return make_pair(firstTmp, secondTmp);
            }

            nums_index[numsTmp - specialNum] = i + 1;
        }

        return make_pair(-1, -1);
    }

    //找出数组乘积最大的子串的乘积
    long long maxSubProduct(vector<int> values)
    {
        size_t size = values.size();
        if(0 == size)
        {
            return 0;
        }

        //找出数组被0切割的子串
        vector<pair<int, int>> subArray;
        int begin = 0;
        int end = 0;
        for (size_t i = 0; i < size; i++)
        {
            if(0 == values[i])
            {
                end = i - 1;
            }

            if(end >= begin && end > 0)
            {
                subArray.emplace_back(make_pair(begin, end));
            }

            begin = i + 1;
        }

        //存在0元素，最大乘积和不小于0
        int maxNum = 0;
        if(subArray.empty())
        {
            subArray.emplace_back(make_pair(0, size - 1));
            maxNum = values[0];
        }
        
        for (auto arrayTmp : subArray)
        {
            int maxProduct = 1;
            int minProduct = 1;

            //{1, 2, 3, -4, 5, 6, 7, -8, 9, 10, 11, -12, 13, 14, 15}
            for (auto i = arrayTmp.first; i <= arrayTmp.second; i++)
            {
                //当前元素小于0时，替换最大值和最小值
                if(i < 0)
                {
                    const int tmpProduct = minProduct;
                    minProduct = maxProduct;
                    maxProduct = tmpProduct;
                }

                minProduct = minProduct * i < i ? minProduct * i : i;
                maxProduct = maxProduct * i > i ? maxProduct * i : i;

                //如果当前元素位置最大乘积更大则更新最大乘积maxNum
                if (maxNum < maxProduct)
                {
                    maxNum = maxProduct;
                }
            }
        }

        return maxNum;
    }

    //找出数组中3个元素和为0的子串数量
    int threeSum_twoPointer(vector<int> nums) const
    {
        const auto size = nums.size();
        if(size < 3)
        {
            return 0;
        }

        sort(nums.begin(), nums.end());

        int cnt = 0;

        for (int i = 0; i < size - 2; i++)
        {
            int begin = i + 1;
            int end = size - 1;
            const int target = -nums[i];

            while(begin > end)
            {
                if (nums[begin] + nums[end] == target)
                {
                    cnt++;
                    begin++;
                    end--;
                }
                else if (nums[begin] + nums[end] > target)
                {
                    end--;
                }
                else
                {
                    begin++;
                }
            }
        }

        return cnt;
    }

    //在一个长度为 n 的数组里的所有数字都在 0 到 n-1 的范围内。
    //数组中某些数字是重复的，但不知道有几个数字是重复的，
    //也不知道每个数字重复几次。请找出数组中任意一个重复的数字。
    int anyDeplicateNum(vector<int> nums)
    {
        const int n = nums.size();
        if(n < 2)
        {
            return -1;
        }

        for (int i = 0; i < n; i++)
        {
            //当前index的value不等于index时
            //交换元素，使index的value=index
            while(nums[i] != i)
            {
                if(nums[nums[i]] == nums[i])
                {
                    return nums[i];
                }
                else
                {
                    const int tmp = nums[i];
                    nums[i] = nums[nums[i]];
                    nums[nums[i]] = tmp;
                }
            }
        }

        return -1;
    }

    //给定一个二维数组，其每一行从左到右递增排序，从上到下也是递增排序。
    //给定一个数，判断这个数是否在该二维数组中
    bool isInArray(vector<vector<int>> nums, int value)
    {
        if (0 == nums.size())
        {
            return false;
        }

        int row = 0;
        int col = nums[0].size() - 1;

        while(row < nums.size() && col >= 0)
        {
            if (value == nums[row][col])
            {
                return true;
            }
            else if (value > nums[row][col])
            {
                row++;
            }
            else
            {
                col--;
            }

        }

        return false;
    }

    //
};

#endif
