#pragma once

#include "uthash.h"
#include "config.h"

typedef struct hashl {
    uint16_t seq_num;
    char *dl_ptr;
    char *nl_ptr;
    UT_hash_handle hh;
} hashed_link;

struct globals {
    struct config config;
    hashed_link *hashl;
};

extern struct globals globals;
