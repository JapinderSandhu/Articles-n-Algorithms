#include<iostream>
#include<cstdlib>
#include<stdio.h>
using namespace std;


int main()
{
	freopen("test.txt","w",stdout);
	int n=10000;
	cout<<n<<endl;
	for(int i=0;i<n;i++)
		cout<<rand()%1000<<" "<<rand()%1000<<endl;
	
	int q=1000000;
	cout<<q<<endl;
	for(int i=0;i<n;i++)
		cout<<rand()%1000<<" "<<rand()%1000<<endl;
}
