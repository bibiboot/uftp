#include "globals.h"
#include <string.h>

void print_file_packet_wise(char *data_ptr);

void print_list(My402List *list);

void create_list(char *data_ptr, My402List *list, const char *list_type);

void get_current_nack_list();
