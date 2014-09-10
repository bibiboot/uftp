#include "reciever_b.h"

void reciever(){
    char buffer[256];
    bzero(buffer,256);

    struct sockaddr_in from;
    int fromlen = sizeof(struct sockaddr_in);

    while (1){
        DBG(".........Waiting.......");
        int n=recvfrom(globals.b_recv_fd, buffer, 1024, 0,
                       (struct sockaddr *)&from, &fromlen);
        if (n < 0) {
            perror("Error in recv");
            exit(1);
        }
        DBG("[] Here is the message: %s\n", buffer);
    }
}

