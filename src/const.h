IPAddress staticIP(192, 168, 1, 33);    // Задана статична IP-адреса ESP32
IPAddress gateway(192, 168, 1, 1);      // IP-адреса вашого роутера/шлюзу
IPAddress subnet(255, 255, 255, 0);     // Маска підмережі
IPAddress dns1(8, 8, 8, 8);         // DNS-сервер (можна використовувати шлюз)
IPAddress secondaryDNS(192, 168, 1, 1);

// --- Конфігурація UDP ---
unsigned int localPort = 33301;        
// UDP клієнт
WiFiUDP cmdUdp;
IPAddress gcs_ip(0, 0, 0, 0); 

// Параметри таймерів для кожного реле
unsigned long r1StartTime = 0;
bool r1Active = false;
const unsigned long r1Duration = 2000; // 0.5 сек для Реле 1

unsigned long r2StartTime = 0;
bool r2Active = false;
const unsigned long r2Duration = 2000; // 0.5 сек для Реле 2

unsigned long r3StartTime = 0;
bool r3Active = false;
const unsigned long r3Duration = 2000; // 0.5 сек для Реле 3

unsigned long r4StartTime = 0;
bool r4Active = false;
const unsigned long r4Duration = 2000; // 0.5 сек для Реле 4

#define relay1 02
#define relay2 04
#define relay3 33
#define relay4 32
