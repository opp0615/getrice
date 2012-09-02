#pragma once
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include "stdlib.h"
#include "resource.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass="Move";

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		  CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		  NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);
	
	while(GetMessage(&Message,0,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc,MemDC;
	PAINTSTRUCT ps;
	
	RECT rt={100,100,200,200};
	static int theta=45;
	HPEN SpinPen,OldPen;
	static double v=0, sv=0, rad=0, Sx, nSx=0, nSy=400 , range=0;
	static char str[3];
	static BOOL key=false, spacedown=false, space2down=false , firstplayer=true;

	itoa(theta,str,10);
	

	HBITMAP MyBitmap, OldBitmap;
	HBITMAP MyBitmapA, OldBitmapA;
	HBITMAP MyBitmapB, OldBitmapB;
	HBITMAP MyBitmapC, OldBitmapC;
	HBITMAP MyBitmapD, OldBitmapD;
			
	switch(iMessage) {
		
		
		
		case WM_KEYDOWN:	
			//버튼조정
			if(spacedown==false)
			{
			switch(wParam){
					case VK_UP:
						theta=theta+5;
						break;
					case VK_DOWN:
						theta=theta-5;
						break;

					case VK_SPACE:
						
							SetTimer(hWnd,1,1,NULL);
							spacedown=true;	
			
						break;
				}
					
			}	

			
			else if(spacedown==true)
			{
				switch(wParam){

				case VK_SPACE:
					space2down=true;
				

				}
			}
		
			
			InvalidateRect(hWnd,NULL,TRUE);

			return 0;
			
		
			
	case WM_TIMER:
		
		InvalidateRect(hWnd,NULL,TRUE);
		return 0;

	case WM_PAINT:
	
		if( spacedown ==false)
		{	
			//각도조절

			rad=M_PI*(double)theta/180;

			hdc=BeginPaint(hWnd,&ps);
			SpinPen=CreatePen(PS_SOLID,3,RGB(255,0,0));
			OldPen=(HPEN)SelectObject(hdc,SpinPen);
			MoveToEx(hdc,0+50,400+50,NULL);
			LineTo(hdc,200*cos(rad)+50,400+50-200*sin(rad));
			SelectObject(hdc,OldPen);
			DeleteObject(SpinPen);
			
			MemDC=CreateCompatibleDC(hdc);
			MyBitmap=LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
			OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);
			BitBlt(hdc,0,400,100,100,MemDC,0,0,SRCCOPY);

			BitBlt(hdc,800,400,100,100,MemDC,0,0,SRCCOPY);

			SelectObject(MemDC,OldBitmap);
			DeleteObject(MyBitmap);
			DeleteDC(MemDC);
			EndPaint(hWnd, &ps);
			
		}

		else if(spacedown==true)
		{
			//속도조절

			if(space2down==false)
			{
				if(sv<13)
				{
					v=v+0.1;
				
					hdc = BeginPaint(hWnd, &ps);

					SpinPen=CreatePen(PS_SOLID,3,RGB(255,0,0));
					OldPen=(HPEN)SelectObject(hdc,SpinPen);
					MoveToEx(hdc,0+50,400+50,NULL);
					LineTo(hdc,200*cos(rad)+50,400+50-200*sin(rad));
					SelectObject(hdc,OldPen);
					DeleteObject(SpinPen);


				
					MemDC=CreateCompatibleDC(hdc);
					MyBitmapA=LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
					OldBitmapA=(HBITMAP)SelectObject(MemDC, MyBitmapA);
					BitBlt(hdc,400,450,(int)v*25,100,MemDC,0,0,SRCCOPY);
				
				
					MemDC=CreateCompatibleDC(hdc);
					MyBitmap=LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
					OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);
					BitBlt(hdc,0,400,100,100,MemDC,0,0,SRCCOPY);

					BitBlt(hdc,800,400,100,100,MemDC,0,0,SRCCOPY);

					SelectObject(MemDC,OldBitmapA);
					DeleteObject(MyBitmapA);
				
					SelectObject(MemDC,OldBitmap);
					DeleteObject(MyBitmap);
					DeleteDC(MemDC);
					EndPaint(hWnd, &ps);

					if(v>=13)
						sv=v;
				}

				else if(sv>13)
				{

					v=v-0.1;

					
					hdc = BeginPaint(hWnd, &ps);

					SpinPen=CreatePen(PS_SOLID,3,RGB(255,0,0));
					OldPen=(HPEN)SelectObject(hdc,SpinPen);
					MoveToEx(hdc,0+50,400+50,NULL);
					LineTo(hdc,200*cos(rad)+50,400+50-200*sin(rad));
					SelectObject(hdc,OldPen);
					DeleteObject(SpinPen);


				
					MemDC=CreateCompatibleDC(hdc);
					MyBitmapA=LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
					OldBitmapA=(HBITMAP)SelectObject(MemDC, MyBitmapA);
					BitBlt(hdc,400,450,(int)v*25,100,MemDC,0,0,SRCCOPY);
				
				
					MemDC=CreateCompatibleDC(hdc);
					MyBitmap=LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
					OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);
					BitBlt(hdc,0,400,100,100,MemDC,0,0,SRCCOPY);

					BitBlt(hdc,800,400,100,100,MemDC,0,0,SRCCOPY);

					SelectObject(MemDC,OldBitmapA);
					DeleteObject(MyBitmapA);
				
					SelectObject(MemDC,OldBitmap);
					DeleteObject(MyBitmap);
					DeleteDC(MemDC);
					EndPaint(hWnd, &ps);

					if(v<=0)
						sv=v;
				}
			}
			else if(space2down==true)
				{
					//발사 player1
					
					rad=M_PI*(double)theta/180;

					hdc = BeginPaint(hWnd, &ps);
					MemDC=CreateCompatibleDC(hdc);
					MyBitmap=LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
					OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);
		
					if(nSy<=400)
					{
				
						Sx=v*cos(rad);
						nSx=nSx+Sx;
						nSy=399+-nSx*tan(rad)+(0.098*nSx*nSx)/(2*v*v*cos(rad)*cos(rad));

					}

		
					if((nSy<0) | (nSy>400) | (nSx>700 & nSy>300) | (nSx>800) )
					{
						nSx=0;
						nSy=399;
						v=0;
						spacedown=false;
						key=false;
						space2down=false;
						theta=45;
					}
			


					BitBlt(hdc, (int)nSx,(int)nSy,100,100,MemDC,0,0,SRCCOPY);

					BitBlt(hdc,800,400,100,100,MemDC,0,0,SRCCOPY);

					SelectObject(MemDC,OldBitmap);
					DeleteObject(MyBitmap);
					DeleteDC(MemDC);
					EndPaint(hWnd, &ps);

				}
		}
		
		

		return 0;

		
	case WM_DESTROY:
		KillTimer(hWnd,1);
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}
