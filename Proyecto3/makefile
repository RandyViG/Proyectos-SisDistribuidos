run: Coordenadas.cpp SocketDatagrama.o
	g++ -std=c++11 Coordenadas.cpp SocketDatagrama.o PaqueteDatagrama.o -o Coordenadas -lpthread
	
SocketDatagrama.o: SocketDatagrama.cpp PaqueteDatagrama.o SocketDatagrama.h
	g++ SocketDatagrama.cpp -c 

PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c
clean:
	rm -f *.o Coordenadas
