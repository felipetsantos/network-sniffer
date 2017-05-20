/*
* UDP functions
*/

struct Udp udp(unsigned char * buffer){
	struct Udp udp;
	memcpy(&udp, &buffer[0], UDP_LEN);
	addSendPrt(ntohs(udp.srcPort));
	addReceivPrt(ntohs(udp.destPort));
	return udp;
}

const char * udpPortStr(uint16_t port){
	switch(ntohs(port)){
		case UDP_PORT_ECHO:
			return "(ECHO)";
		case UDP_PORT_CHARGEN:
			return "(CHARGEN)";
		case UDP_PORT_TIME:
			return "(TIME)";
		case UDP_PORT_DNS:
			return "(DNS)";
		case UDP_PORT_BOOTPS:
			return "(BOOTPS)";
		case UDP_PORT_BOOTPC:
			return "(BOOTPC)";
		case UDP_PORT_TFTP:
			return "(TFTP)";
		case UDP_PORT_NETBIOS_NS:
			return "(NETBIOS-NS)";
		case UDP_PORT_NETBIOS_DGM:
			return "(NETBIOS-DGM)";
		case UDP_PORT_SNMP:
			return "(SNMP)";
		case UDP_PORT_SNMP_TRAP:
			return "(SNMP-TRAP)";
		case UDP_PORT_ISAKMP:
			return "(ISAKMP)";
		case UDP_PORT_SYSLOG:
			return "(SYSLOG)";
		case UDP_PORT_RIP:
			return "(RIP)";
		case UDP_PORT_TRACEROUTE:
			return "(TRACEROUTE)";
	}
	return "";

}

void printUdp(struct Udp udp){
	printf("-###UDP###\n");
	const char* strSrcPort = udpPortStr(udp.srcPort);
	printf("Porta de Origem: %d %s",  ntohs(udp.srcPort), strSrcPort);
	const char* strDestPort = udpPortStr(udp.destPort);
	printf("| Porta de Destino: %d %s\n",  ntohs(udp.destPort), strDestPort);
	printf("Tamanho: %d",  ntohs(udp.len));
	printf("| Checksum: 0x%x\n",  ntohs(udp.checksum));
}