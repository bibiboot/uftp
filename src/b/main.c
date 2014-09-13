#include <stdio.h>
#include "globals.h"
#include "hashl.h"
#include "mmap.h"
#include "list.h"
#include "parser.h"
#include "packetize.h"
#include "conn_b.h"
#include "sender_b.h"
#include "reciever_b.h"
#include "sender_b_stage2.h"
#include "reciever_b_stage2.h"

void init(){
    // 1GB
    //globals.config.total_size = 1048576000;
    // Create socket connection
    main_conn_setup();
    reciever_conn_setup();
    sender_conn_setup();
}

void init_config(){
    void *v;
    main_reciever(v);

    // Create data list
    DBG("[S1] FILE SIZE RECIEVED = %llu", globals.total_size);
    create_recv_list(&globals.datal, DATA);
    create_recv_list(&globals.nackl, NACK);
}

void init_config_stage2(){
    void *v;
    //Sending dummy first
    main_sender_stage2();

    // Create data list
    /*
    globals.total_size = 524288000;
    strcpy(globals.filename, "etc/data/data.bin");
    char *data_ptr = get_memory_map_ptr(globals.filename, &globals.total_size);
    DBG("SIZE = %llu", globals.total_size);

    // Create data list
    create_list(data_ptr, &globals.datal, DATA);
    DBG("List Created");
    */
}

void start(){
    void *val;

    pthread_create(&globals.sen_th, 0, reciever, val);
    pthread_create(&globals.rev_th, 0, sender, val);
}

void start_stage2(){
    void *val;

    pthread_create(&globals.sen_th, 0, reciever_stage2, val);
    pthread_create(&globals.rev_th, 0, sender_stage2, val);
}

int main_stage2(){
    //init();
    init_config_stage2();

    start_stage2();

    pthread_join(globals.rev_th, NULL);
    pthread_join(globals.sen_th, NULL);
    return 0;
}

int main(int argc, char *argv[]){

    // Initilaization
    init();

    // Send start dummy to get filename and size
    init_config();

    // Fork and start sending
    start();

    // Wait for both the childs to get over
    //pthread_join(globals.rev_th, NULL);
    pthread_join(globals.sen_th, NULL);

    DBG("-------------END OF STAGE 1----------");
    DBG("-------------START OF STAGE 2----------");

    main_stage2();

    return 0;
}
