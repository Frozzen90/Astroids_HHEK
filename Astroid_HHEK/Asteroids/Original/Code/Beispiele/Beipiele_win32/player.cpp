// player.cpp: Beispielspieler für Asteroids
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

void Player::Run(void)
{
	FramePacket frame;
	KeysPacket keys;
	GameStatus game;
	char prevframe = 0;
	int t = 0;

	for (;;)
	{
		++t;         // Zeit
		++keys.ping; // jedes gesendete Päckchen erhält eine individuelle Nummer zur Latenzmessung
		SendPacket(keys);
		ReceivePacket(frame);

		if (frame.frameno != ++prevframe || frame.ping != keys.ping)
		{
			printf("Latenz %d. %d Frames verloren.\n", keys.ping - frame.ping, frame.frameno - prevframe);
			prevframe = frame.frameno;
		}

		InterpretScreen(frame, game);

		keys.clear();   // alle Tasten loslassen
		int min_dist = 0x7fffffff;
		int min_dx = 0;
		int min_dy = 0;
		if (game.ship_present)
		{
			for (int i=0; i<game.nasteroids; ++i)
			{   // nächstgelegenen Asteroiden suchen
				int dx = game.asteroids[i].x - game.ship_x;
				while (dx < -512) dx += 1024; // dx normalisieren auf -512 ... 511
				while (dx > 511) dx -= 1024;
				int dy = game.asteroids[i].y - game.ship_y;
				while (dy < -384) dy += 768;  // dy normalisieren auf -384 ... 383
				while (dy > 383) dy -= 768;
				int dist = dx*dx+dy*dy;  // Quadrat des Abstands zu diesem Asteroiden
				switch (game.asteroids[i].sf)
				{	// Abstand um den ungefähren Radius des Asteroiden korrigieren
					case 0:  // großer Asteroid
						dist -= 40*40;
						break;
					case 15: // mittlerer Asteroid
						dist -= 20*20;
						break;
					case 14: // kleiner Asteroid
						dist -= 8*8;
						break;
				}
				if (dist < min_dist)
				{
					min_dist = dist;
					min_dx = dx;
					min_dy = dy;
				}
			}
			if (game.saucer_present)
			{
				int dx = game.saucer_x - game.ship_x;
				while (dx < -512) dx += 1024;
				while (dx > 511) dx -= 1024;
				int dy = game.saucer_y - game.ship_y;
				while (dy < -384) dy += 768;
				while (dy > 383) dy -= 768;
				int dist = dx*dx+dy*dy;
				switch (game.saucer_size)
				{	// Abstand um den ungefähren Radius des UFOs korrigieren
				case 15: // großes UFO
					dist -= 20*12;
					break;
				case 14: // kleines UFO
					dist -= 10*6;
					break;
				}
				if (dist < min_dist)
				{
					min_dist = dist;
					min_dx = dx;
					min_dy = dy;
				}
			}

			// Schiff in Richtung auf das nächstgelegene Objekt drehen
			// mathematisch wird hier das Kreuzprodukt aus den Vektoren 
			// ship_dx/y/0 und min_dx/y/0 berechnet
			if (game.ship_dx * min_dy - game.ship_dy * min_dx > 0)
				keys.left(true);
			else
				keys.right(true);

			if (min_dist < 27*27)  // Flucht, wenn Kollision unausweichlich
				keys.hyperspace(true);

			if (min_dist > 400*400) // beschleunigen, wenn nichts in der Nähe
				keys.thrust(true);

			if (t % 2 == 0)  // Feuerknopf drücken, so schnell es geht
				keys.fire(true);
		}
	}
}

