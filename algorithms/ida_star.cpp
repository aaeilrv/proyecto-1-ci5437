/*
    implementation of a IDA* algorithm 
    to find the optimal solution of a given problem
*/

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <sys/time.h>
#include <assert.h>
#include <ctime>
#include <utility>
#include <limits>
#include "priority_queue.hpp"
#include "heuristic.hpp"
#include "util.hpp"

#define MAX_STR_LEN 999

using namespace std;

heuristics_t h;

pair<state_t*, int> f_bounded_dfs_visit(state_t* state, unsigned long int bound, int cost, int hist, unsigned long int *nodes) {
    ruleid_iterator_t iter;
    pair<state_t*,int>  p;
    state_t child_state;
    int t, f, rule_id, new_cost;

    f = cost + h.get_heuristic(state);

    if (f > bound) return make_pair(nullptr, f);

    if (is_goal(state)) {
        printf("goal reached at depth: %ld - nodes generated: %ld\n", bound, *nodes);
        return make_pair(state, f);
    }

    t = INT_MAX;
    init_fwd_iter(&iter, state);

    // Iterar por nodo hijo del estado actual
    while ((rule_id = next_ruleid(&iter)) >= 0) {
    
        apply_fwd_rule(rule_id, state, &child_state);

        new_cost = cost + get_fwd_rule_cost(rule_id);

        // no visitar estados que ya fueron visitadores
        if (!fwd_rule_valid_for_history(hist, rule_id)) continue;

        (*nodes)++;
        p = f_bounded_dfs_visit(&child_state, bound, new_cost, next_fwd_history(hist, rule_id), nodes);

        if (p.first != nullptr) return p;

        t = min(t, p.second);
    }

    return make_pair(nullptr, t);
}

/*state_t* ida_search(state_t root) {
    unsigned long int bound, n_nodes;
    bound = h.get_heuristic(&root);

    // search with increasing f-value bounds
    while (1) {
        n_nodes = 0;
        pair<state_t*,int> p = f_bounded_dfs_visit(&root, bound, 0, init_history, &n_nodes);

        if (p.first != nullptr) {
            return p.first;
        }

        bound = p.second;
    }
}*/

int main(int argc, char **argv) {
    char state_str[MAX_STR_LEN + 1], *puzzle;
    ssize_t nchars;
    state_t root;
    unsigned long int bound;
    unsigned long int n_nodes;

    puzzle = puzzle_name(argv[0]);
    printf("puzzle name: %s\n", puzzle);
    h.init_heuristic(puzzle);

    for (int i = 0; i < 10; i++) {

        // read
        if ( fgets(state_str, sizeof state_str, stdin) == NULL) {
            printf("error: empty input line\n");
            return 0;
        }

        // convert string into state
        if ((nchars = read_state(state_str, &root)) <= 0) {
            printf("error: invalid state");
            return 0;
        }

        bound = h.get_heuristic(&root);

        // search with increasing f-value bounds

        //ida_search(root);

        while (1) {
            n_nodes = 0;
            pair<state_t*,int> p = f_bounded_dfs_visit(&root, bound, 0, init_history, &n_nodes);

            if (p.first != nullptr) {
                break;
            }

            bound = p.second;
        }
    }
}