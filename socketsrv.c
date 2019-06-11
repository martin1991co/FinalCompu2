#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "head.h"

/*soy el servidor*/
int socketsrv(int puerto){
	char buffer[1024];
	int sockd, cliente, yes= 1;
	socklen_t addrlen;
	struct sockaddr_in addr_srv;
	struct sockaddr_in addr_cli;

    /*socket() devuleve un descriptor de fichero normal, que posteriormente el sistema asociará a una conexión de red*/
    /*El segundo parámetro indica si el socket es orientado a conexión (SOCK_STREAM) o no lo es (SOCK_DGRAM). De esta forma podremos hacer sockets de red o de Unix tanto orientados a conexión como no orientados a conexión.
    El tercer parámetro indica el protocolo a emplear. Habitualmente se pone 0.*/
	if( (sockd = socket(PF_INET, SOCK_STREAM, 0)) < 0){ //TCP
		perror("socket(socketsrv)");
		return -1;
	}

	//* address family */
    /*sin_family es el tipo de conexión (por red o interna)*/
	addr_srv.sin_family = AF_INET;
	//* port */
	addr_srv.sin_port = htons(puerto);
    /*sin_addr.s_addr es la dirección del cliente al que queremos atender.
     INADDR_ANY, atenderemos a cualquier cliente.*/
	//inet_aton("127.0.0.1", &addr_srv.sin_addr);
	addr_srv.sin_addr.s_addr = htonl(INADDR_ANY);

  /*setsockopt() proprociona los medios para controlar el comportamiento de socket, se puede utilizar para asignar espacio de bufer, tiempos de espera, o transmisiones de datos toma permisos*/
	if(setsockopt(sockd, SOL_SOCKET, SO_REUSEADDR, (char *) &yes, sizeof yes) < 0){
		perror("setsocketopt(socketsrv)");
		return -1;
	}

    /*bind() avisa al sistema operativo de que hemos abierto un socket y queremos que asocie nuestro programa a dicho socket
    + Descriptor del socket que hemos abierto
*/
	if( bind(sockd, (struct sockaddr *)&addr_srv, sizeof addr_srv) < 0){
		perror("bind(socketsrv)");
		return -1;
	}

    /*Avisa al sistema de que comience a atender dicha conexion de red, si hay demasiados hace una cola e iran pasando según vayamos pidiendolo
    +Descriptor del socket.
    +El segundo parámetro de listen() indica cuántos clientes máximo podemos tener en la lista de espera.*/
	if(listen(sockd, 10) < 0)	{
		perror("listen(socketsrv)");
		return -1;
	}

	addrlen = sizeof addr_cli;
    /*accept() pedir y aceptar las conexiones de clientes al SO. Le indica al SO que nos dé al siguiente cliente de la cola. Si no hay se quedará bloqueada.
    Esta función devuelve un descriptor de fichero que es el que se tiene que usar para "hablar" con el cliente.*/
	while( (cliente = accept(sockd, (struct sockaddr *) &addr_cli, &addrlen) ) > 0)	{
		switch(fork()){
			case 0:		//proceso hijo
				close(sockd); //cierra conexión
				memset(buffer, 0, sizeof buffer);
				if(read(cliente, buffer, sizeof buffer) > 0){
				    printf("CLIENTE::IP: %s::PORT: %d::%s\n", inet_ntoa(addr_cli.sin_addr), ntohs(addr_cli.sin_port), buffer);
                    archivo_accion(buffer, cliente, inet_ntoa(addr_cli.sin_addr));
                }
                return 0;

			case -1:		// error
				perror ("fork(socketweb)");
				return -1;
		}
		close(cliente);
	}

    /*Cierre de la comunicación y del socket*/
	close(sockd);

	return 0;
}
 
