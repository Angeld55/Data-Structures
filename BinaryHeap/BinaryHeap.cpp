#include <iostream>

class BinaryHeap
{
    int* arr;
    int capacity;
    int count;
private:
    void swap(int* arr,int i,int j)
    {
        int temp = arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
    }
    public:
    BinaryHeap()
    {
        capacity=8;
        arr= new int[capacity];
        count =0;
    }
    BinaryHeap(const int* a,int len)
    {
        arr = new int[len];
        count = len;
        capacity=count;
        for(int i =0;i<len;i++)
            arr[i]=a[i];
        for(int i = len/2;i>=0;i-- )
            Heapyfy(arr+i,count-i);
    }
    int LeftChildIndex(int i)
    {
        return i*2+1;
    }
    int RightChildIndex(int i)
    {
        return i*2+2;
    }
    int ParentIndex(int i)
    {
        return (i-1)/2;
    }
    void Add(int el)
    {
        if(count==capacity)
        {}
        arr[count]=el;
        int indexOfAdded = count;
        int indexOfparent = ParentIndex(indexOfAdded);
        while((indexOfAdded!=0)&&(arr[indexOfAdded]>arr[indexOfparent]))
        {
            swap(arr,indexOfAdded,indexOfparent);
            indexOfAdded = indexOfparent;
            indexOfparent =ParentIndex (indexOfAdded);
        }
        count++;
    }

     int ExtractMax()
     {
         int max = arr[0];
         swap(arr,0,count-1);
         count--;
         Heapyfy(arr,count-1);
         return max;
     }
     void Heapyfy(int* arr,int count)
     {
         int elIndex = 0;
         while(true)
         {
             int leftChIndex = LeftChildIndex(elIndex);
             int rightChIndex = RightChildIndex(elIndex);

             bool isSmallerThanLeft = leftChIndex<count && arr[elIndex]<arr[leftChIndex];
             bool isSmallerThanRight =  rightChIndex<count && arr[elIndex]<arr[rightChIndex];

             if(isSmallerThanLeft&&!isSmallerThanRight)
             {
                swap(arr,elIndex, LeftChildIndex(elIndex));
                elIndex=LeftChildIndex(elIndex);
             }
             else if(!isSmallerThanLeft&&isSmallerThanRight)
             {
                  swap(arr,elIndex, RightChildIndex(elIndex));
                  elIndex=RightChildIndex(elIndex);
             }
             else if(isSmallerThanLeft&&isSmallerThanRight)
             {
                 if(arr[LeftChildIndex(elIndex)]>arr[RightChildIndex(elIndex)])
                 {
                      swap(arr,elIndex, LeftChildIndex(elIndex));
                      elIndex=LeftChildIndex(elIndex);
                 }
                 else
                 {
                      swap(arr,elIndex, RightChildIndex(elIndex));
                      elIndex=RightChildIndex(elIndex);
                 }
             }
             else
             {
                 break;
             }
         }
     }
     void Print()
     {
         int spaces =32;
         int num = 0;
         int diff = 2;
         for(int i =0;i<count;i++)
         {
             for(int j=0;j<spaces;j++)
                std::cout<<" ";
             std::cout<<arr[i];
             if(i==num)
             {
                 std::cout<<std::endl;
                 num+=diff;
                 diff*=2;
                 spaces/=2;
             }
         }
     }
    ~BinaryHeap()
    {
        delete[] arr;
    }

};


void HeapSort(int* arr,int len)
{
    BinaryHeap heap(arr,len); //O(n)
    for(int i =len-1;i>=0;i--)  //n times
        arr[i]=heap.ExtractMax(); //O(logn)

}
int main()
{
    int arr[] = {5,1,6,2,1,99,4,10,2};
    HeapSort(arr,9);
    for(int i = 0;i<9;i++)
        std::cout<<arr[i]<<" ";

}
