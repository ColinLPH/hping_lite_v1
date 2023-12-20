//
// Created by Colin Lam on 2023-12-19.
//

#include <strings.h>
#include <stdlib.h>
#include "hping.h"
#include "options.h"

int main (int argc, char *argv[])
{
    struct hping_options opts;
    memset(&opts, 0, sizeof(struct hping_options));
    opts.argc = argc;
    opts.argv = argv;

    enum state_codes cur_state = ENTRY;
    enum ret_codes rc;
    int (* state_fun)(void *arg);

    while (1) {
        state_fun = state[cur_state];
        rc = state_fun(&opts);
        if (END == cur_state)
            break;
        cur_state = lookup_transitions(cur_state, rc);
    }

    return EXIT_SUCCESS;

}
