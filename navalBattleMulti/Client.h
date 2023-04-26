#pragma once
class Client
{
    public:
        Client();
        void Connect(PCSTR ip, PCSTR port);

        WSADATA wsaData;
        SOCKET clientSocket;


        SOCKADDR_IN serverAddr;


        const char* message = "Wesh kader il a dit c'était le plus gros mangeur de france!\n";

        int sockfd = socket(AF_INET, SOCK_STREAM, 0);

        struct addrinfo* result = NULL;
        struct addrinfo hints;


        int status;


    private:
};

