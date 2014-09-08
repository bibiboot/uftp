#include "realibility_list.h"
#include "string.h"

int packet_size = 100;

void create_data_list(long long int total_size){
    // Create linked list
    // Add memory pointer
    // Add sequence number
    // Add in hashmap with key as sequence num

    long long int seq_num = 0;
    for (;seq_num<=total_size;){
        printf("seq number = %lld\n", seq_num);
        seq_num += packet_size;
    }
}

void create_nack_list(){
    // Create linked list
    // Add sequence number
    // Add in hashmap with key as sequence num
}

void print_file_packet_wise(char *data_ptr, long long int total_size){
    long long int seq_num = 0;
    void *packet_data;
    for (;seq_num<=total_size;){
        memcpy(packet_data, data_ptr[seq_num], packet_size);
        printf("seq number = %lld and data = %s\n", seq_num, (void *)packet_data);
        seq_num += packet_size;
    }
}
