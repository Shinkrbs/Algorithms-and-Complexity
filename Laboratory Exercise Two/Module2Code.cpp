
#include <iostream>
using namespace std;
//n^2 algorithms
void selectionSort();
void bubbleSort();
void insertionSort();
void shellSort();

//O(n logn) algorithms
void mergeSort(int a[],int start,int end);
void mergeArr(int a[],int start, int mid, int end);
void quickSort(int a[],int start, int end);

//void ithItemUsingPartialSelSort();

//O(n) order statistics
int quickSelect(int a[],int start ,int end, int IthIdx);
int Partition(int a[],int start, int end);


int main()
{
    //int a[8] = {3,5,3,2,11,23,22,12};
    //int a[10] = {26,24,3,17,25,24,13,60,47,1};

    //midterm
    //int a[10] = {30,11,10,13,22,14,15,1,3,2};
    int ex[10] = {11,15,3,8,17,23,19,14,0,89};
   // mergeSort(ex,0,9);
   quickSort(ex,0,9);
   // cout<<quickSelect(ex,0,9,4);

   //selectionSort();
   //bubbleSort();
   // mergeSort(ex,0,9);
    // for (int idx=0;idx<8;idx++)
       // cout<<a[idx]<<",";
    //quickSort(ex,0,9);
    //for (int idx=0;idx<8;idx++)
       // cout<<a[idx]<<",";
   //insertionSort();
    //bubbleSort();
    //shellSort();
    /*
    Partition(a,0,9);
    for(int idx=0;idx<10;idx++)
       cout<<a[idx]<<",";

    cout<<endl;

    Partition(a,0,6);
    for(int idx=0;idx<10;idx++)
       cout<<a[idx]<<",";
    cout<<endl;


    Partition(a,1,6);
    for(int idx=0;idx<10;idx++)
       cout<<a[idx]<<",";

    */
   // selectionSort();
   //bubbleSort();

   // insertionSort();
  // shellSort();


  //cout<<quickSelect(ex,0,9,4);

}

int quickSelect(int a[],int start ,int end, int IthIdx)
{
    int q,k,i;
    if (start==end)
        return (a[start]);
    q = Partition(a,start,end);
    k= q - start+1;

   if (IthIdx<k)
   {
       return (quickSelect(a,start,q,IthIdx));
       for (int idx=0;idx<10;idx++)
            cout<<a[idx]<<",";
        cout<<endl;
   }


   else
   {
       return (quickSelect(a,q+1,end,IthIdx-k));
       for (int idx=0;idx<10;idx++)
            cout<<a[idx]<<",";
        cout<<endl;
   }


}


int Partition(int a[],int start, int end)
{
    int pivot = a[start];
    int i = start + 1;

    while (a[i]<=pivot)
        i++;
    int j=end;

    while (a[j]>=pivot)
        j--;

    while (i<j)
    {
        swap (a[i],a[j]);
        i++;
        while (a[i]<=pivot)
            i++;
        j--;
        while (a[j]>=pivot)
            j--;
    }
    swap (a[start],a[j]);
    return j;

}


void quickSort(int a[],int start, int end)
{
    int i, j, pivot;
    if (start<end)
    {
        pivot = a[start];
        i=start+1;
        while(a[i]<pivot)
            i++;
        j=end;
        while(a[j]>pivot)
            j--;
        while(i<j)
        {
            swap(a[i],a[j]);
            i++;
            while(a[i]<pivot)
                i++;
            j--;
            while(a[j]>pivot)
                j--;
        }
     swap(a[start],a[j]);
    for (int idx=0;idx<10;idx++)
        cout<<a[idx]<<",";
    cout<<endl;


    quickSort(a,start,j-1);
    quickSort(a,j+1,end);


    }
}



void mergeSort(int a[],int start,int end)
{
    int mid;
    if(start<end)
    {
        mid = (start+end)/2;
        //cout<<start<<","<<mid<<",";

        mergeSort(a,start,mid);

        mergeSort(a,mid+1,end);
        for (int idx=0;idx<10;idx++)
           cout<<a[idx]<<",";
        cout<<endl;
        mergeArr(a,start,mid,end);

        for (int idx=0;idx<10;idx++)
           cout<<a[idx]<<",";
        cout<<endl;
    }
}

void mergeArr(int a[],int start, int mid, int end)
{
    int temp[10],size,ptr1,ptr2;
    int i,j;

    size = end - start;

    ptr1=start;
    ptr2 =mid+1;

    j=0;
    /* The while loop below would execute  equal to the
     minimum of mid and (n-mid)
    */
    while(ptr1<mid+1&&ptr2<end+1)
    {
        if (a[ptr1]<a[ptr2])
        {
            temp[j]=a[ptr1];
            ptr1++;
            j++;
        }
        else
        {
            temp[j]=a[ptr2];
            ptr2++;
            j++;
        }
    }

    if(ptr1<mid+1)
    {
        for (i=j;i<size+1;i++)
        {
                temp[i]=a[ptr1];
                ptr1++;
        }
    }

    if(ptr2<end+1)
    {
            for (i=j;i<size+1;i++)
            {
                temp[i]=a[ptr2];
                ptr2++;
            }
    }

        for (j=0;j<size+1;j++)
            a[start+j]=temp[j];
}


void selectionSort()
{
    int a[10] = {11,15,3,8,17,23,19,14,0,89};
    int small,idx_small;

    for (int i=0; i<9;i++)
    {
        idx_small = i;
        for (int j=i+1;j<10;j++)
        {
            if (a[j]<a[idx_small])
            {
                idx_small = j;
            }
        }
    swap (a[i],a[idx_small]);

    for (int idx=0;idx<10;idx++)
        cout<<a[idx]<<",";
    cout<<endl;
    }

}

void bubbleSort()
{
   //int a[10] = {26,24,3,17,25,24,13,60,47,1};
   //midterm
    int a[10] = {11,15,3,8,17,23,19,14,0,89};
    int i=0;
    bool swp = 1;

    while (swp)
    {
        swp = 0;
        for (int j=9;j>i;j--)
        {
            if (a[j]<a[j-1])
            {
                swap (a[j],a[j-1]);
                swp = 1;
            }
        }
     for (int idx=0;idx<10;idx++)
        cout<<a[idx]<<",";
    cout<<endl;
        i++;
    }
}

void insertionSort()
{
   // int a[10] = {26,24,3,17,25,24,13,60,47,1};
   //midterm
    int a[10] = {11,15,3,8,17,23,19,14,0,89};
     int key,j;
     for (int i=0;i<10;i++)
     {
        key=a[i];
        j=i-1;
        while(key<a[j]&&j>=0)
        {
            a[j+1]=a[j];
            j--;
        }
        a[j+1] = key;
        for (int idx=0;idx<10;idx++)
            cout<<a[idx]<<",";
        cout<<endl;
     }

}

void shellSort()
{
     int a[10] = {10,15,2,19,3,8,4,81,78,45};

     int n=10,i,j,d;
     int tmp;
     //splitting
     for (d=n/2;d>0;d/=2)
     { // cout<<d<<endl;
        for (i=d;i<n;i++)
        {   tmp = a[i];
          //  cout<<i<<endl;
            //actual insertion
            for (j=i;j>d-1;j-=d)
             {// to check!!!
                 if (tmp<a[j-d])
                    a[j]=a[j-d];
                 else
                    break;
             }
             a[j]=tmp;


       }
for (int idx=0;idx<10;idx++)
            cout<<a[idx]<<",";
        cout<<endl;
        //cout<<d<<",";

     }

           //cout<<endl;

}
