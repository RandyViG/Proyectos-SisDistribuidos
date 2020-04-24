#include <iostream>
#include <cstring>
#include "SocketMulticast.h"

using namespace std;

int main(int argc, char* argv[]){
    if(argc != 5) {
		printf("Uso: %s IP_Multicast puerto n TTL\n", argv[0]);
		exit(0);
	}
    int num, resultado, cuenta = 0 , duplicado, ttl ,port;
    char pesos;
    port= atoi(argv[2]);
    num = atoi( argv[3] );
    ttl = atoi( argv[4] );
    SocketMulticast s(port);
    srand(time(NULL));
    for (int i = 0; i < num ; i++){
        pesos = 1 + rand()%9 ;
        PaqueteDatagrama enviar( &pesos , sizeof(pesos), argv[1] , port );
        duplicado = s.enviaConfiable( enviar , ttl , 1 );
        while( duplicado == -1){
            duplicado = s.enviaConfiable(enviar , ttl , 1 );
        }
        cuenta += pesos;
        printf("Cuenta local %d\n",cuenta);
    }
}