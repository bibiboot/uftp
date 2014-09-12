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

    // Text file
    //globals.config.total_size = 27;
    // 100KB
    //globals.config.total_size = 1024;
    // 1GB
    //globals.config.total_size = 1048576000;
    //1MB
    globals.config.total_size = 1048576;

    // 200MB
    //globals.config.total_size = 209715200;

    // 20MB
    //globals.config.total_size = 20971520;

    // 100MB
    //globals.config.total_size = 104857600;
    // 50MB
    //globals.config.total_size = 52428800;

    // Create data list
    create_recv_list(&globals.datal, DATA);
    create_recv_list(&globals.nackl, NACK);

    strcpy(globals.recv_filename, "etc/data/recv.bin");

    // Create socket connection
    reciever_conn_setup();
    sender_conn_setup();
}

void start(){
    if (fork() == 0) {
        // Recv Child
        reciever();
        DBG("RECV process exiting");
        // Close the child recv socket
        exit(0);
    }

    /*
    if (fork() == 0) {
        // Send child
        sender();
        // Close the child send socket
        exit(0);
    }*/
}

int main(int argc, char *argv[]){

    // Initilaization
    init();

    // Fork and start sending
    start();

    // Wait for both the childs to get over
    int status;
    waitpid(-1, &status, 0);
    //waitpid(-1, &status, 0);
    DBG("-------------CLOSE DOWN----------");
}
