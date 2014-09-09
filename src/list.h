#include "globals.h"
#include <string.h>

void print_file_packet_wise(char *data_ptr);

void print_list(My402List *list);

void create_list(char *data_ptr, My402List *list, const char *list_type);

void get_current_nack_list();

void add_retransmission_node(long long unsigned int  *retrans_list, int num_retrans);


void create_recv_list(My402List *list, const char *list_type);
