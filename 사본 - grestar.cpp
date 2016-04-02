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

//////////////////////////////////
void unitfarmer(int team, int who);
//////////////////////////////////
MAKEUNIT makeunit[100];
MAKEBUILD makebuild[100];
UNIT unit[3][200];
BUILD build[3][200];
int choose[100];
int ax, ay, bx, by;

/////////////////////////////////////////////////////

void draw(HWND hWnd);

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPreInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow){
	downmaskbit=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_DOWNMASK));
	downbit=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_DOWN));
	makeunit[1].bit=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FARMER));
	makeunit[1].maskbit=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_FARMERMASK));
	makebuild[1].bit[1]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_ALLCENTER));
	makebuild[1].bit[2]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_ALLCENTER2));
	makebuild[1].maskbit=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_ALLCENTERMASK));
	makebuild[0].bit[1]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_MONEY));
	
	makeunit[1].create("farmer",50,5,0,3);
	makebuild[1].create("allcenter",1000,0);
	makebuild[1].nani=2;
	makebuild[0].create("source",500,0);

	newbuild(1,1,100,100);
	newunit(1,1,100,250);
	newunit(1,1,150,250);
	newunit(1,1,200,250);
	newunit(1,1,250,250);
	int i;
	for(i=1 ; i<=20 ; i++)
	newbuild(0,0,500,i*10+100);
	MSG msg;
	HWND hWnd;
	WNDCLASS wnd;

	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wnd.hCursor = LoadCursor(hInstance,MAKEINTRESOURCE(IDC_CURSOR1));
	wnd.hIcon = 0;//LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
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
	switch(msg)
	{
	case WM_PAINT:
		draw(hWnd);
		SetTimer(hWnd,1,50,0); 
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		keys[wParam]=1;
		break;
	case WM_KEYUP:
		keys[wParam]=0;
		break;
	case WM_TIMER:
		if(keys[VK_DOWN])
			dfy+=30;
		if(keys[VK_UP])
			dfy-=30;
		if(keys[VK_LEFT])
			dfx-=30;
		if(keys[VK_RIGHT])
			dfx+=30;
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



	/////////////
		for(i=1 ; i<=1 ; i++)
			for(j=1 ; j<=199 ; j++)
			{
				if(unit[i][j].energy>0)
				{
					old2=(HBITMAP *)SelectObject(bitDC,makeunit[unit[i][j].kind].maskbit);
					BitBlt(MemDC,unit[i][j].x-dfx,unit[i][j].y-dfy,1024,768,bitDC,0,0,SRCAND);
					SelectObject(bitDC,old2);
					old2=(HBITMAP *)SelectObject(bitDC,makeunit[unit[i][j].kind].bit);
					BitBlt(MemDC,unit[i][j].x-dfx,unit[i][j].y-dfy,1024,768,bitDC,0,0,SRCPAINT);
					SelectObject(bitDC,old2);
		
				}
			}
		for(i=0 ; i<=1 ; i++)
			for(j=1 ; j<=99 ; j++)
			{
				if(i==0 && build[i][j].energy>0)
				{
					old2=(HBITMAP *)SelectObject(bitDC,makebuild[build[i][j].kind].bit[1]);
					BitBlt(MemDC,build[i][j].x-dfx,build[i][j].y-dfy,1024,768,bitDC,0,0,SRCCOPY);
					SelectObject(bitDC,old2);					
				}
				else if(build[i][j].energy>0)
				{
					old2=(HBITMAP *)SelectObject(bitDC,makebuild[build[i][j].kind].maskbit);
					BitBlt(MemDC,build[i][j].x-dfx,build[i][j].y-dfy,1024,768,bitDC,0,0,SRCAND);
					SelectObject(bitDC,old2);
					old2=(HBITMAP *)SelectObject(bitDC,makebuild[build[i][j].kind].bit[(build[i][j].now/20)%makebuild[build[i][j].kind].nani+1]);
					build[i][j].now++;
					BitBlt(MemDC,build[i][j].x-dfx,build[i][j].y-dfy,1024,768,bitDC,0,0,SRCPAINT);
					SelectObject(bitDC,old2);
				}
			}

	//배경  출력
		old2=(HBITMAP *)SelectObject(bitDC,downmaskbit);
		BitBlt(MemDC,0,420,1024,768,bitDC,0,0,SRCAND);
		SelectObject(bitDC,old2);
		old2=(HBITMAP *)SelectObject(bitDC,downbit);
		BitBlt(MemDC,0,420,1024,768,bitDC,0,0,SRCPAINT);
		SelectObject(bitDC,old2);

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
			break;
		}
}

void unitfarmer(int team, int who)
{
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
	if(unit[team][who].flag==0)
	{
		double min=999999999;
		int where=0;
			
		//자원 중 가장 가까운 자원을 찾아 돌아다님.
		for(i=1 ; i<=99 ; i++)
		{
			if(sqrt(unit[team][who].x-build[0][i].x,unit[team][who].y-build[0][i].y)<min)
			{
				min=sqrt(unit[team][who].x-build[0][i].x,unit[team][who].y-build[0][i].y);
			}
		}
	}
}