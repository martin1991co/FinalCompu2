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

int main(int argc, char *const argv[]){

	printf("            (+-+)/   \n\n");
	printf(".:: SERVIDOR EN FUNCIONAMIENTO ::.\n\n");

	if( (socketsrv(8000)) < 0){
		return -1;
	}

    	return 0;
}

 
