// navalBattleMulti.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "Includes.h"
#include "Client.h"



int main()
{

    try {
        
        Client* player = new Client();
        player->Connect("10.1.170.31", "27523");


    }
    catch (const std::exception& e) {
        // Bloc de code qui sera exécuté en cas d'exception
        // ...
        std::cout << "Exception : " << e.what() << std::endl;
    }
}










    // Spécifier l'adresse du serveur


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