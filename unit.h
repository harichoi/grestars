class MAKEUNIT{
public:
	char key;
	char name[256];
	int energy;
	int attack;
	int deffect;
	int speed;
	int money;
	int maketime;
	int from;
	int delay;
	int forcelength;
	int timetoattack;
	void create(char *_name,int _energy, int _attack, int _deffect, int _speed, int _money, int _maketime, int _from, int _delay, int _forcelength, int _timetoattack, char _key)
	{
		sprintf(name,_name);
		energy=_energy;
		attack=_attack;
		deffect=_deffect;
		speed=_speed;
		money=_money;
		from=_from;
		maketime=_maketime;
		delay=_delay;
		forcelength=_forcelength;
		timetoattack=_timetoattack;
		key=_key;
	}
	HBITMAP bit[10];
	HBITMAP maskbit;
	int width;
	int height;
};
class UNIT{
public:
	int temp3;
	int enemy;
	int attackto[100];
	int attacktime[100];
	int attacktoub[100];
	int showani;
	int temp;
	int temp2;
	int flag;
	int flag2;
	int delay;
	int kind;
	int energy;
	int deffect;
	int speed;
	int score;
	int attack;
	int forcelength;
	int timetoattack; 
	int x;
	int y;
	int fx;
	int fy;
	void create(int _kind, MAKEUNIT temp, int _x, int _y)
	{
		kind=_kind;
		energy=temp.energy;
		speed=temp.speed;
		attack=temp.attack;
		deffect=temp.deffect;
		forcelength=temp.forcelength;
		timetoattack=temp.timetoattack;
		delay=temp.delay;
		x=_x;
		y=_y;
	}
};