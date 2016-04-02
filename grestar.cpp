//kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib 
#include <math.h>
#include <afxext.h>
#include <afxdisp.h>
#include <afxdtctl.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>
#endif 
#include "resource.h"
#include "build.h"
#include "unit.h"
#define pi 3.1415926535
#define NTEAM 2
#define MAPX 2500 
#define MAPY 2500

#define max2(a,b) ((a>b)?a:b)
#define min2(a,b) ((a>b)?b:a)
#define ME 1

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND MainHwnd, DrawHwnd, ToolHwnd, ToolupHwnd, MathHwnd,MultiMathHwnd;
HDC MemDC;
HBITMAP copyright, moneybit, downbit, downmaskbit, allcenterbit, allcentermaskbit, farmerbit, farmermaskbit, bombbit;
int dfx, dfy;
int keys[256];
void newbuild(int team, int kind, int x, int y);
int newunit(int team, int kind, int x, int y);
void attack();
//////////////////////////////////
void unitfarmer();
void computer();
int newbuilds(int team, int kind, int x, int y);
//////////////////////////////////
MAKEUNIT makeunit[100];
MAKEBUILD makebuild[100];
UNIT unit[3][200];
BUILD build[3][200];
int money[3];
int nuc, nbc;
int unitchoose[100];
int buildchoose;
int ax, ay, bx, by;
int map[100][100];

int ndot;
int showdotx[1000],showdoty[1000];
int dbclktime=10;
int befc;
int pop[3];
int maxpop[3];

/////////////////////////////////////////////////////

void draw(HWND hWnd);

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPreInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow){
	downmaskbit=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_DOWNMASK));
	downbit=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_DOWN));
	makeunit[1].bit[0]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FARMER));
	makeunit[1].bit[1]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FARMER2));
	makeunit[1].bit[2]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FARMER3));
	makeunit[1].maskbit=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FARMERMASK));
	makeunit[2].bit[0]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BASIC));
	makeunit[2].maskbit=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BASICMASK));
	makeunit[3].bit[0]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_NEXTBASIC));
	makeunit[3].maskbit=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_NEXTBASICMASK));
	makeunit[4].bit[0]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_TANK));
	makeunit[4].maskbit=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_TANKMASK));
	makebuild[1].bit[1]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_ALLCENTER));
	makebuild[1].bit[2]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_ALLCENTER2));
	makebuild[1].maskbit=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_ALLCENTERMASK));
	makebuild[0].bit[1]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_MONEY));
	makebuild[2].bit[1]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_MAKING));
	makebuild[2].bit[2]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_MAKING2));
	makebuild[3].bit[1]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_SOLDIERCREATOR));
	makebuild[3].bit[2]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_SOLDIERCREATOR2));
	makebuild[3].maskbit=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_SOLDIERCREATORMASK));
	makebuild[4].bit[1]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY));
	makebuild[4].bit[2]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY2));
	makebuild[4].bit[3]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY3));
	makebuild[4].bit[4]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY4));
	makebuild[4].bit[5]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY5));
	makebuild[4].bit[6]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY6));
	makebuild[4].bit[7]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY5));
	makebuild[4].bit[8]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY4));
	makebuild[4].bit[9]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY3));
	makebuild[4].bit[10]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY2));
	makebuild[4].bit[11]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY));
	makebuild[4].bit[12]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY10));
	makebuild[4].bit[13]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY11));
	makebuild[4].bit[14]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY12));
	makebuild[4].bit[15]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY13));
	makebuild[4].bit[16]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY14));
	makebuild[4].bit[17]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY13));
	makebuild[4].bit[18]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY12));
	makebuild[4].bit[19]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY11));
	makebuild[4].bit[20]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FACTORY10));
	makebuild[4].maskbit=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_SOLDIERCREATORMASK));
	bombbit=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BOMB));

	makeunit[1].create("farmer",50,5,0,5,750,300,1,30,75,5,'F');
	makeunit[2].create("basic",50,2,1,7,500,400,3,15,100,2,'B');
	makeunit[3].create("nextbasic",100,10,1,6,4500,600,3,20,150,4,'N');
	makeunit[4].create("tank",200,50,1,3,5000,1500,4,30,350,10,'T');
	makebuild[1].create("allcenter",1000,0,2000,1500);
	makebuild[1].cans(1,0,0,0,0);
	makebuild[2].create("creating..",500,0,0,0);
	makebuild[3].create("soidlercreator",500,0,1500,1000);
	makebuild[3].cans(2,3,0,0,0);
	makebuild[4].create("factory",1000,0,5000,3000);
	makebuild[4].cans(4,0,0,0,0);
	makebuild[1].nani=makebuild[2].nani=makebuild[3].nani=2, makebuild[4].nani=19;
	makebuild[0].create("source",3000,0,0,0);
	
