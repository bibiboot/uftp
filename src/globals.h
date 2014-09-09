#pragma once

#include <stdio.h>
#include "uthash.h"
#include "config.h"
#include "my402list.h"

// Print function name, filename and line number in print
#define DEBUG(fmt, ...) printf("%s:%d: " fmt, __FILE__, __LINE__, __VA_ARGS__);
#define DBG(...) do{fprintf(stderr, "%s (%s, line %d): ", __func__, __FILE__, __LINE__); \
                         fprintf(stderr, __VA_ARGS__);           \
                         fprintf(stderr, "\n");} while(0)
#define DATA "DATA"
#define NACK "NACK"

// Hashmap data structure
typedef struct hashl {
    uint16_t seq_num;
    // Address of the node in list.
    My402ListElem *data_node_ptr;
    My402ListElem *nack_node_ptr;
    UT_hash_handle hh;
} hashed_link;

// Data list is stored as node below
// Both nack and data list have same type of node
struct node {
    uint16_t seq_num;
    // Its pointing to the start address of data
    char *mem_ptr;
};

// datal --> Data list
// nackl --> Nack list
struct globals {
    struct config config;
    // Hashmap
    hashed_link *hashl;
    My402List datal;
    My402List nackl;
};

extern struct globals globals;
