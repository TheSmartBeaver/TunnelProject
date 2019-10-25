
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 2000
#define PORT 123
#define SA struct sockaddr

// Function designed for chat between client and server.
void func(int sockfd)
{
    unsigned char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        //printf("msg du client: %s\n", buff);
        printf("msg du client: \n");
        int i;
        for(i=0; i<2000; i++)
            printf("%c",buff[i]);
        bzero(buff, MAX);
        n = 0;
    }
}

// Driver function
void ext_out()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
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
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server acccept failed...\n");
        exit(0);
    }
    else
        printf("server acccept the client...\n");

    // Function for chatting between client and server
    func(connfd);

    // After chatting close the socket
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

void ext_in(char* my_ip_adrr, int tunfd)
{
int sockfd, connfd;
struct sockaddr_in servaddr, cli;

// socket create and varification
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd == -1) {
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");
bzero(&servaddr, sizeof(servaddr));

// assign IP, PORT
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = inet_addr(my_ip_adrr);
servaddr.sin_port = htons(PORT);

// connect the client socket to server socket
if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
printf("connection with the server failed...\n");
exit(0);
}
else
printf("connected to the server..\n");

// function for chat
//func2(sockfd);
    copySrcOnDstv2(sockfd, tunfd);


// close the socket
close(sockfd);
}

int copySrcOnDstv2(int sockfd, int src){
    unsigned char buff[MAX]; 
    int n; 
    for (;;) { 
        bzero(buff, sizeof(buff)); 
        //printf("Enter the string : ");
        n = 0;
        read(src, buff, 2000);
        /*for (n=0; n<1900; n++)
            buff[n]='a';*/
        fprintf(stdout,"contenu du buffer \n");
        int i;
        for(i=0; i<2000; i++)
            printf("%c",buff[i]);
        printf("\n");
        printf("sockfd %d , src %d \n", sockfd, src);
        //while ((buff[n++] = getchar()) != '\n')
            //;
        write(sockfd, buff, sizeof(buff)); 
        bzero(buff, sizeof(buff));

    } 

    return 0;
}
