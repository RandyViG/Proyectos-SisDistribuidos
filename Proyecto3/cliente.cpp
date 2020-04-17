#include "Solicitud.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <thread>
#include <mutex>

using namespace std;

const double PI = 3.141516;
const double tam = PI / 160;
mutex m;
int pto = 7200;

void getCoords(int * num, int iteracion , int term);
double sumatoria( double x , int termn);
int ValorY( double valor );

void funcion(int i){
    int num[2],resultado;
    char ip[16]= "192.168.100.23";
    //char ip[16]= "127.0.0.1";
    Solicitud sol;
    m.lock();
    for ( int j = 1; j <= 800 ; j++){
        getCoords(num,j,i);
        printf("x: %d Y: %d\n",num[0],num[1]);
        memcpy(&resultado,sol.doOperation( ip , pto , 1 ,(char*)&num ),4);
    }
    m.unlock();
}

int main(int argc, char* argv[]){
    for ( int i = 0 ; i <= 20 ; i++ ){
        thread th1(funcion, i),th2(funcion, i);
        th1.join();
        th2.join();
    }
    return 0;
}

int ValorY( double valor ) {
    double conver = ((100 * (valor + 1.4)) / 2.8) - 150 ;
    double coor = 150 - conver;
    return (int)coor;
}


void getCoords( int * num , int iteracion , int term){
    double x,y;
    x = ( (PI) + (tam*iteracion) );
    y= 2*(sin(x)+sumatoria(x,term));
    int yy=ValorY(y);
    num[0] = iteracion;
    num[1] = yy;
}

double sumatoria( double x , int termn){
    if( termn == 0)
        return 0.0;
    double suma = 0.0, parcial, aux = 2;
    for ( int i = 0; i < termn ; i++){
        parcial = ( 1 / aux ) * sin(aux*x);
        if (((int)aux%2)==0) 
            parcial*=-1;  
        suma += parcial;
        aux+=1;
    }
    return suma;
}