//	makebuild[

	newbuild(1,1,100,100);
	newunit(1,1,50,175);
	newunit(1,1,100,175);
	newunit(1,1,150,175);
	newunit(1,1,200,175);
	newbuild(2,1,MAPX-500,MAPY-100);
	newunit(2,1,MAPX-450,MAPY-175);
	newunit(2,1,MAPX-500,MAPY-175);
	newunit(2,1,MAPX-550,MAPY-175);
	newunit(2,1,MAPX-600,MAPY-175);
	int i;
	srand(GetTickCount());
	for(i=0 ; i<=99 ; i++)
	newbuild(0,0,rand()%MAPX,rand()%MAPY);
	

	money[1]=money[2]=1000;

	MSG msg;
	HWND hWnd;
	WNDCLASS wnd;

	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wnd.hCursor = LoadCursor(hInstance,MAKEINTRESOURCE(IDC_CURSOR1));
	wnd.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	wnd.hInstance = hInstance;
	wnd.lpfnWndProc = WndProc;
	wnd.lpszClassName = "grestar";
	wnd.lpszMenuName =0;// MAKEINTRESOURCE(IDR_MENU1);
	wnd.style = 0;

	RegisterClass(&wnd);

	hWnd = CreateWindow("grestar","grestar",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,800,600,0,0,hInstance,0);
	ShowWindow(hWnd,SW_SHOW);

	//selectx++;selecty++;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int k, i, j;
	double wa, dx, dy;double min=999999999;
		int where=0;
	switch(msg)
	{
	case WM_LBUTTONDBLCLK:
		
		break;
	case WM_RBUTTONDOWN:
		dx=LOWORD(lParam)+dfx;
		dy=HIWORD(lParam)+dfy;
		if(nuc>=1)
		{
			for(i=1 ; i<=nuc ; i++)
			{
				unit[1][unitchoose[i]].flag2=0;
				unit[1][unitchoose[i]].fx=dx;
				unit[1][unitchoose[i]].fy=dy;
			}
		}
		break;
	case WM_LBUTTONDOWN:
		dx=LOWORD(lParam)+dfx;
		dy=HIWORD(lParam)+dfy;
		if(dbclktime<=4)
		{
		where=0;
		for(i=1 ; i<=99 ; i++)
		{
			if(unit[1][i].energy>0){
			if(hypot(dx-unit[1][i].x,dy-unit[1][i].y)<min && dx>=unit[1][i].x-25 && dx<=unit[1][i].x+25 && dy>=unit[1][i].y-25 && dy<=unit[1][i].y+25)
			{
				min=hypot(dx-unit[1][i].x,dy-unit[1][i].y);
				where=i;
			}
			}
		}
	//	if(befc!=where)
	//		break;
	//	exit(1);
		if(keys[VK_SHIFT])
		{
		}
		else
		{
			nuc=0;
		}
		for(i=1 ; i<=99 ; i++)
		{
			if(unit[1][where].kind==unit[1][i].kind){
			if(hypot(dx-unit[1][i].x,dy-unit[1][i].y)<400)
			{
				nuc++;
				unitchoose[nuc]=i;
			}
			}
		}
		}
		else
		{
			dbclktime=0;
		for(i=1 ; i<=99 ; i++)
		{
			if(build[1][i].energy>0){
			if(hypot(dx-build[1][i].x,dy-build[1][i].y)<min && dx>=build[1][i].x-75 && dx<=build[1][i].x+75 && dy>=build[1][i].y-75 && dy<=build[1][i].y+75)
			{
				min=hypot(dx-build[1][i].x,dy-build[1][i].y);
				where=i;
			}
			}
		}
		nbc=1;
		buildchoose=where;
		if(where==0)
			nbc=0;

		where=0;
		for(i=1 ; i<=99 ; i++)
		{
			if(unit[1][i].energy>0){
			if(hypot(dx-unit[1][i].x,dy-unit[1][i].y)<min && dx>=unit[1][i].x-25 && dx<=unit[1][i].x+25 && dy>=unit[1][i].y-25 && dy<=unit[1][i].y+25)
			{
				min=hypot(dx-unit[1][i].x,dy-unit[1][i].y);
				where=i;
				befc=i;
			}
			}
		}
		if(keys[VK_SHIFT])
		{
			nuc++;
			unitchoose[nuc]=where;
			if(where==0)
				nuc--;
		}
		else{
		nuc=1;
		unitchoose[1]=where;
		if(where==0)
			nuc=0;
		else
		{
			nbc=0;
		}
		}
		}
		break;
	case WM_CREATE:
		break;
	case WM_PAINT:
		draw(hWnd);
		SetTimer(hWnd,1,1,0); 
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		keys[wParam]=1;
		if(wParam=='A')
		{
			if(nuc==1 && unit[1][unitchoose[1]].kind==1 && unit[1][unitchoose[1]].energy>0)
			{
				if(money[1]>=makebuild[1].money){
				if(newbuilds(1,1,unit[1][unitchoose[1]].x,unit[1][unitchoose[1]].y))
				money[1]-=makebuild[1].money;
				}
			}
		}
		if(wParam=='S')
		{
			if(nuc==1 && unit[1][unitchoose[1]].kind==1 && unit[1][unitchoose[1]].energy>0)
			{
				if(money[1]>=makebuild[3].money){
				if(newbuilds(1,3,unit[1][unitchoose[1]].x,unit[1][unitchoose[1]].y))
				money[1]-=makebuild[3].money;
				}
			}
		}
		if(wParam=='B')
		{
			if(nbc==1 && build[1][buildchoose].energy>0 && build[1][buildchoose].flag==0 && build[1][buildchoose].kind==3)
			{
				if(money[1]>=makeunit[2].money)
				{
					money[1]-=makeunit[2].money;
					build[1][buildchoose].what=2;
					build[1][buildchoose].flag=1;
					build[1][buildchoose].temp=0;
				}
			}
		}
		if(wParam=='T')
		{
			if(nbc==1 && build[1][buildchoose].energy>0 && build[1][buildchoose].flag==0 && build[1][buildchoose].kind==4)
			{
				if(money[1]>=makeunit[4].money)
				{
					money[1]-=makeunit[4].money;
					build[1][buildchoose].what=4;
					build[1][buildchoose].flag=1;
					build[1][buildchoose].temp=0;
				}
			}
			if(nuc==1 && unit[1][unitchoose[1]].kind==1 && unit[1][unitchoose[1]].energy>0)
			{
				if(money[1]>=makebuild[4].money){
				if(newbuilds(1,4,unit[1][unitchoose[1]].x,unit[1][unitchoose[1]].y))
				money[1]-=makebuild[4].money;
				}
			}
		}
		if(wParam=='N')
		{
			if(nbc==1 && build[1][buildchoose].energy>0 && build[1][buildchoose].flag==0 && build[1][buildchoose].kind==3)
			{
				if(money[1]>=makeunit[3].money)
				{
					money[1]-=makeunit[3].money;
					build[1][buildchoose].what=3;
					build[1][buildchoose].flag=1;
					build[1][buildchoose].temp=0;
				}
			}
		}
		if(wParam=='F')
		{
			if(nbc==1 && build[1][buildchoose].energy>0 && build[1][buildchoose].flag==0 && build[1][buildchoose].kind==1)
			{
				if(money[1]>=makeunit[1].money)
				{
					money[1]-=makeunit[1].money;
					build[1][buildchoose].what=1;
					build[1][buildchoose].flag=1;
					build[1][buildchoose].temp=0;
				}
			}
			for(i=1 ; i<=nuc ; i++){
				if(nuc>=0 && unit[1][unitchoose[i]].kind==1)
				{
					unit[1][unitchoose[i]].flag2=1;
					unit[1][unitchoose[i]].flag=0;
				}
			}
		}
		break;
	case WM_KEYUP:
		keys[wParam]=0;
		break;
	case WM_TIMER:
		dbclktime++;
		computer();
		attack();
		unitfarmer();
		if(keys[VK_DOWN])
			dfy+=30;
		if(keys[VK_UP])
			dfy-=30;
		if(keys[VK_LEFT])
			dfx-=30;
		if(keys[VK_RIGHT])
			dfx+=30;

		///////////unit_move//////////////
		for(i=1 ; i<=NTEAM ; i++)
			for(j=1 ; j<=99 ; j++)
			{
				dx=unit[i][j].fx-unit[i][j].x;
				dy=unit[i][j].fy-unit[i][j].y;

				wa=atan2(dy,dx);
				unit[i][j].x+=cos(wa)*unit[i][j].speed;
				unit[i][j].y+=sin(wa)*unit[i][j].speed;
				if(hypot(dx,dy)<=unit[i][j].speed)
					unit[i][j].x=unit[i][j].fx, unit[i][j].y=unit[i][j].fy;
			}
		for(k=1 ; k<=NTEAM ; k++)
			for(i=1 ; i<=99 ; i++)
				for(j=1 ; j<=99 ; j++)
					if(unit[k][i].energy>0 && unit[k][j].energy>0)
					{
						if(hypot(unit[k][i].x-unit[k][j].x,unit[k][i].y-unit[k][j].y)<50)
						{
						if(unit[k][i].x<unit[k][j].x)
							unit[k][i].fx-=2, unit[k][j].fx+=2;
						else if(unit[k][i].x>unit[k][j].x)
							unit[k][i].fx+=2, unit[k][j].fx-=2;
						if(unit[k][i].y<unit[k][j].y)
							unit[k][i].fy-=2, unit[k][j].fy+=2;
						else if(unit[k][i].y>unit[k][j].y)
							unit[k][i].fy+=2, unit[k][j].fy-=2;
						}
					}
		//////////////////////////////////
		for(i=1 ; i<=NTEAM ; i++)
			for(j=1 ; j<=99 ; j++)
			{
				if(build[i][j].energy>0 && build[i][j].flag==1 && build[i][j].kind!=2)
				{
					build[i][j].temp++;
					if(build[i][j].temp>=makeunit[build[i][j].what].maketime)
					{
						build[i][j].flag=0;
						newunit(i,build[i][j].what,build[i][j].x+rand()%150-75,build[i][j].y+75);
					}
				}
				if(build[i][j].energy>0 && build[i][j].kind==2)
				{
					build[i][j].temp++;
					if(build[i][j].temp>=makebuild[build[i][j].what].maketime)
					{
					//	build[i][j].flag=0;
						build[i][j].energy=0;
						newbuild(i,build[i][j].what,build[i][j].x,build[i][j].y);
					}
				}
			}
		draw(hWnd);
	};
	return DefWindowProc(hWnd,msg,wParam,lParam);
}


