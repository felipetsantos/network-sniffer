void cleanMem(){

	free(srcAccesses);
	free(destAccesses);
	free(sendPrt);
	free(receivPrt);

}

void sortAccesses(){
	
	qsort(srcAccesses, countSrcIp, sizeof(struct IpAccesses), cmpfuncIp);
	qsort(destAccesses, countDestIp, sizeof(struct IpAccesses), cmpfuncIp);

	qsort(sendPrt, countSendPrt, sizeof(struct PrtAccesses), cmpfuncPrt);
	qsort(receivPrt, countReceivPrt, sizeof(struct PrtAccesses), cmpfuncPrt);

}

void initCounters(){

	counters.total = 0;
	counters.countArp = 0;
	counters.countIpv4 = 0;
	counters.countIpv6 = 0;
	counters.countIcmp = 0;
	counters.countIcmp6 = 0;
	counters.countTcp = 0;
	counters.countUdp = 0;

	srcAccesses = malloc(IP_ACCESS_MAX * sizeof(struct IpAccesses));
	destAccesses = malloc(IP_ACCESS_MAX * sizeof(struct IpAccesses));

	sendPrt = malloc(PRT_ACCESS_MAX * sizeof(struct PrtAccesses));
	receivPrt = malloc(PRT_ACCESS_MAX * sizeof(struct PrtAccesses));
	
}

void printStatistics(){
	printf("Total de pacotes capturados:%d\n",counters.total);
	printf("%% de pacotes ARP: %%%.2f\n", calcPercent(counters.countArp));
	printf("%% de pacotes IPV4: %%%.2f\n", calcPercent(counters.countIpv4));
	printf("%% de pacotes IPV6: %%%.2f\n", calcPercent(counters.countIpv6));
	printf("%% de pacotes ICMP: %%%.2f\n", calcPercent(counters.countIcmp));
	printf("%% de pacotes ICMP6: %%%.2f\n", calcPercent(counters.countIcmp6));
	printf("%% de pacotes TCP: %%%.2f\n", calcPercent(counters.countTcp));
	printf("%% de pacotes UDP: %%%.2f\n", calcPercent(counters.countUdp));
	
	sortAccesses();
	
	printf("Protocolo de aplicacao mais usado nas transmissoes: ");
	const char * prtSendStr = getAppProtocolStr(sendPrt[0].prtType);
	printf("%s (%d)\n", prtSendStr, sendPrt[0].accesses);
	
	printf("Protocolo de aplicacao mais usado nas recepcoes: ");
	const char * prtReceivStr = getAppProtocolStr(sendPrt[0].prtType);
	printf("%s (%d)\n", prtReceivStr, receivPrt[0].accesses);
	
	printf("Endereco IP que mais recebeu pacotes : ");
	printIpAddr(destAccesses[0].addr);
	printf("(%d)\n", destAccesses[0].accesses);
	
	printf("Endereco IP da maquina que mais transmitiu pacotes : ");
	printIpAddr(srcAccesses[0].addr);
	printf("(%d)\n", srcAccesses[0].accesses);
}

float calcPercent(int value){
	return (float)((value*100)/counters.total);
}

//# Protocol accesses
const char * getAppProtocolStr(uint16_t protocol){

	switch(protocol){
		// SMTP
		case APP_SMTP:
			return "SMTP";
		// POP
		case APP_POP:
			return "POP3";
		// IMAP
		case APP_IMAP:
			return "IMAP";
		// DNS 
 		case APP_DNS:
			return "DNS";
		// FINGER
		case APP_FINGER:
			return "FINGER";
		// HTTP
		case APP_HTTP:
			return "HTTP";
		// HTTPS
		case  APP_HTTPS:
			return "HTTPS";
		// FTP
		case APP_FTP:
			return "FTP";
		// SSH
		case APP_SSH:
			return "SSH";
		// TELNET
		case APP_TELNET:
			return "TELNET";
		// APP_NNTP
		case APP_NNTP:
			return "NNTP";
		// LDAP
		case APP_LDAP:
			return "LDAP";
		// BOOTP
		case APP_BOOTP:
			return "BOOTP";
		// TFTP
		case APP_TFTP:
			return "TFTP";
		// SNMP
		case APP_SNMP:
			return "SNMP";
	}
	return "";
}

