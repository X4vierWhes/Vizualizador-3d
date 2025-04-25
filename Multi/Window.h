/**********************************************************************************
// Window (Arquivo de Cabeçalho)
// 
// Criação:     19 Mai 2007
// Atualização:	26 Jul 2023
// Compilador:	Visual C++ 2022
//
// Descrição:   Abstrai os detalhes de configuração de uma janela 
//
**********************************************************************************/

#ifndef DXUT_WINDOW_H
#define DXUT_WINDOW_H

// ---------------------------------------------------------------------------------
// Inclusões

#define WIN32_LEAN_AND_MEAN

#include "Types.h"       // tipos personalizados da biblioteca
#include <windows.h>     // inclui funções do windows
#include <windowsx.h>    // inclui extensões do windows
#include <string>        // inclui a classe string
using std::string;       // permite usar o tipo string sem std::

// ---------------------------------------------------------------------------------
// Constantes globais e enumerações

enum WindowModes {FULLSCREEN, WINDOWED};
enum ResizeModes {UNLOCKED, LOCKED, ASPECTRATIO};

// ---------------------------------------------------------------------------------

class Window
{
private:
    HDC          windowHdc;                 // contexto do dispositivo
    RECT         windowRect;                // área cliente da janela
    HWND         windowId;                  // identificador da janela
    int          windowWidth;               // largura da janela
    int          windowHeight;              // altura da janela
    HICON        windowIcon;                // ícone da janela
    HCURSOR      windowCursor;              // cursor da janela
    COLORREF     windowColor;               // cor de fundo da janela
    string       windowTitle;               // nome da barra de título
    DWORD        windowStyle;               // estilo da janela 
    int          windowMode;                // modo tela cheia, em janela ou sem borda
    int          windowPosX;                // posição inicial da janela no eixo x
    int          windowPosY;                // posição inicial da janela no eixo y
    int          windowCenterX;             // centro da janela no eixo x
    int          windowCenterY;             // centro da janela no eixo y
    float        windowAspectRatio;         // aspect ratio da janela
    int          fullWidth;                 // largura da janela com bordas
    int          fullHeight;                // altura da janela com barras e bordas
    float        fullAspectRatio;           // aspect ratio da janela com barras e bordas
    int          resizeMode;                // modo de redimensionamento da janela
    int          styleWidth;                // largura devido a bordas e barras da janela
    int          styleHeight;               // altura devido a bordas e barras da janela
    int          windowMinWidth;            // largura mínima da janela
    int          windowMinHeight;           // altura mínima da janela
 
    static void (*inFocus)();               // executar quando a janela ganhar de volta o foco
    static void (*lostFocus)();             // executar quando a janela perder o foco
    static int   screenWidth;               // largura da tela
    static int   screenHeight;              // altura da tela
    
public:
    Window();                               // construtor
    ~Window();                              // destrutor

    HWND Id();                              // retorna identificador da janela
    int Width();                            // retorna largura atual da janela
    int Height();                           // retorna altura atual da janela
    int Mode() const;                       // retorna modo atual da janela
    int CenterX() const;                    // retorna centro da janela no eixo x
    int CenterY() const;                    // retorna centro da janela no eixo y
    string Title() const;                   // retorna título da janela
    COLORREF Color();                       // retorna cor de fundo da janela
    
    int ScreenWidth() const;                // retorna largura da tela
    int ScreenHeight() const;               // retorna altura da tela
    int ResizeMode() const;                 // retorna modo de redimensionamento
    int FullWidth() const;                  // retorna largura da janela com bordas
    int FullHeight() const;                 // retorna altura da janela com barras e bordas
    int MinWidth() const;                   // retorna largura mínima da janela
    int MinHeight() const;                  // retorna altura mínima da janela
    float AspectRatio() const;              // retorna aspect ratio da área interna da janela
    float FullAspectRatio() const;          // retorna aspect ratio da janela com barras e bordas

