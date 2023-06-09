/*
    implementation of a IDA* algorithm 
    to find the optimal solution of a given problem
*/

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

#define MAX_STR_LEN 999

using namespace std;

heuristics_t h;

pair<state_t*, int> f_bounded_dfs_visit(state_t *state, unsigned long int bound, int cost, int hist) {
    // base cases
    ruleid_iterator_t iter;
    pair<state_t*,int>  p;
    state_t child_state;
    int t, f, rule_id, new_cost;

    f = cost + h.get_heuristic(state);

    if (f > bound) return make_pair(nullptr, f);

    if (is_goal(state)) {
        printf("goal reached\n");
        return make_pair(state, f);
    }

    t = INT_MAX;
    init_fwd_iter(&iter, state);

    while ((rule_id = next_ruleid(&iter)) >= 0) {
        apply_fwd_rule(rule_id, state, &child_state);

        new_cost = cost + get_fwd_rule_cost(rule_id);

        p = f_bounded_dfs_visit(&child_state, bound, new_cost, next_fwd_history(hist, rule_id));

        if (p.first != nullptr) return p;

        t = min(t, p.second);
    }

    return make_pair(nullptr, t);
}

int main(int argc, char **argv) {
    char state_str[MAX_STR_LEN + 1];
    ssize_t nchars;
    state_t root;
    unsigned long int bound;

    h.init_heuristic("15_puzzle");

    for (int i = 0; i < 10; i++) {

        // read
        printf("enter init state: ");
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
        while (1) {
            pair<state_t*,int> p = f_bounded_dfs_visit(&root, bound, 0, init_history);

            if (p.first != nullptr) {
                break;
            }

            bound = p.second;
        }
    }
}
