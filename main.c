#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 50

int main()
{
    int width=0, depth=0, temp, cont=0, min=0, max=0, ret=-1,cont2=0;
    int dado;
    char *teste;
    char buffer[BUFFER_SIZE];

    FILE *fp = fopen ("entrada.txt","r") ;

    if ( fp == NULL){
        perror("Erro ao abrir o arquivo");
        exit(-1);}

    while ( !feof (fp) ){
        fgets (buffer, BUFFER_SIZE, fp);
        teste = strstr (buffer, "WIDTH");

        if (teste != NULL)
            sscanf(buffer ,"WIDTH  = %d;", &width);
        teste = strstr (buffer, "DEPTH");

        if (teste != NULL)
            sscanf(buffer ,"DEPTH  = %d;", &depth);
        teste = strstr (buffer, "CONTENT BEGIN");
        if (teste != NULL)
            break;
    }



    int dados[depth];

    FILE *saida = fopen ("saida.bin","wb") ;


    while ( !feof (fp) )
    {

        fgets (buffer, BUFFER_SIZE, fp);
        teste = strstr (buffer, "[");
        if (teste != NULL)
            break;

        ret = sscanf(buffer ,"%d	%c	%8X;", &temp, &teste, &dado);

        if(ret!=3)
            break;

        else
        {
            cont2++;
            printf("dado[%d]: %x\n",cont2,dado);
            fwrite(&dado, sizeof (int), 1, saida);
        }
        cont++;

    }


    sscanf(buffer, "[%d..%d]	%c	%08X;", &min, &max, &teste, &dado);

    for (cont; cont<=(depth-2) ; cont++)
    {
        cont2++;
        fwrite(&dado, sizeof (int), 1, saida);
         printf("dado[%d]: %x\n",cont2,dado);
    }


    fclose(saida);
    return 0;}

