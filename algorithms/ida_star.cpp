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

pair<state_t*, int> f_bounded_dfs_visit(state_t &state, unsigned long int bound, int cost, int hist) {

    // base cases
    int f = cost + g.getHeuristic(state);

    if (f > bound) return make_pair(nullptr, f);

    if (is_goal(&state)) {
        printf("goal reached");
        return make_pair(state, f);
    }

    int t = INT_MAX;

    int rule_id;
    ruleid_iterator_t iter;

    pair<state_t, int> p;
    state_t m;

    init_fwd_iter(&iter, &state);

    while ((rule_id = next_ruleid(&iter)) >= 0) {
        apply_fwd_rule(rule_id, &state, &m);

        int new_cost = cost + get_fwd_rule_cost(rule_id);

        p = f_bounded_dfs_visit(m, bound, new_cost, next_fwd_history(hist, rule_id));

        if (p.first != nullptr) return p;

        t = min(t, p.second);
    }

    free(m);

    return make_pair(nullptr, t);

}


int main(int argc, char **argv) {
    /*
        read input from std in and then, execute IDA* algorithm using PDBs
    */
    char state_str[MAX_STR_LEN + 1];
    ssize_t nchars;
    state_t init_state;
    unsigned long int bound = heuristic(init_state);

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

    // search with increasing f-value bounds
    while (1) {
        make_pair(state_t, unsigned long int) p = f_bounded_dfs_visit(root, bound, 0, init_history);

        if (p.first != nullptr) {
            return p.first;
        }

        bound = p.second;
    }
}
