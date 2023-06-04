/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** druid_method
*/

#include <stdio.h>

#include "panoramix.h"

static void druid_notify_refill(struct druid *this)
{
    pthread_mutex_lock(&(this->refilled.mutex));
    this->refilled.condition = true;
    pthread_cond_signal(&(this->refilled.condvar));
    pthread_mutex_unlock(&(this->refilled.mutex));
}

static void druid_refill(struct druid *this)
{
    this->nb_refills--;
    printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware \
I can only make %d more refills after this one.\n", this->nb_refills);
    this->need_refill.condition = false;
    this->pot = this->default_values->pot_size;
}

void *druid_method(void *arg)
{
    struct druid *this = (struct druid *)arg;

    printf("Druid: I'm ready... but sleepy...\n");
    pthread_mutex_lock(&(this->need_refill.mutex));
    while (this->nb_refills != 0) {
        while (this->need_refill.condition == false) {
            pthread_cond_wait(&(this->need_refill.condvar),
                &(this->need_refill.mutex));
        }
        druid_refill(this);
        druid_notify_refill(this);
    };
    printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
    return NULL;
}
