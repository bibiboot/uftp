#include <stdio.h>
#include "globals.h"
#include "hashl.h"
#include "mmap.h"
#include "realibility_list.h"

void test_list(){
    // Create memory map files
    char *data_ptr = get_memory_map_ptr(globals.config.filename, &globals.config.total_size);

    // Create data list
    create_list(data_ptr, &globals.datal, DATA);


    // Print data list
    //print_list(&globals.datal);
    // Print data list
    //print_list(&globals.datal);
    /*
    // Create nack list
    create_list(data_ptr, &globals.nackl, NACK);

    // Print data in packet
    //print_file_packet_wise(data_ptr);

    // Print nack list
    print_list(&globals.nackl);

    // Delete node with seq_num = 2
    //delete_node_nack_list(2);

    // Print nack list
    //print_list(&globals.nackl);

    // Get current nack_list
    //get_current_nack_list();

    */
    // Write into file
    write_data_list_to_file();
}

int main(int argc, char *argv[]){
    test_list();
}
