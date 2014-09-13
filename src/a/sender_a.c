#include "sender_a.h"

void* main_sender(void *v){
    struct sockaddr *to = (struct sockaddr *)&globals.main_serv_addr;
    int tolen = sizeof(struct sockaddr);

    // Create data packet
    // Add checksum and packet_type bit
    char *buffer = malloc(sizeof(char)*1024);
    char *head_buf = buffer;
    bzero(buffer, 1024);

    char total_size_st[CHECKSUM_LEN];
    sprintf(total_size_st, "%llu", globals.total_size);
    strncpy(buffer, total_size_st, CHECKSUM_LEN);
    buffer += CHECKSUM_LEN;
    strcpy(buffer, globals.recv_filename);
    //DBG("SEND: %s", head_buf);
    vlong buffer_len = 1024;

    int i = 0, n = 0;
    for (; i<=DUMMY_FREQ; i++) {
        n = sendto(globals.a_main_sender_fd, head_buf, buffer_len, 0, to, tolen);
        if (n < 0) {
            perror("Error on send");
            exit(1);
        }
    }
    free(head_buf);
    close(globals.a_main_sender_fd);
}

void* sender(void *v){
    // Iterate the data list and send data
    My402ListElem *elem=NULL;
    bool is_retransmitted = false;

    for (elem=My402ListFirst(&globals.datal); elem != NULL; elem=My402ListNext(&globals.datal, elem)) {
        struct node *data_node = (elem->obj);
        int n = send_packet(data_node, is_retransmitted);
        if (n < 0) {
            perror("Error on send");
            exit(1);
        }
    }

    // The nodeA knows that last bit is send
    globals.last_bit_send = true;

    // Send dummy data denotes the end of sending data
    send_dummy_packet();
    DBG("[SUMMARY] NUM RETRANS %llu", globals.total_retrans);
}

int send_packet(struct node *data_node, bool is_retransmitted){
    struct sockaddr *to = (struct sockaddr *)&globals.serv_addr;
    int tolen = sizeof(struct sockaddr);

    // Create data packet
    // Add checksum and packet_type bit
    char *buffer;
    vlong buffer_len = create_data_packet(data_node->mem_ptr, data_node->size,
                                          data_node->seq_num, &buffer, is_retransmitted);

    int n = sendto(globals.a_sender_fd, buffer, buffer_len, 0, to, tolen);

    free(buffer);
    return n;
}

int send_dummy_packet(){
    struct sockaddr *to = (struct sockaddr *)&globals.serv_addr;
    int tolen = sizeof(struct sockaddr);

    // Create data packet
    // Add checksum and packet_type bit
    char *buffer;
    vlong buffer_len = create_dummy_packet(&buffer);

    int i = 0,n = 0;
    for (; i<=DUMMY_FREQ; i++) {
        n = sendto(globals.a_sender_fd, buffer, buffer_len, 0, to, tolen);

    }
    free(buffer);
    return n;
}
