/*
Implement all the functions of a dictionary (ADT) using open hashing
technique: separate chaining using linked list Data: Set of (key, value)
pairs, Keys are mapped to values, Keys must be comparable, and Keys
must be unique. Standard Operations: Insert(key, value), Find(key),
Delete(key).
*/

#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Node
{
public:
    pair<int, int> data;
    list<pair<int, int>> *next;
    Node(int k, int v)
    {
        data = make_pair(k, v);
        next = NULL;
    }
    Node()
    {
        data = make_pair(-1, -1);
        next = NULL;
    }
};

class Dictionary
{
private:
    int size;
    int count;
    vector<Node> table;

    int hashFunction(int k)
    {
        return k % size;
    }

public:
    Dictionary(int size = 10)
    {
        this->size = size;
        count = 0;
        table.resize(size);
    }

    void Insert(int k, int v)
    {
        int index = hashFunction(k);
        Node *node = &table[index];

        if (node->data.first == -1)
        {
            node->data = make_pair(k, v);
            count++;
            return;
        }

        if (node->data.first == k)
        {
            cout << "Key already exists, updating value." << endl;
            node->data.second = v;
            return;
        }

        if (node->next == NULL)
        {
            node->next = new list<pair<int, int>>();
            node->next->push_back(node->data);
        }

        for (auto &entry : *(node->next))
        {
            if (entry.first == k)
            {
                cout << "Key already exists in chain, updating value." << endl;
                entry.second = v;
                return;
            }
        }

        node->next->push_back(make_pair(k, v));
        count++;
    }

    int Find(int k)
    {
        int index = hashFunction(k);
        Node *node = &table[index];

        if (node->data.first == -1)
        {
            return -1;
        }

        if (node->data.first == k)
        {
            return node->data.second;
        }

        if (node->next != NULL)
        {
            for (const auto &entry : *(node->next))
            {
                if (entry.first == k)
                {
                    return entry.second;
                }
            }
        }

        return -1;
    }

    int Delete(int k)
    {
        int index = hashFunction(k);
        Node *node = &table[index];

        if (node->data.first == -1)
        {
            return -1;
        }

        if (node->data.first == k)
        {
            if (node->next != NULL && !node->next->empty())
            {
                node->data = node->next->front();
                node->next->pop_front();
                if (node->next->empty())
                {
                    delete node->next;
                    node->next = NULL;
                }
            }
            else
            {
                node->data = make_pair(-1, -1);
            }
            return 1;
        }

        if (node->next != NULL)
        {
            for (auto it = node->next->begin(); it != node->next->end(); ++it)
            {
                if (it->first == k)
                {
                    node->next->erase(it);

                    if (node->next->empty())
                    {
                        delete node->next;
                        node->next = NULL;
                    }
                    return 1;
                }
            }
        }

        return -1;
    }
};

int main()
{
    int size;
    cout << "Enter the size of the dictionary: ";
    cin >> size;

    Dictionary dict(size);
    int choice;

    do
    {
        cout << "\nMenu:\n";
        cout << "1. Insert (key, value)\n";
        cout << "2. Find (key)\n";
        cout << "3. Delete (key)\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int key, value;
            cout << "Enter key: ";
            cin >> key;
            cout << "Enter value: ";
            cin >> value;
            dict.Insert(key, value);
            cout << "Inserted successfully." << endl;
            break;
        }
        case 2:
        {
            int key;
            cout << "Enter key to find: ";
            cin >> key;
            int value = dict.Find(key);
            if (value != -1)
            {
                cout << "Value: " << value << endl;
            }
            else
            {
                cout << "Key not found." << endl;
            }
            break;
        }
        case 3:
        {
            int key;
            cout << "Enter key to delete: ";
            cin >> key;
            int result = dict.Delete(key);
            if (result == 1)
            {
                cout << "Key deleted successfully." << endl;
            }
            else
            {
                cout << "Key not found." << endl;
            }
            break;
        }
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 4);

    return 0;
}
