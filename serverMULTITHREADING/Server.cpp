#include "Utils.h"

Server::Server()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("WSAStartup a échoué avec l'erreur : " + WSAGetLastError());
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Erreur de création du socket : " << WSAGetLastError() << std::endl;
        WSACleanup();
    }
}

Server::~Server()
{
}

void Server::Join(Client* joiningClient)
{
	if (!IsExist(joiningClient))
	{
		clients.push_back(joiningClient);
	}
}

void Server::Leave(Client* leavingClient)
{
	if (IsExist(leavingClient))
	{

	}
}

bool Server::IsExist(Client* client)
{
    if (client == nullptr) {
        throw std::invalid_argument("Client pointer is null.");
    }

    for (int i = 0; i < clients.size(); i++) {
        if (clients[i] == client) {
            return true;
        }
    }

    return false;
}

bool Server::DeleteUsers(Client* client)
{
    for (int i = 0; i < clients.size(); i++) {
        if (clients[i] == client) {
            clients.erase(it, clients.end());
            return true;
        }
    }
    return true;
}


int bean() {

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


