#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reverse.h"
#include <stdbool.h>
#define BUFFER_SIZE 1024

void writeOut(char **lines, int file_line_counter, struct typeAndSize property, bool numbered);
char *reverseLine(char *line, struct typeAndSize property);

void reverseMain(struct typeAndSize property, FILE *file)
{
    //Memóriafoglalás a lines-nak
    char **lines = calloc(1, sizeof(char *));
    //Sikerült-e lefoglalni memóriát
    if (lines == NULL)
    {
        printf("Memory allocation failed!");
        exit(0);
    }

    char buffer[BUFFER_SIZE];
    //A fájl sorainak számát a fájl futása során számolja
    int file_line_counter = 0;
    int size=1;
    while (NULL != fgets(buffer, BUFFER_SIZE, file))
    {
        //Memóriafoglalás mágia (minden haverom utálja a mallocot, calloc a legjobb)
        lines[file_line_counter] = calloc(property.size + 1, sizeof(char));

        //Sikerült-e lefoglalni memóriát
        if (lines[file_line_counter] == NULL)
        {
            printf("Memory allocation failed!");
            //Ha nem sikerült akkor mivel kilép a program az előző memóriacímeket is fel kell szabadítani
            for (int i = 0; i < file_line_counter; i++)
            {
                free(lines[file_line_counter]);
            }
            free(lines);
            exit(0);
        }
        //Azért az újsor karakter se felejtsük el na
        buffer[strcspn(buffer, "\r\n")] = 0;
        strncpy(lines[file_line_counter], buffer, property.size);
        file_line_counter++;


        // Dinamikusan kezeli a memóriafoglalást, ha elértünk annyi sormennyiséget mint amennyit lefoglaltunk akkor megduplázza a méretét
        if(size<=file_line_counter){
            //Ideiglenesen tárolunk
            char** tmp = realloc(lines, sizeof(char *) * size);
            if (tmp == NULL)
            {
                //Ha nem sikerült akkor mivel kilép a program az előző memóriacímeket is fel kell szabadítani
                printf("Memory allocation failed!");
                for (int i = 0; i < file_line_counter; i++)
                {
                    free(lines[file_line_counter]);
                }
                free(lines);
                exit(0);
            }
            else{
                lines=tmp;
            }
            size*=2;
        }
    }
    //Ellenőrzi hogy számozottan kérik a kimenetet vagy sem
    bool numberedOutput = strcmp(property.type, "nolinenums") == 0;

    //Kiírató függvény meghívása
    writeOut(lines, file_line_counter, property, numberedOutput);

    //Helyes lefutás után a memóriák felszabadítása
    for (int i = 0; i < file_line_counter; i++)
    {
        free(lines[i]);
    }
    free(lines);
}
//Egy sor megfordítása
char *reverseLine(char *line, struct typeAndSize property)
{
    //Lefoglal annyi memóriát hogy a sor és a \0 jel elférjen
    char *reversed = calloc(strlen(line)+1, sizeof(char));
    //Segéd indexelés
    int index = 0;
    //A megfordítás az indexeléssel lett megoldva, utolsó indexxel kezdünk és az elsővel fejezzük be
    for (int j = strlen(line)-1; j >= 0; j--)
    {
        reversed[index] = line[j];
        index++;
    }
    reversed[strlen(line)]='\0';
    return reversed;
}
//Kiíratás (itt történik a megfordítás is)
void writeOut(char **lines, int file_line_counter, struct typeAndSize property, bool numbered)
{
    //Ha számozott
    if (numbered)
    {
        //Mivel tükrözve van így fordítva kell számozni
        for (int i = file_line_counter - 1; i >= 0; i--)
        {
            char *reversed = reverseLine(lines[i], property);
            printf("%d %s\n", (i + 1), reversed);
            free(reversed);
        }
    }
    //Ha számozatlan
    else
    {
        //Mivel tükrözve van így fordítva kell számozni
        for (int i = file_line_counter - 1; i >= 0; i--)
        {
            char *reversed = reverseLine(lines[i], property);
            printf("%s\n", reversed);
            free(reversed);
        }
    }
}
