#include "Includes.h"
#include "Client.h"

Client::Client()
{

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup a �chou� avec l'erreur : " << WSAGetLastError() << std::endl;
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Erreur de cr�ation du socket : " << WSAGetLastError() << std::endl;
        WSACleanup();
    }


}

void Client::Connect(PCSTR ip, PCSTR port)
{

        
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;


    status = getaddrinfo(ip, port, &hints, &result);

    if (status != 0) {
        std::cerr << "Impossible de r�soudre l'adresse IP du serveur : " << gai_strerror(status) << std::endl;
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

    message = "Wesh kader il a dit c'�tait le plus gros mangeur de france!\n";
    // Send message to server
    if (send(clientSocket, message, strlen(message), 0) < 0) {
        std::cerr << "Could not send data: " << WSAGetLastError() << std::endl;

    }
    else {
        std::cerr << "SENDFDDD : " << WSAGetLastError() << std::endl;

    }


    std::string buffer(1024, 0); // cr�er un string avec 1024 caract�res initialis�s � 0
    int bytesReceived = 0;

    while ((bytesReceived = recv(clientSocket, &buffer[0], buffer.size(), 0)) > 0) {
        std::cout << "Donn�es re�ues : " << buffer.substr(0, bytesReceived) << std::endl;
    }
}

void Client::StartServer()
{

}
