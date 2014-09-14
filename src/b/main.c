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
    //sender_conn_setup();
}

void init_config(){
    void *v;
    main_reciever(v);

    // Create data list
    DBG("FILE SIZE RECIEVED = %llu", globals.total_size);
    create_recv_list(&globals.datal, DATA);
    create_recv_list(&globals.nackl, NACK);
}

void init_config_stage2(){
    //Sending dummy first
    main_sender_stage2();
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
    gettimeofday(&globals.a_sender_start, NULL);
    init_config_stage2();

    start_stage2();

    pthread_join(globals.rev_th, NULL);
    pthread_join(globals.sen_th, NULL);
    return 0;
}

int main(int argc, char *argv[]){

    DBG("WAITING FOR FILE");
    // Initilaization
    init();

    // Send start dummy to get filename and size
    init_config();

    // Fork and start sending
    start();

    // Wait for both the childs to get over
    pthread_join(globals.sen_th, NULL);

    DBG("STAGE-1 ENDS");
    DBG("STAGE 2 STARTS");

    main_stage2();
    DBG("FILE TRANSFER COMPLETE");

    return 0;
}
