/*
Beginning with an empty binary tree, construct binary tree by inserting
the values in the order given. After constructing a binarytree perform
following operationson it-
• Perform inorder, preorder and post order traversal
• Change a tree so that the roles of the left and right pointers are
swapped atevery node
• Find the height of tree
• Copy this tree to another [operator=]
• Count number of leaves, number of internal nodes.
• Erase all nodes in a binary tree. (Implement both recursive and non
recursive methods)

*/
#include <iostream>
#include <stack>
using namespace std;

class Node
{
public:
    int data;
    Node *left, *right;
    Node(int val)
    {
        data = val;
        left = right = NULL;
    }
    friend BST;
};
class BST
{
private:
    Node *root;
    // Inorder Recursive
    void inOrderRecursive(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        inOrderRecursive(root->left);
        cout << root->data << " ";
        inOrderRecursive(root->right);
    }
    // Pre Order Recursive
    void preOrderRecursive(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        cout << root->data << " ";
        preOrderRecursive(root->left);
        preOrderRecursive(root->right);
    }
    // Post order Recursive
    void postOrderRecursive(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        postOrderRecursive(root->left);
        postOrderRecursive(root->right);
        cout << root->data << " ";
    }

    // Inorder Iterative
    void inOrderIterative(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        stack<Node *> stackInorder;
        Node *current = root;
        while (current != NULL && !stackInorder.empty())
        {
            while (current != NULL)
            {
                stackInorder.push(current);
                current = current->left;
            }
            current = stackInorder.top();
            stackInorder.pop();
            cout << current->data << " ";
            current = current->right;
        }
    }

    void preorderIterative(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        stack<Node *> stackPreorder;
        Node *current = root;
        stackPreorder.push(root);
        while (current != NULL && !stackPreorder.empty())
        {
            current = stackPreorder.top();
            stackPreorder.pop();
            cout << current->data << " ";
            if (current->right != NULL)
            {
                stackPreorder.push(current->right);
            }
            if (current->left != NULL)
            {
                stackPreorder.push(current->left);
            }
        }
    }
    void postorderIterative(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        stack<Node *> stackPostOrder1;
        stack<Node *> stackPostOrder2;

        Node *current = root;
        stackPostOrder1.push(root);
        while (current != NULL && !stackPostOrder1.empty())
        {
            current = stackPostOrder1.top();
            stackPostOrder1.pop();
            stackPostOrder2.push(current);
            if (current->left != NULL)
            {
                stackPostOrder1.push(current->left);
            }
            if (current->right != NULL)
            {
                stackPostOrder1.push(current->right);
            }
        }
        while (!stackPostOrder2.empty())
        {
            cout << stackPostOrder2.top()->data << " ";
            stackPostOrder2.pop();
        }
    }

    int findHeight(Node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        return 1 + max(findHeight(root->left), findHeight(root->right));
    }

    // counting internal nodes or all nodes using inorder
    void recur(Node *root, int &count, int flag)
    {
        if (root == NULL)
        {
            return;
        }
        recur(root->left, count, flag);

        // flag = 1 for Internal nodes
        // flag = 0 for All Nodes
        // flag = -1 for Lead Nodes

        if (flag == 1)
        {
            if (root->left != NULL || root->right != NULL)
            {
                count++;
            }
        }
        else if (flag == -1)
        {
            if (root->left == NULL && root->right == NULL)
            {
                count++;
            }
        }
        else
        {
            count++;
        }
        recur(root->right, count, flag);
    }
    int countNodes(Node *root)
    {
        int flag = 0;
        int count = 0;
        recur(root, count, flag);
        return count;
    }
    int countInternalNodes(Node *root)
    {
        int flag = 1;
        int count = 0;
        recur(root, count, flag);
        return count;
    }
    int countLeafNodes(Node *root)
    {
        int flag = -1;
        int count = 0;
        recur(root, count, flag);
        return count;
    }

    void deleteWholeTree(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        deleteWholeTree(root->left);
        deleteWholeTree(root->right);
        delete root;
    }
    BST operator=(BST &obj)
    {
        if (this == &obj)
        {
            return *this;
        }
        deleteWholeTree(this->root);
        this->root = copyTree(obj.root);
        return *this;
    }
    Node *copyTree(Node *root)
    {
        if (root == NULL)
        {
            return NULL;
        }
        Node *copyRoot = new Node(*root);
        copyRoot->left = copyTree(root->left);
        copyRoot->right = copyTree(root->right);

        return copyRoot;
    }

public:
    BST(Node *n) // Paramter wala constructor
    {
        root = n;
    }

    BST() // Bina Parameter wala constructorś
    {
        root = NULL;
    }
};

int main()
{

    return 0;
}