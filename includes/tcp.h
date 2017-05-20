/*
* TCP HEADER
*/
#ifndef TCP_H_INCLUDED
#define TCP_H_INCLUDED
#define TCP_PORT_ECHO 7
#define TCP_PORT_CHARGEN 19
#define TCP_PORT_FTP_DATA 20
#define TCP_PORT_FTP_CONTROL 21
#define TCP_PORT_SSH 22
#define TCP_PORT_TELNET 23
#define TCP_PORT_SMTP 25
#define TCP_PORT_DNS 53
#define TCP_PORT_FINGER 79
#define TCP_PORT_HTTP 80
#define TCP_PORT_POP3 110
#define TCP_PORT_SUNRPC 111
#define TCP_PORT_NNTP 119
#define TCP_PORT_NETBIOS 139
#define TCP_PORT_IMAP 143
#define TCP_PORT_BGP 179
#define TCP_PORT_LDAP 389
#define TCP_PORT_HTTPS 443
#define TCP_PORT_MICROSOFT_DS 445
#define TCP_PORT_SOCKS 1080

#define TCP_LEN 20

struct Tcp {
	uint16_t src_port;			// 2 bytes - para imprimir precisa usar o  ntohs(tcp.src_port)
	uint16_t dest_port;			// 2 bytes - para imprimir precisa usar o  ntohs(tcp.dest_port)
	uint32_t seq_num;			// 4 bytes
	uint32_t ack_num;			// 4 bytes
	unsigned char offset; 			// 1 byte
	unsigned char flags; 			// 1 bytes
	uint16_t window;			// 2 bytes
	uint16_t checksum;			// 2 bytes
	uint16_t urg_point;			// 2 bytes
};

struct Tcp tcp(unsigned char * buffer);
void printTcp(struct Tcp tcp);

#endif