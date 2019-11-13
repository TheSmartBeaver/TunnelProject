#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "../headers/extremite.h"
#include "../headers/tunalloc.h"


int main(int argc, char** argv){
	int tunfd = tun_alloc(argv[2]);
	if(tunfd<0) {
		printf("\nERREUR tun0 création\n");
		exit(1);
	}

	if(strcmp(argv[1],"ipv6")==0)
    	ext_out("ipv6",tunfd);
	if(strcmp(argv[1],"ipv4")==0)
		ext_out("ipv4",tunfd);
}