#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getParameterValueConfig(char* pNameFile, char* pParameterName)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    char * value = NULL;
    ssize_t read;

    fp = fopen(pNameFile, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1)
    {
        char *token;
        char *search = ":";

        char word[100];
        strcpy(word, line);

        //printf("%s\t",line);
        //Token will point to "SEVERAL".
        token = strtok(line, search);
        //printf("\nPARAMETER: %s",pParameterName);
        //printf("\tTOKEN: %s",token);

        int number = strcmp(token, pParameterName);
        //printf("\tNumber :%d",number);

        if(number == 0)
        {
            value = strtok(NULL, search);
            break;
            //printf("\tVALOR :%s",value);
        }
    }

    fclose(fp);
    if (line)
        free(line);
    return atoi(value);
}


void leer()
{



    FILE* fp;
    char buffer[255];

    fp = fopen("config_puente_02.txt", "r");

    while(fgets(buffer, 255, (FILE*) fp))
    {
        printf("%s\n", buffer);
    }

    fclose(fp);


}
