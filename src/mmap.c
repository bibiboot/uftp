#include "mmap.h"

char * get_memory_map_ptr(const char *filename, long long unsigned int *total_size){
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

    *total_size = (long long unsigned int)sbuf.st_size;
    offset = *total_size;
    return data;
}

void write_data_list_to_file(){
    // Open the file for writing
    FILE *fp = fopen(globals.config.recv_filename, "w");
    if (fp == NULL){
        DBG("Can not open file for writing");
        exit(0);
    }

    My402ListElem *elem=NULL;
    // Iterate over the data list
    for (elem=My402ListFirst(&globals.datal); elem != NULL; elem=My402ListNext(&globals.datal, elem)) {
        struct node *data_node = (elem->obj);
        DBG("[%p] : SEQ = %llu", elem->obj, data_node->seq_num);
        // Write a packet into the file
        write_packet_to_file(fp, data_node);
    }

    fclose(fp);
}

void write_packet_to_file(FILE *fp, struct node *data_node){
    //DBG("Writing %s", buffer);
    int n = fwrite(data_node->mem_ptr, 1, data_node->size, fp);
    DBG("%d", n);
    /*
    if (fwrite(buffer, 1, globals.config.packet_size, fp) != globals.config.packet_size){
        DBG("Error in writing");
        exit(0);
    }*/
}
