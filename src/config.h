#pragma once

#define CONFIG_INIT { \
    .filename = "etc/data/read.bin", \
    .recv_filename = "etc/data/recv.bin", \
    .packet_size = 8, \
    .sender_port = 8084, \
    .recv_port = 9095, \
    .hostname_a = "127.0.0.1", \
    .hostname_b = "127.0.0.1", \
    .total_size = 0, \
    .rtt = 2, }

struct config {
    // Port to send data
    uint16_t sender_port;
    // Port to recieve data
    uint16_t recv_port;
    // RTT of the toplogy
    uint16_t rtt;
    // Packet size to be send
    long long unsigned int packet_size;
    // Total size of the file used to send or recieve
    long long unsigned int total_size;
    // Filename provided in command line which is to be send
    char *filename;
    // Filename to which the recieved file is written
    char *recv_filename;
    char *hostname_a;
    char *hostname_b;
};


