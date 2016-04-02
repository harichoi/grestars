class MAKEBUILD{
public:
	char name[256];
	int energy;
	int money;
	int deffect;
	int maketime;
	int can[100];
	void create(char *_name,int _energy, int _deffect, int _money, int _maketime)
	{
		sprintf(name,_name);
		energy=_energy;
		deffect=_deffect;
		money=_money;
		maketime=_maketime;
	}
	void cans(int a, int b, int c, int d, int e)
	{
		can[a]=can[b]=can[c]=can[d]=can[e]=1;
	}
	int nani;
	HBITMAP bit[20];
	HBITMAP maskbit;
	int width;
	int height;
};
class BUILD{
public:
	int temp;
	int what;
	int flag;
	int kind;
	int energy;
	int deffect;
	int x;
	int y;
	int now;
	int can[100];
	void create(int _kind, MAKEBUILD temp, int _x, int _y)
	{
		kind=_kind;
		energy=temp.energy;
		int i;
		for(i=1 ; i<=99 ; i++)
			can[i]=temp.can[i];
		x=_x;
		y=_y;
	}
};