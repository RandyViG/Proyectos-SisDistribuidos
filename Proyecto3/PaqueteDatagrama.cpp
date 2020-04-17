#include "PaqueteDatagrama.h"
#include <iostream>
#include <string.h>

using namespace std;
PaqueteDatagrama::PaqueteDatagrama(int *d, unsigned int t, char *i, int p){
    datos= new int[t];
    memcpy(datos, d, t);
    longitud=t;
    memcpy(ip, i, 16);
    puerto=p;
}

PaqueteDatagrama::PaqueteDatagrama(unsigned int t){
    datos= new int[t];
    longitud=t;

}
PaqueteDatagrama::~PaqueteDatagrama(){
    delete[] datos;
    longitud = 0;
    puerto = 0;
}

char * PaqueteDatagrama::obtieneDireccion(){
    return ip;
}

unsigned int PaqueteDatagrama::obtieneLongitud(){
    return longitud;
}

int PaqueteDatagrama::obtienePuerto(){
    return puerto;
}

int * PaqueteDatagrama::obtieneDatos(){
    return datos;
}

void PaqueteDatagrama::inicializaPuerto(int p){
    puerto=p;
}

void PaqueteDatagrama::inicializaIp(char * i){
    memcpy(ip, i, 16);
}

void PaqueteDatagrama::inicializaDatos(char * d){
    memcpy(datos,d,longitud);
}