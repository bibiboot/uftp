#pragma once

#define CONFIG_INIT { \
    .filename = "etc/data/read.bin", \
    .recv_filename = "etc/data/recv.bin", \
    .packet_size = 8, \
    .port = 8081, \
    .total_size = 0, \
    .rtt = 2, }

struct config {
    uint16_t port;
    uint16_t rtt;
    long long unsigned int packet_size;
    long long unsigned int total_size;
    char *filename;
    char *recv_filename;
};


