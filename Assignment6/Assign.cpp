#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;
class Node
{
public:
    string name;
    Node *next;
    Node *down;

    Node(string n = "")
    {
        name = n;
        next = nullptr;
        down = nullptr;
    }
    friend class Graph;
};
class Graph
{
    Node *head = nullptr;
    unordered_map<string, bool> visited;

private:
    void dfsUtil(Node *row)
    {
        visited[row->name] = true;
        cout << row->name << " ";

        for (Node *nbr = row->next; nbr; nbr = nbr->next)
        {
            if (!visited[nbr->name])
            {
                Node *nbrRow = findRow(nbr->name);
                if (nbrRow)
                    dfsUtil(nbrRow);
            }
        }
    }

    Node *findRow(const string &name)
    {
        for (Node *r = head; r; r = r->down)
        {
            if (r->name == name)
                return r;
        }
        return nullptr;
    }

    void add(string NodeA, string NodeB)
    {
        if (head == nullptr)
        {
            Node *node1 = new Node(NodeA);
            Node *node2 = new Node(NodeB);
            head = node1;
            node1->next = node2;
        }
        else
        {
            Node *currentNode = head;
            Node *prevNode = nullptr;
            bool found = false;
            while (currentNode != nullptr)
            {
                if (currentNode->name == NodeA)
                {
                    found = true;
                    Node *currentListNode = currentNode;
                    while (currentListNode->next != nullptr)
                        currentListNode = currentListNode->next;
                    Node *newNode = new Node(NodeB);
                    currentListNode->next = newNode;
                    break;
                }
                prevNode = currentNode;
                currentNode = currentNode->down;
            }

            if (!found)
            {
                Node *newNode1 = new Node(NodeA);
                Node *newNode2 = new Node(NodeB);
                prevNode->down = newNode1;
                newNode1->next = newNode2;
            }
        }
    }

public:
    void addNode(string NodeA, string NodeB)
    {
        add(NodeA, NodeB);
        add(NodeB, NodeA);
    }
    void DFS(const string &startName)
    {
        visited.clear();
        Node *startRow = findRow(startName);
        if (!startRow)
        {
            cout << "Start node \"" << startName << "\" not found.\n";
            return;
        }
        cout << "DFS starting at " << startName << ": ";
        dfsUtil(startRow);
        cout << "\n";
    }

    void print()
    {
        Node *currentArrayNode = head;
        while (currentArrayNode != nullptr)
        {
            Node *currentListNode = currentArrayNode;
            while (currentListNode != nullptr)
            {
                cout << currentListNode->name << " -> ";
                currentListNode = currentListNode->next;
            }
            cout << endl;
            currentArrayNode = currentArrayNode->down;
        }
    }
    void BFS(const string &startName)
    {
        visited.clear();
        Node *startRow = findRow(startName);
        if (!startRow)
        {
            cout << "Start node \"" << startName << "\" not found.\n";
            return;
        }

        queue<string> q;
        visited[startRow->name] = true;
        q.push(startRow->name);

        cout << "BFS starting at " << startName << ": ";

        while (!q.empty())
        {
            string current = q.front();
            q.pop();
            cout << current << " ";

            Node *row = findRow(current);
            for (Node *nbr = row->next; nbr; nbr = nbr->next)
            {
                if (!visited[nbr->name])
                {
                    visited[nbr->name] = true;
                    q.push(nbr->name);
                }
            }
        }

        cout << "\n";
    }
};

int main()
{
    Graph g;
    g.addNode("Katraj", "PICT");
    g.addNode("Bharti", "Katraj");
    g.addNode("Bharti", "PICT");
    g.addNode("Katraj", "SKNCOE");
    g.addNode("PICT", "SKNCOE");
    g.addNode("SKNCOE", "Temple");
    g.addNode("Temple", "Katraj");
    g.addNode("Temple", "Kondhwa");
    g.DFS("Katraj");
    g.BFS("Katraj");
    g.print();
    return 0;
}