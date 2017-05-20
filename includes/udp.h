/*
* UDP HEADER
*/
#ifndef UDP_H_INCLUDED
#define UDP_H_INCLUDED
#define UDP_PORT_ECHO 7
#define UDP_PORT_CHARGEN 19
#define UDP_PORT_TIME 37
#define UDP_PORT_DNS 53
#define UDP_PORT_BOOTPS 67
#define UDP_PORT_BOOTPC 68
#define UDP_PORT_TFTP 69
#define UDP_PORT_NETBIOS_NS 137
#define UDP_PORT_NETBIOS_DGM 138
#define UDP_PORT_SNMP 161
#define UDP_PORT_SNMP_TRAP 162
#define UDP_PORT_ISAKMP 500
#define UDP_PORT_SYSLOG 514
#define UDP_PORT_RIP 520
#define UDP_PORT_TRACEROUTE 33434

#define UDP_LEN 8 // IN Bytes

struct Udp {
   uint16_t srcPort;
   uint16_t destPort;
   uint16_t len;
   uint16_t checksum;
};

struct Udp udp(unsigned char * buffer);
void printUdp(struct Udp udp);

#endif