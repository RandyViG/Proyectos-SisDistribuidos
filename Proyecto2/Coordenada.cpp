#include<iostream>
#include"Coordenada.h"

Coordenada :: Coordenada( ) {}
Coordenada :: Coordenada( float xx, float yy ) : x(xx) , y(yy) {}
Coordenada :: Coordenada( float xx, float yy, float dxx, float dyy ) : x(xx), y(yy), dx(dxx), dy(dyy) {}
float Coordenada :: getCoordenadaX( void ) { return x; }
void Coordenada :: setCoordenadas( float xx , float yy ) { x = xx; y = yy; }
float Coordenada :: getCoordenadaY( void ) { return y; }
float Coordenada :: getDx( void ){ return dx; }
float Coordenada :: getDy( void ){ return dy; }
