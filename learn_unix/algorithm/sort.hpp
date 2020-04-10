
#ifndef ALGORITHM_SORT_HPP
#define ALGORITHM_SORT_HPP

#include <vector>

using namespace std;

template <class T>
class ALGSort
{
public:
    ALGSort(vector<T> tmpArray):valueArray(tmpArray) {}
    ~ALGSort() {}

    //ѡ������
    //desc ����Ӵ�С
    bool selectSort(bool desc = true)
    {
        if (valueArray.size() < 1)
        {
            return false;
        }

        int size = valueArray.size();
        for (int i = 0; i < size - 1; i++)
        {
            auto indexIter = valueArray.begin() + i;
            auto tmpIter = valueArray.begin() + i;

            for (auto iter = valueArray.begin() + i + 1; iter != valueArray.end(); iter++)
            {
                if (desc)
                {
                    if (*iter > *indexIter)
                    {
                        indexIter = iter;
                    }
                }
                else
                {
                    if (*iter < *indexIter)
                    {
                        indexIter = iter;
                    }
                }
            }

            if (indexIter != tmpIter)
            {
                swap(*indexIter, *tmpIter);
            }     
        }

        return true;
    }

    //ð������
    //desc ����Ӵ�С
    bool bubbleSort(bool desc = true)
    {
        int size = valueArray.size();

        if (size < 1)
        {
            return false;
        }

        for (int i = 1; i < size; i++)
        {
            auto beginIter = valueArray.begin();
            auto endIter = valueArray.end() - i; //�������������λ
            bool isSwap = false; //�Ƿ���λ�ý���

            for (auto iter = beginIter; iter != endIter; iter++)
            {
                if (desc)
                {
                    if (*iter < *(iter + 1))
                    {
                        swap(*iter, *(iter + 1));
                        isSwap = true;
                    }
                }
                else
                {
                    if (*iter > * (iter + 1))
                    {
                        swap(*iter, *(iter + 1));
                        isSwap = true;
                    }
                }
            }

            //δ��������˵������������
            if (!isSwap)
            {
                return true;
            }
        }

        return true;
    }

