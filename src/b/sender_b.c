#include "sender_b.h"

void sender(){
    My402ListElem *elem=NULL;
    for (elem=My402ListFirst(&globals.datal); elem != NULL; elem=My402ListNext(&globals.datal, elem)) {
        struct node *data_node = (elem->obj);
        printf("[%llu] : PRIeT SEQ = %llu, DATA = %s\n", data_node->size, data_node->seq_num, data_node->mem_ptr);
        int n = send_packet(data_node);
        if (n < 0) {
            perror("Error on send");
            exit(1);
        }
    }
}

int send_packet(struct node *data_node){
    struct sockaddr *to = (struct sockaddr *)&globals.serv_addr;
    int tolen = sizeof(struct sockaddr);

    int n = sendto(globals.b_sender_fd, data_node->mem_ptr, data_node->size, 0, to, tolen);
    return n;
}
