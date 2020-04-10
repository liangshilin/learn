#ifndef ALGORITHM_LIST_H_
#define ALGORITHM_LIST_H_

#include <unordered_map>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_set>

using namespace std;

struct ListNode
{
	ListNode() :val(-1), prev(nullptr), next(nullptr), random(nullptr) {}
	ListNode(int val):val(val), prev(nullptr), next(nullptr), random(nullptr) {}
	ListNode(const ListNode& old)
	{
		val = old.val;
		prev = old.prev;
		next = old.next;
		random = old.random;
	}

	int val;
	ListNode* prev;
	ListNode* next;
	ListNode* random;
};

class ALGList
{
public:
	ALGList() {}
	virtual ~ALGList(){}

	ListNode* replicateList1()
	{
		auto dummy = new ListNode();
		dummy->next = &myList;
		auto cur = dummy->next;

		//原链表为空链表
		if (cur->next == nullptr)
		{
			auto dup = new ListNode(myList);
			return dup;
		}

		//复制链表的每个元素
		//A->B->C->D
		//A->A->B->B->C->C->D->D
		while (cur->next != nullptr)
		{
			ListNode* tmp = new ListNode();
			//复制当前元素
			tmp->val = cur->val;
			tmp->prev = cur->prev;
			tmp->next = cur->next;
			tmp->random = cur->random;
			//当前元素next指向复制元素
			cur->next = tmp;
			//当前元素往后移
			cur = tmp->next;
		}

		//调整复制元素的random
		cur = dummy->next->next;
		while (cur->next != nullptr)
		{
			cur->random = cur->random->next;
			cur = cur->next->next;//下一个复制元素
		}
		
		//调整复制元素的prev
		cur = dummy->next->next;
		while (cur->next != nullptr)
		{
			cur->prev = cur->prev->next;
			cur = cur->next->next; //下一个复制的元素
		}

		//获取复制的链表
		//A->B->C->D
		//A->A->B->B->C->C->D->D
		cur = dummy->next;
		auto dup = dummy->next->next;
		while (dup != nullptr)
		{
			cur->next = dup->next;
			dup->next = cur->next->next;

			cur = cur->next;
			dup = dup->next;
		}
		return dup;
	}

	ListNode* replicateList2()
	{
		//链表只有一个元素
		if (myList.next == nullptr)
		{
			return new ListNode(myList);
		}

		//映射对应的链表和链表地址
		//A->B->C->D
		unordered_map<ListNode*, ListNode*> listTb;
		auto dummy = new ListNode(); 
		dummy->next = new ListNode(myList); //复制链表第一个元素
		listTb[&myList] = dummy->next; //旧元素映射新元素

		auto cur = myList.next;
		auto dup = dummy->next;
		while (cur != nullptr)
		{
			auto tmp = new ListNode(*cur); //复制元素
			listTb[cur] = tmp; //旧元素映射新元素
			dup->next = tmp;
			dup = tmp;
			cur = cur->next;
		}

		//调整复制链表元素的prev和random
		cur = dummy->next;
		while (cur != nullptr)
		{
			cur->prev = listTb[cur->prev];
			cur->random = listTb[cur->random];
			cur = cur->next;
		}

		return dummy->next;
	}
	
	//输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，
	//本题从1开始计数，即链表的尾节点是倒数第1个节点。例如，一个链表有6个节点，
	//从头节点开始，它们的值依次是1、2、3、4、5、6。这个链表的倒数第3个节点是值为4的节点。
	static ListNode* getKthFromEnd(ListNode* head, int k) {
		if(head == nullptr)
		{
			return nullptr;
		}
		
		auto dummy1 = head;
		auto dummy2 = head;

		//dummy1先走K步
		for (int i = 0; i < k; i++)
		{
			//原链表不够K个节点返回false
			if(dummy1 == nullptr)
			{
				return nullptr;
			}

			dummy1 = dummy1->next;
		}

		//dummy1,dummy同时走，当dummy1走到尾端，此时dummy2在倒数第K个节点
		while(dummy1!=nullptr && dummy2 != nullptr)
		{
			dummy1 = dummy1->next;
			dummy2 = dummy2->next;
		}

		return dummy2;
	}
	
