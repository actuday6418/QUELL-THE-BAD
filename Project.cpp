#include<iostream>
#include<stdlib.h>
#include<list>

using namespace std;


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
	      	        lightmap[i]=40;
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
		int mapposition;
		int preferlight;
		int health;
		int LifeTicks;
		int prefertemperature;
        organism();
        organism(organism*);
		int turn();
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
		mapposition=177;
		LifeTicks=0;
      	int posx = mapposition/100;
		int posy = mapposition%100;
		Space.map[posx][posy]=true;
		preferlight=5;
		prefertemperature=5;
		health=100;
		}

organism::organism(organism* parent)
     		{
		thisID=ID;
		ID++;
		mapposition=177;
		LifeTicks=0;
		int posx = parent->mapposition/100;
		int posy = parent->mapposition%100;
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

	
int organism::turn()
	{   
		move();
		LifeTicks++;
		FindMyHealth();
		if(rand()%20==7)
			{mutate();
			return 1;
			}
		return 0;
	}



void organism::move()
	{
		int BackUpMapPosition=mapposition;
		int posx = mapposition/100;
		int posy = mapposition%100;
		Space.map[posx][posy]=false;
		int i=0,x;

		do
		 {
			x=rand()%101;
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
        while(mapposition==177||Space.map[posx][posy]==true);
        
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

	
void organism::mutate()	
	{
		organism x;
                x=this;
		life.push_front(x);
	}




int Begin()
	{
	    {
            organism x;
            life.push_front(x);
        } 
	    int y;
	    list <organism>::  iterator x;
		unsigned long int Ticks=0;
        x= life.begin();
	list <organism> ::iterator t;
		while(Ticks<10)
		{
			Ticks++;
			cout<<"#";
	    if(life.empty())
	    {
		    return 7;
	    }
            if(x==life.end())
                x=life.begin();
            if(x->health==-1)
                {
                 x=life.erase(x);
                continue;
                }
		if(x->turn())
			cout<<"Iterations done:"<<Ticks<<"	Organisms currently alive:"<<life.size()<<"\n";
		
                while(t!=life.end())
                {
		t=life.begin();
     //   t->show();
        ++t;
        }
		}
		return 0;
	}		

int main()
{
srand((unsigned)time(0));
while(true)
{cout<<"&";	if(Begin()!=7)
		break;}
cout<<"END!";
}

