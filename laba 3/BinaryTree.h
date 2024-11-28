#pragma once
#include <exception>
#include <functional>
template<class T>
using Comparator = std::function<bool(const T&, const T&)>;

template<class T>
struct  TreeNode
{
	T data;
	TreeNode* left;
	TreeNode* right;
	int height;

	TreeNode() : data{}, left{ nullptr }, right{ nullptr }, height{ 1 } {}

	TreeNode(const T& item) : data{ item }, left{ nullptr }, right{ nullptr }, height{ 1 } { }

	TreeNode(const TreeNode<T>& other):
		data(other.data),
		height{ other.height },
		left(other.left ? new TreeNode<T>(*other.left) : nullptr),
		right(other.right ? new TreeNode<T>(*other.right) : nullptr) {}
};

template<class T>
class BinaryTree
{
private:
	TreeNode<T>* root;
	Comparator<T> is_equal;
	Comparator<T> comp;

	void DestroyNode(TreeNode<T>* node)
	{
		if (node != nullptr)
		{
			DestroyNode(node->left);
			DestroyNode(node->right);
			delete node;
		}
	}

	int GetHeight(TreeNode<T>* node) const
	{
		return node ? node->height : 0;
	}

	TreeNode<T>* Search(TreeNode<T>* node, const T& val) const
	{
		if (node == nullptr)
		{
			throw std::out_of_range("Value not found in binary tree");
		}
		else if (is_equal(node->data, val))
		{
			return node;
		}
		else if (comp(val, node->data))
		{
			return Search(node->left, val);
		}
		return Search(node->right, val);
	}

	TreeNode<T>* MinValueNode(TreeNode<T>* node) const
	{
		TreeNode<T>* current = node;
		while (current && current->left != nullptr)
		{
			current = current->left;
		}
		return current;
	}

	TreeNode<T>* DeleteNode(TreeNode<T>* node, T val)
	{
		if (!node) return nullptr;

		if (comp(val, node->data))
		{
			node->left = DeleteNode(node->left, val);
		}
		else if (!comp(val, node->data) && !is_equal(val, node->data))
		{
			node->right = DeleteNode(node->right, val);
		}
		else
		{
			if (!node->left || !node->right)
			{
				TreeNode<T>* temp = node->left ? node->left : node->right;
				delete node;
				return temp;
			}

			TreeNode<T>* temp = MinValueNode(node->right);
			node->data = temp->data;
			node->right = DeleteNode(node->right, temp->data);
		}

		UpdateHeight(node);
		return BalanceNode(node);
	}

	int GetBalance(TreeNode<T>* node) const 
	{
		return node ? GetHeight(node->left) - GetHeight(node->right) : 0;
	}

	void UpdateHeight(TreeNode<T>* node) 
	{
		if (node) 
		{
			node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));
		}
	}

	TreeNode<T>* RotateRight(TreeNode<T>* y) 
	{
		TreeNode<T>* x = y->left;
		TreeNode<T>* temp = x->right;
		x->right = y;
		y->left = temp;

		UpdateHeight(y);
		UpdateHeight(x);

		return x;
	}

	TreeNode<T>* RotateLeft(TreeNode<T>* x) 
	{
		TreeNode<T>* y = x->right;
		TreeNode<T>* temp = y->left;

		y->left = x;
		x->right = temp;

		UpdateHeight(x);
		UpdateHeight(y);

		return y;
	}

	TreeNode<T>* BalanceNode(TreeNode<T>* node) 
	{
		if (!node)
		{
			return node;
		}

		UpdateHeight(node);
		int balance = GetBalance(node);

		if (balance > 1) 
		{
			if (GetBalance(node->left) < 0) 
			{
				node->left = RotateLeft(node->left);
			}
			return RotateRight(node);
		}

		if (balance < -1) 
		{
			if (GetBalance(node->right) > 0) 
			{
				node->right = RotateRight(node->right);
			}
			return RotateLeft(node);
		}
		return node;
	}

	TreeNode<T>* BalanceTree(TreeNode<T>* node)
	{
		if (!node) 
		{
			return nullptr;
		}

		node->left = BalanceTree(node->left);
		node->right = BalanceTree(node->right);

		return BalanceNode(node);
	}


	TreeNode<T>* InsertNode(TreeNode<T>* node, const T& value)
	{
		if (!node)
		{
			return new TreeNode<T>(value);
		}

		if (comp(value, node->data))
		{
			node->left = InsertNode(node->left, value);
		}
		else if (!comp(value, node->data) && !is_equal(value, node->data))
		{
			node->right = InsertNode(node->right, value);
		}
		else
		{
			return node;
		}
		node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));

		return BalanceNode(node);
	}
public:

	~BinaryTree()
	{
		DestroyNode(root);
	}

	BinaryTree() : root{ nullptr }, is_equal{ std::equal_to<T>() }, comp{ std::less<T>() } {}

	BinaryTree(const T& val) : root{ new TreeNode<T>(val) },  is_equal{ std::equal_to<T>() }, comp{ std::less<T>() } {}

	BinaryTree(T* items, int count) : BinaryTree()
	{
		for (int i = 0; i < count; i++)
		{
			Insert(items[i]);
		}
	}


	BinaryTree(const TreeNode<T>& other) : root(new TreeNode<T>(other)), is_equal{ std::equal_to<T>() }, comp{ std::less<T>() } {}

	BinaryTree(const BinaryTree<T>& other) : root{ new TreeNode<T>(*other.root) }, is_equal{ std::equal_to<T>() }, comp{ std::less<T>() } {}

	TreeNode<T>* Search(const T& val) const
	{
		return Search(root, val);
	}

	void DeleteNode(const T& val)
	{
		root = DeleteNode(this->root, val);;
	}

	void Insert(T element)
	{
		root= InsertNode(root, element);
	}

	BinaryTree<T>& operator=(const BinaryTree<T>& other)
	{
		if (this == &other) 
			return *this;

		DestroyNode(root); 

		if (other.root)
		{
			root = new TreeNode<T>(*other.root);
		}
		else
		{
			root = nullptr;
		}

		comp = other.comp;
		is_equal = other.is_equal;

		return *this;
	}

	bool IsEmpty() const
	{
		return root == nullptr;
	}

	int GetHeight() const
	{
		return GetHeight(root);
	}

};

