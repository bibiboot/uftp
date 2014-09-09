#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include "globals.h"

void write_packet_to_file(FILE *fp, struct node *data_node);
char * get_memory_map_ptr(const char *filename, long long unsigned int *total_size);
void write_data_list_to_file();
