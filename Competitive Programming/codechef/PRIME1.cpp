#include<iostream>
using namespace std;

#define MAX 1000000

int isprime[MAX/32+2];

#define isSet(n) isprime[n>>5]&(1<<(n&31))
#define unset(n) isprime[n>>5] &= ~(1<<(n&31));
int lessprime[MAX];
void sieve()
{
   int i,j;
   isprime[0]=0xA28A28AC;
   for(int i=1;i<=MAX/32+1;i+=3)
   {
           isprime[i]  =0x28A28A28;
           isprime[i+1]=0x8A28A28A;
           isprime[i+2]=0xA28A28A2;
   }
   for(i=5;i*i<=MAX;i+=2)
                          if(isSet(i))
                            {
                                       for(j=i*i;j<=MAX;j+=i)
                                               unset(j);
                            }
}



int main()
{
	sieve();
	int t;
	cin>>t;
	while(t--)
	{
		int a,b;
		cin>>a>>b;
		for(;a<=b;a++)
		{
			if(isPrime(a))
			{
				cout<<a<<endl;
			}
		}
	}
	return 0;
}
