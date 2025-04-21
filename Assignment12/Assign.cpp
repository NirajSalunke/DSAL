#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <limits>
#include <cstdint>
using namespace std;

class Employee
{
public:
    string name;
    int empID;
    streampos loc;

    Employee() : name(""), empID(0), loc(0) {}

    bool isEmpty() const
    {
        return empID == 0;
    }

    void display() const
    {
        cout << "Name: " << name << ", ID: " << empID << endl;
    }
};

class Org
{
private:
    map<int, Employee> empMap;

public:
    void addEmp(const Employee &e)
    {
        empMap[e.empID] = e;
    }
    Employee searchEmp(int id) const
    {
        auto it = empMap.find(id);
        if (it == empMap.end())
            return Employee();
        return it->second;
    }
};

class MyFile
{
private:
    string filename;
    Org comp;

public:
    MyFile()
    {
        cout << "Enter file name: ";
        getline(cin, filename);
        // Create or truncate binary file
        ofstream ofs(filename, ios::binary);
        if (!ofs)
            cerr << "Error creating file\n";
    }

    void addRecord(const string &name, int id)
    {
        // Prepare employee and record current write pos
        Employee E;
        E.name = name;
        E.empID = id;

        fstream file(filename, ios::in | ios::out | ios::binary);
        if (!file)
        {
            cerr << "Error opening file for update\n";
            return;
        }
        file.seekp(0, ios::end);
        E.loc = file.tellp();
        comp.addEmp(E);

        // Serialize: [name_len][name_bytes][empID]
        uint32_t len = static_cast<uint32_t>(name.size());
        file.write(reinterpret_cast<char *>(&len), sizeof(len));
        file.write(name.data(), len);
        file.write(reinterpret_cast<char *>(&id), sizeof(id));
        file.close();
    }

    void readRecord(int id)
    {
        // Look up offset in memory
        Employee key = comp.searchEmp(id);
        if (key.isEmpty())
        {
            cout << "Employee not found\n";
            return;
        }

        ifstream file(filename, ios::binary);
        if (!file)
        {
            cerr << "Error opening file for read\n";
            return;
        }
        // Jump to record start
        file.seekg(key.loc, ios::beg);

        // Read name length
        uint32_t len;
        file.read(reinterpret_cast<char *>(&len), sizeof(len));
        if (!file)
        {
            cerr << "Error reading name length\n";
            return;
        }
        // Read name bytes
        string name;
        name.resize(len);
        file.read(&name[0], len);
        // Read empID
        int empId2;
        file.read(reinterpret_cast<char *>(&empId2), sizeof(empId2));

        // Display
        cout << "Name: " << name << ", ID: " << empId2 << endl;
        file.close();
    }
};

int main()
{
    MyFile mf;
    int choice = 0;
    while (choice != 3)
    {
        cout << "\nMenu:\n"
             << "1. Add Record\n"
             << "2. Read Record\n"
             << "3. Exit\n"
             << "Enter choice: ";
        if (!(cin >> choice))
            break;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice)
        {
        case 1:
        {
            string name;
            int id;
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            mf.addRecord(name, id);
            break;
        }
        case 2:
        {
            int id;
            cout << "Enter ID to read: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            mf.readRecord(id);
            break;
        }
        case 3:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
