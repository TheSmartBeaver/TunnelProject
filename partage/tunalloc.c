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

int copySrcOnDst(int src, int dst){
    char *buffer = malloc(sizeof(char)*1024);
    int nb_bytes_lues = 0;
    nb_bytes_lues = read(src, buffer, 200);
    for(int i=0; i<1024; i++)
        printf("%c",buffer[i]);
    printf("\n");
    FILE* fichier = NULL;
    fichier = fopen("test.txt", "a");
    if (fichier != NULL)
    {
        fputs(buffer, fichier);
        if(dst==1)
            fprintf(stdout, buffer);
        fclose(fichier);
        printf("gg3\n");
    }
    return nb_bytes_lues;
}

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
  ifr.ifr_flags = IFF_TUN; 
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
  printf("Appuyez sur une touche pour continuer\n");
  getchar();
  printf("Interface %s Configurée:\n",argv[1]);
  system("ip addr");
  //printf("Appuyez sur une touche pour terminer\n");
  //getchar();

  printf("WTF\n");
  printf("fd de tunfd %d\n",tunfd);
  printf("WTF\n");
  int gg = open("test.txt", O_RDWR);
  printf("WTF1\n");
  int nb = -5;
  while(true) {
      nb = copySrcOnDst(tunfd, 1);
      printf("J'ai lu %d bytes\n", nb);
      //printf("fd de gg = %d", gg);
      //getchar();
  }

  return 0;
}
