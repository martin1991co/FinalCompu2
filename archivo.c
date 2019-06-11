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

int archivo_accion(char *buffer, int cliente, char *ip){
    int archivo, opcion;
    char datos[200];

    opcion = get(buffer, datos);
    if(opcion == 1){ //ver bd
        if( archivo_abrir(datos, &archivo) < 0){
            write(cliente, "error", 5);
            return 0;
        }
        archivo_enviar(cliente, archivo);
        close(archivo);
    }
    else if(opcion == 2){ //mensaje completado
        printf("Guardar: %s;%s\n", datos, ip);
    }
    return 0;
}

int archivo_abrir(char *nombre, int *archivo){
    char direccion[100];
    memset(direccion, 0, sizeof direccion); //limpia

    sprintf(direccion, "bd/%s", nombre); //direccion del archivo

    if( (*archivo = open(direccion, O_RDWR)) < 0){ //abrir, sino error
        perror ("open(archivo_abrir)");
		return -1;
    }
    return 0;
}

int archivo_enviar(int cliente, int archivo){
    char buffer[512];
    memset(buffer, 0, sizeof buffer); //limpia

    while(read(archivo, buffer, sizeof buffer) > 0){
        write(cliente, buffer, strlen(buffer));
        memset(buffer, 0, sizeof buffer);
	}

    return 0;
}
 
