#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void copySrcOnDst(int src, int dst){
    void *buffer = malloc(sizeof(char)*1024);

    int nb_bytes_lues = read(src, buffer, 2);
    fprintf(stdout,"J'ai lu %d bytes", nb_bytes_lues);
    
    FILE* fichier = NULL;
    
    fichier = fopen("test.txt", "a");
 
    if (fichier != NULL)
    {
        fputs(buffer, fichier);
        if(dst==1)
            fprintf(stdout, buffer);
        fclose(fichier);
    }

}

/*int main (int argc, char** argv){
while(1){
    copySrcOnDst(0,1);
}
return 0;
}*/
