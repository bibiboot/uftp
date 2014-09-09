#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>

//char * get_memory_map_ptr(const char *filename, long long int *total_size);
char * get_memory_map_ptr(const char *filename, uint16_t *total_size);
