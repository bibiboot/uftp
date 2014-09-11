#include "sender_a.h"

void sender(){
    My402ListElem *elem=NULL;
    for (elem=My402ListFirst(&globals.datal); elem != NULL; elem=My402ListNext(&globals.datal, elem)) {
        struct node *data_node = (elem->obj);
        //printf("[%llu] : PRINT SEQ = %llu, DATA = %s\n", data_node->size, data_node->seq_num, data_node->mem_ptr);
        int n = send_packet(data_node);
        if (n < 0) {
            perror("Error on send");
            exit(1);
        }
    }

    // Send dummy data
    send_dummy_packet();
}

int send_packet(struct node *data_node){
    struct sockaddr *to = (struct sockaddr *)&globals.serv_addr;
    int tolen = sizeof(struct sockaddr);

    // Create data packet
    // Add checksum and packet_type bit
    char *buffer;
    vlong buffer_len = create_data_packet(data_node->mem_ptr, data_node->size,
                                          data_node->seq_num, &buffer);

    int n = sendto(globals.a_sender_fd, buffer, buffer_len, 0, to, tolen);
    return n;
}

int send_dummy_packet(){
    struct sockaddr *to = (struct sockaddr *)&globals.serv_addr;
    int tolen = sizeof(struct sockaddr);

    // Create data packet
    // Add checksum and packet_type bit
    char *buffer;
    vlong buffer_len = create_dummy_packet(&buffer);

    //DBG("[%d] SEND : %s", buffer_len, buffer);

    int n = sendto(globals.a_sender_fd, buffer, buffer_len, 0, to, tolen);
    return n;
}
