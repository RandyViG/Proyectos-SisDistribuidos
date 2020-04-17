#ifndef PAQUETEDATAGRAMA_H_
#define PAQUETEDATAGRAMA_H_
class PaqueteDatagrama {
    public:
        PaqueteDatagrama(int *, unsigned int, char *, int );
        PaqueteDatagrama(unsigned int );
        ~PaqueteDatagrama(); //Destructor
        char *obtieneDireccion();
        unsigned int obtieneLongitud();
        int obtienePuerto();
        int *obtieneDatos();
        void inicializaPuerto(int);
        void inicializaIp(char *);
        void inicializaDatos(char *);
    private:
        int *datos;//Almacena los datos
        char ip[16]; //Almacena la IP
        unsigned int longitud;//Almacena la longitude de la cadena de datos
        int puerto;//Almacena el puerto
};
#endif