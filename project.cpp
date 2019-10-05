#include<iostream>
#include<stdlib.h>

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
		}
		void ShowMap();
	}Space=space();


void space::ShowMap()
{
	for(int i=0;i<100;i++)
		for(int j=0;j<100;j++)
		{
			if(map[i][j]==true)
				cout<<".";
			else
				cout<<" ";
		}
}


class organism
	{
	public:
		static int ID;
	        int thisID;
		void organisms(organism* x)
     		{
		x->thisID=ID;
		ID++;
		x->mapposition=177;
		x->LifeTicks=0;
		int posx = x->mapposition/100;
		int posy = x->mapposition%100;
		Space.map[posx][posy]=true;
		x->preferlight=preferlight;
		x->prefertemperature=prefertemperature;
		x->preferlight+=rand()%3-1;
		x->prefertemperature+=rand()%3-1;
		x->health=100;
		x->node=NULL;
		}
		organism()
		{
		thisID=ID;
		ID++;
		mapposition=177;
		LifeTicks=0;
      		int posx = mapposition/100;
		int posy = mapposition%100;
		Space.map[posx][posy]=true;
		int preferlight=50;
		int prefertemperature=50;
		health=100;
		node=NULL;
		}
		int mapposition;
		int preferlight;
		int health;
		int LifeTicks;
		int prefertemperature;
		organism *node;
		void turn();
		void mutate();
		void FindMyHealth();
		void move();
		void show();
	};

int organism::ID=0;


void organism::show()
{
	cout<<"/n[$]ID"<<ID<<"/n[$]Temp"<<prefertemperature<<"/n[$]Light"<<preferlight<<"/n";
}


void organism::FindMyHealth()
	{
		health=100-LifeTicks-abs(prefertemperature-Space.temperaturemap[mapposition])-abs(preferlight-Space.lightmap[mapposition]);
		
		if(health<=0)
			health=-1;
	}	

	
void organism::turn()
	{
		move();
		if(rand()%45==7)
			mutate();
		LifeTicks++;
		FindMyHealth();
		
		
	
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
			if(mapposition > 9800)
				x=2;
			else if(mapposition < 100)
				x=37;
		if(x>75)
			mapposition+=1;
		else if(x>50)
			mapposition-=1;

		else if(x>25)
			mapposition+=4;
		else
			mapposition-=4;
		posx = mapposition/100;
		posy = mapposition%100;
		i++;
		if(i==100)
			break;
		}
		while(mapposition==177||Space.map[posx][posy]==true);
		if(i!=100)
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


	organism *headptr,*tailptr,*nowptr,*tempptr;
	
void organism::mutate()
	
	
	{
		organism *x = new organism();
		organisms(x);
		tailptr->node = x;
		tailptr = x;
	}


void Begin()
	{
		
		organism *x = new organism;
	        headptr = x;
	        tailptr = x;
		nowptr = x;
		int l;
		
		unsigned long int Ticks=0;
		while(Ticks<100)
		{
			Ticks++;
			
			if(nowptr==NULL)
				nowptr = headptr;
			nowptr->turn();
			if(headptr->health==-1)
			{
				tempptr = headptr;
				headptr = headptr->node;
				delete tempptr;
			}
			if(nowptr->node!=NULL&&nowptr->node->health==-1)
			{
				tempptr=nowptr->node;
				nowptr->node=nowptr->node->node;
                                delete tempptr;
			}
			nowptr=nowptr->node;
		//	Space.ShowMap();	
			cout<<Ticks<<endl;
		}
			tailptr->show();
		while(headptr!=NULL)
		{
			tempptr = headptr;
			headptr=headptr->node;
			delete tempptr;
		}

	}	
		




int main()
	{
      srand((unsigned)time(0));
      for(int i=0;i<10000;i++)
	      	      Space.lightmap[i]=40;
      for(int i=0;i<10000;i++)
	      	      Space.temperaturemap[i]=40;
      Begin();
      return 0;
        }
