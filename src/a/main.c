#include <stdio.h>
#include "globals.h"
#include "hashl.h"
#include "mmap.h"
#include "list.h"
#include "parser.h"
#include "packetize.h"
#include "conn_a.h"
#include "sender_a.h"
#include "sender_a_stage2.h"
#include "reciever_a.h"
#include "reciever_a_stage2.h"

void calculate_throughput(){
    // Calculate the throughput
    // Total time: (End time - Start time) / 1000000 seconds
    // Throughput (Bps): (Size / Total time) Bytes / seconds
    // Throughput(bps) : Throughput(Bytes) * 8globals.a_sender_start;
    long long unsigned int time_diff = time_diff_micro(globals.b_reciever_end, globals.a_sender_start);
    DBG("DFF in micro %llu", time_diff);
    float time_diff_sec = time_diff;
    float throughput = ((globals.total_size*2) / time_diff_sec) * 8;
    DBG("THROUGHPUT = %.2f Mbps", throughput);
}

void init_stage2(){
    update_mem_ptr_data_link_to_null();
    create_recv_list(&globals.nackl, NACK);
}

void init_conn(){
    // Create socket connection
    main_conn_setup();
    reciever_conn_setup();
    sender_conn_setup();
}

void init(){

    // Create memory map files
    char *data_ptr = get_memory_map_ptr(globals.filename, &globals.total_size);
    DBG("FILE SIZE = %llu Bytes", globals.total_size);

    // Create data list
    create_list(data_ptr, &globals.datal, DATA);

    // Create socket connection
    init_conn();
    /*
    main_conn_setup();
    reciever_conn_setup();
    sender_conn_setup();
    */
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
    DBG("[STAGE-1] START TIME %llu seconds (epoch)", to_micro(globals.a_sender_start));
    void *val;

    pthread_create(&globals.sen_th, 0, reciever, val);
    pthread_create(&globals.rev_th, 0, sender, val);
}

void start_stage2(){
    void *val;

    pthread_create(&globals.sen_th, 0, reciever_stage2, val);
    pthread_create(&globals.rev_th, 0, sender_stage2, val);
}

// Stage2
int main_stage2(){

    /*
    if (cmd_parser(argc, argv) != 0) {
        DBG("Error in parsing command line");
    }*/

    strcpy(globals.recv_filename, NEW_RECIEVE_FILENAME);
    DBG("DEST FILENAME : %s", globals.recv_filename);
    //globals.total_size = 524288000;
    globals.last_bit_arrived = false;
    globals.current_seq = 0;

    //Create nack list
    //TODO Replace the init_stage2 later


    //init_conn();
    start_stage2();

    pthread_join(globals.sen_th, NULL);
    return 0;
}

int main(int argc, char *argv[]){

    DBG("FILE TRANSFER STARTS");
    // Command line parsing
    if (cmd_parser(argc, argv) != 0) {
        DBG("Error in parsing command line");
    }
    DBG("SRC : %s, DEST : %s", globals.filename, globals.recv_filename);
    DBG("DEST HOSTNAME : %s", globals.hostname_b);

    // Initilaization
    init();

    // Send start dummy to get filename and size
    init_config();

    // Fork and start sending
    start();

    // Wait for both the childs to get over
    pthread_join(globals.sen_th, NULL);
    pthread_join(globals.rev_th, NULL);

    DBG("STAGE-1 END");
    DBG("STAGE-2 STARTS");

    init_stage2();
    main_stage2();
    DBG("STAGE-2 ENDS");

    calculate_throughput();

    main_sender_stage2();
    DBG("FILE TRANSFER COMPLETE");

    DBG("PERFORM MD5");
    // MD5
    do_md5(globals.filename);
    do_md5(globals.recv_filename);
    return 0;
}
