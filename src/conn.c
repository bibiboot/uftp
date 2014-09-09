#include "conn.h"
#include "globals.h"

void reciever_conn_setup(){
     struct sockaddr_in serv_addr;

     if ((globals.recv_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
         perror("Error opening socket");
         exit(1);
     }

     bzero((char *) &serv_addr, sizeof(serv_addr));

     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(globals.config.recv_port);

     if (bind(globals.recv_fd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0){
         perror("Error on bind");
         exit(1);
     }

     listen(globals.recv_fd,5);
}
/*
void sender_conn_setup(){
    struct sockaddr_in serv_addr;
    struct hostent *server;

    if ((globals.sender_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Error opening socket");
        exit(1);
    }

    server = gethostbyname(globals.config.hostname_b);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);

    serv_addr.sin_port = htons(globals.config.recv_port);
    globals.to= (struct sockaddr *)&serv_addr;
    DBG("%p", globals.to);
}
*/

void sender_conn_setup(){
    struct hostent *server;

    if ((globals.sender_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Error opening socket");
        exit(1);
    }

    server = gethostbyname(globals.config.hostname_b);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &globals.serv_addr, sizeof(globals.serv_addr));
    globals.serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr,
         (char *)&(globals.serv_addr).sin_addr.s_addr,
         server->h_length);

    globals.serv_addr.sin_port = htons(globals.config.recv_port);
}

