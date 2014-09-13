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
    DBG("SIZE = %llu", globals.total_size);
    create_recv_list(&globals.datal, DATA);
    create_recv_list(&globals.nackl, NACK);
}

void start(){
    void *val;

    pthread_create(&globals.sen_th, 0, reciever, val);
    pthread_create(&globals.rev_th, 0, sender, val);
}

int main(int argc, char *argv[]){

    // Initilaization
    init();

    // Send start dummy to get filename and size
    init_config();

    // Fork and start sending
    start();

    // Wait for both the childs to get over
    pthread_join(globals.sen_th, NULL);
    pthread_join(globals.rev_th, NULL);
    DBG("-------------CLOSE DOWN----------");
}
