/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** create_village
*/

#include <string.h>
#include <stdlib.h>

#include "panoramix.h"

static void create_villager(struct druid *druid, struct villager *res, int id)
{
    memset(res, 0, sizeof(*res));

    res->id = id;
    res->nb_fights = druid->default_values->nb_fights;
    res->pot = &(druid->pot);
    res->lock_pot = &(druid->lock_pot);
    res->need_refill = &(druid->need_refill);
    res->refilled = &(druid->refilled);

    pthread_create(&(res->thread), NULL, &villager_method, res);
}

static void create_druid(struct params *params, struct druid *res)
{
    res->nb_refills = params->nb_refills;
    res->pot = params->pot_size;
    res->default_values = params;

    pthread_mutex_init(&(res->lock_pot), NULL);
    init_condvar(&(res->need_refill));
    init_condvar(&(res->refilled));

    pthread_create(&(res->thread), NULL, &druid_method, res);
}

struct village *create_village(struct params *params)
{
    struct village *res = malloc(sizeof(*res));

    if (res == NULL)
        return NULL;
    res->nbr_villagers_alive = params->nb_villagers;
    res->villagers = malloc(sizeof(*(res->villagers)) * params->nb_villagers);
    if (res->villagers == NULL) {
        free(res);
        return NULL;
    }

    create_druid(params, &(res->druid));

    for (int i = 0; i != params->nb_villagers; ++i) {
        create_villager(&(res->druid), &(res->villagers[i]), (i + 1));
        res->villagers[i].nbr_villagers_alive = &(res->nbr_villagers_alive);
    }
    return res;
}
