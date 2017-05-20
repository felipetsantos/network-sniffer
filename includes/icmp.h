/*
* ICMP
*/
#ifndef ICMP_H_INCLUDED
#define ICMP_H_INCLUDED
#define ICMP_TYPE_ECHO_REPLY 0
#define ICMP_TYPE_ECHO_REQUEST 8
#define ICMP_TYPE_DESTINATION_UNREACHABLE 3
#define ICMP_TYPE_TIME_EXCEEDED 11
#define ICMP_TYPE_TRACEROUTE 30

#define ICMP_LEN 8 

struct Icmp {
	unsigned char type;			
	unsigned char code;			
	u_short checksum;			
	uint32_t other;		
};

struct Icmp icmp(unsigned char * buffer);
void printIcmp(struct Icmp icmp);
const char * icmpTypeStr(unsigned char type);
#endif