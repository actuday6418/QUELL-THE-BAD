#include<iostream>
#include<stdlib.h>
#include<list>

using namespace std;


class space
	{
	public:
		bool map[10][10];
		int lightmap[100];
		int temperaturemap[100];
		space()
		{
			for(int i=0;i<10;i++)
				for(int j=0;j<10;j++)
					map[i][j]=false;
            for(int i=0;i<100;i++)
	      	        lightmap[i]=40;
            for(int i=0;i<100;i++)
	      	        temperaturemap[i]=40;
		}
		void ShowMap();
	}Space;


void space::ShowMap()
{
	for(int i=0;i<10;i++)
		{
        cout<<endl;
            for(int j=0;j<10;j++)
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
		int mapposition;
		int preferlight;
		int health;
		int LifeTicks;
		int prefertemperature;
        organism();
        organism(organism*);
		void turn();
		void mutate();
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
		mapposition=17;
		LifeTicks=0;
      	int posx = mapposition/10;
		int posy = mapposition%10;
		Space.map[posx][posy]=true;
		preferlight=5;
		prefertemperature=5;
		health=100;
		}

organism::organism(organism* parent)
     		{
		thisID=ID;
		ID++;
		mapposition=17;
		LifeTicks=0;
		int posx = parent->mapposition/10;
		int posy = parent->mapposition%10;
		Space.map[posx][posy]=true;
		preferlight=parent->preferlight;
		prefertemperature=parent->prefertemperature;
		preferlight+=rand()%3-1;
		prefertemperature+=rand()%3-1;
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
	cout<<"\n[$]ID"<<ID<<" [$]Temp"<<prefertemperature<<" [$]Light"<<preferlight<<" [$]Health"<<health<<" [$]Map_Position"<<mapposition<<"\n";
}

	
void organism::turn()
	{   
		move();
		if(rand()%45==7)
			{mutate();cout<<"LOL!!!";}
		LifeTicks++;
		FindMyHealth();
	}



void organism::move()
	{
		int BackUpMapPosition=mapposition;
		int posx = mapposition/10;
		int posy = mapposition%10;
		Space.map[posx][posy]=false;
		int i=0,x;

		do
		 {
			x=rand()%101;
			if(mapposition > 90)
				x=2;
			else if(mapposition < 10)
				x=37;
		if(x>75)
			mapposition+=1;
		else if(x>50)
			mapposition-=1;

		else if(x>25)
			mapposition+=10;
		else
			mapposition-=10;
		if(i==10)
			break;
        posx = mapposition/10;
		posy = mapposition%10;
		}
        while(mapposition==17||Space.map[posx][posy]==true);
        
		if(i!=10)
			{
				posx = mapposition/10;
				posy = mapposition%10;
				Space.map[posx][posy]=true;
			}
		else
			{
				mapposition=BackUpMapPosition;
  				posx = mapposition/10;
				posy = mapposition%10;
				Space.map[posx][posy]=true;
			}

	}

	
void organism::mutate()
	
	
	{
		organism* x;
cout<<"LOL";
        *x=organism(this);
		life.push_front(*x);
        x->turn();
	}




void Begin()
	{
	    {
            organism x;
            life.push_front(x);
        } 
	    list <organism>::  iterator x;
        list <organism>::  iterator y;
		unsigned long int Ticks=0;
        x= life.begin();
		while(Ticks<50)
		{
			Ticks++;
            if(x==life.end())
                x=life.begin();
            if(x->health==-1)
                {
                y=x;
                ++y;
                life.erase(x);
                x=y;
                continue;cout<<"XX";
                }
		    x->turn();
            advance(x,1);	
			cout<<Ticks<<"K"<<life.size()<<"L"<<endl;
		}
			//life.front().show();
		

	}	
		

int main()
{
  srand((unsigned)time(0));

Begin();
}

