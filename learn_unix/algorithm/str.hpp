#ifndef ALGORITHM_STR_H_
#define ALGORITHM_STR_H_

#include <string>
#include <utility>
#include <unordered_map>

using namespace std;

class ALGStr
{
public:
    ALGStr() = default;
    ALGStr(string&& str11, string&& str22) :str1(move(str11)), str2(move(str22)) {};
    virtual ~ALGStr() = default;

    //判断两个string排序后是否一致
    static bool isSameStrBySort(const string& str1,const string& str2)
    {
        unordered_map<char, int> hashTb;
        for (char tmp : str1)
        {
            if (hashTb.count(tmp))
            {
                hashTb[tmp]++;
            }
            else
            {
                hashTb[tmp] = 1;
            }
        }

        for (auto tmp : str2)
        {
            if (!hashTb.count(tmp))
            {
                return  false;
            }

            if(--hashTb[tmp] < 0)
            {
                return  false;
            }
        }

        return true;
    }

    //给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。
    //请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
    //你可以假设 nums1 和 nums2 不会同时为空
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        int size1 = nums1.size();
        int size2 = nums2.size();
        int midIndex = (size1 + size2) / 2;

        //k n1 n2
        int k = 0;
        int begin1 = 0;
        int end1 = size1 - 1;
        int begin2 = 0;
        int end2 = size2 - 1;
        int tmpk = 2;

        while(true)
        {
            int kIndex = (size1 + size2) / tmpk;

            if(nums1[begin1 + kIndex - 1] < nums2[begin2 + kIndex - 1])
            {
                k += kIndex;
                begin1 = kIndex;
                end2 = kIndex - 1;
            }

            if (nums2[begin2 + kIndex - 1] < nums1[begin1 + kIndex - 1])
            {
                k += kIndex;
                begin2 = kIndex;
                end1 = kIndex - 1;
            }

            tmpk *= 2;

        }
        // 1 2 3 4 5
        // 6 7 8 9 10
        // 1234 56 
        // 6 7 8 9 10 11 
    }

    //输入一个正整数 target ，输出所有和为 target 的连续正整数序列（至少含有两个数）。
    //序列内的数字由小到大排列，不同序列按照首个数字从小到大排列
    vector<vector<int>> findContinuousSequence(int target)
    {
        vector<vector<int>> result;
        if(target < 3)
        {
            return result;
        }

        int A = 1;
        int B = 2;
        int sum = A + B;

        //元素不能大于target/2 + 1，且A<B才能保证至少含两个数
        for (; B <= target / 2 + 1 && A < B;)
        {
            if(sum < target)
            {
                B++;
                sum += B;
            }

            if(sum > target)
            {
                
                sum -= A;
                A++;
            }

            if(sum == target)
            {
                vector<int> subResult;
                for(int j = A;j<=B;j++)
                {
                    subResult.push_back(j);
                }

                result.push_back(subResult);
                A--;
                B++;
                sum = sum + A + B;
            }
        }

        return result;

    }

    //将一个字符串中的空格替换成 "%20"
    static void replace(string& str, char oldchar, string newstr)
    {
        int old_end = str.size() - 1;
        for (auto ch : str)
        {
            if(ch == oldchar)
            {
                //字符串填充两空格
                str.append(newstr);
            }
        }

        int new_end = str.size() - 1;
        while (old_end >= 0 && new_end >= old_end)
        {
            if(str[old_end] == oldchar)
            {
                for (int i = newstr.size() - 1; i >= 0; ++i)
                {
                    str[new_end--] = newstr[i];
                }
            }
            else
            {
                str[new_end--] = str[old_end];
            }

            old_end--;
        }
    }

    //最长不重复子串长度 e.g abcdefgajklidgh
    int maxSubStringLength(string str)
    {
        unordered_map<char, int> indexMap;
        int begin = 0;
        int maxLength = 0;
        int result = 0;

        for (auto i = 0; i < str.length(); i++)
        {
            maxLength++;

            if (indexMap.count(str[i]) > 0)
            {
                if (indexMap[str[i]] >= begin)
                {
                    result = (maxLength - 1) > result ? (maxLength - 1) : result;
                    maxLength = maxLength - (indexMap[str[i]] - begin + 1);
                    begin = indexMap[str[i]] + 1;
                    indexMap[str[i]] = i;
                }
            }

            indexMap[str[i]] = i;
        }

        return maxLength > result ? maxLength : result;
    }

private:
    string str1;
    string str2;
};


#endif
