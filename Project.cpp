#include<iostream>
#include<cstdlib>
#include<list>
#include<random>

using namespace std;

default_random_engine engine;

class space
	{
	public:
		bool map[100][100];
		int lightmap[10000];
		int temperaturemap[10000];
		space()
		{
			for(int i=0;i<100;i++)
				for(int j=0;j<100;j++)
					map[i][j]=false;
            for(int i=0;i<10000;i++)
	      	        lightmap[i]=70;
            for(int i=0;i<10000;i++)
	      	        temperaturemap[i]=40;
		}
		void ShowMap();
	}Space;


void space::ShowMap()
{
	for(int i=0;i<100;i++)
		{
        cout<<endl;
            for(int j=0;j<100;j++)
		    {
			    if(map[i][j]==true)
			    	cout<<".";
			    else
			    	cout<<" ";
		    }
        }
}


class organism
	{
	public:
		static int ID;
	        int thisID;
		int parentID;
		int mapposition;
		int preferlight;
		int health;
		int LifeTicks;
		int prefertemperature;
       		organism();
	        organism(organism*);
		void turn();
		void mutate(int);
		void FindMyHealth();
		void move();
		void show();
	};

list <organism> life;

int organism::ID=0;

organism::organism()
		{
		thisID=ID;
		ID++;
		mapposition=177;
		LifeTicks=0;
		parentID=-1;
        	int posx = mapposition/100;
		int posy = mapposition%100;
		Space.map[posx][posy]=true;
		preferlight=50;
		prefertemperature=50;
		health=100;
		}

void organism::FindMyHealth()
	{
		health=100-LifeTicks-abs(prefertemperature-Space.temperaturemap[mapposition])-abs(preferlight-Space.lightmap[mapposition]);
		if(health<=0)
			health=-1;
	}	


void organism::show()
{
	cout<<"\n[$]ID"<<thisID<<"  [$]Parent ID"<<parentID<<" [$]Life_Ticks"<<LifeTicks<<" [$]Temp"<<prefertemperature<<" [$]Light"<<preferlight<<" [$]Health"<<health<<" [$]Map_Position"<<mapposition<<"\n";
}

	void organism::turn()
	{   
		move();
		LifeTicks++;	
		FindMyHealth();
		int u=20;
		uniform_int_distribution <int> dist(0,u);
		{
			if(dist(engine)==0)
			{	mutate(0);}
		}
	}


void organism::move()
	{
		int BackUpMapPosition=mapposition;
		int posx = mapposition/100;
 		int posy = mapposition%100;
		Space.map[posx][posy]=false;
		int i=0,x;
		uniform_int_distribution <int> distro(0,100);
		
		do
		 {
			x=distro(engine);
 			if(mapposition > 9900)
				x=2;
 			else if(mapposition < 100)
				x=37;
			i++;
		if(x>90)
			mapposition+=2;	
		else if(x>75)
			mapposition+=1;
		else if(x>65)
			mapposition-=2;
		else if(x>50)
			mapposition-=1;

		else if(x>25)
			mapposition+=100;
		else
			mapposition-=100;
		if(i==10)
			break;
       		posx = mapposition/100;
		posy = mapposition%100;
		}
        while(Space.map[posx][posy]==true);
        
		if(i!=10)
			{
				posx = mapposition/100;
				posy = mapposition%100;
				Space.map[posx][posy]=true;
			}
		else
			{
				mapposition=BackUpMapPosition;
  				posx = mapposition/100;
				posy = mapposition%100;
				Space.map[posx][posy]=true;
			}

	}

	void organism::mutate(int def)	
	{
		organism x;
		int y=x.thisID;
                x=*this;
		x.thisID=y;
		x.health=100;
		x.parentID=thisID;
                x.LifeTicks = 0; 
		uniform_int_distribution <int> di(-1,1),undi(1,2);
		y=undi(engine);
		if(y==1)
			x.preferlight += 2*di(engine);
		else if(y==2)
			x.prefertemperature +=2*di(engine);
		int posx = mapposition/100;
		int posy = mapposition%100;
		bool Flag=false;
		y=0;
		uniform_int_distribution <int> distro(0,7);
		while(y<10&&!Flag)
		{
		int Random=distro(engine);
			if(Random==0)
			{	if(Space.map[posx+1][posy]==false)
				{
					posx+=1;
					Flag = true;
				}
			}	
				else if(Random==1)
				{	if(Space.map[posx-1][posy]==false)
				{
					posx-=1;
					Flag=true;
				}}
				
				else if(Random==2)
				{	if(Space.map[posx][posy+1]==false)
				{
					posy+=1;
					Flag=true;
				}}
			
				
				else if(Random==3)
				{if(Space.map[posx][posy-1]==false)
				{
					posy-=1;
					Flag=true;
				}}
				
				
				else if(Random==4)
				{if(Space.map[posx+1][posy+1]==false)
				{
					posy+=1;
					posx+=1;
					Flag=true;
				}}
					
				else if(Random==5)
				{	if(Space.map[posx-1][posy-1]==false)
					{
						posy-=1;
						posx-=1;
						Flag=true;
					}}
					
					else if(Random==6)
					{if(Space.map[posx+1][posy-1]==false)
					{
						posy-=1;
						posx+=1;
						Flag=true;
					}}
					
			                else if(Random==7)
					{if(Space.map[posx-1][posy+1]==false)
					{
						posy+=1;
						posx-=1;
						Flag=true;
					}}
					
			y++;
			x.mapposition = posx*100+posy;
			if(x.mapposition>10000||x.mapposition<0)
				Flag=false;
		}
		if(Flag)
		{
		Space.map[posx][posy]=true;
		life.push_front(x);

		
		}
		else
		{
			organism::ID-=1;
		}
	}




int Begin()
	{
	    
            organism m;
            life.push_front(m); 
	    int y=0,z;
	    list <organism>::iterator x;
	    unsigned long int Ticks=0;
            x= life.begin();
  	    list <organism> ::iterator t;

	    while(Ticks<1000)
		{
			Ticks++;
		//	cin>>y;
	    		if(life.empty())
	   			 {
					cout<<"Terminated on drain";
		  			  return 7;
	   			 }
           		 
            			 x=life.begin();
				 while(x!=life.end())
				 {
           			 if(x->health==-1)
               			 {
              				   x=life.erase(x);
              				   continue;
               			 }
				 x->turn();
				 }
		       	 t = life.begin();
			 z=y=0;
               		 while(t!=life.end())
               		 {	
			 y+=t->prefertemperature;	 
			 z+=t->preferlight;
				 {
			//	  cout<<"Iterations "<<Ticks<<"   organisms alive  "<<life.size()<<"  ";
        			  t->show();
				 }
   		    		  ++t;
			 }

			if(life.size())
		 cout<<"Iterations "<<Ticks<<"  PT"<<y/life.size()<<"  PL"<<z/life.size()<<" Size"<<life.size()<<"\n";
			 }	
		return 0;
	}		



int main()
{
	engine.seed(time(0));
	cout<<"&";Begin();
cout<<"END!\n";
}

