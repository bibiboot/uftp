#include <stdio.h>
#include "globals.h"
#include "hashl.h"
#include "mmap.h"
#include "list.h"
#include "parser.h"
#include "packetize.h"
#include "conn.h"
#include "reciever.h"
#include "sender.h"

void test_arrived(){
    globals.config.total_size = 27;
    create_recv_list(&globals.datal, DATA);
    create_recv_list(&globals.nackl, DATA);

    print_list(&globals.datal);
}

void test_append_retrans(){

    long long unsigned int *retrans_list = malloc(sizeof(long long unsigned int)*1);
    retrans_list[0] = 0;
    int num_retrans = 1;

    add_retransmission_node(retrans_list, num_retrans);

    print_list(&globals.datal);
}

void test_create_write_list(){
    // Create memory map files
    char *data_ptr = get_memory_map_ptr(globals.config.filename, &globals.config.total_size);

    // Create data list
    //DBG("%llu", globals.config.total_size);
    //create_list(data_ptr, &globals.datal, DATA);

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
    //write_data_list_to_file();
}

void test_conn(){
    reciever_conn_setup();
    sender_conn_setup();
}

void test_socket(){

    if (fork() == 0) {
        // Recv Child
        reciever();
        DBG("RECV Exiting");
        // Close the child recv socket
        exit(0);
    }

    if (fork() == 0) {
        // Send child
        sender();
        // Close the child send socket
        exit(0);
    }
    while(1);
}

int main(int argc, char *argv[]){
    //test_create_write_list();
    //test_append_retrans();
    //test_arrived();
    test_conn();
    test_socket();
}