void Player::InterpretScreen(FramePacket &packet, GameStatus& game)
{
	unsigned short vector_ram[512];
	int dx, dy, sf, vx, vy, vz, vs;
	int v1x = 0;
	int v1y = 0;
	int shipdetect = 0;

	game.clear();

	/* Vektor-RAM in 16-Bit-Worte konvertieren. War in der ersten Version mal ein sportlicher
	Typecast: unsigned short *vector_ram = (unsigned short*)packet.vectorram;
	Das klappt aber nur auf Little-Endian-Systemen, daher besser portabel: */
	for (int i=0; i<512; ++i)
		vector_ram[i] = (unsigned char)packet.vectorram[2*i] | (unsigned char)packet.vectorram[2*i+1] << 8;

	if (vector_ram[0] != 0xe001 && vector_ram[0] != 0xe201)
		return; // sollte nicht vorkommen; erster Befehl ist immer ein JMPL

	int pc = 1;
	while (pc < 512)
	{
		int op = vector_ram[pc] >> 12;
		switch (op)
		{
		case 0xa: // LABS
			vy = vector_ram[pc] & 0x3ff;
			vx = vector_ram[pc+1] & 0x3ff;
			vs = vector_ram[pc+1] >> 12;
			break;
		case 0xb: // HALT
			return;
		case 0xc: // JSRL
			switch (vector_ram[pc] & 0xfff)
			{
			case 0x8f3:
				game.asteroids[game.nasteroids++].set(vx, vy, 1, vs);
				break;
			case 0x8ff:
				game.asteroids[game.nasteroids++].set(vx, vy, 2, vs);
				break;
			case 0x90d:
				game.asteroids[game.nasteroids++].set(vx, vy, 3, vs);
				break;
			case 0x91a:
				game.asteroids[game.nasteroids++].set(vx, vy, 4, vs);
				break;
			case 0x929:
				game.saucer_present = true;
				game.saucer_x = vx;
				game.saucer_y = vy;
				game.saucer_size = vs;
				break;
			}  
			break;
		case 0xd: // RTSL
			return;
		case 0xe: // JMPL
			/*
			pc = vector_ram[pc] & 0xfff;
			break;
			*/
			return;
		case 0xf: // SVEC
			/*
			dy = vector_ram[pc] & 0x300;
			if ((vector_ram[pc] & 0x400) != 0)
				dy = -dy;
			dx = (vector_ram[pc] & 3) << 8;
			if ((vector_ram[pc] & 4) != 0)
				dx = -dx;
			sf = (((vector_ram[pc] & 8) >> 2) | ((vector_ram[pc] & 0x800) >> 11)) + 2;
			vz = (vector_ram[pc] & 0xf0) >> 4;
			*/
			break;
		default:
			dy = vector_ram[pc] & 0x3ff;
			if ((vector_ram[pc] & 0x400) != 0)
				dy = -dy;
			dx = vector_ram[pc+1] & 0x3ff;
			if ((vector_ram[pc+1] & 0x400) != 0)
				dx = -dx;
			sf = op;
			vz = vector_ram[pc+1] >> 12;
			if (dx == 0 && dy == 0 && vz == 15)
				game.shots[game.nshots++].set(vx, vy);
			if (op == 6 && vz == 12 && dx != 0 && dy != 0)
			{
				switch (shipdetect)
				{
				case 0:
					v1x = dx;
					v1y = dy;
					++shipdetect;
					break;
				case 1:
					game.ship_present = true;
					game.ship_x = vx;
					game.ship_y = vy;
					game.ship_dx = v1x - dx;
					game.ship_dy = v1y - dy;
					++shipdetect;
					break;
				}
			}
			else if (shipdetect == 1)
				shipdetect = 0;

			break;
		}
		if (op <= 0xa)
			++pc;
		if (op != 0xe) // JMPL
			++pc;
	}   

}


void Asteroid::set(int x, int y, int type, int sf)
{
	this->x = x;
	this->y = y;
	this->type = type;
	this->sf = sf;
}

void Shot::set(int x, int y)
{
	this->x = x;
	this->y = y;
}

void GameStatus::clear(void)
{
	ship_present = false;
	saucer_present = false;
	nasteroids = 0;
	nshots = 0;
}

KeysPacket::KeysPacket(void)
{
	signature[0] = 'c';
	signature[1] = 't';
	signature[2] = 'm';
	signature[3] = 'a';
	signature[4] = 'm';
	signature[5] = 'e';
	keys = '@';
	ping = 0;
}

void KeysPacket::clear(void)
{
	keys = '@';
}

void KeysPacket::hyperspace(bool b)
{
	if (b)
		keys |= KEY_HYPERSPACE;
	else
		keys &= ~KEY_HYPERSPACE;
}

void KeysPacket::fire(bool b)
{
	if (b)
		keys |= KEY_FIRE;
	else
		keys &= ~KEY_FIRE;
}

void KeysPacket::thrust(bool b)
{
	if (b)
		keys |= KEY_THRUST;
	else
		keys &= ~KEY_THRUST;
}

void KeysPacket::left(bool b)
{
	if (b)
	{
		keys |= KEY_LEFT;
		right(false);
	}
	else
		keys &= ~KEY_LEFT;
}

void KeysPacket::right(bool b)
{
	if (b)
	{
		keys |= KEY_RIGHT;
		left(false);
	}
	else
		keys &= ~KEY_RIGHT;
}

void Player::ReceivePacket(FramePacket &packet)
{
	sockaddr_in sender;
	int sender_size = sizeof sender;
	fd_set readfds, writefds, exceptfds;

	do
	{
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);
		FD_ZERO(&exceptfds);
		FD_SET(sd, &readfds);
		FD_SET(sd, &exceptfds);
		select(sd+1, &readfds, &writefds, &exceptfds, NULL);
		int bytes_received = recv(sd, (char *)&packet, sizeof packet, 0);
		if (bytes_received != sizeof packet)
		{
			int err = WSAGetLastError();
			fprintf(stderr, "Fehler %d bei recvfrom().\n", err);
			exit(1);
		}
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);
		FD_ZERO(&exceptfds);
		FD_SET(sd, &readfds);
		timeval zero;
		zero.tv_sec = zero.tv_usec = 0;
		select(sd+1, &readfds, &writefds, &exceptfds, &zero);
	} while(FD_ISSET(sd, &readfds));
}

void Player::SendPacket(KeysPacket &packet)
{
	sockaddr_in server;
	memset(&server, 0, sizeof server);
	server.sin_family = AF_INET;
	server.sin_port = htons(1979);
	server.sin_addr.s_addr = server_ip;
	if (sizeof packet != sendto(sd, (char *)&packet, sizeof packet, 0, (sockaddr*)&server, sizeof server))
	{
#if defined(WINDOWS)
		int err = WSAGetLastError();
		if (err != WSAEWOULDBLOCK)
		{
			fprintf(stderr, "Fehler %d bei sendto().\n", err);
			exit(1);
		}
#else
		if (errno != EAGAIN)
		{
			perror("Fehler bei sendto()");
			exit(1);
		}
#endif
	}
}
