#ifndef TAG_H
#define TAG_H

typedef
struct Tag {
    const char name[40];
    const char *(*fnc)(void);
} Tag;

const char *
_username(void);

const char *
_hostname(void);

const char *
_release(void);

const char *
_memory(void);

const char *
_uptime(void);

const char *
_shell(void);

#endif /* TAG_H */

