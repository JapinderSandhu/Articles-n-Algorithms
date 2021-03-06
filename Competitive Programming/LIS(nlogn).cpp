/*
  Name: Longest increasing subsequence O(nlogn) algorithm.
  Copyright: 
  Author: Shobhit Saxena
  Date: 17/12/12 01:29
  Description: Well this is a O(nlogn) algorithm to find LIS. for further reading refer to http://www.geeksforgeeks.org/archives/9591
*/


#include<stdio.h>

#define SIZE(a) sizeof(a)/sizeof(*a)
#define MAX 10000



int pos(int lis[],int l,int r,int key)
{
    int m;
 
 
    while( r - l > 1 ) 
    {
        m = l + (r - l)/2;
        (lis[m] >= key ? r : l) = m; // ternary expression returns an l-value
    }
    if(lis[r]==key)
    return r+1;
    
}

int LIS(int a[],int n)
{
    int lis[MAX];
    lis[0]=a[0];
    int len=1;
    for(int i=1;i<n;i++)
    {
            if(a[i]<lis[0]) lis[0]=a[i];
            else if(a[i]>=lis[len-1]) lis[len++]=a[i];
            else 
			{
				int r=pos(lis,-1,len-1,a[i]);
				lis[r]=a[i];
				if(r==len)
					len++;      
			}
    }
    return len;
}


int main()
{
    int a[]={1,2,3,1,1,1,1};
    printf("%d",LIS(a,SIZE(a)));
    getchar();
}
