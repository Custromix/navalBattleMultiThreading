#pragma once

class Server
{
private:
	std::vector<Client*> clients;
	WSADATA wsaData;
	SOCKET serverSocket;
	sockaddr_in serverAddr;

	std::map<std::string, int> command;

public:
	Server(int port);
	~Server();

	void InitCommand();

	void Start();

	void Join(Client* joiningClient);
	void Leave(Client* leavingClient);
	CResult<int>* IsExist(Client* client);
	bool DeleteUsers(Client* client);
	void Listen();

	void ListenCommand(int command);

	std::vector<Client*> GetClients() { return clients; }

	ServerStatus statusServ;


};

enum ServerStatus
{
	START,
	STOP
};

