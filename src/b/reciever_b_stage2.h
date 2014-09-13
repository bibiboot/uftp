#include "globals.h"

void *reciever_stage2(void *v);

void data_packet_handler_stage2(char *buffer, int size_recieved);

void dummy_packet_handler_stage2(char *buffer, int size_recieved);

void nack_packet_handler_stage2(char *buffer, int size_recieved);
