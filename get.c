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

int get(char *buffer, char *datos){
    int option=0;
    char *token;

    token = strtok(buffer , "::");

    if (strcmp(token, "ver") == 0){
        option = 1;
    }
    else if (strcmp(token, "completado") == 0){
        option = 2;
    }
    if(token != NULL){
        token = strtok(NULL,"::");
        strcpy(datos,token);
    }
    return option;
}
 
