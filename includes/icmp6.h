/*
* ICMP6 HEADER
*/
#ifndef ICMP6_H_INCLUDED
#define ICMP6_H_INCLUDED


#define ICMP6_TYPE_ECHO_REPLY 128
#define ICMP6_TYPE_ECHO_REQUEST 129
#define ICMP6_TYPE_DESTINATION_UNREACHABLE 3
#define ICMP6_TYPE_TIME_EXCEEDED 6

#define ICMP6_LEN 8 

struct Icmp6 {
	unsigned char type;			
	unsigned char code;			
	u_short checksum;			
	uint32_t message;		
};

struct Icmp6 icmp6(unsigned char * buffer);
void printIcmp6(struct Icmp6 icmp6);
const char * icmp6TypeStr(unsigned char type);

#endif