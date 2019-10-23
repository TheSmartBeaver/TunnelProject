#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h> 
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <unistd.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <stdbool.h>

#include "iftun.h"
#include "extremite.h"

int tun_alloc(char *dev)
{
  struct ifreq ifr;
  int fd, err;

  if( (fd = open("/dev/net/tun", O_RDWR)) < 0 ){
    perror("open");
    exit(-1);
  }

  memset(&ifr, 0, sizeof(ifr));

  /* Flags: IFF_TUN   - TUN device (no Ethernet headers) 
   *        IFF_TAP   - TAP device  
   *
   *        IFF_NO_PI - Do not provide packet information  
   */ 
  ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
  if( *dev )
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

  if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
    close(fd);
    perror("ioctl");
    return err;
  }
  strcpy(dev, ifr.ifr_name);
  return fd;
}      

int main (int argc, char** argv){

  int tunfd;
  printf("Création de %s\n",argv[1]);
  tunfd = tun_alloc(argv[1]);
  if(tunfd == -1){
      perror("tun_alloc");
      exit(1);
  }
  printf("Faire la configuration de %s...\n",argv[1]);
  printf("Interface %s Configurée:\n",argv[1]);
  system("ip addr");
  //printf("Appuyez sur une touche pour terminer\n");
  //getchar();
  printf("fd de tunfd %d\n",tunfd);
  int gg = open("test.txt", O_RDWR);
  int nb = -5;

  /*while (true){
      copySrcOnDst(tunfd,1);
  }*/

  ext_in("172.16.2.156", tunfd);

  printf("Appuyer met fin au tunnel");
  getchar();

  return 0;
}
