#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "extremite.h"
#include "tunalloc.h"
/*arpa sert à enlever le warning !!!!!!!!!!!!!!!!!!!!!!!*/
#include <arpa/inet.h>

int main(int argc, char** argv){
    int tunfd;

    tunfd = tun_alloc(argv[1]);
    if(tunfd == -1){
        perror("tun_alloc");
        exit(1);
    }
    char cmdLink[50] = "ip link set ";
	strcat(cmdLink,argv[1]);
	strcat(cmdLink," up");
	printf("J'execute %s\n",cmdLink);
	system(cmdLink);


    if(strcmp("VM1",argv[2])==0) {
		printf("On est dans VM1\n");
		char cmdIpAddr[100] = "ip addr add 172.16.2.180/28 dev ";
		strcat(cmdIpAddr,argv[1]);
		printf("J'execute %s\n",cmdIpAddr);
		system(cmdIpAddr);
		ext_in("172.16.2.156", tunfd, "ipv4");
	}
	else if(strcmp("VM1-6",argv[2])==0){
		printf("On est dans VM1-6\n");
		system("ip addr add fc00:1234:2::30 dev tun0");
		ext_in("fc00:1234:2::36", tunfd, "ipv6");
	}
	else {printf("\nERREUR\n"); exit(1);}



    printf("Appuyer met fin au tunnel");
    getchar();

    return 0;
}