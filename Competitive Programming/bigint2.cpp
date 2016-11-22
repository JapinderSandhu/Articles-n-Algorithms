#include<bits/stdc++.h>
using namespace std;
#define HASHVAL 1000000007

class sieve
{
	private:
		vector<int> isprime;
		bool isSet(int n) const
		{
			return (isprime[n>>5]&(1<<(n&31)));
		}
		bool unSet(int n)
		{
			isprime[n>>5] &= ~(1<<(n&31));
		}
		
		
	public:
		sieve(int MAX)
		{
			isprime.resize(MAX/32+10);
		
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
            		for(j=i*i;j<=MAX;j+=i)
                		unSet(j);
		}
		
		bool isPrime(int n) const
		{
			return isSet(n);
		}		
};

template<size_t SIZE> class bigint
{
	public:
		const static int SCALE = 100000000; 
		const static int WEIGHT = 8;
		int digit[SIZE];
		int firstdigit;
		int lastdigit;
		void itoa(int a,char *result,int &i) const
		{
			char temp[20];
			int temppos=0;
			while(a)
			{
				char last_digit=(a%10)+'0';
				temp[temppos++]=last_digit;
				a/=10;
			}	
			for(int j=temppos-1;j>=0;j--)
				result[i++]=temp[j];
			result[i]='\0';
		}

	public:
		bigint()
		{
			reset();
		}
		
		bigint(long long a)
        {
            reset();
            do
            {
                digit[firstdigit--]=a%SCALE;
                a/=SCALE;
            }while(a);    
        }
		
		bigint(string &number){
			reset();
			int last=number.size();
			int currentNumber = 0;
			int scale=1;
			while(last>0){
				last--;
				currentNumber+=(number[last]-'0')*scale;
				scale*=10;
				if(scale==SCALE){
					scale=1;
					digit[firstdigit--]=currentNumber;
					currentNumber=0;
				}
			}
			if(currentNumber!=0)
				digit[firstdigit--]=currentNumber;
		}
		bigint(const bigint &a)
		{
			firstdigit=a.firstdigit;
			lastdigit=a.lastdigit;
			for(int i=firstdigit+1;i<=lastdigit;i++)
			{
				digit[i]=a.digit[i];
			}
		}
		
		void reset()
		{
			firstdigit=lastdigit=SIZE-1;
		}
		
		bool operator ==(const bigint &num)
		{	
			for(int i=firstdigit+1;i<=lastdigit;i++)
			{
				if(digit[i]!=num.digits[i])
					return false;
			}
			return true;
		}
		
		bigint operator +=(const bigint &a)
		{
			int i;
			for(i=a.firstdigit+1;i<firstdigit+1;i++) // pad zeros in front
				digit[i]=a.digit[i];
			
			for(i=firstdigit+1;i<=a.firstdigit;i++);
			
			for(;i<=lastdigit;i++)
				digit[i]+=a.digit[i];
			
			int carry=0;
			firstdigit=min(firstdigit,a.firstdigit);
			for(i=lastdigit;i>firstdigit;i--)
			{
				digit[i]=digit[i]+carry;
				carry=digit[i]/SCALE;
				digit[i]=digit[i]%SCALE;
			}
			
			
			
			if(carry)
			{
				digit[firstdigit]=carry;
				firstdigit--;
			}
			return *this;
		}
		
		string  to_string()	 const	
		{
		   char a[(lastdigit-firstdigit+1)*WEIGHT];
		   int pos=0;
		   for(int i=firstdigit+1;i<=lastdigit;i++)
           {         
                        itoa(digit[i],a,pos);
                        if(i!=lastdigit)
                        {
									  int numzeros=WEIGHT;
                                      int x=digit[i+1];
                                      while(x)
                                      {
                                        numzeros--;
                                        x/=10;
                                      }
                                      if(digit[i+1]==0)
                                            numzeros--;
                                      
                                      for(int j=0;j<numzeros;j++)
                                          a[pos++]='0';
                        }   
           }
           a[pos]='\0';
           return a;
		}
		bigint operator +(const bigint &a)
		{
			bigint temp=*this;
			temp+=a;
			
			return temp;
		}
		
		void debug() const
		{
			for(int i=firstdigit+1;i<=lastdigit;i++)
				cout<<digit[i]<<" ";
			cout<<endl;
		}
		
		long long operator %(int num)
		{
			long long result=0;
			for(int i=firstdigit+1;i<=lastdigit;i++)
				result=(result*SCALE+digit[i])%num;
			return result;
		}
		
		bigint& operator /=(long long num)
		{
			long long lastCarry=0;
			for(int i = firstdigit+1;i<=lastdigit;i++){
				long long currentNumber = lastCarry*SCALE+digit[i];
				digit[i]=currentNumber/num;
				lastCarry=currentNumber%num;
			}
			while(firstdigit+1<=lastdigit&&!digit[firstdigit+1]){
				firstdigit++;
			}
		}
		
		bool operator == (const string &a)
		{
			return to_string()==a;
		}
		
};

template<size_t SIZE> ostream & operator <<(ostream &stream, const bigint<SIZE> &number){
	stream<<number.to_string();
	return stream;
}

int main()
{
	const int SIEVE_SIZE = 62000;
	sieve S(SIEVE_SIZE);
	int t;
	cin>>t;
	vector<int> primes;
	primes.reserve(10000);
	for(int i=2;i<SIEVE_SIZE;i++)
		if(S.isPrime(i))
			primes.push_back(i);
			
	vector<int> factors;
	while(t--){
		string n;
		cin>>n;
		
		long long numberL;
		
		bigint<200> numberB(n);
		bool isLong=false;
		if(n.length()<=18){
			sscanf(n.c_str(),"%lld",&numberL);
			isLong=true;
		}
			
		factors.clear();
		factors.reserve(10000);
		for(int i=0;i<primes.size();i++){
			if(isLong){
				if(numberL==1) break;
				while((numberL%primes[i])==0){
					factors.push_back(primes[i]);
					numberL/=primes[i];
				}
			}
			else {
				if(numberB.digit[numberB.lastdigit]==1&&numberB.firstdigit==numberB.lastdigit-1)
					break;
				while((numberB%primes[i])==0){
					factors.push_back(primes[i]);
					numberB/=primes[i];
				}	
			}
		}
		bool flag=false;
		if(isLong){
			if(numberL!=1)
				flag=true;
		}
		else{
			if(!(numberB.digit[numberB.lastdigit]==1&&numberB.firstdigit==numberB.lastdigit-1))
			flag=true;	
		}
		cout<<factors.size()+flag<<endl;
		for(int i=0;i<factors.size();i++)
			cout<<factors[i]<<"\n";
		if(flag){
			if(isLong)
				cout<<numberL<<endl;
			else
				cout<<numberB<<endl;
		}
	}
}
