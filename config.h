#ifndef CONFIG_H
#define CONFIG_H

#include "tag.h"

static const Tag fetch[] = {
    "usr", _username,
    "hst", _hostname,
    "ker", _release,
    "mem", _memory,
    "shl", _shell,
    "upt", _uptime,
};


#endif /* CONFIG_H */
