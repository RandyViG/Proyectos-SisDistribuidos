#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>
int puerto = 7200;

int main(void){
   long long int num[2];
   char s_addr[4];
   int s, res, clilen,i;
   struct sockaddr_in server_addr, msg_to_client_addr;

   s = socket(AF_INET, SOCK_DGRAM, 0);
   
   /* se asigna una direccion al socket del servidor*/
   bzero((char *)&server_addr, sizeof(server_addr));
   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = INADDR_ANY;
   server_addr.sin_port = htons(puerto);
   bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr));
   clilen = sizeof(msg_to_client_addr);
   while(1) {
      recvfrom(s, (char *) num, 2*sizeof( long long int), 0, (struct sockaddr *)&msg_to_client_addr, &clilen);
      memcpy(s_addr,&msg_to_client_addr.sin_addr.s_addr,4);
      printf("Num 1: %Ld  Num 2: %Ld\n",num[0],num[1]);
      
      /* envía la petición al cliente. La estructura msg_to_client_addr contiene la dirección socket del cliente */
      //sendto(s, (char *)&res, sizeof(int), 0, (struct sockaddr *)&msg_to_client_addr, clilen);
   }
}

