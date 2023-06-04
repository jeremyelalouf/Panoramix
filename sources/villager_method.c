/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** villager_method
*/

#include <stdio.h>

#include "panoramix.h"

static void villager_fight(struct villager *this)
{
    this->nb_fights -= 1;
    printf("Villager %d: Take that roman scum! Only %d left.\n",
        this->id, this->nb_fights);
}

static bool villager_ask(struct villager *this)
{
    pthread_mutex_lock(this->lock_pot);
    printf("Villager %d: I need a drink... I see %d servings left.\n",
        this->id, *(this->pot));
    if (*(this->pot) != 0) {
        *(this->pot) -= 1;
        pthread_mutex_unlock(this->lock_pot);
        return true;
    }
    return false;
}

static void villager_ask_refill(struct villager *this)
{
    pthread_mutex_lock(&(this->need_refill->mutex));
    this->need_refill->condition = true;
    pthread_cond_signal(&(this->need_refill->condvar));
    pthread_mutex_unlock(&(this->need_refill->mutex));

    pthread_mutex_lock(&(this->refilled->mutex));

    while (this->refilled->condition == false) {
        pthread_cond_wait(&(this->refilled->condvar),
            &(this->refilled->mutex));
    }
    this->refilled->condition = false;

    pthread_mutex_unlock(&(this->refilled->mutex));

    pthread_mutex_unlock(this->lock_pot);
}

void *villager_method(void *arg)
{
    struct villager *this = (struct villager *)arg;

    printf("Villager %d: Going into battle!\n", this->id);
    while (this->nb_fights != 0) {
        if (villager_ask(this) == true)
            villager_fight(this);
        else
            villager_ask_refill(this);
    }
    printf("Villager %d: I'm going to sleep now.\n", this->id);
    *(this->nbr_villagers_alive) -= 1;
    return NULL;
}
