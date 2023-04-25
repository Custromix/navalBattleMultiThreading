#pragma once

class Server
{
private:
	std::vector<Client*> clients;

public:
	Server();
	~Server();

	void Join(Client* joiningClient);
	void Leave(Client* leavingClient);
	bool IsExist(Client* client);
	bool DeleteUsers(Client* client);

	std::vector<Client*> GetClients() { return clients; }

};

