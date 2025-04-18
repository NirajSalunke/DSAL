#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    int data;
    Node(int val)
    {
        this->data = val;
    }
    friend class Heap;
};

class Heap
{
private:
    vector<Node> arr;

    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parentIndex = (index - 1) / 2;
            if (arr[parentIndex].data < arr[index].data)
            {
                swap(arr[parentIndex], arr[index]);
                index = parentIndex;
            }
            else
            {
                break;
            }
        }
    }

    void heapifyDown(int index)
    {
        int size = arr.size();
        while (true)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;
            if (left < size && arr[left].data > arr[largest].data)
            {
                largest = left;
            }
            if (right < size && arr[right].data > arr[largest].data)
            {
                largest = right;
            }

            if (largest != index)
            {
                swap(arr[index], arr[largest]);
                index = largest;
            }
            else
            {
                break;
            }
        }
    }

public:
    void insertAlot(vector<int> &arr, int size)
    {
        for (int i = 0; i < size; i++)
        {
            insert(arr[i]);
        }
    }
    void insert(int val)
    {
        arr.push_back(Node(val));
        heapifyUp(arr.size() - 1);
    }

    int extractMax()
    {
        if (arr.empty())
            throw out_of_range("Heap is empty");

        int maxVal = arr[0].data;
        arr[0] = arr.back();
        arr.pop_back();
        if (!arr.empty())
        {
            heapifyDown(0);
        }
        return maxVal;
    }
};

void heapSort(vector<int> &arr)
{
    Heap h;
    for (int x : arr)
    {
        h.insert(x);
    }
    for (int i = arr.size() - 1; i >= 0; --i)
    {
        arr[i] = h.extractMax();
    }
}

int main()
{
    vector<int> arr = {12, 11, 13, 5, 6, 7};

    cout << "Given Array: ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;

    heapSort(arr);

    cout << "Sorted Array:   ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;

    return 0;
}