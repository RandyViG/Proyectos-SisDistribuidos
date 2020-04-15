#include <iostream>
#include "Asteroide.h"
#include "gfx.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>

#define PI 3.1415926535

using namespace std;

Asteroide :: Asteroide( void ) {}

Asteroide :: Asteroide( Coordenada c , int s) : size(s),center(c) {
    corner = 8 + rand() % 14;
}
vector<Coordenada> Asteroide :: getCords( void ){ return coords; }

int Asteroide :: getCorner( void ){ return corner; }

void Asteroide :: makeAsteroide() {
    float x,y,dx,dy;
    rad = 2 * PI / corner;
    for ( int i=0 ; i < corner ; i++ ){
        dx = rand() % size/3;
        dy = rand() % size/4;
        x = ( center.getCoordenadaX() + size * cos(rad*i) ) + dx;
        y = ( center.getCoordenadaY() + size * sin(rad*i) ) + dy;
        coords.push_back( Coordenada(x,y,dx,dy) );     
    }
}

void Asteroide :: drawAsteroide( ){
    if ( (positionX*dirX*speed)+coords[0].getCoordenadaX() > 800 || (positionX*dirX*speed)+coords[0].getCoordenadaX() < 0 ) 
        positionX = 0;
    else
        positionX++;
    if ( ( positionY*dirY*speed)+coords[0].getCoordenadaY() > 600 || ( positionY*dirY*speed)+coords[0].getCoordenadaY() < 0 )
        positionY = 0;
    else
        positionY++;
    dirX = (dirX==0 && dirY==0) ? 1 : dirX;
    for(int i = 0 ; i < corner ; i++)
        gfx_line( ( positionX*dirX*speed)+coords[i].getCoordenadaX() , ( positionY*dirY*speed)+coords[i].getCoordenadaY(), ( positionX*dirX*speed)+coords[ (i+1) % corner ].getCoordenadaX(), ( positionY*dirY*speed)+coords[ (i+1) % corner ].getCoordenadaY() );
}

void Asteroide :: setDirection( void ){
    int direction[]={-1,1,0},d;
    d = rand() % 3;
    dirX = direction[d];
    d = rand() % 3;
    dirY = direction[d];
}

void Asteroide :: setSpeed( void ){
    if( size < 20 )
        speed = 5;
    else if ( size < 30)
        speed = 4;
    else if ( size < 40 )
        speed = 3;
    else if ( size < 50)
        speed = 2;
    else
        speed = 1;
}

void Asteroide :: rotation( int t ){
    float x1,y1,dx,dy;
    float newAngule;
    vector <Coordenada> aux;
    newAngule = t%360 * PI / 180;
    for( int i = 0; i < corner ; i++ ){
        dx = coords[i].getDx();
        dy = coords[i].getDy();
        x1 =  center.getCoordenadaX() + size * cos( (rad*i) + (newAngule) )  + dx;
        y1 =  center.getCoordenadaY() + size * sin( (rad*i) + (newAngule) ) + dy;
        aux.push_back( Coordenada(x1,y1,dx,dy) );
    }
    for( int i = 0 ; i < corner ; i++ ){
        coords[i] = aux[i];
    }
}
