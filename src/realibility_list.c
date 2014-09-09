#include "realibility_list.h"

/**
 * @brief Print nodes of list
 */
void print_list(My402List *list){
    My402ListElem *elem=NULL;
    for (elem=My402ListFirst(list); elem != NULL; elem=My402ListNext(list, elem)) {
        struct node *data_node = (elem->obj);
        DBG("[%p] : SEQ = %d", elem->obj, data_node->seq_num);
    }
}

/**
 * @brief Create list
 *
 */
void create_list(char *data_ptr, My402List *list, const char *list_type){
    // Initialize the data list
    if (My402ListInit(list)==0){
        exit(1);
    }

    // Iterate and add nodes with seq_num and mem address
    uint16_t seq_num = 0;
    for (;seq_num<=globals.config.total_size; seq_num += globals.config.packet_size){
        struct node *data_node = malloc(sizeof(struct node));
        data_node->seq_num = seq_num;
        data_node->mem_ptr = data_ptr + seq_num;

        My402ListElem *link_node;
        if (My402ListAppend(list , data_node, &link_node)==0)
        {
	    printf("Append Failed");
	    exit(1);
        }
        DBG("LINK NODE = %p, SEQ_NUM = %d", link_node, seq_num);

        // Check if DATA or NACK list
        // Add the linked list node pointer to the hashmap node
        if (strcmp(list_type, DATA) == 0) {
            // DATA list
            hashed_link *hash_node = malloc(sizeof(hashed_link));
            hash_node->seq_num = data_node->seq_num;
            hash_node->data_node_ptr = link_node;
            add_hashl(hash_node);
        }
        else {
            // NACK list
            hashed_link *hash_node = (hashed_link *)(find_hashl(data_node->seq_num));
            if (!hash_node) {
                DBG("This should never happen");
                exit(1);
            }
            hash_node->nack_node_ptr = link_node;
        }
    }
}

void print_file_packet_wise(char *data_ptr){
    long long int seq_num = 0;
    char packet_data[globals.config.packet_size];

    //printf("Packet size = %d and First address = %p\n", globals.config.packet_size, data_ptr);

    for (;seq_num < globals.config.total_size;){
        strncpy(packet_data, data_ptr + seq_num, (size_t)globals.config.packet_size);
        memcpy(packet_data, data_ptr + seq_num, (size_t)globals.config.packet_size);
        //printf("Sequence number = [%llu] Packet address = %p and value = %s\n",
        //        seq_num, data_ptr + seq_num, data_ptr + seq_num);
        //printf("Sequence number = [%llu] Copied Packet address = %p and value = %s\n",
                //seq_num, packet_data, packet_data);
        seq_num += globals.config.packet_size;
    }
}
