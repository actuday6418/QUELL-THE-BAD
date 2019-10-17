#include<iostream>
#include<cstdlib>
#include<list>
#include<random>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

//All references to this engine thing and distrobutions are for generating random nunumbe with the random library


default_random_engine engine;

//class implementing the environment variables and map
class space
	{
	public:
		bool map[500][500];
		int lightmap[250000];
		int temperaturemap[250000];
		space()
		{
			for(int i=0;i<500;i++)
				for(int j=0;j<500;j++)
					map[i][j]=false;
            for(int i=0;i<250000;i++)
	      	        lightmap[i]=70;
            for(int i=0;i<250000;i++)
	      	        temperaturemap[i]=40;
		}
		void ShowMap();
	}Space;


void space::ShowMap()
{
	for(int i=0;i<500;i++)
		{
        cout<<endl;
            for(int j=0;j<500;j++)
		    {
			    if(map[i][j]==true)
			    	cout<<".";
			    else
			    	;
		    }
        }
}

//class for orgamisms and their attributes
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

//list that holds the collection of organisms alive
list <organism> life;

int organism::ID=0;

//only the initial organism uses this constructor 
organism::organism()
		{
		thisID=ID;
		ID++;
		mapposition=1777;
		LifeTicks=0;
		parentID=-1;
        	int posx = mapposition/500;
		int posy = mapposition%500;
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

//Not in use right now
void organism::show()
{
	cout<<"\n[$]ID"<<thisID<<"  [$]Parent ID"<<parentID<<" [$]Life_Ticks"<<LifeTicks<<" [$]Temp"<<prefertemperature<<" [$]Light"<<preferlight<<" [$]Health"<<health<<" [$]Map_Position"<<mapposition<<"\n";
}

//Function called everytime it is an organism's turn to make a move and/or mutate
void organism::turn()
{   
		move();
		LifeTicks++;	
		FindMyHealth();
		int u=10;
		uniform_int_distribution <int> dist(0,u);
		{
			if(dist(engine)==0)
			{	mutate(0);}
		}
}

//Function that moves an organism from one point on the map to another
void organism::move()
	{
		int BackUpMapPosition=mapposition;
		int posx = mapposition/500;
 		int posy = mapposition%500;
		Space.map[posx][posy]=false;
		int i=0,x;
		uniform_int_distribution <int> distro(0,100);
		
		do
		 {
			x=distro(engine);
 			if(mapposition > 249500)
				x=2;
 			else if(mapposition < 500)
				x=37;
			i++;
		if(x>90)
			mapposition+=4;	
		else if(x>75)
			mapposition+=3;
		else if(x>65)
			mapposition-=4;
		else if(x>50)
			mapposition-=3;

		else if(x>25)
			mapposition+=1000;
		else
			mapposition-=1000;
		if(i==10)
			break;
       		posx = mapposition/500;
		posy = mapposition%500;
		}
        while(Space.map[posx][posy]==true);
        
		if(i!=10)
			{
				posx = mapposition/500;
				posy = mapposition%500;
				Space.map[posx][posy]=true;
			}
		else
			{
				mapposition=BackUpMapPosition;
  				posx = mapposition/500;
				posy = mapposition%500;
				Space.map[posx][posy]=true;
			}

	}

//Function called from turn each time the organism has to mutate
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
		int posx = mapposition/500;
		int posy = mapposition%500;
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
			x.mapposition = posx*500+posy;
			if(x.mapposition>250000||x.mapposition<0)
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
	    //The initial organism
            organism m;
            life.push_front(m); 

	    //SFML declarations
	    RenderWindow window(VideoMode(1000, 1000), "EVOLUTION IN BITS AND BYTES");
            VertexArray line(Points,250000SF
	    Event event;
	    int place;

	    list <organism>::iterator x;
	    unsigned long int Ticks=0;
            x= life.begin();
  	    list <organism> ::iterator t;
    while (window.isOpen())
    {
	    x=life.begin();

	    //Main loop with Ticks as number of iterations
	    while(Ticks<100)
		{
			if(x==life.end())
				x=life.begin();
			Ticks++;
		  while (window.pollEvent(event))
		  {
                    if (event.type == Event::Closed) 
			    window.close();
		  }
		  window.clear(Color::White);
           		 if(life.empty())
			 {
				 cout<<"Terminated on drained ";
				 return 7;
			 }
			 x->turn();
			 if(x->health==-1)
				 x=life.erase(x);
		    
                //Code that sets the vector array values of color and position for each point on the map
                for(int i=0;i<500;i++)
                for(int j=0;j<500;j++)
                {
                place = i*500+j;
                line[place].position = Vector2f((float)i,(float)j);
                if(Space.map[i][j]==true)
                line[place].color = Color::Red;
                else 
                line[place].color = Color::White;
                }

		//SFML draw and display
                window.draw(line);
                window.display();
}

			 }	
		return 0;
	}		



int main()
{
	//seeding the random engine
	engine.seed(time(0));
	Begin();
}

