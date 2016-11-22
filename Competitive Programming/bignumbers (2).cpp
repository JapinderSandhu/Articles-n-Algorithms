#include<stdio.h>

#define MAXDIGITS 100

#define MOD 100000000
#define weight 8

class verybig
{
       private:
               long long digits[MAXDIGITS];
               int last_digit;
               int first_digit;
       public: 
               
               verybig(int a=0)
               {
                        first_digit=last_digit=MAXDIGITS-1;
                       
                        do
                        {
                                 digits[first_digit--]=a%MOD;
                                 a/=MOD;
                        }while(a);
               }
               void display();
               void multiply(int a);
                  
};
void verybig::display()
{
           for(int i=first_digit+1;i<=last_digit;i++)
           {
                        
                                      printf("%lld",digits[i]);
                        if(i!=last_digit)
                        {
                                      int numzeros=weight-1;
                                      long long x=digits[i+1];
                                      while(x)
                                      {
                                              numzeros--;
                                              x/=10;
                                      }
                                      if(digits[i+1]!=0)
                                                        numzeros++;
                                      
                                      for(int j=0;j<numzeros;j++)
                                                       printf("0");
                        }   
                                      
           }
}
void verybig::multiply(long long a)
{
           for(int i=last_digit;i>first_digit;i--)
           {
                   digits[i]*=a;
                   if(i!=last_digit)
                   {
                                    digits[i]+=digits[i+1]/MOD;
                                    digits[i+1]%=MOD;                 
                   }
           }
           if(digits[first_digit+1]/MOD!=0)
           {
                                           digits[first_digit]=digits[first_digit+1]/MOD;
                                           digits[first_digit+1]%=MOD;
                                           first_digit--;
           }
}

int main()
{
  int t;
    scanf("%d",&t);
    while(t--)
    {
              verybig ob(1);
              int n;
              scanf("%d",&n);
              for(int i=1;i<=n;i++)
                      ob.multiply(i);
 
             ob.display();
             printf("\n");
    }
    return 0;    
}
