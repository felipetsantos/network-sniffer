/*
* ICMP6 functions
*/

struct Icmp6 icmp6(unsigned char * buffer){
	struct Icmp6 icmp6;
	memcpy(&icmp6, &buffer[0], ICMP6_LEN);
	return icmp6;
}

const char * icmp6TypeStr(unsigned char type){
	switch(type){
		case ICMP6_TYPE_ECHO_REPLY:
			return "ECHO REPLY";
		case ICMP6_TYPE_ECHO_REQUEST:
			return "ECHO REQUEST";
		case ICMP6_TYPE_DESTINATION_UNREACHABLE:
			return "DESTINATION UNREACHABLE";
		case ICMP6_TYPE_TIME_EXCEEDED:
			return "TIME EXCEEDED";
		case ICMP_TYPE_TRACEROUTE:
			return "TRACEROUTE";
	}
	return "";

}

void printIcmp6(struct Icmp6 icmp6){
	const char * strType = icmp6TypeStr(icmp6.type);
	printf("-###ICMP###\n");
	printf("Tipo: %d (%s)\n",  icmp6.type, strType);
	printf("Codigo: %d\n",  icmp6.code);
	printf("Checksum: 0x%x\n",  ntohs(icmp6.checksum));

}