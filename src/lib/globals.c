#include "globals.h"

// Initializing the global structure with default values
struct globals globals = {
    .config = CONFIG_INIT,
    // This is null as per documentation of uthash
    .hashl = NULL,
    // Current sequence recieved is 0
    .current_seq = 0,
    // Used by nodeB for detecting if dummy packet arrived or not
    .last_bit_arrived = false
};
