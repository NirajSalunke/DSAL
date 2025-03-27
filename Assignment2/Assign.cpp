#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *left, *right;
    Node(int val)
    {
        data = val;
        left = NULL;
        right = NULL;
    }
};

class BST
{
private:
    Node *root;

    void swapChildren(Node *root)
    {
        if (root == NULL)
        {
            return;
        }

        Node *temp = root->left;
        root->left = root->right;
        root->right = temp;

        swapChildren(root->left);
        swapChildren(root->right);
    }

    void insertNode(Node *&root, Node *tobeInserted)
    {
        if (root == NULL)
        {
            root = tobeInserted;
            return;
        }
        if (tobeInserted->data < root->data)
        {
            insertNode(root->left, tobeInserted);
        }
        else
        {
            insertNode(root->right, tobeInserted);
        }
    }

    bool search(Node *root, int key)
    {
        if (root == NULL)
        {
            return false;
        }
        if (root->data == key)
        {
            return true;
        }
        else if (key < root->data)
        {
            return search(root->left, key);
        }
        else
        {
            return search(root->right, key);
        }
    }

    int minNode(Node *root)
    {
        if (root == NULL)
        {
            return INT_MIN;
        }

        Node *current = root;
        while (current->left)
        {
            current = current->left;
        }
        return current->data;
    }

    int maxNode(Node *root)
    {
        if (root == NULL)
        {
            return INT_MAX;
        }

        Node *current = root;
        while (current->right)
        {
            current = current->right;
        }
        return current->data;
    }

    int longestPath(Node *root)
    {
        if (root == NULL)
        {
            return 0;
        }

        int leftPath = longestPath(root->left);
        int rightPath = longestPath(root->right);

        return max(leftPath, rightPath) + 1;
    }

public:
    BST()
    {
        root = NULL;
    }

    void insert(int val)
    {
        Node *newNode = new Node(val);
        insertNode(root, newNode);
    }
    void insertArray(int arr[], int size)
    {
        for (int i = 0; i < size; i++)
        {
            insert(arr[i]);
        }
    }

    void swapTree()
    {
        swapChildren(root);
    }

    int longestPathOfTree()
    {
        return longestPath(root);
    }

    bool searchNode(int key)
    {
        return search(root, key);
    }

    int maxDataInTree()
    {
        return maxNode(root);
    }

    int minDataInTree()
    {
        return minNode(root);
    }
};

int main()
{
    BST bst;
    int choice;

    do
    {
        cout << "\nMenu:\n";
        cout << "1. Insert a node\n";
        cout << "2. Insert multiple nodes\n";
        cout << "3. Find number of nodes in the longest path\n";
        cout << "4. Find minimum and maximum data value in the tree\n";
        cout << "5. Swap the roles of left and right pointers\n";
        cout << "6. Search for an element\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int val;
            cout << "Enter the value to insert: ";
            cin >> val;
            bst.insert(val);
            break;
        }
        case 2:
        {
            int n;
            cout << "Enter the number of elements: ";
            cin >> n;
            int arr[n];
            cout << "Enter " << n << " elements: ";
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
            }
            bst.insertArray(arr, n);
            cout << "Elements inserted successfully." << endl;
            break;
        }
        case 3:
        {
            int pathLength = bst.longestPathOfTree();
            cout << "The number of nodes in the longest path is: " << pathLength << "\n";
            break;
        }
        case 4:
        {
            int minVal = bst.minDataInTree();
            int maxVal = bst.maxDataInTree();
            cout << "Minimum value: " << minVal << "\n";
            cout << "Maximum value: " << maxVal << "\n";
            break;
        }
        case 5:
        {
            bst.swapTree();
            cout << "Tree has been swapped.\n";
            break;
        }
        case 6:
        {
            int key;
            cout << "Enter the value to search: ";
            cin >> key;
            if (bst.searchNode(key))
            {
                cout << "Element found in the tree.\n";
            }
            else
            {
                cout << "Element not found in the tree.\n";
            }
            break;
        }
        case 7:
        {
            cout << "Exiting program.\n";
            break;
        }
        default:
        {
            cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    } while (choice != 7);

    return 0;
}
