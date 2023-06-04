/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** error_handling
*/

#include <string.h>
#include <stdlib.h>

#include "panoramix.h"

static void fill_params(struct params *res, int val[4])
{
    res->nb_villagers = val[0];
    res->pot_size = val[1];
    res->nb_fights = val[2];
    res->nb_refills = val[3];
}

struct params *error_handling(int ac, const char *av[])
{
    struct params *res = malloc(sizeof(struct params));
    int val[4] = {0};

    if (res == NULL)
        return NULL;
    if (ac != 5) {
        free(res);
        return NULL;
    }
    memset(res, 0, sizeof(struct params));
    for (int i = 0; i != (ac - 1); ++i) {
        val[i] = atoi(av[i + 1]);
        if (val[i] <= 0) {
            free(res);
            return NULL;
        }
    }
    fill_params(res, val);
    return res;
}
