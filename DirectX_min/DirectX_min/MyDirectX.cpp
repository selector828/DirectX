#include "MyDirectX.h"
//[�O���[�o���ϐ�]__________________________________________________________
LPDIRECT3D9       pD3d;
LPDIRECT3DDEVICE9 pDevice;
MYWINDOW          MyWindow;
HINSTANCE         hInstance;
//[WinMain�֐�]_____________________________________________________________
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	hInstance = hInst;
	MyWindow.Init();
	// �_�C���N�g�RD�̏������֐����Ă�
	if (FAILED(InitD3d(MyWindow.hWnd)))
	{
		return 0;
	}
	//Init();��x�̂ݎ��s
	MSG msg;
	// ���b�Z�[�W���[�v
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//Update();���b60FPS
		}
	}
	return (INT)msg.wParam;
}
//[�E�B���h�E�v���V�[�W���[]________________________________________________
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch ((CHAR)wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
//[Direct3D�̏�����]________________________________________________________
HRESULT InitD3d(HWND hWnd)
{
	// �uDirect3D�v�I�u�W�F�N�g�̍쐬
	if (NULL == (pD3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0, "Direct3D�̍쐬�Ɏ��s���܂���", "", MB_OK);
		return E_FAIL;
	}
	// �uDIRECT3D�f�o�C�X�v�I�u�W�F�N�g�̍쐬
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;

	if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &pDevice)))
	{
		if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &pDevice)))
		{
			MessageBox(0, "HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�", NULL, MB_OK);
			if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp, &pDevice)))
			{
				if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp, &pDevice)))
				{
					MessageBox(0, "DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���", NULL, MB_OK);
					return E_FAIL;
				}
			}
		}
	}
	return S_OK;
}
//[�E�B���h�E����]__________________________________________________________
void MYWINDOW::Init(void) {

	this->wndClass.cbSize = sizeof(this->wndClass);
	this->wndClass.style = CS_HREDRAW | CS_VREDRAW;
	this->wndClass.lpfnWndProc = WndProc;
	this->wndClass.cbClsExtra = 0;
	this->wndClass.cbWndExtra = 0;
	this->wndClass.hInstance = hInstance;
	this->wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	this->wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	this->wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	this->wndClass.lpszMenuName = NULL;
	this->wndClass.lpszClassName = WINDOW_TITLE;
	this->wndClass.hIconSm = LoadIcon(NULL, IDI_ASTERISK);

	RegisterClassEx(&this->wndClass);

	this->hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	ShowWindow(this->hWnd, SW_SHOW);
	UpdateWindow(this->hWnd);
}
//[�|�C���^���]____________________________________________________________
void Free(void) {
	SAFE_RELEASE(pDevice);
	SAFE_RELEASE(pD3d);
}