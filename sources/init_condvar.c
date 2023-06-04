/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** init_condvar
*/

#include "panoramix.h"

int init_condvar(struct condvar *this)
{
    this->condition = false;
    if (pthread_mutex_init(&(this->mutex), NULL) != 0)
        return -1;
    if (pthread_cond_init(&(this->condvar), NULL) != 0)
        return -1;
    return 0;
}
