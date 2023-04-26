// serverMULTITHREADING.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Utils.h"

#pragma comment(lib, "ws2_32.lib")


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    HWND WindowOui = CreateWindow(
        L"Mon Programme",      // Nom de la classe de la fenêtre
        L"pipi",            // Titre de la fenêtre
        WS_OVERLAPPEDWINDOW,// Style de la fenêtre
        CW_USEDEFAULT,      // Position horizontale de la fenêtre
        CW_USEDEFAULT,      // Position verticale de la fenêtre
        CW_USEDEFAULT,      // Largeur de la fenêtre
        CW_USEDEFAULT,      // Hauteur de la fenêtre
        NULL,               // Handle de la fenêtre parent
        NULL,               // Handle du menu de la fenêtre
        GetModuleHandle(NULL),          // Handle de l'instance de l'application
        NULL                // Paramètre additionnel
    );

    if (WindowOui == NULL)
    {
        std::cout << "NULL";
        // Gestion de l'erreur de création de la fenêtre
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
        // Bloc de code qui sera exécuté en cas d'exception
        // ...
        std::cout << "Exception : " << e.what() << std::endl;
    }


}
