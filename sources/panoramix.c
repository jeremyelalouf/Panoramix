/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** panoramix
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "panoramix.h"

int panoramix(struct params *params)
{
    struct village *village = create_village(params);

    if (village == NULL)
        return -1;
    for (int i = 0; i != params->nb_villagers; ++i)
        pthread_join(village->villagers[i].thread, NULL);
    if (village->nbr_villagers_alive == 0) {
        pthread_cancel(village->druid.thread);
    }
    destroy_village(village, params);
    return 0;
}
