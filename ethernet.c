/*
* Ethernet functions
*/

struct Ethernet ethernet(unsigned char *buffer){
	struct Ethernet ethernet;
	memcpy(&ethernet, &buffer[0], ETHERNET_LEN);
	return ethernet;
}

void printEthernet(struct Ethernet ethernet){
	printf("-###ETHERNET###\n");
	printf("MAC Destino:");
	printMac(ethernet.dest);
	printf("| MAC Origem:");
	printMac(ethernet.src);
	printf("\n");
	printEthernetType(ethernet.type);
}

void printEthernetType(u_short type){
	const char* strType;
	printf("Tipo: ");
	strType = ethernetTypeToStr(type);
	printf("0x%04x", ntohs(type));
	printf(" (%s)\n", strType);
}


int isIPV4(u_short type){
	if(ntohs(type) == ETHERNET_TYPE_IPV4){
		return 1;
	}else{
		return 0;
	}
}

int isIPV6(u_short type){
	if(ntohs (type) == ETHERNET_TYPE_IPV6){
		return 1;
	}else{
		return 0;
	}
}

int isARP(u_short type){
	if(ntohs (type) == ETHERNET_TYPE_ARP){
		return 1;
	}else{
		return 0;
	}
}

const char * ethernetTypeToStr(u_short type){
	if(isIPV4(type)){
		return "IPV4";
	}else if(isIPV6(type)){
		return "IPV6";
	}else if(isARP(type)){
		return "ARP";
	}else{
		return "Desconhecido";
	}
}