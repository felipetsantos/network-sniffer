/*
* IPV6 HEADER
*/
#ifndef IPV6_H_INCLUDED
#define IPV6_H_INCLUDED
#define IPV6_LEN 40 //bytes
#define MASK_FLOWLABEL 0xFFF00000


struct Ipv6Addr{
	uint16_t octets[8];
};

struct Ipv6{
	 uint32_t versionAndTrafficAndFlowLabel;
	 uint16_t payLoadLen;
	 unsigned char nextHeader;
	 unsigned char hopLimit;
	 struct Ipv6Addr src;
	 struct Ipv6Addr dest;
};

struct Ipv6 ipv6(unsigned char *buffer);
void printIpv6(struct Ipv6 ipv6);
void printIpv6Addr(struct Ipv6Addr addrIpv6);

#endif