void draw(HWND hWnd)
{
	int i, j, k;
	char str[256];
	HBITMAP bit, *old, *old2;
	HBRUSH *old3, brush;
	HPEN *old4, pen;
	HDC hDC;
	HDC MemDC;
	HDC bitDC;
	k=0;
	j=0;
	for(i=1 ; i<=30 ; i++)
		k+=build[0][i].energy;
	j=k;
	k/=30;
	sprintf(str,"자원평균 : %d, 자원합계 : %d",k,j);

	hDC=GetDC(hWnd);
	bit=CreateCompatibleBitmap(hDC,1200,1200);
	MemDC=CreateCompatibleDC(hDC);
	bitDC=CreateCompatibleDC(hDC);
	//hDC=BeginPaint(hWnd,&ps);
	old = (HBITMAP *)SelectObject(MemDC,bit);

	SetBkMode(MemDC,0);
	pen=CreatePen(5,0,RGB(0,0,0));
	old4=(HPEN *)SelectObject(MemDC,pen);
	for(i=0 ; i<=MAPX/50 ; i++){
		for(j=0 ; j<=MAPY/50 ; j++){
			double a, b;
			a=i;
			b=j;
			if(map[i][j]%100==1)
				brush=CreateSolidBrush(RGB(sin(a/10)*sin(b/10)*100+100,255,sin(b/10)*100+100));
			else if(map[i][j]%100==2)
				brush=CreateSolidBrush(RGB(sin(a/10)*sin(b/10)*100+100,cos(a/10)*100+100,255));
			else
				brush=CreateSolidBrush(RGB(sin(a/10)*sin(b/10)*100+100,cos(a/10)*100+100,sin(b/10)*100+100));
				
			old3=(HBRUSH *)SelectObject(MemDC,brush);
			Rectangle(MemDC,i*50-dfx-25,50*j-dfy-25,50*i+50-dfx-25,50*j+50-dfy-25);
			SelectObject(MemDC,old3);
			DeleteObject(brush);
		}
	}
	SelectObject(MemDC,old4);
	DeleteObject(pen);
SetTextColor(MemDC,RGB(255,255,255));
TextOut(MemDC,10,10,str,strlen(str));

	/////////////

	if(nbc>=1)
	{
		Rectangle(MemDC,build[1][buildchoose].x-80-dfx,build[1][buildchoose].y-80-dfy,build[1][buildchoose].x+80-dfx,build[1][buildchoose].y+80-dfy);
	}
	if(nuc>=1)
	{
		for(i=1 ; i<=nuc ; i++)
		{
			Rectangle(MemDC,unit[1][unitchoose[i]].x-30-dfx,unit[1][unitchoose[i]].y-30-dfy,unit[1][unitchoose[i]].x+30-dfx,unit[1][unitchoose[i]].y+30-dfy);
		}
	}
	for(j=1 ; j<=99 ; j++)
				if(build[0][j].energy>0)
				{
					old2=(HBITMAP *)SelectObject(bitDC,makebuild[build[0][j].kind].bit[1]);
					BitBlt(MemDC,build[0][j].x-dfx-25,build[0][j].y-dfy-25,1024,768,bitDC,0,0,SRCCOPY);
					SelectObject(bitDC,old2);					
				}

		for(i=1 ; i<=NTEAM ; i++)
			for(j=1 ; j<=99 ; j++)
			{
				if(build[i][j].energy>0)
				{
					if(build[i][j].kind==2)
					{
						old2=(HBITMAP *)SelectObject(bitDC,makebuild[build[i][j].kind].bit[(build[i][j].now/(20-build[i][j].flag*19))%makebuild[build[i][j].kind].nani+1]);
					build[i][j].now++;
					BitBlt(MemDC,build[i][j].x-dfx-75,build[i][j].y-dfy-75,1024,768,bitDC,0,0,SRCCOPY);
					SelectObject(bitDC,old2);
					Rectangle(MemDC,build[i][j].x-dfx-build[i][j].energy/10,build[i][j].y-dfy+76,build[i][j].x-dfx+build[i][j].energy/10,build[i][j].y-dfy+80);
					
					}
					else
					{
					old2=(HBITMAP *)SelectObject(bitDC,makebuild[build[i][j].kind].maskbit);
					BitBlt(MemDC,build[i][j].x-dfx-75,build[i][j].y-dfy-75,1024,768,bitDC,0,0,SRCAND);
					SelectObject(bitDC,old2);
					old2=(HBITMAP *)SelectObject(bitDC,makebuild[build[i][j].kind].bit[(build[i][j].now/(20-build[i][j].flag*19))%makebuild[build[i][j].kind].nani+1]);
					build[i][j].now++;
					BitBlt(MemDC,build[i][j].x-dfx-75,build[i][j].y-dfy-75,1024,768,bitDC,0,0,SRCPAINT);
					SelectObject(bitDC,old2);
					Rectangle(MemDC,build[i][j].x-dfx-build[i][j].energy/10,build[i][j].y-dfy+76,build[i][j].x-dfx+build[i][j].energy/10,build[i][j].y-dfy+80);
					}
				}
			}
		for(i=1 ; i<=NTEAM ; i++)
			for(j=1 ; j<=199 ; j++)
			{
				if(unit[i][j].energy>0)
				{
					old2=(HBITMAP *)SelectObject(bitDC,makeunit[unit[i][j].kind].maskbit);
					BitBlt(MemDC,unit[i][j].x-dfx-25,unit[i][j].y-dfy-25,1024,768,bitDC,0,0,SRCAND);
					SelectObject(bitDC,old2);
					old2=(HBITMAP *)SelectObject(bitDC,makeunit[unit[i][j].kind].bit[unit[i][j].showani]);
					BitBlt(MemDC,unit[i][j].x-dfx-25,unit[i][j].y-dfy-25,1024,768,bitDC,0,0,SRCPAINT);
					SelectObject(bitDC,old2);
					Rectangle(MemDC,unit[i][j].x-dfx-unit[i][j].energy/10,unit[i][j].y-dfy+26,unit[i][j].x-dfx+unit[i][j].energy/10,unit[i][j].y-dfy+30);
					
				}
			}

	//배경  출력
		old2=(HBITMAP *)SelectObject(bitDC,downmaskbit);
		BitBlt(MemDC,0,420,1024,768,bitDC,0,0,SRCAND);
		SelectObject(bitDC,old2);
		old2=(HBITMAP *)SelectObject(bitDC,downbit);
		BitBlt(MemDC,0,420,1024,768,bitDC,0,0,SRCPAINT);
		SelectObject(bitDC,old2);
		SetTextColor(MemDC,RGB(255,255,255));
		sprintf(str,"M[%d], P[%d/90]",money[1],pop[1]);
		TextOut(MemDC,600,10,str,strlen(str));

		SetTextColor(MemDC,RGB(0,0,0));
		if(nbc==0 && nuc==0)
{
	sprintf(str,"*이 게임은 버튼이 아닌 자판 중심으로 이루어집니다.*");
	TextOut(MemDC,30,475,str,strlen(str));
	sprintf(str,"유닛이나 건물을 클릭하시면 사용법에 대하여 자세하게 설명해놓았습니다.");
	TextOut(MemDC,30,500,str,strlen(str));
}
		int th=0;
		if(nbc==1)
		{
			sprintf(str,"%s : E[%d]",makebuild[build[1][buildchoose].kind].name,build[1][buildchoose].energy);
			for(i=1 ; i<=99 ; i++)
				if(build[1][buildchoose].can[i]==1)
				{
					sprintf(str,"%s[%c]-%d",makeunit[i].name,makeunit[i].key,makeunit[i].money);
					TextOut(MemDC,100+th,470,str,strlen(str));
					th+=strlen(str)*8;
				}
			if(build[1][buildchoose].flag==1 && build[1][buildchoose].kind!=2)
			{
				sprintf(str,"유닛 생산중 : %d/%d",build[1][buildchoose].temp,makeunit[build[1][buildchoose].what].maketime);
				TextOut(MemDC,100,500,str,strlen(str));
			}
			if(build[1][buildchoose].flag==1 && build[1][buildchoose].kind==2)
			{
				sprintf(str,"건물 생산중 : %d/%d",build[1][buildchoose].temp,makebuild[build[1][buildchoose].kind].maketime);
				TextOut(MemDC,100,500,str,strlen(str));
			}
		}
		if(nuc==1)
		{
			sprintf(str,"%s - Energy[%d] Attack[%d] Deffect[%d]",makeunit[unit[1][unitchoose[1]].kind].name,unit[1][unitchoose[1]].energy,unit[1][unitchoose[1]].attack,unit[1][unitchoose[1]].deffect);			TextOut(MemDC,30,475,str,strlen(str));
			if(unit[1][unitchoose[1]].kind==1)
			{
				sprintf(str,"'F'-자원 캐기 'A'-AllCenter짓기 'S'-Soldiercreator짓기");
				TextOut(MemDC,30,500,str,strlen(str));
			} 
		}
		//총알
int a;
		for(i=1 ; i<=NTEAM ; i++)
			for(j=1 ; j<=99 ; j++)
				for(a=1 ; a<=99 && unit[i][j].energy>0 ; a++)
				if(unit[i][j].attacktime[a]>0)
				{
					double ax, ay;
					if(unit[i][j].attacktoub[a]==1){
					ax=unit[3-i][unit[i][j].attackto[a]].x-unit[i][j].x;
					ay=unit[3-i][unit[i][j].attackto[a]].y-unit[i][j].y;
					}
					else
					{
						ax=build[3-i][unit[i][j].attackto[a]].x-build[i][j].x;
						ay=build[3-i][unit[i][j].attackto[a]].y-build[i][j].y;
					
					}
					ax=ax*(double(unit[i][j].attacktime[a])/unit[i][j].timetoattack)+unit[i][j].x;
					ay=ay*(double(unit[i][j].attacktime[a])/unit[i][j].timetoattack)+unit[i][j].y;
					old2=(HBITMAP *)SelectObject(bitDC,bombbit);
					BitBlt(MemDC,ax-dfx,ay-dfy,1024,768,bitDC,0,0,SRCCOPY);
					SelectObject(bitDC,old2);
				}
BitBlt(hDC,0,0,1024,768,MemDC,0,0,SRCCOPY);
	SelectObject(MemDC,old);
	ReleaseDC(hWnd,MemDC);
	ReleaseDC(hWnd,bitDC);
	ReleaseDC(hWnd,hDC);
	DeleteObject(bit);
	DeleteObject(old);
	DeleteObject(old2);
	DeleteObject(old3);
	DeleteObject(MemDC);
	DeleteObject(bitDC);
	DeleteObject(hDC);


	//	EndPaint(hWnd,&ps);
}


