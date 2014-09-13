#include <stdio.h>
#include "globals.h"
#include "hashl.h"
#include "mmap.h"
#include "list.h"
#include "parser.h"
#include "packetize.h"
#include "conn_a.h"
#include "sender_a.h"
#include "reciever_a.h"

void init(){

    // Create memory map files
    char *data_ptr = get_memory_map_ptr(globals.filename, &globals.total_size);
    DBG("SIZE = %llu", globals.total_size);

    // Create data list
    create_list(data_ptr, &globals.datal, DATA);

    // Create socket connection
    main_conn_setup();
    reciever_conn_setup();
    sender_conn_setup();
}

int cmd_parser(int argc, char *argv[]){
    if (argc != 3) {
        return 1;
    }

    int num = sscanf(argv[2], "%[^:]:%s", globals.hostname_b, globals.recv_filename);
    if (num != 2) {
        return 1;
    }

    strcpy(globals.filename, argv[1]);

    return 0;
}

void init_config(){
    void *v;
    main_sender(v);
}

void start(){
    gettimeofday(&globals.a_sender_start, NULL);
    void *val;

    pthread_create(&globals.sen_th, 0, reciever, val);
    pthread_create(&globals.rev_th, 0, sender, val);
}

int main(int argc, char *argv[]){

    // Command line parsing
    if (cmd_parser(argc, argv) != 0) {
        DBG("Error in parsing command line");
    }
    printf("SRC : %s, DEST : %s\n", globals.filename, globals.recv_filename);

    // Initilaization
    init();

    // Send start dummy to get filename and size
    init_config();

    // Fork and start sending
    start();

    // Wait for both the childs to get over
    pthread_join(globals.sen_th, NULL);
    pthread_join(globals.rev_th, NULL);
    DBG("---------CLOSING DOWN-------");
}
