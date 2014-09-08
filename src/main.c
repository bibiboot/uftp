#include <stdio.h>
#include "globals.h"

int main(int argc, char *argv[]){
    // FATAL("Testing");
    printf("PORT = %d\n", globals.config.port);
    return 0;

}
