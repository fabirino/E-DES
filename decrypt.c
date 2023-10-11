#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){

    if(argc !=2){
        printf("Usage: ./decrypt <32-characters key>\n");
        return 1;
    }

    char* input = argv[1];

    return 0;
}