void attack()
{
	int k, l, i, j, a;

	for(i=1 ; i<=NTEAM ; i++)
	{
		for(j=1 ; j<=99 ; j++)
		{
			unit[i][j].temp3++;
			for(a=1 ; a<=99 && unit[i][j].energy>0 ; a++)
				if(unit[i][j].attacktime[a]>0)
				{
					unit[i][j].attacktime[a]++;
					if(unit[i][j].attacktime[a]>=unit[i][j].timetoattack)
					{
						unit[i][j].attacktime[a]=0;
						if(unit[i][j].attacktoub[a]==1)
						{
							if(unit[3-i][unit[i][j].attackto[a]].energy<0)
							pop[3-i]++;
						unit[3-i][unit[i][j].attackto[a]].energy-=unit[i][j].attack-unit[3-i][unit[i][j].attackto[a]].deffect;
						if(unit[3-i][unit[i][j].attackto[a]].energy<0)
							pop[3-i]--;
						}
						if(unit[i][j].attacktoub[a]==2){
							if(build[3-i][unit[i][j].attackto[a]].energy<0)
								pop[3-i]++;
						build[3-i][unit[i][j].attackto[a]].energy-=unit[i][j].attack-build[3-i][unit[i][j].attackto[a]].deffect;
							if(build[3-i][unit[i][j].attackto[a]].energy<0)
								pop[3-i]--;
						}
					}
				}
		}
	}
	for(k=1 ; k<=NTEAM ; k++)
		for(l=k+1 ; l<=NTEAM ; l++)
		{
			for(i=1 ; i<=99 ; i++)
				for(j=1 ; j<=99 ; j++)
				{
					//ki 가 lj 를 공격한다. 그리고 lj도 ki 를 공격한다.
					if(unit[k][i].energy>0 && unit[l][j].energy>0)
					{
						if(unit[k][i].temp3>=unit[k][i].delay)
						if(hypot(unit[k][i].x-unit[l][j].x,unit[k][i].y-unit[l][j].y)<=unit[k][i].forcelength)
						{
							for(a=1 ; a<=99 ; a++)
								if(unit[k][i].attacktime[a]==0)
								{
									unit[k][i].attacktime[a]=1;
									unit[k][i].attackto[a]=j;
								unit[k][i].temp3=0;
								
									unit[k][i].attacktoub[a]=1;
									break;
								}
						}
						if(unit[l][j].temp3>=unit[l][j].delay)
						if(hypot(unit[k][i].x-unit[l][j].x,unit[k][i].y-unit[l][j].y)<=unit[l][j].forcelength)
						{
							for(a=1 ; a<=99 ; a++)
								if(unit[l][j].attacktime[a]==0)
								{
									unit[l][j].attacktime[a]=1;
									unit[l][j].attackto[a]=i;
									unit[l][j].temp3=0;
									unit[l][j].attacktoub[a]=1;
									break;
								}
						}
					}
				}
		}
				
	for(k=1 ; k<=NTEAM ; k++)
		for(l=1 ; l<=NTEAM ; l++)
		{
			if(k==l)
				continue;
			for(i=1 ; i<=99 ; i++)
				for(j=1 ; j<=99 ; j++)
				{
					//ki 가 lj의 건물을 공격한다.
					if(unit[k][i].energy>0 && build[l][j].energy>0)
					{
						if(unit[k][i].temp3>=unit[k][i].delay)
						if(hypot(unit[k][i].x-build[l][j].x,unit[k][i].y-build[l][j].y)<=unit[k][i].forcelength)
						{
							for(a=1 ; a<=99 ; a++)
								if(unit[k][i].attacktime[a]==0)
								{
									unit[k][i].attacktime[a]=1;
									unit[k][i].attackto[a]=j;
									unit[k][i].attacktoub[a]=2;
								unit[k][i].temp3=0;
									break;
								}
						}
					}
				}
		}
				
			
}

