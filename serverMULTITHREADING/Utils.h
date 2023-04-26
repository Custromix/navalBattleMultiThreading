#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <map>

#include "CResult.h";
#include "Client.h";
#include "Server.h";

class Client;
class Server;