	/*给定一个单链表 L：L0→L1→…→Ln-1→Ln 
	将其重新排列后变为： L0→Ln→L1→Ln-1→L2→Ln-2→…
	你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。*/
	void reorderList1(ListNode* head) {
		if (head == nullptr)
		{
			return;
		}

		if (head->next == nullptr || head->next->next == nullptr)
		{
			return;
		}

		vector<ListNode*> listVector;
		//获取链表节点数
		auto cur = head;
		while (cur != nullptr)
		{
			listVector.push_back(cur);
			cur = cur->next;
		}

		int index1 = 0;
		int index2 = listVector.size() - 1;
		ListNode* dummy = new ListNode();
		for (auto i = 0; i < listVector.size(); i++)
		{
			if (index1 == index2)
			{
				dummy->next = listVector[index1];
				listVector[index1]->next = nullptr;
				break;
			}
			if (index1 > index2)
			{
				dummy->next = nullptr;
				break;
			}

			dummy->next = listVector[index1];
			listVector[index1]->next = listVector[index2];
			dummy = listVector[index2];
			index1++;
			index2--;
		}
		return;
	}

	void reorderList2(ListNode* head)
	{
		if(head == nullptr || head->next == nullptr || head->next->next == nullptr)
		{
			return;
		}

		//找到链表的中间节点
		auto oneStep = head;
		auto twoStep = head;
		// 1 2 3 4 5 6
		// 1 3 5 7 9 10 
		while(twoStep != nullptr )
		{
			if (twoStep->next == nullptr)
			{
				twoStep = nullptr;
				break;
			}
			
			oneStep = oneStep->next;			
			twoStep = twoStep->next->next;
		}

		//后半段链表逆序
		auto cur = oneStep;
		auto next = cur->next;
		while(next != nullptr)
		{
			const auto tmp = next->next;
			next->next = cur;
			cur = next;
			next = tmp;
		}

		// 1 2 3
		// 6 5 4
		// 1 2 3
		// 7 6 5 4
		auto second = cur;
		auto first = head;
		while(first != oneStep)
		{
			const auto tmp1 = first->next;
			const auto tmp2 = second->next;
			first->next = second;
			second->next = tmp1;
			second = tmp2;
			first = tmp1;
		}

		first->next = nullptr;
		
	}

	//编写一个函数，检查输入的链表是否是回文的 如1->2->2->1,1->2->3->2->1
	bool isPalindrome(ListNode* head) {

		if(head == nullptr || head->next == nullptr)
		{
			return true;
		}

		auto slow = head;
		auto fast = head;
		//快慢指针找到中间节点
		while(fast != nullptr && fast->next != nullptr)
		{
			slow = slow->next;
			fast = fast->next->next;
			
		}

		if(fast != nullptr)
		{
			slow = slow->next;
		}

		auto mid = slow; //存储中间节点
		fast = slow->next;
		while(fast != nullptr)
		{
			const auto tmp = fast->next;
			fast->next = slow;
			slow = fast;
			fast = tmp;
		}
		mid->next = nullptr;

		//比较前后半段是否一致
		auto prevHalf = head;
		auto backHalf = slow;
		while(backHalf != nullptr)
		{
		    if(prevHalf->val != backHalf->val)
		    {
				//isPalindromeHelper(slow, mid);
				return false;
		    }

			prevHalf = prevHalf->next;
			backHalf = backHalf->next;
		}

		//isPalindromeHelper(slow, mid);
		return true;
	}

	void isPalindromeHelper(ListNode* begin, ListNode* end)
	{
		if(begin == nullptr || begin->next == nullptr)
		{
			return;
		}

		auto tmp1 = begin;
		auto tmp2 = begin->next;

		while(tmp2 != end)
		{
			auto tmp3 = tmp2->next;
			tmp2->next = tmp1;
			tmp1 = tmp2;
			tmp2 = tmp3;
		}

		return;
	}

	//去除链表重复的元素,返回头节点
	//用hashtable
	ListNode* removeDuplicateNodes(ListNode* head)
	{
	    if(head == nullptr || head->next == nullptr)
	    {
			return head;
	    }

		unordered_set<int> uniqueLists;
		
		auto prev = head;
		auto cur = head->next;
		uniqueLists.insert(prev->val);
		while(cur != nullptr)
		{
			if(uniqueLists.count(cur->val) > 0)
			{
				auto tmp = cur;
				prev->next = cur->next;
				cur = cur->next;
				delete tmp;
				continue;;
			}

			uniqueLists.insert(cur->val);
			prev = prev->next;
			cur = cur->next;
		}

		return head;
	}

