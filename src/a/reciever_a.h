#include "globals.h"

void reciever();

void data_packet_handler(char *buffer, int size_recieved);

void dummy_packet_handler(char *buffer, int size_recieved);

void nack_packet_handler(char *buffer, int size_recieved);
