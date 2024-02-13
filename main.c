#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reverse.h"
#include <stdbool.h>
#include <ctype.h>

bool validType(char *type);
bool isNum(char *num);

int main(int argc, char *argv[])
{
    //Ellenőrzi mennyi argumentum lett megadva valamint hogy megfelelő típusúak-e az argumentumok
    if (argc > 3 && validType(argv[1]) && isNum(argv[2]))
    {
        //Struct ami tárolja a kiíratás típusát és hogy mennyi karakterig olvassa az input sorait
        struct typeAndSize property;
        property.size = atoi(argv[2]);
        property.type = argv[1];

        //Minden fájlt beolvas ha többet adunk meg
        for (int i = 3; i < argc; i++)
        {
            FILE *input = fopen(argv[i], "r");
            if (input == NULL)
            {
                //Ha nem sikerült megnyitni hibaüzenet
                printf("File opening unsuccessful: %s", argv[i]);
            }
            else
            {
                reverseMain(property, input);
            }
            fclose(input);
        }
    }
    //Ha pontosan három argumentum van akkor az stdin-ről olvassa be az inputot
    else if (argc == 3 && validType(argv[1]) && isNum(argv[2]))
    {
        struct typeAndSize property;
        property.size = atoi(argv[2]);
        property.type = argv[1];
        reverseMain(property, stdin);
    }
    //Ha nem megfelelő mennyiségű argumentumot adtak meg akkor egy mintát ír ki
    else
    {
        fprintf(stdout, "Usage:\n");
        fprintf(stdout, "\trev [SHOW LINE NUMBERS] [MAX LINE LENGTH] files...");
    }
    return 0;
}
//Függvény ami megnézi hogy az első argumentum megfelelő string-e
bool validType(char *type)
{
    bool valid = false;
    if (strcmp(type, "linenums") == 0 || strcmp(type, "nolinenums") == 0)
    {
        valid = true;
    }

    return valid;
}

//Függvény ami számjegyenként ellenőrizve megnézi hogy szám-e a bemenet
bool isNum(char *num){
    int size = strlen(num);
    if (size == 0) {
        return false;
    }

    for (int i = 0; i < size; i++) {
        if (!isdigit(num[i])) {
            return false;
        }
    }
    return true;
}
