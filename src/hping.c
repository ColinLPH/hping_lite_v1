//
// Created by Colin Lam on 2023-12-19.
//

#include "hping.h"

int entry_state(void *arg)
{
    printf("Starting...\n");
    return ok;
}

int parse_args(void *arg)
{
    struct hping_options *opts = (struct hping_options *) arg;
    return ok;
}

int set_up(void *arg)
{
    struct hping_options *opts = (struct hping_options *) arg;
    return ok;
}

int execute(void *arg)
{
    struct hping_options *opts = (struct hping_options *) arg;
    return ok;
}

int clean_up(void *arg)
{
    struct hping_options *opts = (struct hping_options *) arg;
    return ok;
}

int print_error(void *arg)
{
    struct hping_options *opts = (struct hping_options *) arg;
    return ok;
}

int end_state(void *arg)
{
    return ok;
}
