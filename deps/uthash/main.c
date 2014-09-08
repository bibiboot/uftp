#include "uthash.h"
#include <stdio.h>

typedef struct my_struct {
    int id;
    char name[10];
    UT_hash_handle hh;
} mys;

mys *users = NULL;

void add_user(mys *s){
    HASH_ADD_INT( users, id, s);
}

mys *find_user(int user_id){
    mys *s;
    HASH_FIND_INT( users, &user_id, s);
    return s;
}

int main(int argc, char *argv[]){
    mys s= { .id = 1 , .name = "George" };
    add_user(&s);

    mys *result = find_user(1);
    printf("Name = %s\n", result->name);
    return 0;
}
