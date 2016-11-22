#include<stdio.h>

int number[100010][102];
#define GETCHAR getchar_unlocked
#define PUTCHAR putchar_unlocked
inline int readlong() 
{
	int flag=1;
    int n = 0;
    char c;
    while (1)
    { 
              c=GETCHAR();
              if(c>='0'&&c<='9') {n = n * 10 + c - '0';flag=0;}
              else if(flag!=1) break; 
                              
    }
    return n;
}
 

inline void writeInt(int x) 
{
     int i = 10;
     char buf[11];
     // buf[10] = 0;
     buf[10] = '\n';

     do 
     {
        buf[--i] = x % 10 + '0';
        x/= 10;
     }while(x);
     do 
     {
        PUTCHAR(buf[i]);
     } while (buf[i++] != '\n');
}

long long p(int n,int m,long long MOD)
{
    if(m==0) return 1;
    
    long long x=p(n,m/2,MOD);
    if(m%2==0) 
               return (x*x)%MOD;
    else
               return (((x*x)%MOD)*n)%MOD;
}


int main()
{
	
	int n;
	n=readlong();
	int i,j;
	
	for(i=2;i<=100;i++)
	{
		number[0][i]=0;
	}
	
	for(i=1;i<=n;i++)
	{
		int a;
		a=readlong();
		for(j=1;j<=100;j++)
			number[i][j]=number[i-1][j];
			
		number[i][a]++;
	}
	
	int t;
	t=readlong();
	int l,r;
		long long MOD;
	while(t--)
	{
		l=readlong();
		r=readlong();
		MOD=readlong();
		
		
		long long ans=1;
		if(MOD==1)
			printf("%d\n",0);
		else
		{
			for(i=1;i<=100;i++)
			{
				if(number[r][i]-number[l-1][i])
				{	
					ans=ans*p(i,number[r][i]-number[l-1][i],MOD);
					ans=ans%MOD;
				}
			}
			writeInt(ans);
		}
	}
	return 0;
}
