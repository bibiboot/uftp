#pragma once

#define CONFIG_INIT { \
    .filename = "etc/data/read.bin", \
    .packet_size = 1, \
    .port = 8081, \
    .total_size = 0, \
    .rtt = 2, }

struct config {
    uint16_t port;
    uint16_t rtt;
    uint16_t packet_size;
    uint16_t total_size;
    char *filename;
};


