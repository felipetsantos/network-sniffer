/*
* IPV6 functions
*/

struct Ipv6 ipv6(unsigned char *buffer){
	struct Ipv6 ipv6;
	memcpy(&ipv6, &buffer[0], IPV6_LEN);
	return ipv6;
}


void printIpv6(struct Ipv6 ipv6){
	printf("-###IPV6###\n");
	printf("Versao:");
	uint32_t bitCorrect = ntohl(ipv6.versionAndTrafficAndFlowLabel);
	unsigned char version =  (bitCorrect) >> (28);
	printf("%d""\n",  version);
	printf("Traffic Class:");
	unsigned char trafficClass =  (bitCorrect >> 20);
	printf("%d""\n", trafficClass);
	printf("Flow Label:");
	uint32_t x = 1;
	uint32_t flowLabel =  bitCorrect;
	flowLabel = flowLabel & ~(MASK_FLOWLABEL); // 11111111111100000000000000000000 MASK para pegar os 20 bits do flow label 
	printf("0x%08x""\n", flowLabel);
	printProtocol(ipv6.nextHeader);
	printf("\n");
	printf("Hoplimit:%d\n", ipv6.hopLimit);
	printf("Origem:");
	printIpv6Addr(ipv6.src);
	printf("\n");
	printf("Destino:");
	printIpv6Addr(ipv6.dest);
	printf("\n");
}

void printIpv6Addr(struct Ipv6Addr addrIpv6){
	printf("%04x", ntohs(addrIpv6.octets[0]));
  	for(int i=1;i<8;i++){
    	printf(":%04x", ntohs(addrIpv6.octets[i]));
  	}
}