int newbuilds(int team, int kind, int x, int y)
{
	int i;
	int a,b;
	if(map[x/50][y/50]>=100 || map[x/50][y/50]==0)
		return 0;
	for(i=1 ; i<=199 ; i++)
		if(build[team][i].energy<=0)
		{
			build[team][i].create(2,makebuild[2],x/50*50,y/50*50);
			for(a=-2 ; a<=2 ; a++)
				for(b=-2 ; b<=2 ; b++)
				{
					if(x/50+a>=0 && y/50+b>=0)
			map[x/50+a][y/50+b]=team+100;
				}
			for(a=-5 ; a<=5 ; a++)
				for(b=-5 ; b<=5 ; b++){
					
					if(x/50+a>=0 && y/50+b>=0)
					if(map[x/50+a][y/50+b]==0)
						map[x/50+a][y/50+b]=team;
				}
			build[team][i].what=kind;
			build[team][i].flag=1;
			break;
		}
		return 1;
}
void newbuild(int team, int kind, int x, int y)
{
	int i, a, b;
	for(i=1 ; i<=199 ; i++)
		if(build[team][i].energy<=0)
		{
			if(team==0)
			{
				build[team][i].create(kind,makebuild[kind],x,y);
			}
			else
			{
				build[team][i].create(kind,makebuild[kind],x/50*50,y/50*50);
				for(a=-2 ; a<=2 ; a++)
					for(b=-2 ; b<=2 ; b++){
						
					if(x/50+a>=0 && y/50+b>=0)
			map[x/50+a][y/50+b]=team+100;
					}
			for(a=-5 ; a<=5 ; a++)
				for(b=-5 ; b<=5 ; b++)
					if(map[x/50+a][y/50+b]==0)
					{
						
					if(x/50+a>=0 && y/50+b>=0)
						map[x/50+a][y/50+b]=team;
					}
			}
			build[team][i].flag=0;
			break;
		}
}

