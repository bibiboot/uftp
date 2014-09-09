#include "mmap.h"

char * get_memory_map_ptr(const char *filename, uint16_t *total_size){
    int fd, offset=100;
    char *data;
    struct stat sbuf;

    if ((fd = open(filename, O_RDONLY)) == -1) {
	perror("open");
	exit(1);
    }

   if (stat(filename, &sbuf) == -1) {
	perror("stat");
	exit(1);
   }

    if ((data = mmap((caddr_t)0, sbuf.st_size, PROT_READ, MAP_SHARED, fd, 0)) == (caddr_t)(-1)) {
	perror("mmap");
	exit(1);
    }

    *total_size = (long long int)sbuf.st_size;
    offset = *total_size;
    return data;
}
