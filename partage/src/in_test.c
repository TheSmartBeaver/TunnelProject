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

    system("ip addr");
    printf("\nfd de tunfd %d\n",tunfd);

    ext_in("172.16.2.156", tunfd);

    printf("Appuyer met fin au tunnel");
    getchar();

    return 0;
}