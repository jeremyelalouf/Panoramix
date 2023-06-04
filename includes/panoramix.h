/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** panoramix
*/

#ifndef PANORAMIX_H_
    #define PANORAMIX_H_

    #include <pthread.h>
    #include <stddef.h>
    #include <stdbool.h>

typedef void *thread_method_t(void *arg);

struct condvar {
    bool condition;

    pthread_mutex_t mutex;
    pthread_cond_t condvar;
};

struct villager {
    int id;
    pthread_t thread;

    int *pot;
    int nb_fights;

    pthread_mutex_t *lock_pot;
    struct condvar *need_refill;
    struct condvar *refilled;
    int *nbr_villagers_alive;
};

struct druid {
    pthread_t thread;

    int nb_refills;
    int pot;

    struct params *default_values;

    pthread_mutex_t lock_pot;
    struct condvar need_refill;
    struct condvar refilled;
};

struct params {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
};

struct village {
    struct villager *villagers;
    struct druid druid;

    int nbr_villagers_alive;
};

struct params *error_handling(int ac, const char *av[]);
int panoramix(struct params *params);

struct village *create_village(struct params *params);
void destroy_village(struct village *village, struct params *params);

int init_condvar(struct condvar *this);

thread_method_t villager_method;
thread_method_t druid_method;

#endif /* !PANORAMIX_H_ */
