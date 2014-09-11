#include "globals.h"

void create_nack_packet();

vlong create_data_packet(char *mem_ptr, vlong payload_size,
                         vlong seq_num, char **buffer);

vlong create_dummy_packet(char **buffer);
