#pragma once

#include "uthash.h"
#include "config.h"
#include "my402list.h"
#include <stdio.h>

typedef struct hashl {
    uint16_t seq_num;
    char *dl_ptr;
    char *nl_ptr;
    UT_hash_handle hh;
} hashed_link;

struct globals {
    struct config config;
    hashed_link *hashl;
    My402List datal;
    My402List nackl;
};

extern struct globals globals;
