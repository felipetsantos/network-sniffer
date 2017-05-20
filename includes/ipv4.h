#ifndef IPV4_H_INCLUDED
#define IPV4_H_INCLUDED


#define IPV4_LEN 20 //bytes

struct Ipv4 {
   unsigned char versionAndIhl;
   unsigned char serviceType;
   uint16_t totalLen;
   uint16_t identification;
   uint16_t flagsAndOffeset;
   unsigned char ttl;
   unsigned char protocol;
   uint16_t checksum;
   unsigned char src[4];
   unsigned char dest[4];
   unsigned char options[4];
};

struct Ipv4 ipv4(unsigned char *buffer);
void printIpv4(struct Ipv4 ipv4);
void printFlags(uint16_t flags);
void printProtocol(unsigned char protocol);

#endif