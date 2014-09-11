#include "reciever_a.h"

void reciever(){
    char buffer[256];
    bzero(buffer,256);

    struct sockaddr_in from;
    int fromlen = sizeof(struct sockaddr_in);

    while (1){
        int size_recieved=recvfrom(globals.a_recv_fd,
                                   buffer, 1024, 0,
                       (struct sockaddr *)&from, &fromlen);
        if (size_recieved < 0) {
            perror("Error in recv");
            exit(1);
        }
        //DBG("[] Here is the message: %s\n", buffer);
        int packet_type = get_recieved_packet_type(buffer);

        switch (packet_type) {
            case DATA_PACKET:
                data_packet_handler(buffer, size_recieved);
                break;
            case NACK_PACKET:
                nack_packet_handler(buffer, size_recieved);
                break;
            case DUMMY_PACKET:
                dummy_packet_handler(buffer, size_recieved);
                break;
        }
    }
}


void data_packet_handler(char *buffer, int size_recieved) {}

void dummy_packet_handler(char *buffer, int size_recieved) {}

void nack_packet_handler(char *buffer, int size_recieved){
    char *checksum, *payload;
    vlong payload_size = get_packet_data_nack(buffer, size_recieved, &checksum, &payload);

    vlong seq_num = atoi(payload);

    hashed_link *hash_node = (hashed_link *)(find_hashl(seq_num));
    if (hash_node == NULL) {
        DBG("Hash node is null, this is not possible");
        exit(1);
    }
    struct node *data_node = (struct node*)((hash_node->data_node_ptr)->obj);

    // Retransmit the data back again with sequence number
    DBG("[RETRANS SEND]: SEQ: %llu", seq_num);
    int n = send_packet(data_node);
    if (n < 0) {
        perror("Retransmiston: Error in sending packet");
        exit(1);
    }

}
