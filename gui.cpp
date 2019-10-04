#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstdlib>
#include<ctime>
#include<cmath>

using namespace std;
int main()
	
{int a;
 int temperature[100];	

	srand((unsigned)time(0));
        
	
      //phase1
      //10 x 10 seen as n x n	
	for(int i=0;i<100;i++)        //assigning temperature with all values as zeroes
	{temperature[i]=0;}
	

	
temperature[55]=rand()%101;	
	//linear right
                    for(int i=56;i<60;i++)
	{	if(rand()%2==0)
		temperature[i]=temperature[i-1]+rand()%5;
		else
		temperature[i]=temperature[i-1]-rand()%5; }
		
	//linear left
	       for(int i=54;i>=50;i--)
	       {  if(rand()%2==0)
		   temperature[i]=temperature[i+1]+rand()%5;
		   else
			  temperature[i]=temperature[i+1]-rand()%5; } 
         //direct up

	for(int i=45;i>0;i=i-10)
	{ if(rand()%2==0)
		   temperature[i]=temperature[i+10]+rand()%5;
		   else
			  temperature[i]=temperature[i+10]-rand()%5;} 
//direct down
	for(int i=65;i<100;i=i+10)	
{ if(rand()%2==0)
		   temperature[i]=temperature[i-10]+rand()%5;
		   else
			  temperature[i]=temperature[i-10]-rand()%5;} 
	
//diagonal
for(int i=66;i<100;i+=11)
{if(rand()%2==0)
	temperature[i]=temperature[i-11]+rand()%5;
	else
		temperature[i]=temperature[i-11]-rand()%5;
}
for(int i=44;i>=0;i-=11){
if(rand()%2==0)
	temperature[i]=temperature[i+11]+rand()%5;
	else
		temperature[i]=temperature[i+11]-rand()%5;}
	

//off diagonal
for(int i=64;i<100;i+=9)
{if(rand()%2==0)
	temperature[i]=temperature[i-9]+rand()%5;
	else
		temperature[i]=temperature[i-9]-rand()%5;
}
for(int i=46;i>=0;i-=9){
	if(rand()%2==0)
	temperature[i]=temperature[i+9]+rand()%5;
	else
		temperature[i]=temperature[i+9]-rand()%5;}
	

	
	
	
	
	
		//displaying part
	for(int i=0;i<100;i=i+10)
	{for(int j=i;j<i+10;j++)
		{
		cout<<temperature[j]<<" ";}
	cout<<"\n";
	}
 
	return 0;
}
