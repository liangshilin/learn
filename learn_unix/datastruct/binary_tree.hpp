#ifndef ALGORITHM_BINARY_TREE_H_
#define ALGORITHM_BINARY_TREE_H_

#include <vector>
#include <queue>
#include <random>
#include <unordered_map>

using namespace std;

struct TreeNode
{
	vector<int> yyy;
	
    int val;
    TreeNode *left;
    TreeNode *right;
	TreeNode* father;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr), father(nullptr) {}

	void delSelf()
    {
		yyy.push_back(6);
		if (nullptr != left)
			left->delSelf();
		if (nullptr != right)
			right->delSelf();

		delete this;
    }
};

class ALGBinaryTree
{
public:
	ALGBinaryTree() = default;
	virtual ~ALGBinaryTree() = default;

	//先序遍历
	static void preOrder(vector<TreeNode*> resultArray, TreeNode* root)
	{
		if (root == nullptr)
		{
			return;
		}
		preOrderHelper(resultArray, root);
	}

	//中序遍历
	static void inOrder(vector<TreeNode*> resultArray, TreeNode* root)
	{
		if(root == nullptr)
		{
			return;
		}

		inOrderHelper(resultArray, root);
	}

	//后序遍历
	static void PostOrder(vector<TreeNode*> resultArray, TreeNode* root)
	{
		if (root == nullptr)
		{
			return;
		}

		PostOrderHelper(resultArray, root);
	}

	//从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行
	vector<vector<int>> levelOrder(TreeNode* root) const
	{
		vector<vector<int>> result;
		if(root == nullptr)
		{
			return  result;
		}

		queue<TreeNode*> queue1, queue2;
		auto cur = &queue1;
		auto next = &queue2;
		cur->push(root);
		
		while(true)
		{
			vector<int> lineResult;

			while(!cur->empty())
			{
				const auto tmpTN = cur->front();
				lineResult.push_back(tmpTN->val);
				if(tmpTN->left != nullptr)
					next->push(tmpTN->left);
				if(tmpTN->right != tmpTN)
					next->push(tmpTN->right);
				cur->pop();		
			}

			result.push_back(lineResult);
			if (next->empty())
				break;

			swap(cur, next);
		}

		return result;
	}

	//二叉树数据结构TreeNode可用来表示单向链表（其中left置空，right为下一个链表节点）。
	//实现一个方法，把二叉搜索树转换为单向链表，要求值的顺序保持不变，转换操作应是原址的，也就是在原始的二叉搜索树上直接修改。
	//返回转换后的单向链表的头节点
	TreeNode* convertBiNode(TreeNode* root)
	{
		if (root == nullptr)
		{
			return nullptr;
		}

		head = new TreeNode(-1);
		prev = head;
		convertBiNode_inOrder(root);
		return prev->right;
	}

	void convertBiNode_inOrder(TreeNode* cur)
	{
		if (cur == nullptr)
		{
			return;
		}

		convertBiNode_inOrder(cur->left);
		cur->left = nullptr;
		head->right = cur;
		head = cur;
		convertBiNode_inOrder(cur->right);
	}

	//根据二叉树的前序遍历和中序遍历的结果，重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字
	TreeNode* rebuildBinaryTree(const vector<int> preArray, const vector<int> inArray)
	{
		int i = 0;
		for (auto value : inArray)
		{
			hash_map[value] = i++;
		}

	}
	//????????????????
	TreeNode* rebuildBinaryTreeHelper(const vector<int>& preArray, int preLeft, int preRight, int inLeft)
	{
	    if(preLeft > preRight)
	    {
			return nullptr;
	    }

		auto* root = new TreeNode(preArray[preLeft]);
		int index = hash_map[preArray[preLeft]];
		int leftSize = index - 1;
		root->left = rebuildBinaryTreeHelper(preArray, preLeft + 1, preLeft + leftSize, inLeft);
		root->right = rebuildBinaryTreeHelper(preArray, preLeft + leftSize + 1, preRight, inLeft + leftSize + 1);

		return root;
	}

