#include "reciever_b.h"

#define RECV_WINDOW 1500

char filename[100] = "etc/data/recv.bin";

bool is_last_packet_recieved() {
    return globals.last_bit_arrived;
}

void reciever(){

    while (1){
        // If last packet is recieved
        // break out of the loop
        if (is_last_packet_recieved() &&
            is_nack_list_empty()) {
            // Delete the nack timer
            // Break out of the loop
            // Return
            // TODO: Delete the nack timer
            DBG("NACK is EMPTY");
            goto COMPLETE_FILE_REACHED;
        }

        //DBG(".........Waiting.......");
        int n=recv_packet();
    }
COMPLETE_FILE_REACHED:
    DBG("Complete file is downloaded");
    write_data_list_to_file(filename);
}

int recv_packet(){
    char buffer[RECV_WINDOW];
    bzero(buffer, RECV_WINDOW);

    struct sockaddr_in from;
    int fromlen = sizeof(struct sockaddr_in);

    int size_recieved=recvfrom(globals.b_recv_fd, buffer, 1024, 0,
                               (struct sockaddr *)&from, &fromlen);
    if (size_recieved < 0) {
        perror("Error in recv");
        exit(1);
    }

    //DBG("[%d] Seq: [%llu], Recv: [%s], Payload: [%s]",
    //    size_recieved, seq_num, buffer,
    //    buffer+PACKET_TYPE_LEN+SEQ_NUM_LEN+CHECKSUM_LEN);

    // Check the packet with checksum
    // If no match then return i.e. drop packet
    int packet_type = get_recieved_packet_type(buffer);

    switch (packet_type) {
        case DATA_PACKET:
            data_packet_handler(buffer, size_recieved);
            break;
        case NACK_PACKET:
            //nack_packet_handler(size_recieved);
            break;
        case DUMMY_PACKET:
            dummy_packet_handler(buffer, size_recieved);
            break;
    }
    return size_recieved;
}

void data_packet_handler(char *buffer, int size_recieved) {

    char *seq_num, *checksum, *payload;
    vlong payload_size = get_packet_data(buffer, size_recieved, &seq_num, &checksum, &payload);
    vlong sq_num= atoll(seq_num);

    //DBG("RECIEVED: [%d], SEQ: [%s], CHECKSUM: [%s], PAYLOAD: [%s]",
        //size_recieved, seq_num, checksum, payload);
    DBG("RECIEVED: [%d], SEQ: [%s], CHECKSUM: [%s]",
        size_recieved, seq_num, checksum);

    // Checksum matched and sequence number known
    // Update the memory pointer
    update_mem_ptr_data_link(payload, sq_num, payload_size);

    // Remove the node from the nack list
    delete_node_nack_list(sq_num);
}

void dummy_packet_handler(char *buffer, int size_recieved) {
    // On the bit for last bit arrived
    globals.last_bit_arrived = true;
    DBG("DUMMY PACKET: [%s]", buffer);

    // Get checksum and filename of the destination
    char *checksum, *payload;
    vlong payload_size = get_packet_data_dummy(buffer, size_recieved, &checksum, &payload);
    // Payload here is the filename
}
