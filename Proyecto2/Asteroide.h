#ifndef __ASTEROIDE_H__
#define __ASTEROIDE_H__

#include<iostream>
#include<vector>
#include"Coordenada.h"

using namespace std;

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

#endif