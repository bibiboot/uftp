#pragma once

#define CONFIG_INIT { \
    .port = 8081, \
    .rtt = 2, }

struct config {
    uint16_t port;
    uint16_t rtt;
};


