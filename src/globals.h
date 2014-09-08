#pragma once

#include "uthash.h"
#include "config.h"

struct globals {
    struct config config;
};

extern struct globals globals;
