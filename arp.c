/*
* ARP functions
*/
struct Arp arp(unsigned char * buffer){
	struct Arp arp;
	memcpy(&arp, &buffer[0], ARP_LEN);
	return arp;
};

const char * arpOpStr(u_short operation){
	switch(ntohs(operation)){
		case ARP_TYPE_REQUEST:
			return "ARP REQUEST";
		case ARP_TYPE_REPLY:
			return "ARP REPLY";
	}
	return "";

}


void printArp(struct Arp arp){
	printf("###ARP###\n");
	printf("Tipo de Endereço de Hardware: %d\n", ntohs(arp.hw_addr_type));
	const char* strType = ethernetTypeToStr(arp.prot_addr_type);
	printf("Tipo de Endereço de Protocolo: 0x%04x(%s)\n", ntohs(arp.prot_addr_type),strType);
	printf("Tamanho do Endereço de Hardware: %d\n", arp.hw_addr_len);
	printf("Tamanho do Endereço de Protocolo: %d\n", arp.prot_addr_len);
	const char * strOp = arpOpStr(arp.operation);
	printf("Operação: %d (%s)\n", ntohs(arp.operation), strOp);
	printf("Endereço de Hardare de Origem:");
	printMac(arp.src_hw_addr);
	printf("\n");
	printf("Endereço de Protocolo de Origem: ");
	printIpAddr(arp.src_prot_addr);
	printf("\n");
	printf("Endereço de Hardware Alvo: ");
	printMac(arp.target_hw_addr);
	printf("\n");
	printf("Endereço de Protocolo Alvo:");
	printIpAddr(arp.target_prot_addr);
	printf("\n");
}	