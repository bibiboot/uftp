#include "sender.h"

void sender(){
    char buffer[256];
    struct sockaddr *to = (struct sockaddr *)&globals.serv_addr;
    int tolen = sizeof(struct sockaddr);

    strcpy(buffer, "I am client");
    int n = sendto(globals.sender_fd, buffer, 256, 0, to, tolen);
    if (n < 0) {
        perror("Error on send");
        exit(1);
    }

    DBG("Sending: %s", buffer);
}
