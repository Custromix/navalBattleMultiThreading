// serverMULTITHREADING.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")


int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup a échoué avec l'erreur : " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Créer un socket pour le serveur
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Erreur de création du socket : " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Lier le socket à une adresse IP et un port
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(27523);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Erreur lors de la liaison du socket : " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Mettre le socket en mode écoute
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Erreur lors de la mise en mode écoute du socket : " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    else {
        std::cout << "Le serveur est à l'écoute sur le port : " << serverAddr.sin_port << std::endl;

    }


    // Attendre une connexion entrante
    SOCKET clientSocket;
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    if ((clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrSize)) == INVALID_SOCKET) {
        std::cerr << "Erreur lors de la connexion entrante : " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    else {
        std::cout << "Client connecté" << std::endl;
    }


    // Recevoir les données envoyées par le client
    //char buffer[1024];
    std::string buffer;
    int bytesReceived = 0;

    while ((bytesReceived = recv(clientSocket, &buffer[0], buffer.size(), 0)) > 0) {
        std::cout << "Données reçues : " << buffer << std::endl;
    }

    if (bytesReceived == SOCKET_ERROR) {
        std::cerr << "Erreur lors de la réception des données : " << WSAGetLastError() << std::endl;
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
