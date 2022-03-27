#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Node
{
    int val;     //节点值
    int size;    //以该节点为根的BST的大小
    int cnt;     //值为val的元素的个数
    int dep;     //以该节点为根的BST的高度
    Node *left;  //左子树
    Node *right; //右子树
    Node(int val) : val(val), size(1), cnt(1), dep(1), left(nullptr), right(nullptr) {}
};
class BST
{
public:
    BST() : root(nullptr), s(0) {}
    ~BST()
    {
        mclear(root);
    }

    void add(int val)
    {
        root = madd(root, val);
    }

    int size()
    {
        return root->size;
    }

    bool empty()
    {
        return root->size == 0;
    }

    bool contain(int val)
    {
        return mcontain(root, val);
    }
    //非递归版本
    bool contain1(int val)
    {
        auto tmp = root;
        while (tmp)
        {
            if (tmp->val == val)
                return true;
            else if (tmp->val > val)
                tmp = tmp->left;
            else
                tmp = tmp->right;
        }
        return false;
    }

    //写一个前序当代表其他不写了
    void preOrder()
    {
        vector<int> res;
        mpre(root, res);
        for (auto c : res)
            cout << c;
        cout << endl;
    }

private:
    Node *root; //根节点
    void mclear(Node *node)
    {
        if (!node)
            return;
        mclear(node->left);
        mclear(node->right);
        delete[] node;
        node = nullptr;
    }
    //以root为根的BST是否包含元素val
    bool mcontain(Node *root, int val)
    {
        // base
        if (!root)
            return false;

        if (val = root->val)
            return true;
        if (val < root->val)
            mcontain(root->left, val);
        else
            mcontain(root->right, val);
        return false;
    }
    //返回插入新节点后BST的根
    Node *madd(Node *node, int val)
    {
        // base
        if (node == nullptr)
        {
            s++;
            return new Node(val);
        }
        //递归的插入节点
        if (val < node->val)
        {
            node->left = madd(node->left, val);
        }
        else if (val > node->val)
        {
            node->right = madd(node->right, val);
        }

        return node;
    }

    void mpre(Node *node, vector<int> &res)
    {
        if (!node)
            return;
        res.push_back(node->val);
        mpre(node->left, res);
        mpre(node->right, res);
    }
};

int main()
{
    BST tree;
    cout << tree.empty() << endl;
    tree.add(3);
    tree.add(7);
    cout << tree.contain1(7) << endl;
    cout << tree.size() << endl;
    cout << tree.contain(7) << endl;
    tree.preOrder();
    cout << tree.size() << endl;
}