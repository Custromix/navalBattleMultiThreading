#include "Utils.h"

#define WM_SOCKET (WM_USER + 1)

Server::Server(int port, HWND Window)
{
    Window_ = Window;
    //win.create(sf::VideoMode(1024, 610), "SFML Server");

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

void Server::Start() 
{


    if (Window_ == NULL) {
        std::cerr << "Erreur fenetre NULL : " << WSAGetLastError() << std::endl;

        // gestion de l'erreur
    }

    // Obtenir l'ancien style de la fenêtre
    LONG_PTR oldStyle = GetWindowLongPtr(Window_, GWL_STYLE);

    // Définir le nouveau style de la fenêtre
    SetWindowLongPtr(Window_, GWL_STYLE, oldStyle | WS_HSCROLL | WS_VSCROLL);


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
            std::cout << "Client connecté" << std::endl;
            // Join(newClient);
        }

        WSAAsyncSelect(clientSocket, Window_, WM_SOCKET, FD_READ | FD_CLOSE);


        MSG msg;

        // Boucle principale
        while (GetMessage(&msg, NULL, 0, 0))
        {
            std::cout << "Message reçus" << std::endl;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        /*if ((clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrSize)) == INVALID_SOCKET) {
            std::cerr << "Erreur lors de la connexion entrante : " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
        }
        else {
            std::cout << "Client connecté" << std::endl;
           // Join(newClient);
        }

        std::string buffer(1024, 0); // créer un string avec 1024 caractères initialisés à 0
        int bytesReceived = 0;


        while ((bytesReceived = recv(clientSocket, &buffer[0], buffer.size(), 0)) > 0) {
            std::cout << "Données reçues : " << buffer.substr(0, bytesReceived) << std::endl;
        }

        char buffedr[1024] = "FERME TA GUEULE !"; // la chaîne de caractères à envoyer
        if (send(clientSocket, buffedr, strlen(buffedr), 0))
            std::cout << "Données envoyé : "  << std::endl;
        else
            std::cout << "Données pas envoyé : " << std::endl;*/

    } while (statusServ != STOP);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    std::cout << "Socket fdermé : " << std::endl;

    switch (msg)
    {
    case WM_SOCKET:
    {
        std::cout << "Socket fermé : " << std::endl;

        Server* pServer = reinterpret_cast<Server*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

        if (WSAGETSELECTERROR(lParam)) {
            std::cout << "Socket fermé : " << std::endl;
        }
        else {
            switch (WSAGETSELECTEVENT(lParam)) {
            case FD_READ:
            {
                char buffer[1024];
                int bytesReceived = recv(pServer->clientSocket, buffer, sizeof(buffer), 0);
                if (bytesReceived == SOCKET_ERROR) {
                    // Il y a eu une erreur
                }
                else {
                    std::cout << "Données reçues : " << buffer << std::endl;
                    // Traitez les données reçues ici
                }
                break;
            }
            case FD_CLOSE:
            {
                std::cout << "Socket fermé : " << std::endl;

                // Le socket a été fermé
                break;
            }

            default:
                std::cout << "Socket fermé : " << std::endl;

                break;
            }
        }
        break;
    }
    case WM_CLOSE:
    {
        std::cout << "Socket fermé : " << std::endl;

        DestroyWindow(hwnd);
    }
        break;
    case WM_DESTROY:
    {
        std::cout << "Socket fermé : " << std::endl;

        PostQuitMessage(0);
    }
        break;
    default:
        std::cout << "Default : " << std::endl;

        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

//void CALLBACK SocketEventHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    if (uMsg == WM_SOCKET)
//    {
//        if (WSAGETSELECTEVENT(lParam) == FD_READ)
//        {
//            char buffer[1024];
//            int bytesReceived = recv(wParam, buffer, sizeof(buffer), 0);
//            if (bytesReceived > 0)
//            {
//                std::cout << "Données reçues : " << buffer << std::endl;
//                // Les données ont été reçues avec succès, traitez-les ici
//            }
//            else if (bytesReceived == 0)
//            {
//                std::cout << "Rien : " << buffer << std::endl;
//                // Le socket a été fermé par le client, fermez-le également
//                closesocket(wParam);
//            }
//            else
//            {
//                std::cout << "Une erreur s'est produite lors de la réception des données : " << buffer << std::endl;
//                // Une erreur s'est produite lors de la réception des données, traitez l'erreur ici
//            }
//        }
//    }
//}

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

void Server::Listen()
{
    currentCommand = "";

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        throw std::runtime_error("Erreur lors de la mise en mode écoute du socket : " + WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
    }
    else
        std::cout << "Le serveur est à l'écoute sur le port : " << serverAddr.sin_port << std::endl;

    do {

        std::cin >> currentCommand;

        ListenCommand(command[currentCommand]);

    } while (statusServ != START);

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

// Lorsque l'événement de réception de données est déclenché
void CALLBACK SocketHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_SOCKET)
    {
        if (WSAGETSELECTEVENT(lParam) == FD_READ)
        {
            // Lire les données envoyées par le client
            char buffer[1024];
            int bytesReceived = recv(wParam, buffer, sizeof(buffer), 0);

            // Traiter les données reçues
            // ...
        }
    }
}




