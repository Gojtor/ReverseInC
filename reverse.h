#ifndef REVERSE_H
#define REVERSE_H

 struct typeAndSize{
        char* type;
        int size;
};

void reverseMain(struct typeAndSize property,FILE *file);

#endif