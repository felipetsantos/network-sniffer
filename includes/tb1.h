#ifndef TB1_H_INCLUDED
#define TB1_H_INCLUDED

#define BUFFSIZE 1518

/*
* IP HEADER
*/
#define IP_PROTOCOL_ICMP 1
#define IP_PROTOCOL_TCP 6
#define IP_PROTOCOL_UDP 17
#define IP_PROTOCOL_ICMP6 58


#define LAST(k,n) ((k) & ((1<<(n))-1))
#define MID(k,m,n) LAST((k)>>(m),((n)-(m)))
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
void printMac(unsigned char *mac);
void printIpAddr(unsigned char * ipAddr);
void afterIp(unsigned char *buffer, unsigned char protocol,int len);
int isIpICMP(unsigned char protocol);
int isIpTCP(unsigned char protocol);
int isIpUDP(unsigned char protocol);
int isIpICMP6(unsigned char protocol);
char * showNetInterfaces();
void selectInterface(int argc, char *argv[]);
#endif