// serverMULTITHREADING.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Utils.h"

#pragma comment(lib, "ws2_32.lib")


int main()
{
    try {
        Server* g_server = new Server(257523);

        g_server->Listen();

    }
    catch (const std::exception& e) {
        // Bloc de code qui sera ex�cut� en cas d'exception
        // ...
        std::cout << "Exception : " << e.what() << std::endl;
    }

}
