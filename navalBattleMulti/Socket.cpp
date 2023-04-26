#include "Socket.h"

Socket::Socket()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup a �chou� avec l'erreur : " << WSAGetLastError() << std::endl;
    }

    // Cr�er un socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Erreur de cr�ation du socket : " << WSAGetLastError() << std::endl;
        WSACleanup();
    }
}
