#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <cmath>
#include "gfx.h"

using namespace std;

#define PI 3.1415926535

class Coordenada{
    private:
        float x;
        float y;
        float dx;
        float dy;
    public:
        Coordenada();
        Coordenada( float , float );
        Coordenada( float , float , float , float );
        float getCoordenadaX( void );
        void setCoordenadas( float , float );
        float getCoordenadaY( void );
        float getDx( void );
        float getDy( void );
};

class Asteroide{
        private:
            int size;
            int positionX = 0;
            int positionY = 0;
            int corner;
            int dirX;
            int dirY;
            int speed;
            float rad;
            Coordenada center;
            vector <Coordenada> coords;

        public:
            Asteroide( void );
            Asteroide( Coordenada , int );
            void makeAsteroide( void );
            vector<Coordenada> getCords( void );
            int getCorner( void );
            void drawAsteroide( );
            void setDirection( void );
            void rotation( int );
            void setSpeed( void );
            
    };

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

Coordenada :: Coordenada( ) {}

Coordenada :: Coordenada( float xx, float yy ) : x(xx) , y(yy) {}

Coordenada :: Coordenada( float xx, float yy, float dxx, float dyy ) : x(xx), y(yy), dx(dxx), dy(dyy) {}

float Coordenada :: getCoordenadaX( void ) { return x; }

void Coordenada :: setCoordenadas( float xx , float yy ) { x = xx; y = yy; }

float Coordenada :: getCoordenadaY( void ) { return y; }

float Coordenada :: getDx( void ){ return dx; }

float Coordenada :: getDy( void ){ return dy; }