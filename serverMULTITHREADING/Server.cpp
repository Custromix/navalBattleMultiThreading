#include "Utils.h"

Server::Server(int port)
{
    statusServ = ServerStatus::STOP;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("WSAStartup a �chou� avec l'erreur : " + WSAGetLastError());
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        throw std::runtime_error("Erreur de cr�ation du socket : " + WSAGetLastError());
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
    currentCommand = "";

    SOCKET clientSocket;
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    Client* client = new Client();

    do{

        if ((clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrSize)) == INVALID_SOCKET) {
            std::cerr << "Erreur lors de la connexion entrante : " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
        }
        else {
            std::cout << "Client connect�" << std::endl;
           // Join(newClient);
        }

        std::string buffer(1024, 0); // cr�er un string avec 1024 caract�res initialis�s � 0
        int bytesReceived = 0;

        while ((bytesReceived = recv(clientSocket, &buffer[0], buffer.size(), 0)) > 0) {
            std::cout << "Donn�es re�ues : " << buffer.substr(0, bytesReceived) << std::endl;
        }

        char buffedr[1024] = "FERME TA GUEULE !"; // la cha�ne de caract�res � envoyer
        if (send(clientSocket, buffedr, strlen(buffedr), 0))
            std::cout << "Donn�es envoy� : "  << std::endl;
        else
            std::cout << "Donn�es pas envoy� : " << std::endl;

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
            std::cout << "Client connect�" << std::endl;
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
    currentCommand = "";

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        throw std::runtime_error("Erreur lors de la mise en mode �coute du socket : " + WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
    }
    else
        std::cout << "Le serveur est � l'�coute sur le port : " << serverAddr.sin_port << std::endl;
 
    do {

        std::cin >> currentCommand;

        ListenCommand(command[currentCommand]);

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