	//给定两个用链表表示的整数，每个节点包含一个数位
	//这些数位是反向存放的，也就是个位排在链表首部
    //编写函数对这两个整数求和，并用链表形式返回结果
    //输入：(7 -> 1 -> 6) + (5 -> 9 -> 2)，即617 + 295
	//输出：2 -> 1 -> 9，即912
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
		if(l1 == nullptr)
		{
			return l2;
		}

		if(l2 == nullptr)
		{
			return l1;
		}

		const auto dummy = new ListNode();
		auto cur = dummy;
		int carry = 0;
		auto tmp1 = l1;
		auto tmp2 = l2;
		int first, second;
		while(tmp1 != nullptr || tmp2 != nullptr || carry != 0)
		{
			if (tmp1 == nullptr)
				first = 0;
			else
				first = tmp1->val;

			if (tmp2 == nullptr)
				second = 0;
			else
				second = tmp2->val;
		
			auto tmpValue = first + second + carry;
		    carry = tmpValue/10;
			tmpValue = tmpValue % 10;
				
			cur->next = new ListNode(tmpValue);
			cur = cur->next;

			if (tmp1 == nullptr)
				tmp1 = nullptr;
			else
				tmp1 = tmp1->next;

			if (tmp2 == nullptr)
				tmp2 = nullptr;
			else
				tmp2 = tmp2->next;
		}

		return dummy->next;
	}

	ListNode* addTwoNumberStandard(ListNode* l1, ListNode* l2)
	{
		int carry_bit = 0;
		ListNode* l_sum = new ListNode(-1);
		ListNode* l_sum_bak = l_sum;

		while (l1 && l2) {
			int sum = l1->val + l2->val + carry_bit;
			int cur_bit = sum % 10;
			carry_bit = sum / 10;

			l_sum_bak->next = new ListNode(cur_bit);
			l_sum_bak = l_sum_bak->next;

			l1 = l1->next;
			l2 = l2->next;
		}

		ListNode* l_remain = l1;
		(l1 && !l2) ? (l_remain = l1) : (!l1 && l2) ? (l_remain = l2) : 0;
		while (l_remain) {
			int sum = l_remain->val + carry_bit;
			int cur_bit = sum % 10;
			carry_bit = sum / 10;
			l_sum_bak->next = new ListNode(cur_bit);
			l_sum_bak = l_sum_bak->next;
			l_remain = l_remain->next;
		}

		if (carry_bit) {
			l_sum_bak->next = new ListNode(carry_bit);
		}

		return l_sum->next;
		
	}

	//两个链表第一个相交的节点
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
    {
		if(headA == nullptr || headB == nullptr)
		{
			return nullptr;
		}
		auto A = headA;
		auto B = headB;

		while (A != nullptr && B != nullptr)
		{
			A = A->next;
			B = B->next;
		}

		//两个链表长度一样
		if (A == nullptr && B == nullptr)
		{
			A = headA;
			B = headB;
			while (A != nullptr && B != nullptr)
			{
				if (A == B)
				{
					return A;
				}

				A = A->next;
				B = B->next;
			}
			return nullptr;
		}

		//两个链表长度不一致
		if (B == nullptr)
		{
			B = headA;
		}
		else if(A == nullptr)
		{
			A = headB;
		}

		while(A != nullptr && B != nullptr)
		{
			A = A->next;
			B = B->next;
		}

		if (B == nullptr)
		{
			B = headA;
		}
		else if (A == nullptr)
		{
			A = headB;
		}

		while(A != nullptr && B != nullptr)
		{
		    if(A == B)
		    {
				return A;
		    }
		}

		return nullptr;
	}

	//从尾到头打印链表(递归)
	vector<ListNode*> reverseOrderPrint1(ListNode* head)
	{
		//vector<ListNode*> result;
		if (head == nullptr)
		{
			result.clear();
			return result;
		}

		reverseOrderPrintHelper(head);
		return result;
	}

	void reverseOrderPrintHelper(ListNode* element)
	{
		if (element == nullptr)
		{
			return;
		}

		reverseOrderPrintHelper(element->next);
		result.push_back(element);
	}

	//使用栈
	vector<ListNode*> reverseOrderPrint2(ListNode* head)
	{
		if (head == nullptr)
		{
			result.clear();
			return result;
		}

		stack<ListNode*> stack_tmp;
		auto cur = head;
		while (cur != nullptr)
		{
			stack_tmp.push(cur);
			cur = cur->next;
		}

		while(!stack_tmp.empty())
		{
			result.push_back(stack_tmp.top());
			stack_tmp.pop();
		}

		return result;
	}

private:
	ListNode myList;
	vector<ListNode*> result;
};


#endif
