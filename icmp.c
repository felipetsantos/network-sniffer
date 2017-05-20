/*
* ICMP functions
*/

struct Icmp icmp(unsigned char * buffer){
	struct Icmp icmp;
	memcpy(&icmp, &buffer[0], ICMP_LEN);
	return icmp;
}

const char * icmpTypeStr(unsigned char type){
	switch(type){
		case ICMP_TYPE_ECHO_REPLY:
			return "ECHO REPLY";
		case ICMP_TYPE_ECHO_REQUEST:
			return "ECHO REQUEST";
		case ICMP_TYPE_DESTINATION_UNREACHABLE:
			return "DESTINATION UNREACHABLE";
		case ICMP_TYPE_TIME_EXCEEDED:
			return "TIME EXCEEDED";
		case ICMP_TYPE_TRACEROUTE:
			return "TRACEROUTE";
	}
	return "";

}

void printIcmp(struct Icmp icmp){
	const char * strType = icmpTypeStr(icmp.type);
	printf("-###ICMP###\n");
	printf("Tipo: %d ( %s )\n",  icmp.type, strType);
	printf("Codigo: %d\n",  icmp.code);
	printf("Checksum: 0x%x\n",  ntohs(icmp.checksum));
}
