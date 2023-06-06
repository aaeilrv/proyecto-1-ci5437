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

#define MAX_STR_LEN 999

using namespace std;



pair<state_t*, int> f_bounded_dfs_visit(state_t n, unsigned long int bound) {
    // base cases
    int f = n.g + h(n.state);
    if (f > bound) {
        return make_pair(nullptr, f);
    }

    if (is_goal(n.state)) {
        return make_pair(n.state, f);
    }

    float t = numeric_limits<float>::infinity();

    for (auto succ : n.state.succ()) {
        state_t m = n.make_state_t(succ.first, succ.second);

        pair<state_t, unsigned> p = f_bounded_dfs_visit(m, bound);

        if (p.first != nullptr) {
            return p;
        }

        if (t > p.second) {
            t = p.second;
        }
    }

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
        make_pair(state_t, unsigned long int) p = f_bounded_dfs_visit(root, bound);

        if (p.first != nullptr) {
            return p.first;
        }

        bound = p.second;
    }
}