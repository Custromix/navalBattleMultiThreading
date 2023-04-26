#include "Utils.h"

Server::Server(int port)
{
    statusServ = ServerStatus::STOP;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("WSAStartup a échoué avec l'erreur : " + WSAGetLastError());
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        throw std::runtime_error("Erreur de création du socket : " + WSAGetLastError());
        WSACleanup();
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(27523);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        throw std::runtime_error("Erreur lors de la liaison du socket : " + WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
    }


    InitCommand();
}

Server::~Server()
{
}

void Server::InitCommand() 
{
    command["server:start"] = 1;
    command["server:stop"] = 0;
}

void Server::Start() 
{
    do{

        std::cout << "caca";

    } while (statusServ != STOP);
}

void Server::Join(Client* joiningClient)
{
	if (!IsExist(joiningClient))
	{
		clients.push_back(joiningClient);
	}

    SOCKET clientSocket;
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);


    while (true) {
        if ((clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrSize)) == INVALID_SOCKET) {
            std::cerr << "Erreur lors de la connexion entrante : " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
        }
        else {
            std::cout << "Client connecté" << std::endl;
        }
    }
}

void Server::Leave(Client* leavingClient)
{
	if (IsExist(leavingClient))
	{

	}
}

CResult<int>* Server::IsExist(Client* client)
{
    CResult<int>* result = new CResult<int>(false);

    if (client == nullptr) {
        throw std::invalid_argument("Client pointer is null.");
    }

    for (int i = 0; i < clients.size(); i++) {
        if (clients[i] == client) {
            result->SetSatue(true);
            result->SetValue(i);
            return result;
        }
    }

    return result;
}

bool Server::DeleteUsers(Client* client)
{
    if (IsExist(client)->GetStatus()) 
    {
        auto it = std::remove(clients.begin(), clients.end(), client);
        clients.erase(it, clients.end());
        return true;
    }
    else
        return false;
}

void Server::Listen()
{
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        throw std::runtime_error("Erreur lors de la mise en mode écoute du socket : " + WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
    }
    else
        std::cout << "Le serveur est à l'écoute sur le port : " << serverAddr.sin_port << std::endl;
 
    do {

        std::string input;
        std::cin >> input;

        ListenCommand(command[input]);

    } while (statusServ != START);

}

void Server::ListenCommand(int command)
{
    switch (command)
    {
    case 0:
        break;

    case 1:
        statusServ = START;
        Start();
        break;

    default:
        break;
    }
}


int bean() {

	//WSADATA wsaData;
 //   if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
 //       std::cerr << "WSAStartup a échoué avec l'erreur : " << WSAGetLastError() << std::endl;
 //       return 1;
 //   }

 //   // Créer un socket pour le serveur
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 //   if (serverSocket == INVALID_SOCKET) {
 //       std::cerr << "Erreur de création du socket : " << WSAGetLastError() << std::endl;
 //       WSACleanup();
 //       return 1;
 //   }

    // Lier le socket à une adresse IP et un port
    //sockaddr_in serverAddr;
    //serverAddr.sin_family = AF_INET;
    //serverAddr.sin_port = htons(27523);
    //serverAddr.sin_addr.s_addr = INADDR_ANY;

    //if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
    //    std::cerr << "Erreur lors de la liaison du socket : " << WSAGetLastError() << std::endl;
    //    closesocket(serverSocket);
    //    WSACleanup();
    //    return 1;
    //}

    // Mettre le socket en mode écoute
    //if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
    //    std::cerr << "Erreur lors de la mise en mode écoute du socket : " << WSAGetLastError() << std::endl;
    //    closesocket(serverSocket);
    //    WSACleanup();
    //    return 1;
    //}
    //else {
    //    std::cout << "Le serveur est à l'écoute sur le port : " << serverAddr.sin_port << std::endl;

    //}


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