int newunit(int team, int kind, int x, int y)
{
	if(pop[team]>=90)
		return 0;
	int i;
	for(i=1 ; i<=199 ; i++)
		if(unit[team][i].energy<=0)
		{
			unit[team][i].create(kind,makeunit[kind],x,y);
			pop[team]++;
			unit[team][i].fx=x;
			unit[team][i].fy=y;
			break;
		}
		return 1;
}

void unitfarmer()
{
	int i, a, b;
	/*제일 가까운 미네랄을 찾는다*/
	/* Farmer 설명서
	int temp;//자원 캔 정도
	int temp2;
	int flag;//자원을 캤는가/ 캐고 있는가 / 안캤는가 캤으면 무엇을 캤는가.
	int flag2;//자원 캐기를 원하는가/ 아니면 원하지 않는가.
	int delay;
	int kind;
	int energy;
	int deffect;
	int speed;
	int score;
	int attack;
	int x;
	int y;
	*/
	//flag 0 : 자원 안캠 flag 1 : 자원 캐고 있음. flag 2 : 자원2 캐고 있음 flag 3 : 자원 다 캠
	int team, who;
		for(b=1 ; b<=99 ; b++)
			build[0][b].flag=0;
	for(a=1 ; a<=NTEAM ; a++)
	{
		for(b=1 ; b<=99 ; b++)
		{
			if(unit[a][b].kind==1 && unit[a][b].flag2==1 && unit[a][b].energy>0)
			{
			team=a;
			who=b;
	if(unit[team][who].flag==0)
	{
		unit[team][who].showani=0;
		double min=999999999;
		int where=0;
			
		//자원 중 가장 가까운 자원을 찾아 돌아다님.
		for(i=1 ; i<=99 ; i++)
		{
			if(build[0][i].energy>0 && build[0][i].flag==0){
			if(hypot(unit[team][who].x-build[0][i].x,unit[team][who].y-build[0][i].y)<min)
			{
				min=hypot(unit[team][who].x-build[0][i].x,unit[team][who].y-build[0][i].y);
				where=i;
			}
			}
		}
		if(min<=50)
		{
			unit[team][who].flag=1;
		}
		else if(where!=0)
		{
			unit[team][who].fx=build[0][where].x;
			unit[team][who].fy=build[0][where].y;
		}
	}
	if(unit[team][who].flag==1)
	{
		unit[team][who].showani=1;
		double min=999999999;
		int where=0;
		
		for(i=1 ; i<=99 ; i++)
		{
			if(build[0][i].energy>0 && build[0][where].flag==0 || build[0][i].energy>0 && build[0][where].flag==who){
			if(hypot(unit[team][who].x-build[0][i].x,unit[team][who].y-build[0][i].y)<min)
			{
				min=hypot(unit[team][who].x-build[0][i].x,unit[team][who].y-build[0][i].y);
				where=i;
			}
			}
		}
		
		if(min<=50)
		{
			build[0][where].flag=who;
			unit[team][who].temp++;
			build[0][where].energy--;
			if(unit[team][who].temp>=50)
			{
				unit[team][who].flag=3;
				build[0][where].flag=0;
			}
		}
		else
		{
			unit[team][who].flag=0;
			build[0][where].flag=0;
		}
	}
	if(unit[team][who].flag==3)
	{
		unit[team][who].showani=2;
		double min=999999999;
		int where=0;
		
		for(i=1 ; i<=99 ; i++)
		{
			if(build[team][i].energy>0  && build[team][i].kind==1){
			if(hypot(unit[team][who].x-build[team][i].x,unit[team][who].y-build[team][i].y)<min)
			{
				min=hypot(unit[team][who].x-build[team][i].x,unit[team][who].y-build[team][i].y);
				where=i;
			}
			}
		}
		unit[team][who].fx=build[team][where].x;
		unit[team][who].fy=build[team][where].y;
		if(min<=100)
		{
			money[team]+=unit[team][who].temp;
			unit[team][who].temp=0;
			unit[team][who].flag=0;
		}
	}
			}
		}
	}
}

