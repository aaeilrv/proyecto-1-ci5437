/*
    implementation of a A* algorithm 
    to find the optimal solution of a given problem
*/

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <sys/time.h>
#include "priority_queue.hpp"

#define MAX_STR_LEN 999

using namespace std;

void a_star(state_t *state) {
    PriorityQueue<state_t> p;
    state_map_t *visited = new_state_map();
    ruleid_iterator_t iter;
    state_t curr_state, child_state;
    unsigned long int n_nodes;
    int priority, ruleid, *curr_cost, child_cost;

    p.Add(0, 0, *state);
    state_map_add(visited, state, 0); // we already visit the initial state
    n_nodes++;

    while (!p.Empty()) {
        priority = p.CurrentPriority();
        curr_state = p.Top();
        p.Pop();

        n_nodes++;

        curr_cost = state_map_get(visited, &curr_state); // if curr state was visited before, curr_cost == null

        if (curr_cost == nullptr) {
            /* stop iteration if curr state is goal state*/
            if (is_goal(&curr_state)) {
                printf("goal reached at depth %d - nodes generated %lu", priority, n_nodes);
                destroy_state_map(visited);
                return;
            }

            // loop through the succesor of curr state
            init_fwd_iter(&iter, &curr_state);
            while((ruleid = next_ruleid(&iter)) >= 0) {
                apply_fwd_rule(ruleid, &curr_state, &child_state);
                /* use heuristic */
                child_cost = priority + get_fwd_rule_cost(ruleid);
                p.Add(child_cost, child_cost, child_state); 
                state_map_add(visited, &child_state, child_cost);
            }
        }
    }

    destroy_state_map(visited);
    printf("goal never reached, max depth %d - nodes generated %lu", priority, n_nodes);
}

int main(int argc, char **argv) {
    /*
        read input from std in and then, execute a_star algorithm using pdbs or wathever
    */
    char state_str[MAX_STR_LEN+1];
    ssize_t nchars;
    state_t init_state;

    // read
    printf("enter init state: ");
    if ( fgets(state_str, sizeof state_str, stdin) == NULL) {
        printf("error: empty input line\n");
        return 0;
    }

    // convert string into state
    if ((nchars = read_state(state_str, &init_state)) <= 0) {
        printf("error: invalid state");
        return 0;
    }

    a_star(&init_state);
}