    void Icon(const uint icon);             // define ícone da janela
    void Cursor(const uint cursor);         // define cursor da janela
    void Title(const string title);         // define título da janela 
    void Size(int width, int height);       // define tamanho da janela
    void Resize(int width, int height);     // ajusta tamanho da área interna da janela
    void FullResize(int width, int height); // ajusta tamanho externo da janela
    void Mode(int mode);                    // define modo da janela
    void ResizeMode(int mode);              // define modo de redimensionamento
    void Color(int r, int g, int b);        // define cor de fundo da janela
    void HideCursor(bool hide);             // habilita ou desabilita a exbição do cursor

    void Close();                           // fecha janela
    void Clear();                           // limpa área cliente
    bool Create();                          // cria janela com a configuração estabelecida

    void InFocus(void(*func)());            // altera função executada ao ganhar foco
    void LostFocus(void(*func)());          // altera função executada na perda do foco

    // trata eventos do Windows
    static LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

// ---------------------------------------------------------------------------------

// Funções Membro Inline

// retorna o identificador da janela do jogo
inline HWND Window::Id()
{ return windowId; }

// retorna a largura atual da janela
inline int Window::Width() 
{ return windowWidth;  }

// retorna a altura atual da janela
inline int Window::Height() 
{ return windowHeight; }

// retorna o modo atual da janela (FULLSCREEN/WINDOWED)
inline int Window::Mode() const
{ return windowMode; }

// retorna o centro da janela no eixo horizontal
inline int Window::CenterX() const
{ return windowCenterX; }

// retorna o centro da janela no eixo vertical
inline int Window::CenterY() const
{ return windowCenterY; }

// retorna título da janela
inline string Window::Title() const
{ return windowTitle; }

// retorna a cor de fundo da janela
inline COLORREF Window::Color()
{ return windowColor; }

// retorna largura da tela
inline int Window::ScreenWidth() const
{ return screenWidth; }

// retorna altura da tela
inline int Window::ScreenHeight() const
{ return screenHeight; }

// retorna modo de redimensionamento
inline int Window::ResizeMode() const
{ return resizeMode; }

// retorna largura da janela com bordas
inline int Window::FullWidth() const
{ return fullWidth; }

// retorna altura da janela com barras e bordas
inline int Window::FullHeight() const
{ return fullHeight; }

// retorna largura mínima da janela
inline int Window::MinWidth() const
{ return windowMinWidth; }

// retorna altura mínima da janela
inline int Window::MinHeight() const
{ return windowMinHeight; }

// retorna aspect ratio da área interna da janela
inline float Window::AspectRatio() const
{ return windowAspectRatio; }

// retorna aspect ratio da janela com barras e bordas
inline float Window::FullAspectRatio() const
{ return fullAspectRatio; }

// ----------------------------------------------------------

// define o ícone da janela
inline void Window::Icon(const uint icon)    
{ windowIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(icon)); }

// define o cursor da janela
inline void Window::Cursor(const uint cursor)
{ windowCursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(cursor)); }

// define o título da janela 
inline void Window::Title(const string title)
{ windowTitle = title; }

// define a cor de fundo da janela
inline void Window::Color(int r, int g, int b)    
{ windowColor = RGB(r,g,b); }

// habilita ou desabilita a exbição do cursor
inline void Window::HideCursor(bool hide)
{ ShowCursor(!hide); }

// ----------------------------------------------------------

// fecha a janela e sai do jogo 
inline void Window::Close()
{ PostMessage(windowId, WM_DESTROY, 0, 0); }

// limpa a área cliente
inline void Window::Clear()
{ FillRect(windowHdc, &windowRect, CreateSolidBrush(Color())); }

// ----------------------------------------------------------

// altera função executada no ganho de foco
inline void Window::InFocus(void(*func)())                
{ inFocus = func; }

// altera função executada na perda de foco
inline void Window::LostFocus(void(*func)())
{ lostFocus = func; }

// ---------------------------------------------------------------------------------

#endif