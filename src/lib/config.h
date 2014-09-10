#pragma once

#define CONFIG_INIT { \
    .filename = "etc/data/read.bin", \
    .packet_size = 8, \
    .a_recv_port = 3002, \
    .b_recv_port = 2002, \
    .hostname_a = "127.0.0.1", \
    .total_size = 0, \
    .rtt = 2, }

struct config {
    // Port to recieve data
    uint16_t a_recv_port;
    uint16_t b_recv_port;
    // RTT of the toplogy
    uint16_t rtt;
    // Packet size to be send
    long long unsigned int packet_size;
    // Total size of the file used to send or recieve
    long long unsigned int total_size;
    // Filename provided in command line which is to be send
    char *filename;
    // Filename to which the recieved file is written
    char *hostname_a;
};


