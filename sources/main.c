/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** main
*/

#include <stddef.h>

#include "panoramix.h"

int main(int argc, const char *argv[])
{
    struct params *params = NULL;

    params = error_handling(argc, argv);
    if (params == NULL)
        return 84;
    if (panoramix(params) == -1)
        return 84;
    return 0;
}
