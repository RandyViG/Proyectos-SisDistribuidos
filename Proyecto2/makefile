animacion:	animacion.o gfx.o Coordenada.o Asteroide.o
		g++ gfx.o Asteroide.o Coordenada.o animacion.o -o animacion -lX11

animacion.o:	animacion.cpp
		g++ animacion.cpp -c

gfx.o:		gfx.c
		gcc gfx.c -c

Coordenada.o:	Coordenada.cpp
		g++	Coordenada.cpp -c

Asteroide.o:	Asteroide.cpp
		g++ Asteroide.cpp -c

clean: 
		rm -f *.o animacion
