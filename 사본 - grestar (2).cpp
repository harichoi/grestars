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

#define max2(a,b) ((a>b)?a:b)
#define min2(a,b) ((a>b)?b:a)
#define ME 1

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND MainHwnd, DrawHwnd, ToolHwnd, ToolupHwnd, MathHwnd,MultiMathHwnd;
HDC MemDC;
HBITMAP copyright, moneybit, downbit, downmaskbit, allcenterbit, allcentermaskbit, farmerbit, farmermaskbit;
int dfx, dfy;
int keys[256];
void newbuild(int team, int kind, int x, int y);
void newunit(int team, int kind, int x, int y);
void attack();
//////////////////////////////////
void unitfarmer();
void newbuilds(int team, int kind, int x, int y);
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

int ndot;
int showdotx[1000],showdoty[1000];

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
	makebuild[1].bit[1]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_ALLCENTER));
	makebuild[1].bit[2]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_ALLCENTER2));
	makebuild[1].maskbit=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_ALLCENTERMASK));
	makebuild[0].bit[1]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_MONEY));
	makebuild[2].bit[1]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_MAKING));
	makebuild[2].bit[2]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_MAKING2));
	makebuild[3].bit[1]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_SOLDIERCREATOR));
	makebuild[3].maskbit=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_SOLDIERCREATORMASK));
	
	makeunit[1].create("farmer",50,5,0,5,1000,300,1,10,75,15);
	makeunit[2].create("basic",50,2,1,7,500,400,2,5,100,10);
	makebuild[1].create("allcenter",1000,0,5000,1500);
	makebuild[2].create("creating..",500,0,0,0);
	makebuild[3].create("soidlercreator",500,0,1500,1000);
	makebuild[1].nani=makebuild[2].nani=2,makebuild[3].nani=1;
	makebuild[0].create("source",3000,0,0,0);
	
