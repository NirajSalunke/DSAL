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
};

class BST
{
private:
    Node *root;

    void insert(Node *&root, Node *tobeInserted)
    {
        if (root == NULL)
        {
            root = tobeInserted;
            return;
        }
        if (tobeInserted->data < root->data)
        {
            insert(root->left, tobeInserted);
        }
        else
        {
            insert(root->right, tobeInserted);
        }
    }

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

    void swapChildren(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        swapChildren(root->left);
        swapChildren(root->right);
        swap(root->left, root->right);
    }

    int findHeight(Node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        return 1 + max(findHeight(root->left), findHeight(root->right));
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

    Node *copyTree(Node *root)
    {
        if (root == NULL)
        {
            return NULL;
        }
        Node *copyRoot = new Node(root->data);
        copyRoot->left = copyTree(root->left);
        copyRoot->right = copyTree(root->right);
        return copyRoot;
    }

    void recur(Node *root, int &count, int flag)
    {
        if (root == NULL)
        {
            return;
        }
        recur(root->left, count, flag);

        if (flag == 1 && (root->left != NULL || root->right != NULL))
        {
            count++;
        }
        else if (flag == -1 && (root->left == NULL && root->right == NULL))
        {
            count++;
        }
        else if (flag == 0)
        {
            count++;
        }

        recur(root->right, count, flag);
    }

public:
    BST() { root = NULL; }

    void insert(int val)
    {
        Node *newNode = new Node(val);
        insert(root, newNode);
    }

    void inOrder() { inOrderRecursive(root); }
    void preOrder() { preOrderRecursive(root); }
    void postOrder() { postOrderRecursive(root); }

    void swapTree() { swapChildren(root); }

    int height() { return findHeight(root); }

    BST copy()
    {
        BST newTree;
        newTree.root = copyTree(root);
        return newTree;
    }

    int countNodes()
    {
        int count = 0;
        recur(root, count, 0);
        return count;
    }

    int countInternalNodes()
    {
        int count = 0;
        recur(root, count, 1);
        return count;
    }

    int countLeafNodes()
    {
        int count = 0;
        recur(root, count, -1);
        return count;
    }

    void clearTree()
    {
        deleteWholeTree(root);
        root = NULL;
    }
};

int main()
{
    BST tree;
    int choice, val;

    do
    {
        cout << "\nMenu:";
        cout << "\n1. Insert Node";
        cout << "\n2. Inorder Traversal";
        cout << "\n3. Preorder Traversal";
        cout << "\n4. Postorder Traversal";
        cout << "\n5. Swap Tree";
        cout << "\n6. Find Height";
        cout << "\n7. Copy Tree";
        cout << "\n8. Count All Nodes";
        cout << "\n9. Count Internal Nodes";
        cout << "\n10. Count Leaf Nodes";
        cout << "\n11. Clear Tree";
        cout << "\n12. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert: ";
            cin >> val;
            tree.insert(val);
            break;
        case 2:
            cout << "Inorder Traversal: ";
            tree.inOrder();
            cout << endl;
            break;
        case 3:
            cout << "Preorder Traversal: ";
            tree.preOrder();
            cout << endl;
            break;
        case 4:
            cout << "Postorder Traversal: ";
            tree.postOrder();
            cout << endl;
            break;
        case 5:
            tree.swapTree();
            cout << "Tree swapped." << endl;
            break;
        case 6:
            cout << "Height of Tree: " << tree.height() << endl;
            break;
        case 7:
        {
            BST copiedTree = tree.copy();
            cout << "Tree copied." << endl;
            break;
        }
        case 8:
            cout << "Total Nodes: " << tree.countNodes() << endl;
            break;
        case 9:
            cout << "Internal Nodes: " << tree.countInternalNodes() << endl;
            break;
        case 10:
            cout << "Leaf Nodes: " << tree.countLeafNodes() << endl;
            break;
        case 11:
            tree.clearTree();
            cout << "Tree cleared." << endl;
            break;
        case 12:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 12);

    return 0;
}
