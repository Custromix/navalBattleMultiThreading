#pragma once

class Client
{
    public:
        Client();
        void Connect(PCSTR ip, PCSTR port);
        void StartServer();

        WSADATA wsaData;
        SOCKET clientSocket;


        SOCKADDR_IN serverAddr;


        const char* message;

        int sockfd = socket(AF_INET, SOCK_STREAM, 0);

        struct addrinfo* result = NULL;
        struct addrinfo hints;


        int status;


    private:
};

