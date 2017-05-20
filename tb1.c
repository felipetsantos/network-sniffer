#include <poll.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <ifaddrs.h>
/* Diretorios: net, netinet, linux contem os includes que descrevem */
/* as estruturas de dados do header dos protocolos   	  	        */

#include <net/if.h>  //estrutura ifr
#include <netinet/ether.h> //header ethernet
#include <netinet/in.h> //definicao de protocolos
#include <arpa/inet.h> //funcoes para manipulacao de enderecos IP

#include <netinet/in_systm.h> //tipos de dados

#include "includes/tb1.h"
#include "includes/ethernet.h"
#include "includes/icmp.h"
#include "includes/ipv4.h"
#include "includes/arp.h"
#include "includes/udp.h"
#include "includes/tcp.h"
#include "includes/ipv6.h"
#include "includes/icmp6.h"
#include "includes/statistics.h"

#include "ipv4.c"
#include "ethernet.c"
#include "udp.c"
#include "tcp.c"
#include "arp.c"
#include "icmp.c"
#include "ipv6.c"
#include "icmp6.c"
#include "statistics.c"



unsigned char buff1[BUFFSIZE]; // buffer de recepcao
int sockd;
int on;
struct ifreq ifr;
char * inferfaces[30];
int nInterface = 0;
char * interfaceSelected;


// Atencao!! Confira no /usr/include do seu sisop o nome correto
// das estruturas de dados dos protocolos.
int main(int argc,char *argv[])
{
	
  if((sockd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
     printf("Erro na criacao do socket.\n");
     exit(1);
  }
  
  showNetInterfaces();
  selectInterface(argc,argv);
  printf("\n\n##Interface selecionada: %s\n", interfaceSelected);

	// O procedimento abaixo eh utilizado para "setar" a interface em modo promiscuo
	strcpy(ifr.ifr_name, interfaceSelected);
	if(ioctl(sockd, SIOCGIFINDEX, &ifr) < 0)
		printf("erro no ioctl!");
	ioctl(sockd, SIOCGIFFLAGS, &ifr);
	ifr.ifr_flags |= IFF_PROMISC;
	ioctl(sockd, SIOCSIFFLAGS, &ifr);

  struct pollfd pfd;
  int s;

  pfd.fd = fileno(stdin);
  pfd.events = POLLRDNORM;
  initCounters();
  while ((s = poll(&pfd, 1, 0)) == 0) {
      printf("----------------------------------------------------------\n");
   		recv(sockd,(char *) &buff1, sizeof(buff1), 0x0);
   		struct Ethernet frameEth;

   		frameEth = ethernet(&buff1[0]);
      printEthernet(frameEth);
   		
      if(isIPV4(frameEth.type)){
        struct Ipv4 frameIpv4;
   			frameIpv4 = ipv4(&buff1[ETHERNET_LEN]);
   			printIpv4(frameIpv4);
        counters.countIpv4++;
        counters.total++;
        afterIp(&buff1[0], frameIpv4.protocol, ETHERNET_LEN+IPV4_LEN);
        
   		}else if(isIPV6(frameEth.type)){

        struct Ipv6 frameIpv6;
        frameIpv6 = ipv6(&buff1[ETHERNET_LEN]);
        printIpv6(frameIpv6);
        counters.countIpv6++;
        counters.total++;
        afterIp(&buff1[0], frameIpv6.nextHeader, ETHERNET_LEN+IPV6_LEN);


   		}else if(isARP(frameEth.type)){

        struct Arp frameArp;
        frameArp = arp(&buff1[ETHERNET_LEN]);
        counters.countArp++;
        counters.total++;
        printArp(frameArp);

   		}else{
   			printf("Tipo do pacote não implementado.\n");
   		}
      printf("----------------------------------------------------------\n");
      printf("PARA ENCERRAR TECLE [ENTER]\n\n");
	}

  printStatistics();
}


void afterIp(unsigned char *buffer, unsigned char protocol,int len){

      if(isIpUDP(protocol)){

        struct Udp frameUdp;
        frameUdp = udp(&buff1[len]);
        counters.countUdp++;
        counters.total++;
        printUdp(frameUdp);

      }else if(isIpICMP(protocol)){

        struct Icmp frameIcmp;
        frameIcmp = icmp(&buff1[len]);
        counters.countIcmp++;
        counters.total++;
        printIcmp(frameIcmp);

      }else if(isIpTCP(protocol)){

        struct Tcp frameTcp;
        frameTcp = tcp(&buff1[len]);
        counters.countTcp++;
        counters.total++;
        printTcp(frameTcp);

      }else if(isIpICMP6(protocol)){

        struct Icmp6 frameIcmp6;
        frameIcmp6 = icmp6(&buff1[len]);
        counters.countIcmp6++;
        counters.total++;
        printIcmp6(frameIcmp6);

      }

}

  /* Metodos comuns entre as estruturas */
void printMac(unsigned char *mac){
  printf("%02x", mac[0]);
  for(int i=1;i<6;i++){
    printf(":%02x", mac[i]);
  }
}
  
void printIpAddr(unsigned char * ipAddr){
  printf("%d.%d.%d.%d", ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]);
}

int isIpICMP(unsigned char protocol){
  if(protocol == IP_PROTOCOL_ICMP){
    return 1;
  }else{
    return 0;
  }
}

int isIpTCP(unsigned char protocol){
  if(protocol == IP_PROTOCOL_TCP){
    return 1;
  }else{
    return 0;
  }
}

int isIpUDP(unsigned char protocol){
  if(protocol == IP_PROTOCOL_UDP){
    return 1;
  }else{
    return 0;
  }
}

int isIpICMP6(unsigned char protocol){
  if(protocol == IP_PROTOCOL_ICMP6){
    return 1;
  }else{
    return 0;
  }
}

char * showNetInterfaces(){
  struct ifaddrs *addrs,*tmp;
  
  getifaddrs(&addrs);
  tmp = addrs;
  printf("\nInterfaces disponiveis:\n");
  while (tmp)
  {
      if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_PACKET){
          inferfaces[nInterface] = tmp->ifa_name;
          printf("  %d - %s\n", nInterface+1, tmp->ifa_name);
          nInterface++;
      }
      tmp = tmp->ifa_next;
  
  }
  freeifaddrs(addrs);
}

void selectInterface(int argc, char *argv[]){

   if(nInterface > 0){
    if(argc > 1){
      interfaceSelected = inferfaces[atoi(argv[1])-1];
      return;
    }
    int op;
    int ivalid = 0;
    do{
      printf("\nDigite o numero da interface: ");
      scanf("%d", &op);
      if(op < 1 || op > nInterface){
        printf("Opcao invalida. Digite o numero de acordo com o menu.");
        ivalid = 1;
      }
    }while(ivalid);
    interfaceSelected = inferfaces[op-1];
  }else{
     printf("Nenhuma interface de rede disponivel.\n");
     exit(1);
  } 
}

