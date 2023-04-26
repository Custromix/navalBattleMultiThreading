
class Client
{

private:
    SOCKET* clientSocket;
    sockaddr_in* clientAddr;

public:
    Client();
    ~Client();

    SOCKET* GetSocket()                                     { return clientSocket; }
    sockaddr_in* GetSockAddr()                              { return clientAddr; }
    void SetSocket(SOCKET* sock_)                           { clientSocket = sock_; }
    void SetSockAddr(sockaddr_in* sockAddr_)                { clientAddr = sockAddr_; }

};

