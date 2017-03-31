#pragma once //�d���C���N���[�h�h�~
//[�C���N���[�h�t�@�C��]______________________________________________
#include <windows.h>
#include <d3dx9.h>
//[���C�u�����[�t�@�C��]______________________________________________
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )
//[�萔�E�}�N��]______________________________________________________
#define WINDOW_TITLE  "�E�B���h�E�^�C�g��"
#define WINDOW_WIDTH  ( 800 )
#define WINDOW_HEIGHT ( 600 )
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
//[�\����]____________________________________________________________
typedef struct {
	LPSTR      Name;
	HWND       hWnd;
	WNDCLASSEX wndClass;
	UINT       uWidth;
	UINT       uHeight;

	void Init(void);
} MYWINDOW, *PMYWINDOW;
//[�֐��v���g�^�C�v]__________________________________________________
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT InitD3d(HWND);
void Free(void);
//[END]_______________________________________________________________