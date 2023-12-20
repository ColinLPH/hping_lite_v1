#ifndef HPING_LITE_V1_FSM_H
#define HPING_LITE_V1_FSM_H

int entry_state(void *arg);
int parse_args(void *arg);
int set_up(void *arg);
int execute(void *arg);
int clean_up(void *arg);
int print_error(void *arg);
int end_state(void *arg);

enum state_codes { ENTRY, PARSEARGS, SETUP,
    EXECUTE, FATALERROR, CLEANUP, END}; //must be the same order as states

enum ret_codes {ok, error};

struct transition {
    enum state_codes src_state;
    enum ret_codes   ret_code;
    enum state_codes dst_state;
};

struct transition state_transitions[] = {
        {ENTRY, ok, PARSEARGS},
        {PARSEARGS, ok, SETUP},
        {PARSEARGS, error, FATALERROR},
        {SETUP, ok, EXECUTE},
        {SETUP, error, FATALERROR},
        {EXECUTE, ok, CLEANUP},
        {EXECUTE, error, FATALERROR},
        {FATALERROR, ok, CLEANUP},
        {CLEANUP, ok, END}
};

static int compare_transitions(const void *a, const void *b);
static enum state_codes lookup_transitions(enum state_codes current_state, enum ret_codes return_code);

int (* state[])(void *arg) = {entry_state, parse_args, set_up,
                              execute, print_error, clean_up, end_state}; //function pointers go here

#endif