//	makebuild[

	newbuild(1,1,100,100);
	newunit(1,1,100,175);
	newunit(1,1,150,175);
	newunit(1,1,200,175);
	newunit(1,1,250,175);
	newbuild(2,1,500,100);
	newunit(2,1,500,175);
	newunit(2,1,550,175);
	newunit(2,1,600,175);
	newunit(2,1,650,175);

	int i;
	srand(GetTickCount());
	for(i=-5 ; i<=10 ; i++)
	newbuild(0,0,300+rand()%100,i*20+100+rand()%100);
	for(i=-5 ; i<=10 ; i++)
	newbuild(0,0,i*20+100+rand()%100,300+rand()%100);
	

	money[1]=1000;

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
			}
			}
		}
		nuc=1;
		unitchoose[1]=where;
		if(where==0)
			nuc=0;
		else
		{
			nbc=0;
		}

		break;
	case WM_CREATE:
		break;
	case WM_PAINT:
		draw(hWnd);
		SetTimer(hWnd,1,50,0); 
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
				newbuilds(1,1,unit[1][unitchoose[1]].x,unit[1][unitchoose[1]].y);
				money[1]-=makebuild[1].money;
				}
			}
		}
		if(wParam=='S')
		{
			if(nuc==1 && unit[1][unitchoose[1]].kind==1 && unit[1][unitchoose[1]].energy>0)
			{
				if(money[1]>=makebuild[3].money){
				newbuilds(1,3,unit[1][unitchoose[1]].x,unit[1][unitchoose[1]].y);
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
						newunit(1,build[i][j].what,build[i][j].x+rand()%150-75,build[i][j].y+75);
					}
				}
				if(build[i][j].energy>0 && build[i][j].kind==2)
				{
					build[i][j].temp++;
					if(build[i][j].temp>=makebuild[build[i][j].what].maketime)
					{
					//	build[i][j].flag=0;
						build[i][j].energy=0;
						newbuild(1,build[i][j].what,build[i][j].x,build[i][j].y);
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
	for(i=0 ; i<=100 ; i++){
		for(j=0 ; j<=100 ; j++){
			brush=CreateSolidBrush(RGB(i*j,(i+1)/(j+1)*500,(i+j)*10));
			old3=(HBRUSH *)SelectObject(MemDC,brush);
			Rectangle(MemDC,i*20-dfx,20*j-dfy,20*i+20-dfx,20*j+20-dfy);
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
		
				}
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
					}
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
		sprintf(str,"M[%d]",money[1]);
		TextOut(MemDC,700,10,str,strlen(str));

		SetTextColor(MemDC,RGB(0,0,0));
		if(nbc==0 && nuc==0)
{
	sprintf(str,"*이 게임은 버튼이 아닌 자판 중심으로 이루어집니다.*");
	TextOut(MemDC,30,475,str,strlen(str));
	sprintf(str,"유닛이나 건물을 클릭하시면 사용법에 대하여 자세하게 설명해놓았습니다.");
	TextOut(MemDC,30,500,str,strlen(str));
}
		if(nbc==1)
		{
			if(build[1][buildchoose].flag==1 && build[1][buildchoose].kind!=2)
			{
				sprintf(str,"유닛 생산중 : %d/%d",build[1][buildchoose].temp,makeunit[build[1][buildchoose].what].maketime);
				TextOut(MemDC,100,500,str,strlen(str));
			}
			if(build[1][buildchoose].flag==1 && build[1][buildchoose].kind==2)
			{
				sprintf(str,"건물 생산중 : %d/%d",build[1][buildchoose].temp,1000);
				TextOut(MemDC,100,500,str,strlen(str));
			}
		}
		if(nuc==1)
		{
			sprintf(str,"%s - Energy[%d] Attack[%d] Deffect[%d]",makeunit[unit[1][unitchoose[1]].kind].name,unit[1][unitchoose[1]].energy,unit[1][unitchoose[1]].attack,unit[1][unitchoose[1]].deffect);
			TextOut(MemDC,30,475,str,strlen(str));
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
					ax=unit[3-i][unit[i][j].attackto[a]].x-unit[i][j].x;
					ay=unit[3-i][unit[i][j].attackto[a]].y-unit[i][j].y;
					ax=ax*(double(unit[i][j].attacktime[a])/unit[i][j].timetoattack)+unit[i][j].x;
					ay=ay*(double(unit[i][j].attacktime[a])/unit[i][j].timetoattack)+unit[i][j].y;
					SetPixel(MemDC,ax,ay,RGB(rand()%255,rand()%255,rand()%255));SetPixel(MemDC,ax+1,ay,RGB(rand()%255,rand()%255,rand()%255));
					SetPixel(MemDC,ax,ay+1,RGB(rand()%255,rand()%255,rand()%255));SetPixel(MemDC,ax+1,ay+1,RGB(rand()%255,rand()%255,rand()%255));
				//	MoveToEx(MemDC,unit[i][j].x,unit[i][j].y,0);
				//	LineTo(MemDC,ax,ay);
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
						unit[3-i][unit[i][j].attackto[a]].energy-=unit[i][j].attack-unit[3-i][unit[i][j].attackto[a]].deffect;
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
									break;
								}
						}
					}
				}
		}
				
			
}

void newbuilds(int team, int kind, int x, int y)
{
	int i;
	for(i=1 ; i<=199 ; i++)
		if(build[team][i].energy<=0)
		{
			build[team][i].create(2,makebuild[2],x,y);
			build[team][i].what=kind;
			build[team][i].flag=1;
			break;
		}
}
void newbuild(int team, int kind, int x, int y)
{
	int i;
	for(i=1 ; i<=199 ; i++)
		if(build[team][i].energy<=0)
		{
			build[team][i].create(kind,makebuild[kind],x,y);
			break;
		}
}

void newunit(int team, int kind, int x, int y)
{
	int i;
	for(i=1 ; i<=199 ; i++)
		if(unit[team][i].energy<=0)
		{
			unit[team][i].create(kind,makeunit[kind],x,y);		
			unit[team][i].fx=x;
			unit[team][i].fy=y;
			break;
		}
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