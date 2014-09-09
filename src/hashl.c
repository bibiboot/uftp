#include "hashl.h"
#include "globals.h"

void add_hashl(hashed_link *h){
    HASH_ADD_INT( globals.hashl, seq_num, h);
}

hashed_link *find_hashl(uint16_t seq_num){
    hashed_link *h;
    HASH_FIND_INT( globals.hashl, &seq_num, h);
    return h;
}
