#include <stdio.h>
#include "globals.h"
#include "hashl.h"

void test_hashmap(){
    void *chunk_ptr = malloc(sizeof(100));
    strcpy(chunk_ptr, "Hello");
    hashed_link h = { .seq_num = 1 , .dl_ptr = chunk_ptr  };
    add_hashl(&h);

    hashed_link *result = (hashed_link *)(find_hashl(1));
    printf("Name = %s\n", (result->dl_ptr));
}

void test_global(){
    printf("PORT = %d\n", globals.config.port);
}

int main(int argc, char *argv[]){
    test_global();
    test_hashmap();
}
