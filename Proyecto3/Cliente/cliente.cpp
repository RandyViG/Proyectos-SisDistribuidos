#include "Solicitud.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <cmath>
#include <mutex>

using namespace std;

const double PI = 3.141592653589;
const double periodos = PI / 160;
char ip[16]= "127.0.0.1";
mutex m;
int pto = 7200;

void graficar( int i );
int escala( double y );
void calcularCoordenadas(int * coordenada, int iteracion , int termino);
double serieFourier( double x , int termino);

int main( void ){
    for ( int i = 0 ; 1 ; i++ ){
        thread dibujar(graficar, i),borrar(graficar, i);
        dibujar.join(); borrar.join();
    }
    return 0;
}

void graficar(int i){
    int coordenada[2],result;
    Solicitud sol;
    m.lock();
    for ( int j = 1; j <= 800 ; j++){
        calcularCoordenadas(coordenada,j,i);
        memcpy(&result,sol.doOperation( ip , pto , 1 ,(char*)&coordenada ),4);
        usleep(1500);
    }
    m.unlock();
}

int escala( double y ) {
    double coord = 300 - (40*y) ;
    return (int)coord;
}

void calcularCoordenadas( int * coordenada , int iteracion , int termino){
    double x,y;
    x = ( (PI) + ( periodos * iteracion ) );
    y = 2 * ( sin(x) + serieFourier(x,termino) );
    coordenada[0] = iteracion;
    coordenada[1] = escala(y);
}

// Onda en Diente de Sierra
double serieFourier( double x , int termino){
    double suma = 0.0, parcial, aux = 2;
    for ( int i = 0; i < termino ; i++){
        parcial = ( 1 / aux ) * sin(aux*x);
        if ( (int)aux % 2 == 0 ) 
            parcial *= -1;  
        suma += parcial;
        aux +=1 ;
    }
    return suma;
}
