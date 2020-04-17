#include <iostream>
#include <cstring>
#include "Solicitud.h"
#include "mensaje.h"

#define SEGUNDOS 2
#define MICROSEGUNDOS 500000
using namespace std;

Solicitud :: Solicitud (){
    socketlocal = new SocketDatagrama( 0 );
}

int * Solicitud :: doOperation( char *IP, int puerto, int operationId, char *arguments ){
    
    struct mensaje datos,respuesta;
    int *aux;
    int i,n;
    datos.messageType = 0;
    datos.operationId = operationId;
    datos.requestId = id++;
    memcpy( datos.arguments ,arguments , sizeof(arguments) );
    printf("id %d Env x: %d , Env y: %d\n",id,datos.arguments[0],datos.arguments[1]);
    PaqueteDatagrama dat = PaqueteDatagrama( (char *)&datos, sizeof(datos), IP ,puerto );
    PaqueteDatagrama paqdata = PaqueteDatagrama( sizeof(respuesta) );
    for(i=0; i < 20 ; i++){
        socketlocal->envia(dat);
        n = socketlocal->recibeTimeout(paqdata,SEGUNDOS,MICROSEGUNDOS);
        if ( n != -1){
            memcpy(&respuesta, paqdata.obtieneDatos(), sizeof(respuesta) );
            if( respuesta.requestId < id )
                continue;
            aux = respuesta.arguments;
            printf("Exito\n");
            return aux;
        }
    }
    printf("\n *** Servidor No Disponible, Intente Mas Tarde ***\n");
    exit(-1);
}
