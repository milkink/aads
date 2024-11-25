#include&lt;iostream&gt;  
#include&lt;climits&gt;  
#include&lt;cstdlib&gt;  
using namespace std;  
 
int randomPartition(int arr[], int l, int r);  
 
int ithSmallest(int arr[], int l, int r, int k)  
{  
    if (k &gt; 0 &amp;&amp; k &lt;= r - l + 1)  
    {  
        int pos = randomPartition(arr, l, r);  
 
        if (pos-l == k-1)  
            return arr[pos];  
        if (pos-l &gt; k-1)
            return ithSmallest(arr, l, pos-1, k);  
 
        return ithSmallest(arr, pos+1, r, k-pos+l-1);  
    }  
   
    return INT_MAX;  
}  
 
void swap(int *a, int *b)  
{  
    int temp = *a;  
    *a = *b;  
    *b = temp;  
}  
int partition(int arr[], int l, int r)  
{  
    int x = arr[r], i = l;  
    for (int j = l; j &lt;= r - 1; j++)  
    {  
        if (arr[j] &lt;= x)  
        {  
            swap(&amp;arr[i], &amp;arr[j]);  
            i++;  
        }  
    }  

    swap(&amp;arr[i], &amp;arr[r]);  
    return i;  
}  
 
int randomPartition(int arr[], int l, int r)  
{  
    int n = r-l+1;  
    int pivot = rand() % n;  
    swap(&amp;arr[l + pivot], &amp;arr[r]);  
    return partition(arr, l, r);  
}  
 
int main()  
{
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    int n = sizeof(arr)/sizeof(arr[0]);
    int i;
    cout &lt;&lt; &quot;Enter value of i: &quot;;
    cin &gt;&gt; i;
    cout &lt;&lt; &quot;i&#39;th smallest element is &quot; &lt;&lt; ithSmallest(arr, 0, n - 1, i);  
    return 0;
}
