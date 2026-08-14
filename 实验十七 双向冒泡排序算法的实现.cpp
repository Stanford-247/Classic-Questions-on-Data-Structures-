#include <iostream>
using namespace std;

void BubbleSort(int a[], int n)
{
    int left = 0;
    int right = n-1;
    bool swapped = true;
    while(left < right&&swapped)
    {
        swapped = false;
        for(int i = left; i < right;i++)
        {
            if(a[i] > a[i+1])
            {
                swapped = true;
                int t = a[i];
                a[i] = a[i+1];
                a[i+1] = t;
            }
        }
        right--;
        for(int i = right; i > left; i--)
        {
            if(a[i] < a[i-1])
            {
               swapped = true;
                int t = a[i];
                a[i] = a[i-1];
                a[i-1] = t; 
            }
        }
        left++;
    }
}
int main()
{
    int a[] = {3, 1, 5, 9, 4, 11, 89, 22};
    int n = sizeof(a)/sizeof(a[0]);
    BubbleSort(a, n);
    cout<<"双向冒泡排序后的数组：";
    for(int i = 0;i < n;i++)
    {
        cout<<a[i]<<' ';
    }
    return 0;
}