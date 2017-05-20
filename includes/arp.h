/*
* ARP HEADER
*/
#ifndef ARP_H_INCLUDED
#define ARP_H_INCLUDED
#define ARP_TYPE_REQUEST 1
#define ARP_TYPE_REPLY 2

#define ARP_LEN 28 // IN Bytes


struct Arp {
	u_short hw_addr_type;				// 2 bytes para imprimir precisa usar o  ntohs(arp.hw_addr_type)
	u_short prot_addr_type;				// 2 bytes para imprimir precisa usar o  ntohs(arp.u_short)
	unsigned char hw_addr_len; 			// 1 byte
	unsigned char prot_addr_len; 		// 1 byte
	u_short operation;					// 2 bytes para imprimir precisa usar o  ntohs(arp.operation)
	unsigned char src_hw_addr[6];		// 6 bytes mac	
	unsigned char src_prot_addr[4];		// 4 bytes ip
	unsigned char target_hw_addr[6];	// 6 bytes mac
	unsigned char target_prot_addr[4];	// 4 bytes ip
};

struct Arp arp(unsigned char * buffer);
void printArp(struct Arp arp);

#endif