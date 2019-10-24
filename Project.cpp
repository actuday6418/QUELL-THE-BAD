#include<iostream>
#include<cstdlib>
#include<list>
#include<random>
#include <SFML/Graphics.hpp>

using namespace std;

//All references to this engine thing and distributions are for generating random numbers with the random library


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
class Life
{
	public:
		list <organism> life;
		int iterate();
		//constructor for the initial organism
		Life()
		{
			organism m;
		        life.push_front(m);
		}
}life;

int Life::iterate()
{
	    list <organism>::iterator x;
            x= life.begin();
	    while(x!=life.end())
	    {
		x->turn();
		if(x->health==-1)
		{
			int posx = x->mapposition/500;
			int posy = x->mapposition%500;
			Space.map[posx][posy]=false;
			x=life.erase(x);
		}
		if(life.empty())
			return 7;
		++x;
	    }
	    return 0;
}


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
		health=50-LifeTicks-abs(prefertemperature-Space.temperaturemap[mapposition])-abs(preferlight-Space.lightmap[mapposition]);
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
			mutate(0);
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
			 posx = BackUpMapPosition/500;
			 posy = BackUpMapPosition%500;
			 mapposition = BackUpMapPosition;
			x=distro(engine);
 			if(mapposition > 249500)
				x=2;
 			else if(mapposition < 500)
				x=37;
			i++;
//		if(x>90)
//			mapposition+=4;	
		 if(x>75&&!(BackUpMapPosition>249998))
			mapposition+=1;
//		else if(x>65)
//			mapposition-=4;
		else if(x>50&&!(BackUpMapPosition<1))
			mapposition-=1;

		else if(x>25&&!(BackUpMapPosition>249500))
			mapposition+=500;
		else if(!(BackUpMapPosition<500))
			mapposition-=500;
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
		life.life.push_front(x);
		
		}
		else
		{
			organism::ID-=1;
		}
}



int Begin()
	{
	    //SFML declarations
	    sf::RenderWindow window(sf::VideoMode(1000, 1000), "EVOLUTION IN BITS AND BYTES");
	    sf::VertexArray line(sf::Points,250000);
	    int place;
	    int Ticks=0,MaxTicks=300;
     	    sf::Event event;
    while (window.isOpen())
    {
			Ticks++;

		//For closing the window 
		while (window.pollEvent(event))
		  {
                    if (event.type == sf::Event::EventType::Closed) 
		    { 
		      window.close();
		      return 7;
		    }
		  }

		window.clear(sf::Color::White);

			if(life.iterate()==7)
			{
			//	window.close();
				cout<<"Terminated on drained!";
			//	return 7;
			}
		
    
                //Code that sets the vector array values of color and position for each point on the map
                for(int i=0;i<500;i++)
                for(int j=0;j<500;j++)
                {
                place = i*500+j;
                line[place].position = sf::Vector2f((float)i,(float)j);
                if(Space.map[i][j]==true)
                line[place].color = sf::Color::Red;
                else 
                line[place].color = sf::Color::White;
                }

		//SFML draw and display
                window.draw(line);
                window.display();
		if(Ticks==MaxTicks)
			break;
    }
    list <organism>:: iterator x;
    x = life.life.end();
   x++;
   x->show();
		while(true)
		{

		//For closing the window 
		while (window.pollEvent(event))
		  {
                    if (event.type == sf::Event::EventType::Closed) 
		    { 
		      window.close();
		      return 7;
		    }
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

