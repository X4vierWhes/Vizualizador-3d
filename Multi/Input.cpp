/**********************************************************************************
// Input (Código Fonte)
//
// Criação:		06 Jan 2020
// Atualização:	08 Jul 2023
// Compilador:	Visual C++ 2022
//
// Descrição:	A classe Input concentra todas as tarefas relacionadas
//              aos dispositivos de entrada do tipo teclado e mouse.
//
**********************************************************************************/

#include "Input.h"

// -------------------------------------------------------------------------------
// inicialização de membros estáticos da classe

bool Input::keys[256] = { 0 };							// estado do teclado/mouse
bool Input::ctrl[256] = { 0 };							// controle de liberação das teclas

int	  Input::mouseX = 0;								// posição do mouse no eixo x
int	  Input::mouseY = 0;								// posição do mouse no eixo y
short Input::mouseWheel = 0;							// valor da roda do mouse
									
// -------------------------------------------------------------------------------

Input::Input()
{
	// supõe que a janela já foi criada
	// altera a window procedure da janela ativa para InputProc
	SetWindowLongPtr(GetActiveWindow(), GWLP_WNDPROC, (LONG_PTR)Input::InputProc);
}

// -------------------------------------------------------------------------------

Input::~Input()
{
	// volta a usar a Window Procedure da classe Window
	//SetWindowLongPtr(GetActiveWindow(), GWLP_WNDPROC, (LONG_PTR)Window::WinProc);
}

// -------------------------------------------------------------------------------

bool Input::KeyPress(int vkcode)
{
	if (ctrl[vkcode])
	{
		if (KeyDown(vkcode))
		{
			ctrl[vkcode] = false;
			return true;
		}
	}
	else if (KeyUp(vkcode))
	{
		ctrl[vkcode] = true;
	}

	return false;
}

// -------------------------------------------------------------------------------

short Input::MouseWheel()
{
	short val = mouseWheel;
	mouseWheel = 0;
	return val;
}

// -------------------------------------------------------------------------------

LRESULT CALLBACK Input::InputProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	// tecla pressionada
	case WM_KEYDOWN:
		keys[wParam] = true;
		return 0;

	// tecla liberada
	case WM_KEYUP:
		keys[wParam] = false;
		return 0;
		
	// movimento do mouse
	case WM_MOUSEMOVE:			
		mouseX = GET_X_LPARAM(lParam);
		mouseY = GET_Y_LPARAM(lParam);
		return 0;

	// movimento da roda do mouse
	case WM_MOUSEWHEEL:
		mouseWheel = GET_WHEEL_DELTA_WPARAM(wParam);
		return 0;

	// botão esquerdo do mouse pressionado
	case WM_LBUTTONDOWN:		
	case WM_LBUTTONDBLCLK:
		keys[VK_LBUTTON] = true;
		return 0;

	// botão do meio do mouse pressionado
	case WM_MBUTTONDOWN:		
	case WM_MBUTTONDBLCLK:
		keys[VK_MBUTTON] = true;
		return 0;

	// botão direito do mouse pressionado
	case WM_RBUTTONDOWN:		
	case WM_RBUTTONDBLCLK:
		keys[VK_RBUTTON] = true;
		return 0;

	// botão esquerdo do mouse liberado
	case WM_LBUTTONUP:			
		keys[VK_LBUTTON] = false;
		return 0;

	// botão do meio do mouse liberado
	case WM_MBUTTONUP:			
		keys[VK_MBUTTON] = false;
		return 0;

	// botão direito do mouse liberado
	case WM_RBUTTONUP:			
		keys[VK_RBUTTON] = false;
		return 0;
	}

	return CallWindowProc(Window::WinProc, hWnd, msg, wParam, lParam);
}

// -------------------------------------------------------------------------------
