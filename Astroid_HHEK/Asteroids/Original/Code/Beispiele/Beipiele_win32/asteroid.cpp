// asteroid.cpp: Beispielspieler für Asteroids 
// Harald Bögeholz / c't
#define WINDOWS
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#if defined(WINDOWS)
#include <winsock2.h>
#else
// 2 Includes für socket()
#include <sys/types.h>
#include <sys/socket.h>
// 2 Includes für inet_addr()
#include <netinet/in.h>
#include <arpa/inet.h>
// 2 Includes für fcntl()
#include <unistd.h>
#include <fcntl.h>
// für memset()
#define INVALID_SOCKET -1
#define WSAGetLastError() errno
#endif

#include "player.h"


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Aufruf: asteroid <IP-Adresse>\n");
		exit(1);
	}
	unsigned long server_ip = inet_addr(argv[1]);
	if (server_ip == INADDR_NONE)
	{
		fprintf(stderr, "Ungueltige IP-Adresse: '%s'\n", argv[1]);
		exit(1);
	}

#if defined(WINDOWS)
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2,2), &wsadata))
	{
		fprintf(stderr, "Fehler beim Initialisieren von Winsock.\n");
		exit(2);
	}
#endif*/


	SOCKET sd;
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == INVALID_SOCKET)
	{
		fprintf(stderr, "Fehler %d bei socket().\n", WSAGetLastError());
		exit(2);
	}

#if defined(WINDOWS)
	unsigned long enable_nonblocking = 1;
	if (ioctlsocket(sd, FIONBIO, &enable_nonblocking))
	{
		fprintf(stderr, "Kann Socket nicht auf nonblocking setzen (%d)", WSAGetLastError());
		exit(1);
	}
#else
    if (-1 == fcntl(sd, F_SETFL, O_NONBLOCK))
    {
        perror("Kann Socket nicht auf non-blocking setzen");
        exit(1);
    }
#endif
	sockaddr_in sa;
	memset(&sa, 0, sizeof sa);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = 0;
	sa.sin_port = 0;

	if (bind(sd, (struct sockaddr*) &sa, sizeof sa))
	{
		fprintf(stderr, "Fehler %d bei bind().\n", WSAGetLastError());
		exit(2);
	}

	Player player(sd, server_ip);
	player.Run();

	return 0;
}
