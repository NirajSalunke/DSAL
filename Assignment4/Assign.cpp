#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    long long value;
    string Name;

    Node(long long value, string Name)
    {
        this->Name = Name;
        this->value = value;
    }

    Node()
    {
        this->value = -1;
        this->Name = "";
    }
};

class Database
{
private:
    int size;
    int count;
    Node *table;

    long HashFunction(long long key)
    {
        return key % size;
    }

public:
    Database()
    {
        size = 10;
        count = 0;
        table = new Node[size];
    }

    Database(int size)
    {
        this->size = size;
        count = 0;
        table = new Node[size];
    }

    int insert(long long value, string name)
    {
        if (count == size)
        {
            return -1; // Table full
        }
        int index = HashFunction(value);

        if (table[index].value == -1)
        {
            table[index].value = value;
            table[index].Name = name;
            count++;
            return 1;
        }

        int i = (index + 1) % size;
        while (i != index)
        {
            if (table[i].value == value)
            {
                return 0;
            }
            if (table[i].value == -1)
            {
                table[i].value = value;
                table[i].Name = name;
                count++;
                return 1;
            }
            i = (i + 1) % size;
        }
        return 0;
    }

    string search(long long val)
    {
        int index = HashFunction(val);

        if (table[index].value == val)
        {
            return table[index].Name;
        }

        int i = (index + 1) % size;
        while (i != index)
        {
            if (table[i].value == val)
            {
                return table[i].Name;
            }
            i = (i + 1) % size;
        }
        return "";
    }

    int del(long long val)
    {
        int index = HashFunction(val);

        if (table[index].value == val)
        {
            table[index].value = -1;
            table[index].Name = "";
            count--;
            return 1;
        }

        int i = (index + 1) % size;
        while (i != index)
        {
            if (table[i].value == val)
            {
                table[i].value = -1;
                table[i].Name = "";
                count--;
                return 1;
            }
            i = (i + 1) % size;
        }
        return -1;
    }

    void display()
    {
        cout << "\nTelephone Book Database:\n";
        for (int i = 0; i < size; i++)
        {
            if (table[i].value != -1)
            {
                cout << i << " -> " << table[i].Name << ": " << table[i].value << endl;
            }
            else
            {
                cout << i << " -> Empty" << endl;
            }
        }
    }
};

int main()
{
    int size, choice;
    cout << "Enter size of hash table: ";
    cin >> size;

    Database db(size);

    do
    {
        cout << "\nMenu:";
        cout << "\n1. Insert";
        cout << "\n2. Search";
        cout << "\n3. Delete";
        cout << "\n4. Display";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            long long value;
            string name;
            cout << "Enter telephone number: ";
            cin >> value;
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);

            int result = db.insert(value, name);
            if (result == 1)
            {
                cout << "Inserted successfully.\n";
            }
            else if (result == -1)
            {
                cout << "Error: Hash table is full.\n";
            }
            else
            {
                cout << "Error: Duplicate entry.\n";
            }
            break;
        }
        case 2:
        {
            long long value;
            cout << "Enter telephone number to search: ";
            cin >> value;

            string name = db.search(value);
            if (name != "")
            {
                cout << "Name: " << name << endl;
            }
            else
            {
                cout << "Telephone number not found.\n";
            }
            break;
        }
        case 3:
        {
            long long value;
            cout << "Enter telephone number to delete: ";
            cin >> value;

            int result = db.del(value);
            if (result == 1)
            {
                cout << "Deleted successfully.\n";
            }
            else
            {
                cout << "Error: Telephone number not found.\n";
            }
            break;
        }
        case 4:
            db.display();
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