uint16_t getProtocolId(uint16_t protocol){

	switch(protocol){
		// SMTP
		case APP_SMTP:
		case APP_SMTP1: 
		case APP_SMTP2: 
		case APP_SMTP3: 
		case APP_SMTP4:
			return APP_SMTP;
		// POP
		case APP_POP:
			return APP_POP;
		// IMAP
		case APP_IMAP:
		case APP_IMAP1:
			return APP_IMAP;
		// DNS 
 		case APP_DNS:
			return APP_DNS;
		// FINGER
		case APP_FINGER:
			return APP_FINGER;
		// HTTP
		case APP_HTTP:
			return APP_HTTP;
		// HTTPS
		case  APP_HTTPS:
			return APP_HTTPS;
		// FTP
		case APP_FTP:
		case APP_FTP1_DATA:
			return APP_FTP;
		// SSH
		case APP_SSH:
			return APP_SSH;
		// TELNET
		case APP_TELNET:
			return APP_TELNET;
		// APP_NNTP
		case APP_NNTP:
			return APP_NNTP;
		// LDAP
		case APP_LDAP:
			return APP_LDAP;
		// BOOTP
		case APP_BOOTP:
		case APP_BOOTP1:
			return APP_BOOTP;
		// TFTP
		case APP_TFTP:
			return APP_TFTP;
		// SNMP
		case APP_SNMP:
		case APP_SNMP1:
			return APP_SNMP;
	}
	return 0;
}
void genericAddPrt(uint16_t unifyPrt, int * countPrt, struct PrtAccesses *accesses, int *blocks){

	int p = (*countPrt);
	for(int i=0;i<(*countPrt);i++){
		if(unifyPrt == accesses[i].prtType){
			p = i;
			break;
		}
	}

	// if protocol exceed accesses limit, the memory will be realloc to store more protocols. It still have to be reviewed
	if((*countPrt) >= (*blocks)*PRT_ACCESS_MAX){
		(*blocks)++;
		accesses = (struct PrtAccesses*) realloc(accesses, (*blocks)*PRT_ACCESS_MAX);
	}

	if(p == (*countPrt)){
		struct PrtAccesses prtAccesses;
		accesses[p] = prtAccesses;
		accesses[p].prtType = unifyPrt;
		accesses[p].accesses = 1;
		(*countPrt)++;
	}else{
		accesses[p].accesses++;
	}

}
void addSendPrt(uint16_t protocol){
	uint16_t unifyPrt;
	// call unify protocol
	unifyPrt =  getProtocolId(protocol);
	if(unifyPrt != 0){
		genericAddPrt(unifyPrt, &countSendPrt, sendPrt, &sendPrtBlocks);
	}
}

void addReceivPrt(uint16_t protocol){
	uint16_t unifyPrt;
	// call unify protocol
	unifyPrt =  getProtocolId(protocol);
	if(unifyPrt != 0){
		genericAddPrt(unifyPrt, &countReceivPrt, receivPrt, &receivPrtBlocks);
	}
}

int cmpfuncPrt (const void * a, const void * b){
   struct PrtAccesses  *ia  = (struct PrtAccesses *)a;
   struct PrtAccesses  *ib  = (struct PrtAccesses *)b;
   return ( ib->accesses- ia->accesses  );
}
//# IP accesses
int ipsAreEquals(unsigned char addr1[4], unsigned char addr2[4]){
	int r = 1;
	for(int i=0; i< 4;i++){
		if(addr1[i] != addr2[i]){
			return 0;
		}
	}

	return r;
}

void genericAddIp(unsigned char addr[4], int * countIp, struct IpAccesses *accesses, int *blocks){

	int p = (*countIp);
	for(int i=0;i<(*countIp);i++){
		if(ipsAreEquals(addr, accesses[i].addr)){

			p = i;
			break;
		}
	}

	// if ip exceed access limit, the memory will be realloc to store more ips. It still have to be reviewed
	if((*countIp) >= (*blocks)*IP_ACCESS_MAX){
		(*blocks)++;
		accesses = (struct IpAccesses*) realloc(accesses, (*blocks)*IP_ACCESS_MAX);
	}

	if(p == (*countIp)){
		struct IpAccesses ipAccesses;
		accesses[p] = ipAccesses;
		accesses[p].addr[0] = addr[0];
		accesses[p].addr[1] = addr[1];
		accesses[p].addr[2] = addr[2];
		accesses[p].addr[3] = addr[3];
		accesses[p].accesses = 1;
		(*countIp)++;
	}else{
		printf("ip:%d\n", addr[0]);
		accesses[p].accesses++;
	}

}

void addSrcIp(unsigned char addr[4]){
	genericAddIp(addr, &countSrcIp, srcAccesses, &srcIpBlocks);
}

void addDestIp(unsigned char addr[4]){
	genericAddIp(addr, &countDestIp, destAccesses, &destIpBlocks);
}

int cmpfuncIp (const void * a, const void * b){
   struct IpAccesses  *ia  = (struct IpAccesses *)a;
   struct IpAccesses  *ib  = (struct IpAccesses *)b;
   return ( ib->accesses- ia->accesses  );
}