#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
using namespace std;

SocketDatagrama::SocketDatagrama(int p){
        s = socket(AF_INET, SOCK_DGRAM, 0);
    
        bzero((char *)&direccionLocal, sizeof(direccionLocal));
		bzero((char *)&direccionForanea, sizeof(direccionForanea));
        direccionLocal.sin_family = AF_INET;
        direccionLocal.sin_addr.s_addr = INADDR_ANY;
        direccionLocal.sin_port = htons(p);
        
        bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal));
    
}

SocketDatagrama::~SocketDatagrama(){
    close(s);
}

int SocketDatagrama::envia(PaqueteDatagrama &p){
    
    direccionForanea.sin_family = AF_INET;
    direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
   	direccionForanea.sin_port = htons( p.obtienePuerto() );
    return sendto(s, (int *)p.obtieneDatos(), p.obtieneLongitud() * sizeof(int), 0, (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));
}

int SocketDatagrama::recibe(PaqueteDatagrama &p){
    unsigned int len = sizeof(direccionForanea);
	int rec = recvfrom(s, (char *)p.obtieneDatos(), p.obtieneLongitud() * sizeof(char), 0, (struct sockaddr *) &direccionForanea, &len);
	unsigned char ip[4];
	char dirIp[16];
	memcpy(ip, &direccionForanea.sin_addr.s_addr, 4);

	string ip1 = to_string(ip[0]);
	string ip2 = to_string(ip[1]);
	string ip3 = to_string(ip[2]);
	string ip4 = to_string(ip[3]);

	ip1.append(".");
	ip1.append(ip2);
	ip1.append(".");
	ip1.append(ip3);
	ip1.append(".");
	ip1.append(ip4);
	strcpy(dirIp, ip1.c_str());

	p.inicializaIp(dirIp);
	p.inicializaPuerto( ntohs(direccionForanea.sin_port) );
	return rec;
}

