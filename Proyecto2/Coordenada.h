#ifndef __COORDENADA_H__
#define __COORDENADA_H__

#include<iostream>

using namespace std;

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

#endif
