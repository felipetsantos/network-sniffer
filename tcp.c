/*
* TCP functions
*/

struct Tcp tcp(unsigned char * buffer){
	struct Tcp tcp;
	memcpy(&tcp, &buffer[0], TCP_LEN);
	addSendPrt(ntohs(tcp.src_port));
	addReceivPrt(ntohs(tcp.dest_port));
	return tcp;
}


int isNthBitSet (uint16_t n, int p) {
	int result = (n>>(p));
	if(result & 1){
		return 1;
	}else{
		return 0;
	}
}

const char * tcpPortStr(uint16_t port){
	switch(ntohs(port)){
		case TCP_PORT_ECHO:
			return "(ECHO)";
		case TCP_PORT_CHARGEN:
			return "(CHARGEN)";
		case TCP_PORT_FTP_DATA:
			return "(FTP-DATA)";
		case TCP_PORT_FTP_CONTROL:
			return "(FTP-CONTROL)";
		case TCP_PORT_SSH:
			return "(SSH)";
		case TCP_PORT_TELNET:
			return "(TELNET)";
		case TCP_PORT_SMTP:
			return "(SMTP)";
		case TCP_PORT_DNS:
			return "(DNS)";
		case TCP_PORT_FINGER:
			return "(FINGER)";
		case TCP_PORT_HTTP:
			return "(HTTP)";
		case TCP_PORT_POP3:
			return "(POP3)";
		case TCP_PORT_SUNRPC:
			return "(SUNRPC)";
		case TCP_PORT_NNTP:
			return "(NNTP)";
		case TCP_PORT_NETBIOS:
			return "(NETBIOS)";
		case TCP_PORT_IMAP:
			return "(IMAP)";
		case TCP_PORT_BGP:
			return "(BGP)";
		case TCP_PORT_LDAP:
			return "(LDAP)";
		case TCP_PORT_HTTPS:
			return "(HTTPS)";
		case TCP_PORT_MICROSOFT_DS:
			return "(MICROSOFT-DS)";
		case TCP_PORT_SOCKS:
			return "(SOCKS)";
	}
	return "";

}

void printTcp(struct Tcp tcp){
	printf("-###TCP###\n");
	const char* strSrcPort = tcpPortStr(tcp.src_port);
	printf("Porta de Origem: %d %s ", ntohs(tcp.src_port), strSrcPort);
	const char* strDestPort = tcpPortStr(tcp.dest_port);
	printf("| Porta de Destino: %d %s\n", ntohs(tcp.dest_port), strDestPort);
	printf("Numero de Sequencia: %" PRIu32 "\n", ntohl(tcp.seq_num));
	printf("Numero de Reconhecimento: %" PRIu32 "\n", ntohl(tcp.ack_num));
	unsigned char just_offset = tcp.offset>>4;
	printf("Tamanho Header: %d (%d bytes)\n", just_offset,(4*just_offset));
	printf("flags:\n");
	printf("| Reservada: %03d\n",MID(tcp.offset,4,6));
	printf("| NS: %d\n",isNthBitSet(tcp.offset,8));
	printf("| CWR: %d\n",isNthBitSet(tcp.flags,1));
	printf("| ECE: %d\n",isNthBitSet(tcp.flags,2));
	printf("| URG: %d\n",isNthBitSet(tcp.flags,3));
	printf("| ACK: %d\n",isNthBitSet(tcp.flags,4));
	printf("| PSH: %d\n",isNthBitSet(tcp.flags,5));
	printf("| RST: %d\n",isNthBitSet(tcp.flags,6));
	printf("| SYN: %d\n",isNthBitSet(tcp.flags,7));
	printf("| FIN: %d\n",isNthBitSet(tcp.flags,8));
	printf("Window: %d\n", ntohs(tcp.window));
	printf("Checksum: 0x%x\n", ntohs(tcp.checksum));
	printf("Urgent Point: 0x%x\n", ntohs(tcp.urg_point));
}