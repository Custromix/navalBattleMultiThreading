// navalBattleMulti.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "Includes.h"

int sockfd = socket(AF_INET, SOCK_STREAM, 0);


int main()
{
    // Initialiser Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup a échoué avec l'erreur : " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Créer un socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Erreur de création du socket : " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    struct addrinfo* result = NULL;
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int status = getaddrinfo("10.1.170.31", "27523", &hints, &result);

    if (status != 0) {
        std::cerr << "Impossible de résoudre l'adresse IP du serveur : " << gai_strerror(status) << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // Spécifier l'adresse du serveur
    SOCKADDR_IN serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = ((struct sockaddr_in*)result->ai_addr)->sin_addr.s_addr;
    serverAddr.sin_port = htons(27523);

    freeaddrinfo(result);

    // Se connecter au serveur
    if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Impossible de se connecter au serveur : " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    const char* message = "Wesh kader il a dit c'était le plus gros violuer de france!\n";
    // Send message to server
    if (send(clientSocket, message, strlen(message), 0) < 0) {
        std::cerr << "Could not send data: " << WSAGetLastError() << std::endl;
        return 1;
    }

    /*
    // Envoyer la requête HTTP
    const char* httpRequest = "GET / HTTP/1.1\r\nHost: www.google.com\r\nConnection: close\r\n\r\n";
    if (send(clientSocket, httpRequest, strlen(httpRequest), 0) == SOCKET_ERROR) {
        std::cerr << "Erreur lors de l'envoi de la requête HTTP : " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // Recevoir la réponse HTTP
    const int bufferSize = 1024;
    char buffer[bufferSize];
    std::string response;
    int bytesReceived = 0;
    while ((bytesReceived = recv(clientSocket, buffer, bufferSize - 1, 0)) > 0) {
        buffer[bytesReceived] = '\0';
        response += buffer;
    }

    // Afficher la réponse HTTP
    std::cout << response << std::endl;
    */
    // Fermer le socket et libérer les ressources Winsock
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}