	//给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回 。
    //注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针
	TreeNode* findNextNode(TreeNode* root, TreeNode* node)
	{
		if (node->right == nullptr)
		{
			auto father = node->father;
			while(father != nullptr)
			{
			    if(father->left == node)
			    {
					return father;
			    }

				father = father->father;
				node = father;
			}
		}
		else
		{
			node = node->right;
			while (node->left != nullptr)
			{
				node = node->left;
			}

			return node;
		}
	}

	//树中两个节点的最低公共祖先(二叉查找树)
	TreeNode* lowestAncestorNode1(TreeNode* root, TreeNode* elem1, TreeNode* elem2)
	{
	    if(nullptr == root)
	    {
			return nullptr;
	    }

		auto cur = root;
		while (cur != nullptr)
		{
			if (cur->val >= elem1->val && cur->val <= elem2->val)
			{
				return cur;
			}
			else if (cur->val > elem2->val)
			{
				cur = cur->left;
			}
			else if (cur->val < elem1->val)
			{
				cur = cur->right;
			}
		}

		return nullptr;
	}

	//树中两个节点的最低公共祖先(二叉树)
	TreeNode* lowestAncestorNode2(TreeNode* root, TreeNode* elem1, TreeNode* elem2)
	{
		if (nullptr == root)
		{
			return nullptr;
		}

		auto cur = root;
		bool lflag = false;
		bool rflag = false;

		while (cur != nullptr)
		{
			auto left = cur->left;
			auto right = cur->right;

			while (left != nullptr)
			{
			    
			}
		}

		return nullptr;
	}

	//二叉树的直径(最长路径)
	int maxLengthOfBinary(TreeNode* root)
	{
		int result = 1;
		treeDepth(root, result);

		return result - 1;
	}

	int treeDepth(TreeNode* cur, int& result)
	{
		if (cur == nullptr)
		{
			return 0;
		}

		int left = treeDepth(cur->left, result);
		int right = treeDepth(cur->right, result);
		result = max(result, left + right + 1);

		return max(left, right) + 1;
	}

private:
	//生成随机大小的二叉树
	void generateBinaryTree()
	{
	    if(nullptr != root)
	    {
			root->delSelf();
			root = nullptr;
	    }

		// 随机生成数据添加到二叉树上		
		// 以随机值播种，若可能
		std::random_device rd;

		// 选择 1 与 10000 间的随机数
		std::default_random_engine re(rd());
		std::uniform_int_distribution<int> uniform_dist(0, 10000);

		for (int i = 0; i < uniform_dist(re); i++)
		{
			auto tmp = new TreeNode(uniform_dist(re));
			pushElement(tmp);
		}
	}

	void pushElement(TreeNode* element)
	{
		if (nullptr == element)
		{
			return;
		}

		TreeNode** tmp = &root;
		while(*tmp)
		{
		    if(element->val < (*tmp)->val)
		    {
                tmp = &((*tmp)->left);
            }
			else
			{
                tmp = &((*tmp)->right);
            }
		}

		*tmp = element;
	}

	static void preOrderHelper(vector<TreeNode*> resultArray, TreeNode* cur)
	{
		if (cur == nullptr)
		{
			return;
		}

		resultArray.push_back(cur);		
		preOrderHelper(resultArray, cur->left);
		preOrderHelper(resultArray, cur->right);	
	}

	static void inOrderHelper(vector<TreeNode*> resultArray, TreeNode* cur)
	{
		if(cur == nullptr)
		{
			return;
		}

		inOrderHelper(resultArray, cur->left);
		resultArray.push_back(cur);
		inOrderHelper(resultArray, cur->right);	
	}

	static void PostOrderHelper(vector<TreeNode*> resultArray, TreeNode* cur)
	{
		if(cur == nullptr)
		{
			return;
		}

		PostOrder(resultArray, cur->left);
		PostOrder(resultArray, cur->right);
		resultArray.push_back(cur);
	}

private:
	TreeNode* head;
	TreeNode* prev;
	TreeNode* root;
	unordered_map<int, int> hash_map;
};

#endif
