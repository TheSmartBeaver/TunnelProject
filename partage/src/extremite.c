
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <stdbool.h>
#include "../headers/tunalloc.h"
#include "../headers/iftun.h"
#include <arpa/inet.h>


#define MAX 2000
#define PORT 123
#define SA struct sockaddr



void func(int sockfd, int src)
{
    unsigned char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, MAX);

        read(sockfd, buff, sizeof(buff));

        printf("msg du client: \n");
        int i;
        for(i=0; i<2000; i++)
            printf("%c",buff[i]);
	printf("\n");

	    write(src,buff, sizeof(buff));

        bzero(buff, MAX);
        n = 0;
    }
}

void ext_out(char* ipvn, int tunfd)
{

    int ipType=-5;
    if(strcmp(ipvn,"ipv6")==0) {
    	printf("On utilise ipv6\n");
		ipType = 1;
	}
    if(strcmp(ipvn,"ipv4")==0) {
		printf("On utilise ipv4\n");
		ipType = 0;
	}

	
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    int reuseaddr = 1;
    struct sockaddr_in6 addr;

    //printf("\n Je tente création tun0 \n");
    //printf("\n mon tun0 = %d\n",tun);

	system("ip link set tun0 up");

    // socket create and verification
    if(ipType==0)
    	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(ipType==1) {
		sockfd = socket(AF_INET6, SOCK_STREAM, 0);
		setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
	}
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    if(ipType==0) {
		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		servaddr.sin_port = htons(PORT);
	}

	if(ipType==1) {
		addr.sin6_family = AF_INET6;
		addr.sin6_port = htons(PORT);
		addr.sin6_addr = in6addr_any;
	}

    // Binding newly created socket to given IP and verification
    if (ipType==0 && (bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    } else
		if (ipType==1 && bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
			printf("socket bind failed...\n");
			exit(0);
		}
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    if(ipType==0) {
		connfd = accept(sockfd, (SA *) &cli, &len);
		if (connfd < 0) {
			printf("server acccept failed...\n");
			exit(0);
		} else
			printf("server acccept the client...\n");
	}

	if(ipType==1) {
		connfd = accept(sockfd, NULL, NULL);
		if (connfd < 0) {
			printf("server acccept failed...\n");
			exit(0);
		} else
			printf("server acccept the client...\n");
	}
    func(connfd, tunfd);

    close(sockfd);
}

void func2(int sockfd, int src, int dest)
{
      unsigned char buff[MAX]; 
    int n; 
    for (;;) { 
        bzero(buff, sizeof(buff)); 
        //printf("Enter the string : ");
        n = 0;
        for (n=0; n<MAX; n++)
            buff[n]='a';
        //while ((buff[n++] = getchar()) != '\n')
            //;
        write(sockfd, buff, sizeof(buff)); 
        bzero(buff, sizeof(buff));

    } 
}

void ext_in(char* my_ip_adrr, int tunfd, char* ipvn)
{
int sockfd, connfd;
struct sockaddr_in servaddr, cli;
struct sockaddr_in6 addr;

// socket create and varification
if(strcmp(ipvn,"ipv4")==0)
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
if(strcmp(ipvn,"ipv6")==0)
	sockfd = socket(AF_INET6, SOCK_STREAM, 0);
if (sockfd == -1) {
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");
bzero(&servaddr, sizeof(servaddr));

// assign IP, PORT
if(strcmp(ipvn,"ipv4")==0){
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(my_ip_adrr);
	servaddr.sin_port = htons(PORT);
}
if(strcmp(ipvn,"ipv6")==0){
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(PORT);
	inet_pton(AF_INET6, "fc00:1234:2::36", &addr.sin6_addr);
}

// connect the client socket to server socket
if (strcmp(ipvn,"ipv4")==0 && connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
	printf("connection with the server failed...\n");
	exit(0);
}
else if(strcmp(ipvn,"ipv6")==0 && (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) != 0)){
	printf("connection with the server failed...\n");
	exit(0);
}
else
	printf("connected to the server..\n");

//func2(sockfd);
    copySrcOnDstv2(sockfd, tunfd);


// close the socket
close(sockfd);
}



