#include "darksys.h"

void darksys_init(darksys *$, void *(*update)(), uint16_t params, uint16_t capacity)
{
    $->update = update;
    $->params = params;

    uclist_init_add(&$->list, capacity * params);
}

uint16_t darksys_add(darksys *$, void *data[])
{
    void **items = (void **)$->list.items;
    uint16_t size = $->list.size;
    uint16_t params = $->params;

    for (uint16_t i = 0; i < size; i++)
        for (uint16_t j = 0; j < params; j++)
            if (items[i] == data[j])
                return 0;

    for (uint16_t i = 0; i < params; i++)
        uclist_add(&$->list, data[i]);

    return 1;
}

uint16_t darksys_delete(darksys *$, void *data)
{
    void **items = (void **)$->list.items;
    uint16_t size = $->list.size;
    uint16_t params = $->params;

    for (uint16_t i = 0; i < size; i++)
        if (items[i] == data)
        {
            uint16_t start = (i / params) * params;
            uint16_t new_size = size - params;

            if (start != new_size)
            {
                void **src = &items[new_size];
                void **dst = &items[start];

                for (i = 0; i < params; i++)
                    *dst++ = *src++;
            }

            $->list.size = new_size;

            return 1;
        }

    return 0;
}

void darksys_update(darksys *$)
{
    if ($->list.size && $->update)
        $->update($);
}

void darksys_reset(darksys *$)
{
    uclist_reset(&$->list);
}

void darksys_end(darksys *$)
{
    uclist_end(&$->list);
}
