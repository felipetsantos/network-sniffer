/*
* IPV4 functions
*/

struct Ipv4 ipv4(unsigned char *buffer){
	struct Ipv4 ipv4;
	memcpy(&ipv4, &buffer[0], IPV4_LEN);
	int ihl = MID(ipv4.versionAndIhl,0,3);
	if(ihl > 5){
		int optionsSize = (ihl-5);
		memcpy(&ipv4.options, &buffer[20+optionsSize], optionsSize); 
	}
	addSrcIp(ipv4.src);
	addDestIp(ipv4.dest);
	return ipv4;
}

void printIpv4(struct Ipv4 ipv4){
	printf("-###IPV4###\n");
	printf("Versão:");
	printf("%d",  MID(ipv4.versionAndIhl,4,7));
	printf("| IHL:");
	printf("%d (%d bytes)",  MID(ipv4.versionAndIhl,0,3), MID(ipv4.versionAndIhl,0,3)*4);
	printf("| Tipo de Serviço:");
	printf("%x",  ipv4.serviceType);
	printf("| Tamanho Total(bytes):");
	printf("%d\n",  ntohs(ipv4.totalLen));
	printf("Identificador:");
	printf("0x%x(%d)",	ntohs(ipv4.identification), ntohs(ipv4.identification));
	printFlags(ipv4.flagsAndOffeset);
	printf(" | Offset Fragment:");
	printf("%d\n", MID(ntohs(ipv4.flagsAndOffeset),0,12));
	printf("TTL:");
	printf("%d",  ipv4.ttl);
	printProtocol(ipv4.protocol);
	printf(" | Checksum:");
	printf("0x%x\n",  ntohs(ipv4.checksum));
	printf("Origem:");
	printIpAddr(ipv4.src);
	printf("| Destino:");
	printIpAddr(ipv4.dest);
	printf("\n");
}

void printFlags(uint16_t flags){
	printf(" | FLAGS:");
	uint16_t i = MID(ntohs(flags), 13, 15);
	if(i == 1){
		printf(" 001 (Tem Fragmentos)");
	}else if(i == 2){
		printf(" 010 (Não fragmentar)");
	}else if(i == 3){
		printf(" 011 (Não fragmentar)(Tem Fragmentos)");
	}else if(i == 0){
		printf(" 000 (Sem fragmento)");
	}
}

void printProtocol(unsigned char protocol){

	printf(" | Protocolo:");
	printf("%d ", protocol);
	if(isIpICMP(protocol)){
		printf("(ICMP)");
	}else if(isIpTCP(protocol)){
		printf("(TCP)");
	}else if(isIpUDP(protocol)){
		printf("(UDP)");
	}else if(isIpICMP6(protocol)){
		printf("(ICMP6)");
	}
}