//
// Created by Colin Lam on 2023-12-19.
//
#include <stdlib.h>
#include "fsm.h"

/* Comparison function for binary search */
static int compare_transitions(const void *a, const void *b) {
    struct transition *transitionA = (struct transition *)a;
    struct transition *transitionB = (struct transition *)b;

    if (transitionA->src_state == transitionB->src_state) {
        return (int)(transitionA->ret_code) - (int)(transitionB->ret_code);
    } else {
        return (int)(transitionA->src_state) - (int)(transitionB->src_state);
    }
}

/* Function to look up the next state based on current state and return code using binary search */
static enum state_codes lookup_transitions(enum state_codes current_state, enum ret_codes return_code) {
    struct transition key = {current_state, return_code, 0};
    struct transition *result;

    result = (struct transition *)bsearch(&key, state_transitions, sizeof(state_transitions) / sizeof(struct transition),
                                          sizeof(struct transition), compare_transitions);

    if (result != NULL) {
        return result->dst_state;
    } else {
        return END;
    }
}
