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

    //�ҳ����������Ӵ���
    //{1,5,-3,7,2,-7,9,3,2,6,-5,8}
    int maxSubNum(vector<int> values)
    {
        size_t size = values.size();
        if(0 == size)
        {
            return 0;
        }

        //�����һ��Ԫ��Ϊ����Ӵ���
        int maxNums = values.at(0);
        int nums = 0;

        for (auto element : values)
        {
            //��ǰԪ�ص��ۼӺ�
            nums += element;

            //�ۼӺʹ�������Ӵ��ͣ���������ִ���
            if(maxNums < nums)
            {
                maxNums = nums;
            }

            //��ǰԪ���ۼӺ�С��0�������ۼӺ�Ϊ0
            if(nums < 0)
            {
                nums = 0;
            }
        }
    }

    //find����͵���0���Ӵ�
    //{1,2,3,-5,2,4,6,-10}
    pair<int,int> specialSub(vector<int> values)
    {
        size_t size = values.size();
        if(0 == size)
        {
            return make_pair(-1, -1);
        }

        //hash table �洢��ǰλ�õ��ۼƺ�
        unordered_map<int, int> nums_index;
        int numsTmp = 0;

        for (size_t i = 0; i < size; i++)
        {
            numsTmp += values[i];

            //����ۼӺ�����hash table��˵�������Ӵ���Ϊ0
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

    //find����͵���special num���Ӵ�
    //{1,2,3,-5,2,4,6,-10}
    pair<int, int> specialSub(vector<int> values, int specialNum)
    {
        size_t size = values.size();
        if (0 == size)
        {
            return make_pair(-1, -1);
        }

        //hash table �洢��ǰλ�õ��ۼƺ�
        unordered_map<int, int> nums_index;
        int numsTmp = 0;

        for (size_t i = 0; i < size; i++)
        {
            numsTmp += values[i];

            //����ۼӺ�����hash table��˵�������Ӵ���Ϊ0
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

    //�ҳ�����˻������Ӵ��ĳ˻�
    long long maxSubProduct(vector<int> values)
    {
        size_t size = values.size();
        if(0 == size)
        {
            return 0;
        }

        //�ҳ����鱻0�и���Ӵ�
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

        //����0Ԫ�أ����˻��Ͳ�С��0
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
                //��ǰԪ��С��0ʱ���滻���ֵ����Сֵ
                if(i < 0)
                {
                    const int tmpProduct = minProduct;
                    minProduct = maxProduct;
                    maxProduct = tmpProduct;
                }

                minProduct = minProduct * i < i ? minProduct * i : i;
                maxProduct = maxProduct * i > i ? maxProduct * i : i;

                //�����ǰԪ��λ�����˻�������������˻�maxNum
                if (maxNum < maxProduct)
                {
                    maxNum = maxProduct;
                }
            }
        }

        return maxNum;
    }

    //�ҳ�������3��Ԫ�غ�Ϊ0���Ӵ�����
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

    //��һ������Ϊ n ����������������ֶ��� 0 �� n-1 �ķ�Χ�ڡ�
    //������ĳЩ�������ظ��ģ�����֪���м����������ظ��ģ�
    //Ҳ��֪��ÿ�������ظ����Ρ����ҳ�����������һ���ظ������֡�
    int anyDeplicateNum(vector<int> nums)
    {
        const int n = nums.size();
        if(n < 2)
        {
            return -1;
        }

        for (int i = 0; i < n; i++)
        {
            //��ǰindex��value������indexʱ
            //����Ԫ�أ�ʹindex��value=index
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

    //����һ����ά���飬��ÿһ�д����ҵ������򣬴��ϵ���Ҳ�ǵ�������
    //����һ�������ж�������Ƿ��ڸö�ά������
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
