// player.h: Beispielspieler für Asteroids
// Harald Bögeholz / c't
#define WINDOWS
#if defined(WINDOWS)
#define ADDRESS DWORD
#else
#define SOCKET int
#define ADDRESS in_addr_t
// 3 Includes für sockaddr_in
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

static const int MAX_ASTEROIDS = 100;
static const int MAX_SHOTS = 10;

class Asteroid
{
public:
	int x;    // Koordinaten des Mittelpunkts
	int y;
	int type; // 1 ... 4, äußere Form
	int sf;   // scale factor: 0 = groß, 15 = mittel, 14 = klein

	void set(int x, int y, int type, int sf);
};

class Shot
{
public:
	int x;
	int y;

	void set(int x, int y);
};

class GameStatus
{
public:
	bool ship_present;  // Schiff sichtbar
	int ship_x;         // Mittelpunkt des Schiffs
	int ship_y;
	int ship_dx;        // Blickrichtung des Schiffes
	int ship_dy;
	bool saucer_present;// UFO sichtbar
	int saucer_x;       // Mittelpunkt des UFOs
	int saucer_y;
	int saucer_size;    // Größe: 15 = groß, 14 = klein
	int nasteroids; // Anzahl Asteroiden
	Asteroid asteroids[MAX_ASTEROIDS];
	int nshots;     // Anzahl Schüsse
	Shot shots[MAX_SHOTS];
	void clear(void);
};

#pragma pack(1)
struct FramePacket
{
	char vectorram[1024];
	char frameno;  // wird bei jedem Frame inkrementiert
	char ping;     // Der Server schickt das letzte empfangene ping-Byte zurück
};

class KeysPacket
{
private:
	static const char KEY_HYPERSPACE = 1;
	static const char KEY_FIRE = 2;
	static const char KEY_THRUST = 4;
	static const char KEY_RIGHT = 8;
	static const char KEY_LEFT = 0x10;

	char signature[6];
	char keys;
public:
	char ping;     // wird vom Server bei nächster Gelegenheit zurückgeschickt. Für Latenzmessung.

	KeysPacket(void);
	void clear(void);         // alle Tasten loslassen
	void hyperspace(bool b);  // Hyperspace drücken (true) oder loslassen (false)
	void fire(bool b);        // Feuerknopf drücken (true) oder loslassen (false)
	void thrust(bool b);      // Beschleunigen ...
	void right(bool b);       // rechts drehen ...
	void left(bool b);        // links drehen
};
#pragma pack()


class Player
{
public:
	Player(SOCKET sd, ADDRESS server_ip) : sd(sd), server_ip(server_ip) {};
	void Run(void);
	void InterpretScreen(FramePacket &packet, GameStatus& game);
	void ReceivePacket(FramePacket &packet);
	void SendPacket(KeysPacket &packet);
private:
	SOCKET sd;
	ADDRESS server_ip;
};
