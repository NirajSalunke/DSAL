#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

class Graph
{
    vector<vector<long>> adjMat;
    map<string, int> cities;
    map<int, string> inv_cities;
    map<string, bool> visited;
    int vertexCount;
    int edgeCount;
    using CityDistance = pair<pair<string, string>, int>;

    void addDistBetnCities(string City1, string City2, long Distance)
    {
        adjMat[cities[City1]][cities[City2]] = Distance;
        adjMat[cities[City2]][cities[City1]] = Distance;
    }

    // prim
    pair<vector<CityDistance>, long> getMinRoadToAll()
    {
        long minDist = 0;
        visited.clear();

        auto compare = [](const CityDistance &a, const CityDistance &b)
        {
            return a.second > b.second;
        };

        priority_queue<CityDistance, vector<CityDistance>, decltype(compare)> pq(compare);
        vector<CityDistance> MST;
        pq.push({{inv_cities[0], inv_cities[0]}, -1});

        while (!pq.empty())
        {
            auto temp = pq.top();
            pq.pop();
            if (visited[temp.first.second])
                continue;

            visited[temp.first.second] = true;
            if (temp.second != -1)
            {
                MST.push_back(temp);
                minDist += temp.second;
            }
            for (int i = 0; i < vertexCount; i++)
            {
                if (adjMat[cities[temp.first.second]][i] != 0 && !visited[inv_cities[i]])
                {
                    pq.push({{temp.first.second, inv_cities[i]}, adjMat[cities[temp.first.second]][i]});
                }
            }
        }
        return {MST, minDist};
    }

public:
    Graph()

    {
        cout << "Enter Total Number of cities:- ";
        cin >> vertexCount;
        cout << "Enter Total Number distance betn citites , we know:- (edges) ";
        cin >> edgeCount;
        for (int i = 0; i < vertexCount; i++)
        {
            vector<long> arr(vertexCount, 0);
            adjMat.push_back(arr);
        }
        for (int i = 0; i < vertexCount; i++)
        {
            string name;
            cout << "Enter City " << i + 1 << " name:- ";
            cin >> name;
            cities[name] = i;
            inv_cities[i] = name;
        }
        for (int i = 0; i < edgeCount; i++)
        {
            cout << "Edge number " << i + 1 << endl;
            add();
        }
    }
    void printer()
    {
        cout << "  ";
        for (int k = 0; k < vertexCount; k++)
        {
            cout << inv_cities[k] << " ";
        }
        cout << endl;
        for (int i = 0; i < vertexCount; i++)
        {
            for (int j = 0; j < vertexCount; j++)
            {
                if (j == 0)
                {
                    cout << inv_cities[i] << " ";
                }
                cout << adjMat[i][j] << " ";
            }
            cout << endl;
        }
    }
    void add()
    {
        string name1, name2;
        long dist;
        cout << "Enter City1 name:- ";
        cin >> name1;
        cout << "Enter City2  name:- ";
        cin >> name2;
        cout << "Enter Distance  betn:- ";
        cin >> dist;
        addDistBetnCities(name1, name2, dist);
    }
    void printBestPath()
    {
        pair<vector<CityDistance>, long> result = getMinRoadToAll();
        cout << "Min Distance covering to travel the all cities:- " << result.second << endl;

        for (auto it : result.first)
        {
            cout << it.first.first << " -> " << it.first.second << " distance betn them => " << it.second << endl;
        }
    }
};

int main()
{
    Graph g;
    g.printer();
    string yes;
    cout << "Wanna visit all citites with least petrol expenses (ahh ik u got less mileage) :- enter yes or no?" << endl;
    cin >> yes;
    if (yes == "yes" || yes == "Yes" || yes == "YES")
    {
        g.printBestPath();
    }
    else
    {
        cout << "Looks like u have good mileage" << endl;
    }
    return 0;
}