    //��������
    //desc ����Ӵ�С
    bool insertSort(bool desc = true)
    {
        int size = valueArray.size();

        if (size < 1)
        {
            return false;
        }

        for (int i = 1; i < size; i++)
        {
            auto beginIter = valueArray.begin() + i; //δ����λ��
            auto endIter = valueArray.begin();

            for (auto iter = beginIter; iter != endIter; iter--)
            {
                if (desc)
                {
                    if (*iter > *(iter - 1))
                    {
                        swap(*iter, *(iter - 1));
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    if (*iter < *(iter - 1))
                    {
                        swap(*iter, *(iter - 1));
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        return true;
    }

    //��������(�ݹ�ⷨ)
    //desc ����Ӵ�С
    bool quickSort1(bool desc = true)
    {
        int size = valueArray.size();

        if (size < 1)
        {
            return false;
        }

        recursiveQuickHelper1(0, size - 1, desc);
        //recursiveQuickHelper2(0, size - 1, desc);
        return true;
        
    }

    //��������(�����ⷨ)
    //desc ����Ӵ�С
    bool quickSort2(bool desc = true)
    {
        int size = valueArray.size();
        if (size < 1)
        {
            return false;
        }

        struct IndexPair
        {
            int start;
            int end;
        };

        //�洢��Ҫ���ŵ�������
        vector<IndexPair> subAarry;

        subAarry.push_back({ 0,size });
        int subIndex = 0; 

        
        while (subAarry.size() > subIndex)
        {
            auto beginIter = valueArray.begin();
            auto endIter = beginIter + valueArray.end();
            auto curSubAarry = subAarry.at(subIndex); //��ǰ���������������
            auto flagValue = *(beginIter + curSubAarry.end());

            int index = curSubAarry.start;
            for (auto iter = beginIter + curSubAarry.start; iter != endIter; iter++)
            {
                if (desc)
                {
                    if (*iter > flagValue)
                    {
                        swap(*iter, *(beginIter + index));
                        index++;
                    }
                }
                else
                {
                    if (*iter < flagValue)
                    {
                        swap(*iter, *(beginIter + index));
                        index++;
                    }
                }

            }

            if ((beginIter + index) != (beginIter + end))
            {
                swap(*(beginIter + index), *(beginIter + end));
            }

            if (index - 1 < curSubAarry.start)
            {
                subAarry.push_back({ curSubAarry.start, index - 1 });
            }

            if (index + 1 > curSubAarry.end)
            {
                subAarry.push_back({ index + 1, curSubAarry.end });
            }

            subIndex++;
        }
        
    }

    //�鲢����(�ݹ�)
    //desc ����Ӵ�С
    bool mergeSort1(bool desc = true)
    {
        const int size = valueArray.size();

        if (size < 1)
        {
            return false;
        }

        recursiveMergeHelper(0, size - 1, desc);
        return true;
    }

    //�鲢����(����)
    //desc ����Ӵ�С
    bool mergeSort2(bool desc = true)
    {
        const int size = valueArray.size();

        if (size < 1)
        {
            return false;
        }

        for (auto len = 2; (len/2) <= size; len *= 2)
        {
            for (auto start = 0; start < size; start += len)
            {
                const int mid = start + len / 2;
                const int end = (start + len - 1) < size ? (start + len - 1) : size - 1;
                mergeOperating(start, mid - 1, mid, end, desc);
            }
        }

        return true;
    }

    //��������(ʹ��ȡֵ��ΧС�������ε�����)
    //desc ����Ӵ�С
    bool countSort1(bool desc = true)
    {
        int size = valueArray.size();

        if (size < 1)
        {
            return false;
        }

        int maxValue = findMaxValue();
        vector<int> tmpArray(maxValue + 1);

        //Ԫ�ص����±�װͰ
        for (auto iter = valueArray.begin(); iter != valueArray.end(); iter++)
        {
            tmpArray.at(*iter)++;
        }

        // 0 1 2 3 4 5 6 7 8 9
        // 2 0 1 0 0 0 0 1 1 1
        auto beginIter = valueArray.begin();
        auto rbeginIter = valueArray.rbegin();
        for (int i = 0; i < tmpArray.size(); i++)
        {
            while (tmpArray.at(i) > 0)
            {
                if (!desc)
                {
                    *beginIter = i;
                    beginIter++;
                }
                else
                {
                    *rbeginIter = i;
                    rbeginIter++;             
                }

                tmpArray.at(i)--;
            }
        }

        return true;
    }

	bool countSort2(bool desc = true)
	{
		int size = valueArray.size();

		if (size < 1)
		{
			return false;
		}

		int maxValue = findMaxValue();
		vector<int> tmpArray(maxValue + 1);

		//Ԫ�ص����±�װͰ
		for (auto iter1 = valueArray.begin(); iter1 != valueArray.end(); iter1++)
		{
            tmpArray.at(*iter1)++;
		}

		// 0 1 2 3 4 5 6 7 8 9
		// 2 0 1 0 0 0 0 1 1 1

        //ͳ���������±�Ԫ����ԭ������±�
        for (auto iter2 = tmpArray.begin() + 1; iter2 != tmpArray.end(); iter2++)
        {
            *iter2 += *(iter2 - 1);
        }

        
        vector<int> mirrorArray(valueArray);
        for (auto iter3 = mirrorArray.begin(); iter3 != mirrorArray.end(); iter3++)
        {
            valueArray.at(tmpArray[*iter3] - 1) = *iter3;
            tmpArray[*iter3]--;
        }

		return true;
	}

    //ϣ������
    //desc ����Ӵ�С
    bool shellSort(bool desc = true)
    {
        const int size = valueArray.size();
        if (size < 1)
        {
            return false;
        }

        int step = 1;
        while (step < size / 3)
        {
            step = 3 * step + 1;
        }

        while (step >= 1)
        {
            //�Ե�ǰstep������������������e.g {0,4,8,12},{1,5,9,13},{2,6,10,14},{3,7,11,15}
            for (int i = step; i < size; ++i)
            {
                //e.g j=4{0,4}; j=5{1,5}; j=6{2,6}; j=7{3,7}; j=8{0,4,8}; j=12{0,4,8,12}
                for (int j = i; j >= step; j -= step)
                {
                    if (desc)
                    {
						if (valueArray[j] > valueArray[j - step])
						{
							swap(valueArray[j], valueArray[j - step]);
						}
                    }
                    else
                    {
                        if (valueArray[j] < valueArray[j - step])
                        {
                            swap(valueArray[j], valueArray[j - step]);
                        }
                    }
                }
            }

            step /= 3;
        }

        return true;
    }

    //��������
    bool radixSort(bool desc = true)
    {
        int size = valueArray.size();
        if (size < 1)
        {
            return false;
        }

        int digit = getMaxDigit();
        int divisor = 1;
        for (int i = 1; i < digit + 1; i++)
        {
            vector<int> tmpArray(10, 0);
            
            for (auto iter1 = valueArray.begin(); iter1 != valueArray.end(); iter1++)
            {
                int index = (*iter1 / divisor) % 10;
                tmpArray.at(index)++;
            }

            for (auto iter2 = tmpArray.begin() + 1; iter2 != tmpArray.end(); iter2++)
            {
                *iter2 += *(iter2 - 1);
            }

            vector<int> mirrorArray(valueArray);
            for (auto iter3 = mirrorArray.begin(); iter3 != mirrorArray.end(); iter3++)
            {
                int index = (*iter3 / divisor) % 10;
                valueArray[tmpArray[index] - 1] = *iter3;
                tmpArray[index]--;
            }

            digit *= 10;
        }
    }

private:
    //ѡ���һ��Ԫ��Ϊ�ָ��
    void recursiveQuickHelper1(int start, int end, bool desc)
    {
        if (end >= start)
        {
            return;
        }

        auto beginIter = valueArray.begin();
        auto segValue = *(beginIter + end); //�ָ��
        auto endIter = beginIter + end;

        int index = start;
        for (auto iter = beginIter + start; iter != endIter; iter++)
        {
            if (desc)
            {
                if (*iter >= segValue)
                {
                    swap(*iter, *(beginIter + index));
                    index++;
                }
            }
            else
            {
                if (*iter <= segValue)
                {
                    swap(*iter, *(beginIter + index));
                    index++;
                }
            }          
        }

        //�����ָ��λ��
        if (index != end)
        {
            swap(*(beginIter + index), *(beginIter + end));
        }

        recursiveQuickHelper1(start, index - 1, desc);
        recursiveQuickHelper1(index + 1, end, desc);

    }

    //ѡ��һ��Ԫ��Ϊ�ָ��
    void recursiveQuickHelper2(int start, int end, bool desc)
    {
        if (end <= start)
        {
            return;
        }

        auto beginIter = valueArray.begin();
        auto endIter = beginIter + start;
        int segValue = *(beginIter + start);
        int index = end;
        for (auto iter = beginIter + end; iter != endIter; iter--)
        {
            if (desc)
            {
                if (*iter <= segValue)
                {
                    if (iter != (beginIter + index))
                    {
                        swap(*iter, *(beginIter + index));
                    }
                    index--;
                }
            }
            else
            {
                if (*iter >= segValue)
                {
                    if (iter != (beginIter + index))
                    {
                        swap(*iter, *(beginIter + index));
                    }
                    index--;
                }
            }
        }

        if (index != start)
        {
            swap(*(beginIter + index), *(beginIter + start));
        }

        recursiveQuickHelper2(start, index - 1, desc);
        recursiveQuickHelper2(index + 1, end, desc);

    }

    void recursiveMergeHelper(int start, int end, bool desc)
    {
        if (end >= start)
        {
            return;
        }

        int mid = start + (end - start) / 2;

        recursiveMergeHelper(start, mid, desc);
        recursiveMergeHelper(mid + 1, end, desc);
        mergeOperating(start, mid, mid + 1, end, desc);

    }

    void mergeOperating(int start1, int end1, int start2, int end2, bool desc)
    {
        int tmpStart = start1;
        vector<T> tmpArray;

        while(start1 <= end1 && start2 <= end2)
        {
            if(desc)
            {
                if (valueArray[start1] >= valueArray[start2])
                {
                    tmpArray.push_back(valueArray[start1]);
                    start1++;
                }
                else
                {
                    tmpArray.push_back(valueArray[start2]);
                    start2++;
                }
            }
            else
            {
                if (valueArray[start1] <= valueArray[start2])
                {
                    tmpArray.push_back(valueArray[start1]);
                    start1++;
                }
                else
                {
                    tmpArray.push_back(valueArray[start2]);
                    start2++;
                }
            }
        }

        while (start1 <= end1)
        {
            tmpArray.push_back(valueArray[start1]);
            start1++;
        }

        while (start2 <= end2)
        {
            tmpArray.push_back(valueArray[start2]);
            start2++;
        }

        for (auto element : tmpArray)
        {
            valueArray[tmpStart++] = element;
        }
    }

    int findMaxValue()
    {
        auto maxIter = valueArray.begin();
        for (auto iter = valueArray.begin() + 1; iter != valueArray.end(); iter++)
        {
            if (*iter > * maxIter)
            {
                maxIter = iter;
            }
        }

        return *maxIter;
    }

    int getMaxDigit()
    {
        const int maxValue = findMaxValue();

        int digit = 1;
        int digitValue = 10;
        while ((maxValue / digitValue) > 0)
        {
            digitValue *= 10;
            digit++;
        }

        return digit;
    }

private:
    vector<T> valueArray;
};

#endif // !ALGORITHM_SORT_HPP