int computerway[100]=
{
	0,3,1,3,3,1,3,3,3,1,3,1,1,3,3,1,3,1,3,1,3,1,3,1,3,1,3,
};
int cw;
void computer()
{
	
	srand(GetTickCount());
	int k, i, j;
	int who;
	k=2;
	who=0;
	//일단 농부들을 자원 채취한다.
	for(i=1 ; i<=199 ; i++)
	{
		if(unit[k][i].kind==1 && unit[k][i].energy>0)
		{
			if(who>0){
			unit[k][i].flag2=1;
			}
			else
			{
				who=i;
			}
		}
	}
	if(who==0)
		return;
	for(i=1 ; i<=99 ; i++)
	{
		if(build[k][i].energy>0)
		{
			for(j=1 ; j<=99 ; j++)
				if(build[k][i].can[j]==1)
				{
					if(rand()%800==0 && money[2]<=2000 || rand()%100==0 && money[2]>2000 && money[2]<=10000 || cw==0)
					{
						if(money[2]>=makeunit[j].money && build[k][i].flag==0)
						{
							money[2]-=makeunit[j].money;
							build[k][i].what=j;
							build[k][i].temp=1;
							build[k][i].flag=1;
						}
					}
				}
		}
	}
	if(rand()%100==0){
	int rx, ry;
	while(1)
	{
		rx=rand()%(MAPX/50);
		ry=rand()%(MAPY/50);

		if(map[rx][ry]==k)
		{
			break;
		}
	}
	unit[k][who].fx=rx*50;
	unit[k][who].fy=ry*50;
	}

	//for(i=1 ; i<=3 ; i++)
	{
	//	if(i==2)
//			continue;
		if(rand()%(20+cw*10)==0)
		{
			cw++;
			if(money[2]>=makebuild[computerway[cw]].money)
			{
				if(newbuilds(k,computerway[cw],unit[k][who].x,unit[k][who].y))
					money[2]-=makebuild[computerway[cw]].money,cw++;
			}
			cw--;
		}
	}
	int bs=0;
	int px;
	int py;
	/* 공격부대의 모임 */
	for(i=1 ; i<=99 ; i++)
		if(map[unit[1][i].x/50][unit[1][i].y/50]%100==k && unit[1][i].energy>0)
		{
			bs=1;
			px=unit[1][i].x;
			py=unit[1][i].y;
		}
	/////////////////////
	if(bs)
	{
		for(i=1 ; i<=99 ; i++)
		{
			unit[k][i].fx=px,unit[k][i].fy=py;
			unit[k][i].flag2=0;
		}
	}
	bs=0;
	for(i=1 ; i<=99 ; i++)
		if(unit[k][i].kind!=1 && unit[k][i].energy>0)
		{
			bs++;
		}
	if(bs>=10 && rand()%100==0)
	{
		while(1)
		{
			px=rand()%(MAPX/50);
			py=rand()%(MAPY/50);
			if(map[px][py]%100==1)
				break;
		}
	for(i=1 ; i<=99 ; i++)
		if(unit[k][i].kind!=1)
		{
			bs++;
			unit[k][i].fx=px*50;
			unit[k][i].fy=py*50;
		}
	}
}