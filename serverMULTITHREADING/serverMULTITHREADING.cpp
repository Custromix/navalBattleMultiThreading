// serverMULTITHREADING.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Utils.h"

#pragma comment(lib, "ws2_32.lib")


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    HWND WindowOui = CreateWindow(
        L"Mon Programme",      // Nom de la classe de la fen�tre
        L"pipi",            // Titre de la fen�tre
        WS_OVERLAPPEDWINDOW,// Style de la fen�tre
        CW_USEDEFAULT,      // Position horizontale de la fen�tre
        CW_USEDEFAULT,      // Position verticale de la fen�tre
        CW_USEDEFAULT,      // Largeur de la fen�tre
        CW_USEDEFAULT,      // Hauteur de la fen�tre
        NULL,               // Handle de la fen�tre parent
        NULL,               // Handle du menu de la fen�tre
        GetModuleHandle(NULL),          // Handle de l'instance de l'application
        NULL                // Param�tre additionnel
    );

    if (WindowOui == NULL)
    {
        std::cout << "NULL";
        // Gestion de l'erreur de cr�ation de la fen�tre
    }
    else
    {
        std::cout << "PAS NULL";
    }


    try {

        Server* g_server = new Server(257523, WindowOui);

        g_server->Listen();

    }
    catch (const std::exception& e) {
        // Bloc de code qui sera ex�cut� en cas d'exception
        // ...
        std::cout << "Exception : " << e.what() << std::endl;
    }


}
