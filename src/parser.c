#include "parser.h"

#define NACK 0
#define DUMMY 1
#define DATA 2

/**
 * @brief Get recieved packet type
 *
 * @param packet start address of the buffer
 * @param size total size of the packet
 * @return NACK
 *         DUMMY
 *         DATA
 */
int get_recieved_packet_type(char *packet, long long unsigned int size){
    return DATA;
}

/**
 * @brief Get payload of the data
 *        Parse according to the packet type
 *        and retrieve the payload inside the packet
 *
 * @param packet_type type of packet
 * @return corrected start address of memory
 */
char *get_payload(int packet_type){
    // Switch and add methods for different types
    char *temp;
    return temp;
}
