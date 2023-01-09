#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <string>
#include <iostream>
#include "resource.h"

char columnaWM[1024] = "";
char filaWM[1024] = "";
char estadoWM[1024] = "";
char textoCajaWM[1024] = "";
Matriz M;
std::string estadoVr = "q0", senteciaVr = "";
int indiceVr = 0;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */

    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Machine Turing By Marshall Lee"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           800,                 /* The programs width */
           600,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );


    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    M.Insertar ("0", "q0", "q1,X,D");
    M.Insertar ("0", "q1", "q1,0,D");
    M.Insertar ("0", "q2", "q2,0,I");
    M.Insertar ("1", "q1", "q2,Y,I");
    M.Insertar ("X", "q2", "q0,X,D");
    M.Insertar ("Y", "q0", "q3,Y,D");
    M.Insertar ("Y", "q1", "q1,Y,D");
    M.Insertar ("Y", "q2", "q2,Y,I");
    M.Insertar ("Y", "q3", "q3,Y,D");
    M.Insertar ("B", "q3", "q4,B,S");

    /*M.Insertar ("0", "q0", "q0,X,D");
    M.Insertar ("1", "q0", "q0,Y,D");
    M.Insertar ("B", "q0", "q0,B,S");*/

    /*M.Insertar ("0", "q0", "q1,X,D");
    M.Insertar ("0", "q1", "q2,X,D");
    M.Insertar ("0", "q4", "q4,0,I");
    M.Insertar ("1", "q2", "q3,Y,D");
    M.Insertar ("1", "q3", "q4,Y,D");
    M.Insertar ("Y", "q4", "q0,Y,D");
    M.Insertar ("B", "q4", "q5,B,S");*/



    PAINTSTRUCT ps;
    HINSTANCE hThisInstance;
    HDC hdc;
    HWND filedit;
    char arr[1];
       //Matriz M

    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:{

            cajaLeer = CreateWindowEx(0, _T("EDIT"), _T(""), ES_LEFT|WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP|ES_MULTILINE, 150, 20, 200, 30,
                                       hwnd, (HMENU)CAJALEER,hThisInstance, NULL);

            //Para mostrar el texto [Col:]
            columnaMt = CreateWindowEx(0, _T("STATIC"), _T("Col: "), SS_CENTER|SS_NOTIFY|WS_CHILD|WS_VISIBLE|WS_TABSTOP, 10, 105, 25, 20,
                                     hwnd, 0, 0, 0);
            //Caja editable de columna
            hEdtNum1 = CreateWindowEx(0, _T("EDIT"), _T(""), ES_LEFT|WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP|ES_MULTILINE, 40, 100, 100, 30,
                                       hwnd, (HMENU)BEDIT1,hThisInstance, NULL);
            //Para mostrar el texto [Col:]
            filaMt = CreateWindowEx(0, _T("STATIC"), _T("Est: "), SS_CENTER|SS_NOTIFY|WS_CHILD|WS_VISIBLE|WS_TABSTOP, 150, 105, 25, 20,
                                     hwnd, 0, 0, 0);
            //Caja editable Fila
            hEdtNum2 = CreateWindowEx(0, _T("EDIT"), _T(""), ES_LEFT|WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP|ES_MULTILINE, 180, 100, 100, 30,
                                       hwnd, (HMENU)BEDIT2,hThisInstance, NULL);
            //Para mostrar el texto [Est:]
            estadoMt = CreateWindowEx(0, _T("STATIC"), _T("Est: "), SS_CENTER|SS_NOTIFY|WS_CHILD|WS_VISIBLE|WS_TABSTOP, 20, 25, 25, 20,
                                     hwnd, 0, 0, 0);
            //Caja editable Estado
            hEdtNum3 = CreateWindowEx(0, _T("EDIT"), _T(""), ES_LEFT|WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP|ES_MULTILINE, 325, 100, 150, 30,
                                       hwnd, (HMENU)BEDIT3,hThisInstance, NULL);

            boton1 = CreateWindowEx(0, "button", ("Insertar"), WS_VISIBLE|WS_CHILD, 495, 100, 70, 30, hwnd, (HMENU)BT1,0, 0);
            boton2 = CreateWindowEx(0, "button", ("Eliminar"), WS_VISIBLE|WS_CHILD, 575, 100, 70, 30, hwnd, (HMENU)BT2,0, 0);
            boton3 = CreateWindowEx(0, "button", ("Probar"), WS_VISIBLE|WS_CHILD, 370, 20, 70, 30, hwnd, (HMENU)BT3,0, 0);
        }
            break;
        case WM_COMMAND:
            Comando = LOWORD(wParam);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            TextOut(hdc, 20, 60, "Resultado: ", 11);
            switch(Comando){
                case BT1:{
                    filedit = GetDlgItem(hwnd, BEDIT1); // I tried with and without this
                    GetWindowText(filedit, columnaWM, sizeof(columnaWM));
                    filedit = GetDlgItem(hwnd, BEDIT2); // I tried with and without this
                    GetWindowText(filedit, filaWM, sizeof(filaWM));
                    filedit = GetDlgItem(hwnd, BEDIT3); // I tried with and without this
                    GetWindowText(filedit, estadoWM, sizeof(estadoWM));
                    filedit = GetDlgItem(hwnd, CAJALEER); // I tried with and without this
                    GetWindowText(filedit, textoCajaWM, sizeof(textoCajaWM));
                    std::string columnaWMcp = columnaWM;
                    std::string estadoWMcp = estadoWM;
                    std::string filaWMcp = filaWM;
                    if((columnaWMcp != "") && (estadoWMcp != "") && (filaWMcp != ""))
                        M.Insertar(columnaWM, filaWM, estadoWM);
                    break;
                }
                case BT2:{
                    filedit = GetDlgItem(hwnd, BEDIT1); // I tried with and without this
                    GetWindowText(filedit, columnaWM, sizeof(columnaWM));
                    filedit = GetDlgItem(hwnd, BEDIT2); // I tried with and without this
                    GetWindowText(filedit, filaWM, sizeof(filaWM));
                    std::string columnaWMcp = columnaWM;
                    std::string filaWMcp = filaWM;
                    if((columnaWMcp != "") && (filaWMcp != ""))
                        M.Eliminar(columnaWM, filaWM);
                    break;
                }
                case BT3:{
                    if(indiceVr == 0){
                        filedit = GetDlgItem(hwnd, CAJALEER); // I tried with and without this
                        GetWindowText(filedit, textoCajaWM, sizeof(textoCajaWM));
                        indiceVr++;
                    }
                    std::string cpCajaleer = textoCajaWM;
                    if(cpCajaleer != ""){
                        indiceVr = M.Verificar2(textoCajaWM, estadoVr, senteciaVr, indiceVr);

                        std::string cpTextoCajaWM = textoCajaWM;
                        TextOut(hdc, 100, 60, textoCajaWM, cpTextoCajaWM.length());

                        char cpTempEstadoVr [senteciaVr.length() + 1];
                        for(int i = 0; i < senteciaVr.length(); i++)
                            cpTempEstadoVr[i] = senteciaVr[i];
                        TextOut(hdc, 50, 25, cpTempEstadoVr, senteciaVr.length());
                    }
                    break;
                }
            }
            M.Mostrar(hdc);
            //M.Verificar(hdc, textoCajaWM);
            //funtionPaintText(hdc, fila, columna, estado, textoCaja);
            EndPaint(hwnd, &ps);
        break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
