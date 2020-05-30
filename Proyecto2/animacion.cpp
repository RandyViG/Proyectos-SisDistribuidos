#include "gfx.h"
#include "Asteroide.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main( int argc , char * argv[] ){
    if( argc < 2 ){
        printf("Error Uso: %s n\n",argv[0]);
        exit(-1);
    }
    int t,s,n;
    float x,y;
    n = atoi(argv[1]);
    gfx_open(800, 600, "Animacion GFX Asteroides");
    gfx_color(19,196,236);
    Asteroide asteroides[n];
    srand(time(NULL));

    for(int i = 0 ; i < n ; i++ ){
        x = rand() % 700;
        y = rand() % 500;
        s = 10 + rand() % 60;
        Asteroide aux( Coordenada(x,y) , s );
        asteroides[i] = aux;
        asteroides[i].makeAsteroide();
        asteroides[i].setDirection();
        asteroides[i].setSpeed();     
    }
    for(t = 0 ; t < 800 ; t++ ){
        gfx_clear();
        for(int i = 1; i < n ; i++){
            asteroides[i].drawAsteroide( );
            asteroides[i].rotation( t );
        }
        gfx_flush();
        usleep(41666); //24 por segundo
    }
    return 0;
}