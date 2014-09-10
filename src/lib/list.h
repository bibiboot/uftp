#include "globals.h"
#include <string.h>

void get_current_nack_list();

void print_list(My402List *list);

void print_file_packet_wise(char *data_ptr);

void create_recv_list(My402List *list, const char *list_type);

void create_list(char *data_ptr, My402List *list, const char *list_type);

void add_retransmission_node(long long unsigned int  *retrans_list, int num_retrans);
