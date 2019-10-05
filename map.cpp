#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstdlib>
#include<ctime>
#include<cmath>


using namespace std;

//function1
int randfunc()
{int x;
	x=rand()%11;
	if(x>2)
          x=1;
	else if (x>6)
		x=rand()%5;
	else
		x=rand()%7;
       return(x);}
	 	
int main()
{srand((unsigned) time(0));

	//init with zeroes
	int temp[500];
	long int n,s;
	n=400;
	s=sqrt(n);
	for(int i=0;i<n;i++)
	{temp[i]=0;}

//FIRST ROW AND COLUMN
temp[0]=rand()%101;
for(int i=1;i<s;i++)
{int b;
	b=randfunc();
	if (rand()%2==0 && temp[i-1]<94)
	temp[i]=abs(temp[i-1]+b);
	else
	temp[i]=abs(temp[i-1]-b);
	
}	
	
	
//2
for(int i=s;i<=n-s;i+=s)
{int b;
	b=randfunc();
	if (rand()%2==0 && temp[i-s]<94)
		temp[i]=abs(temp[i-s]+b);
	else
		temp[i]=abs(temp[i-s]-b);
	
}		
//outermostestloop
for(int k=s+1;k<n;k=k+s+1)
{
	
	
//actual program
int b;
b=randfunc();
if(rand()%2==0 && temp[k-(s+1)]<94)
temp[k]=(temp[k-1]+temp[k-(s+1)])/2+b;
else
temp[k]=(temp[k-1]+temp[k-(s+1)])/2-b; //diagonal elements

for(int i=k+1;i<=s+k;i++)
{int b;
	b=randfunc();
	if (rand()%2==0 && temp[i-s-1]<94)
	temp[i]=abs(temp[i-s-1]+rand()%2);
	else
	temp[i]=abs(temp[i-s-1]-rand()%2);
	
}	
	
	

for(int i=k+s;i<=n-s;i+=s)
{int b;
	b=randfunc();
	if (rand()%2==0 && temp[i-1]<94)
		temp[i]=abs(temp[i-1]+b);
	else
		temp[i]=abs(temp[i-1]-b);
	
}	
	
	
	
	
	
	
}	
	
	
	
	//displaying part
	for(int i=0;i<n;i+=s)
	{for(int j=i;j<i+s;j++)
		{cout<<temp[j]<<" ";}
		cout<<"\n";
	}


	return 0;
}

