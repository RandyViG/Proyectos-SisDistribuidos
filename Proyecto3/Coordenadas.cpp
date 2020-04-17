#include <iostream>
#include <cmath>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

#include <thread>
#include <vector>
#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include <mutex>

using namespace std;

vector<int> getCoords(int * num, int iteracion , int term);
double sumatoria( double x , int termn);
int ValorY( double valor );

const double PI = 3.141516;
const double tam = PI / 200;
mutex m;
int pto = 7200;
SocketDatagrama client = SocketDatagrama( pto );

void funcion(int i){
    int num[2];
    char ip[16]= "192.168.100.23";
    vector <int> aux;
    m.lock();
    for ( int j = 1; j <= 800 ; j++){
        aux=getCoords(num,j,i);
        num[0]=aux[0];
        num[1]=aux[1];
        PaqueteDatagrama dat = PaqueteDatagrama(num, 8,ip, pto );  
        //usleep(6300);
        sleep(1);
        client.envia(dat);
    }
    m.unlock();
}

int main( int argc, char *argv[] ) {
    /*int pto = 7200,num[2];
    char ip[16]= "127.0.0.1";
    vector <int> aux;
    SocketDatagrama client = SocketDatagrama( pto );*/
    //Terminos
    for ( int i = 0 ; i <= 20 ; i++ ){
        thread th1(funcion, i),th2(funcion, i);
        th1.join();
        th2.join();
        /*for ( int j = 1; j <= 800 ; j++){
            aux=getCoords(num,j,i);
            num[0]=aux[0];
            num[1]=aux[1];
            PaqueteDatagrama dat = PaqueteDatagrama(num, 8,ip, pto );  
            usleep(2300);
            client.envia(dat);
            //sendto(s, (char *)num, 2*sizeof(int), 0, (struct sockaddr*)&msg_to_server_addr, sizeof(msg_to_server_addr));
            
        }*/
    }
    /*struct sockaddr_in msg_to_server_addr, client_addr;
    int s, res,i;
    int num[2];
    unsigned char s_addr[4];
    //Hilos
    //thread th1(funcion, 5), th2(funcion, 10);
    s = socket(AF_INET, SOCK_DGRAM, 0);
    bzero((char *)&msg_to_server_addr, sizeof(msg_to_server_addr));
    msg_to_server_addr.sin_family = AF_INET;
    msg_to_server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    msg_to_server_addr.sin_port = htons(puerto);
    
    bzero((char *)&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = INADDR_ANY;
    vector <int> aux;
    client_addr.sin_port = htons(0); //El sistema asigna el puerto
    bind(s, (struct sockaddr *)&client_addr,sizeof(client_addr));
    

    for ( int i = 0 ; i <= 20 ; i++ ){
        for ( int j = 1; j <= 800 ; j++){
            aux=getCoords(num,j,i);
            num[0]=aux[0];
            num[1]=aux[1];
            usleep(2300);
            sendto(s, (char *)num, 2*sizeof(int), 0, (struct sockaddr*)&msg_to_server_addr, sizeof(msg_to_server_addr));
            
        }
    }
   
   close(s);*/
}

int ValorY( double valor ) {
    double conver = ((150 * (valor + 1.4)) / 2.8) - 150 ;
    double coor = 150 - conver;
    return (int)coor;
}


vector<int> getCoords( int * num , int iteracion , int term){
    double x,y;
    vector<int> aux;
    x = ( (-2*PI) + (tam*iteracion) );
    if ( x > 2*PI ) 
        x = 2*PI;
    //y = (4/PI) * ( sin(x) + sumatoria(x,term));
    y= 4*(sin(x)+sumatoria(x,term));
    int yy=ValorY(y);
    aux.push_back(iteracion);
    aux.push_back(yy+150);
    //printf("Iteracion: %f , valor f: %f  y: %f\n",num[0],num[1],y);
    return aux;
}

double sumatoria( double x , int termn){
    if( termn == 0)
        return 0.0;
    double suma = 0.0, parcial, coef = 3 , argu = 3;
    for ( int i = 0; i < termn ; i++){
        parcial = ( 1 / coef ) * sin(argu*x);
        if (((int)coef%2)==0)
            parcial*-1;
        suma = suma + parcial;
        coef = coef +1 ;
        argu = argu +1;
    }
    return suma;
}

