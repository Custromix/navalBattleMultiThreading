#include "Includes.h"
#include "Client.h"

Client::Client()
{

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup a échoué avec l'erreur : " << WSAGetLastError() << std::endl;
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Erreur de création du socket : " << WSAGetLastError() << std::endl;
        WSACleanup();
    }


}

void Client::Connect(PCSTR ip, PCSTR port)
{

        
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;


    status = getaddrinfo("10.1.170.31", "27523", &hints, &result);

    if (status != 0) {
        std::cerr << "Impossible de résoudre l'adresse IP du serveur : " << gai_strerror(status) << std::endl;
        closesocket(clientSocket);
        WSACleanup();
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = ((struct sockaddr_in*)result->ai_addr)->sin_addr.s_addr;
    serverAddr.sin_port = htons(27523);


    freeaddrinfo(result);



    // Se connecter au serveur
    if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Impossible de se connecter au serveur : " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
    }

    // Send message to server
    if (send(clientSocket, message, strlen(message), 0) < 0) {
        std::cerr << "Could not send data: " << WSAGetLastError() << std::endl;

    }
    else {
        std::cerr << "SENDFDDD : " << WSAGetLastError() << std::endl;

    }
}
