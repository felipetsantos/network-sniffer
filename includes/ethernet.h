#ifndef ETHERNET_H_INCLUDED
#define ETHERNET_H_INCLUDED
#define ETHERNET_LEN 14 //bytes
#define ETHERNET_TYPE_IPV4 0x0800
#define ETHERNET_TYPE_IPV6 0x86dd
#define ETHERNET_TYPE_ARP 0x0806

/*
* Ethernet 
*/

struct Ethernet {
   unsigned char  dest[6];
   unsigned char  src[6];
   u_short  type;
};

struct Ethernet ethernet(unsigned char *buffer);
void printEthernet(struct Ethernet ethernet);
void printEthernetType(u_short type);
const char * ethernetTypeToStr(u_short type);
int isIPV4(u_short type);
int isIPV6(u_short type);
int isARP(u_short type);

#endif