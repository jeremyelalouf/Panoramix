/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** destroy_village
*/

#include <stdlib.h>

#include "panoramix.h"

void destroy_village(struct village *village, struct params *params)
{
    free(village->villagers);
    pthread_cond_destroy(&(village->druid.need_refill.condvar));
    pthread_mutex_destroy(&(village->druid.need_refill.mutex));
    pthread_mutex_destroy(&(village->druid.lock_pot));
    free(village);
    free(params);
}
