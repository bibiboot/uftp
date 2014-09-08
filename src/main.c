#include <stdio.h>
#include "globals.h"
#include "hashl.h"
#include "mmap.h"

/*
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
*/

void test_ll(){
    My402ListElem *elem = NULL;
    int *temp;
    int i,j,k,l;

    //List Initialization
    if (My402ListInit(&globals.datal)==0){
	printf("Initialization of the list failed");
	return ;
    }
    //Creating the List
    i=10;
    j=20;
    k=30;

    if (My402ListAppend(&globals.datal , &i)==0)
    {
	printf("Append Failed");
	return;
    }

    printf("\nNode Value :%d \n",i);
    /*
    if (My402ListAppend(&Q1 , &j)==0){
        printf("Append Failed");
        return ;
    }
    printf("\nNode Value :%d \n",j);

    if (My402ListAppend(&Q1 , &k)==0){
	printf("Append Failed");
	return ;
    }
    printf("\nNode Value :%d \n",k);

    //Deleting the list
    for(l=0;l<3;l++)
    {
	elem = My402ListFirst(&Q1);
	temp = elem-> obj;
	printf("\nDeleted Value is %d", *temp);
	My402ListUnlink(&Q1,elem);
    }
    printf("\n\n-----------------Program Ends----------------------\n");
    */
}

void test_hashmap(){
    void *chunk_ptr = malloc(sizeof(100));
    strcpy(chunk_ptr, "Hello");
    hashed_link h = { .seq_num = 1 , .dl_ptr = chunk_ptr  };
    add_hashl(&h);

    hashed_link *result = (hashed_link *)(find_hashl(1));
    printf("Name = %s\n", (result->dl_ptr));
}

void test_global(){
    printf("PORT = %d\n", globals.config.port);
}

int main(int argc, char *argv[]){
    test_ll();
    test_global();
    test_hashmap();

    char *filename = "etc/data/data.bin";
    long long int total_file_size = 0;
    char *data_ptr = get_memory_map_ptr(filename, &total_file_size);
}
