#pragma once

#include <stdint.h>
#include "../glibs/uclist.h"

typedef struct darksys
{
    uclist list;
    void (*update)(struct darksys *);
    uint16_t params;
} darksys;

void darksys_init(darksys *, void *(*)(), uint16_t, uint16_t);
uint16_t darksys_add(darksys *, void *[]);
uint16_t darksys_delete(darksys *, void *);
void darksys_update(darksys *);
void darksys_reset(darksys *);
void darksys_end(darksys *);

#define DARKSYS_FOREACH(...) _SYS_GET_MACRO(__VA_ARGS__, _SYS_FOREACH_5, _SYS_FOREACH_4, _SYS_FOREACH_3, _SYS_FOREACH_2, _SYS_FOREACH_1, _SYS_FOREACH_0)(__VA_ARGS__)
#define DARKSYS_ITERATOR(...) _SYS_GET_MACRO(__VA_ARGS__, _SYS_ITERATOR_5, _SYS_ITERATOR_4, _SYS_ITERATOR_3, _SYS_ITERATOR_2, _SYS_ITERATOR_1, _SYS_ITERATOR_0)(__VA_ARGS__)

//

#define _SYS_GET_MACRO(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME

#define _SYS_FOREACH(SYSTEM, IT)                              \
    void **items = SYSTEM->list.items;                        \
    for (uint16_t i = 0, size = SYSTEM->list.size; i < size;) \
        IT;

//

#define _SYS_FOREACH_0(SYSTEM, IT) \
    _SYS_FOREACH(SYSTEM, { IT; })

#define _SYS_FOREACH_1(SYSTEM, A, IT) \
    _SYS_FOREACH(SYSTEM, { A = items[i++]; IT; })

#define _SYS_FOREACH_2(SYSTEM, A, B, IT) \
    _SYS_FOREACH(SYSTEM, { A = items[i++]; B = items[i++]; IT; })

#define _SYS_FOREACH_3(SYSTEM, A, B, C, IT) \
    _SYS_FOREACH(SYSTEM, { A = items[i++]; B = items[i++]; C = items[i++]; IT; })

#define _SYS_FOREACH_4(SYSTEM, A, B, C, D, IT) \
    _SYS_FOREACH(SYSTEM, { A = items[i++]; B = items[i++]; C = items[i++]; D = items[i++]; IT; })

#define _SYS_FOREACH_5(SYSTEM, A, B, C, D, E, IT) \
    _SYS_FOREACH(SYSTEM, { A = items[i++]; B = items[i++]; C = items[i++]; D = items[i++]; E = items[i++]; IT; })

//

#define _SYS_ITERATOR_0(NAME, IT) \
    void NAME(darksys *system) { _SYS_FOREACH_0(system, IT); }

#define _SYS_ITERATOR_1(NAME, A, IT) \
    void NAME(darksys *system) { _SYS_FOREACH_1(system, A, IT); }

#define _SYS_ITERATOR_2(NAME, A, B, IT) \
    void NAME(darksys *system) { _SYS_FOREACH_2(system, A, B, IT); }

#define _SYS_ITERATOR_3(NAME, A, B, C, IT) \
    void NAME(darksys *system) { _SYS_FOREACH_3(system, A, B, C, IT); }

#define _SYS_ITERATOR_4(NAME, A, B, C, D, IT) \
    void NAME(darksys *system) { _SYS_FOREACH_4(system, A, B, C, D, IT); }

#define _SYS_ITERATOR_5(NAME, A, B, C, D, E, IT) \
    void NAME(darksys *system) { _SYS_FOREACH_5(system, A, B, C, D, E, IT); }
