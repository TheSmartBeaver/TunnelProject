#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int copySrcOnDst(int src, int dst){
    char buffer[2000]; /*taille doit être au min celle du MTU (1500) ???*/
    int nb_bytes_lues = 0;
    nb_bytes_lues = read(src, buffer, 2000);
    int i;
    for(i=0; i<2000; i++)
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
    }
    return nb_bytes_lues;
}
