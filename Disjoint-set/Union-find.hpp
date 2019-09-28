#include <iostream>

class UnionFind //(for numbers from 1 to n)
{
    int* arr;
    public:
    UnionFind(int count)
    {
        arr = new int[count];
        for(int i = 0;i<count;i++)
            arr[i]=i;  
    }
    int GetRoot(int el)
    {
       while(el!=arr[el])
           el = arr[el];
       return el;
       
    }
    bool AreInOneSet(int el1,int el2)
    {
        return GetRoot(el1)==GetRoot(el2);
    }
    void Union(int el1,int el2)
    {
        int r = GetRoot(el1);
        int r2 = GetRoot(el2);
        arr[r]=r2;    
    }
};
