#include <stdio.h>
#include "globals.h"
#include "hashl.h"
#include "mmap.h"
#include "realibility_list.h"

int main(int argc, char *argv[]){

    // Create memory map files
    char *data_ptr = get_memory_map_ptr(globals.config.filename, &globals.config.total_size);

    // Create data list
    create_list(data_ptr, &globals.datal, DATA);

    // Create nack list
    create_list(data_ptr, &globals.nackl, NACK);

    // Print data in packet
    print_file_packet_wise(data_ptr);

    // Print data list
    print_list(&globals.datal);
    // Print nace list
    print_list(&globals.nackl);
}
