#include "uthash.h"
#include <stdio.h>
#include <string.h>

typedef struct hash {
    uint16_t seq_num;
    char *dl_ptr;
    char *nl_ptr;
    UT_hash_handle hh;
} hashl;

hashl *hl = NULL;

void add_hashl(hashl *s){
    HASH_ADD_INT( hl, seq_num, s);
}

hashl *find_hashl(int seq_num){
    hashl *h;
    HASH_FIND_INT( hl, &seq_num, h);
    return h;
}

int main(int argc, char *argv[]){
    void *chunk_ptr = malloc(sizeof(100));
    strcpy(chunk_ptr, "Hello");
    hashl h = { .seq_num = 1 , .dl_ptr = chunk_ptr  };
    add_hashl(&h);

    hashl *result = find_hashl(1);
    printf("Name = %s\n", (result->dl_ptr));
    return 0;
}
