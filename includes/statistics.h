#ifndef STATISTICS_H_INCLUDED
#define STATISTICS_H_INCLUDED

#define IP_ACCESS_MAX 100000
#define PRT_ACCESS_MAX 100000

// #APP

// SMTP
#define APP_SMTP 25
#define APP_SMTP1 2525
#define APP_SMTP2 587
#define APP_SMTP3 465
#define APP_SMTP4 2526
// POP
#define APP_POP 110
// IMAP
#define APP_IMAP 143
#define APP_IMAP1 993
// DNS 
#define APP_DNS 53
// FINGER
#define APP_FINGER 79
// HTTP
#define APP_HTTP 80
// HTTPS
#define APP_HTTPS 443
// FTP
#define APP_FTP 21
#define APP_FTP1_DATA 20
// SSH
#define APP_SSH 22
// TELNET
#define APP_TELNET 23
//NETBIOS
#define APP_NETBIOS 139
// NNTP
#define APP_NNTP 119
// LDAP
#define APP_LDAP 389
// UDP (esses 3 + DNS)
// BOOTP
#define APP_BOOTP 67   	// BOOTPS
#define APP_BOOTP1 68	// BOOTPC
// TFTP
#define APP_TFTP 69
// SNMP
#define APP_SNMP 161
#define APP_SNMP1 162 	// TRAP


// #Struct
struct Counters{
	int total;
	int countArp;
	int countIpv4;
	int countIpv6;
	int countIcmp;
	int countIcmp6;
	int countTcp;
	int countUdp;
};

struct IpAccesses
{
	unsigned char addr[4];
	int accesses;
};

struct PrtAccesses{
	uint16_t prtType;
	int accesses;
};

// #Variables
struct Counters counters;
//ips accesses
struct IpAccesses *srcAccesses;
struct IpAccesses *destAccesses;
int srcIpBlocks  = 1;
int destIpBlocks = 1;
int countSrcIp = 0;
int countDestIp = 0;
// protocol accesses
struct PrtAccesses *sendPrt;
struct PrtAccesses *receivPrt;
int sendPrtBlocks  = 1;
int receivPrtBlocks = 1;
int countSendPrt = 0;
int countReceivPrt = 0;

// #Functions
void printStatistics();
void cleanMem();
void sortAccesses();

//counters
float calcPercent(int value);
void initCounters();

// ip accesses
void addSrcIp(unsigned char addr[4]);
void addDestIp(unsigned char addr[4]);
int ipsAreEquals(unsigned char addr1[4], unsigned char addr2[4]);
int cmpfuncIp (const void * a, const void * b);

// protocol
//unify diferents ports in a single number, Ex: if port is smtp it can be 25 or 465 or 587... it will be convert to 25
uint16_t getProtocolId(uint16_t protocol);
const char * getAppProtocolStr(uint16_t protocol);
void addSendPrt(uint16_t protocol);
void addReceivPrt(uint16_t protocol);
int cmpfuncPrt (const void * a, const void * b);

#endif