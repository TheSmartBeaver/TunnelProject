//
// Created by totor on 13/11/2019.
//


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


#include <netdb.h>
#include <netinet/in.h>

#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <sys/stat.h>
#include <fcntl.h>

#include "extremite.h"
#include "tunalloc.h"
/*arpa sert à enlever le warning !!!!!!!!!!!!!!!!!!!!!!!*/
#include <arpa/inet.h>


struct mesParams
{
	int tunfd;
	char* ipvn;
	char* tun_name;
	char* machine;
};

void *thread_in(void *arg)
{
	printf("Nous sommes dans le thread in.\n");

	/* Pour enlever le warning */
	(void) arg;
	struct mesParams *args = (void *)arg;
	printf("fd : %d\n",args->tunfd);

	char cmdLink[50] = "ip link set ";
	strcat(cmdLink,args->tun_name);
	strcat(cmdLink," up");
	printf("J'execute %s\n",cmdLink);
	system(cmdLink);


	if(strcmp("VM1",args->machine)==0) {
		printf("On est dans VM1\n");
		char cmdIpAddr[100] = "ip addr add 172.16.2.180/28 dev ";
		strcat(cmdIpAddr,args->tun_name);
		printf("J'execute %s\n",cmdIpAddr);
		system(cmdIpAddr);
		ext_in("172.16.2.156", args->tunfd, "ipv4");
	}
	else if(strcmp("VM1-6",args->machine)==0){
		printf("On est dans VM1-6\n");
		system("ip addr add fc00:1234:2::30 dev tun0");
		ext_in("fc00:1234:2::36", args->tunfd, "ipv6");
	}
	else {printf("\nERREUR\n"); exit(1);}



	printf("Appuyer met fin au tunnel");
	getchar();

	pthread_exit(NULL);
}

void *thread_out(void *arg)
{
	printf("Nous sommes dans le thread out.\n");

	/* Pour enlever le warning */
	(void) arg;
	struct mesParams *args = (void *)arg;

	if(strcmp(args->ipvn,"ipv6")==0)
		ext_out("ipv6",args->tunfd);
	if(strcmp(args->ipvn,"ipv4")==0)
		ext_out("ipv4",args->tunfd);
	pthread_exit(NULL);
}

int main(int argc, char** argv)
{
	pthread_t thread1, thread2;
	printf("WTF1\n");
	int tunfd;
	tunfd = tun_alloc(argv[1]);
	if(tunfd == -1){
		perror("tun_alloc");
		exit(1);
	}
	printf("WTF2\n");
	struct mesParams params;
	params.tunfd = tunfd;
	params.ipvn = "ipv6";
	params.machine = "VM1-6";
	params.tun_name = "tun0";

	printf("WTF3\n");

	struct mesParams params2;
	params2.tunfd = tunfd;
	params2.ipvn = "ipv4";

	printf("WTF4\n");

	printf("Avant la création du thread.\n");

	if(pthread_create(&thread1, NULL, thread_in, (void *)&params) == -1) {
		perror("pthread_create");
		return EXIT_FAILURE;
	}

	printf("WTF5\n");

	if(pthread_create(&thread2, NULL, thread_out, (void *)&params2) == -1) {
		perror("pthread_create");
		return EXIT_FAILURE;
	}

	printf("Après la création du thread.\n");

	for (;;){/*printf("je tourne\n");*/ }


	return EXIT_SUCCESS;
}
