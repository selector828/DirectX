#pragma once //重複インクルード防止
//[インクルードファイル]______________________________________________
#include <windows.h>
#include <d3dx9.h>
//[ライブラリーファイル]______________________________________________
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )
//[定数・マクロ]______________________________________________________
#define WINDOW_TITLE  "ウィンドウタイトル"
#define WINDOW_WIDTH  ( 800 )
#define WINDOW_HEIGHT ( 600 )
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
//[構造体]____________________________________________________________
typedef struct {
	LPSTR      Name;
	HWND       hWnd;
	WNDCLASSEX wndClass;
	UINT       uWidth;
	UINT       uHeight;

	void Init(void);
} MYWINDOW, *PMYWINDOW;
//[関数プロトタイプ]__________________________________________________
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT InitD3d(HWND);
void Free(void);
//[END]_______________________________________________________________