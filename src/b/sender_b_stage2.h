#include "globals.h"

void* main_sender_stage2();

void *sender_stage2(void *v);

int send_dummy_packet_stage2();

int send_packet_stage2(struct node *data_node, bool is_retransmitted);
