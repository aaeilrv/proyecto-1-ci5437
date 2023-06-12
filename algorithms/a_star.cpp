/*
    implementation of a A* algorithm 
    to find the optimal solution of a given problem
*/

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <sys/time.h>
#include "priority_queue.hpp"
#include "heuristic.hpp"
#include "util.hpp"
#define MAX_STR_LEN 999
using namespace std;

heuristics_t h;

void a_star(state_t* state) {
    PriorityQueue<state_t> p;
    ruleid_iterator_t iter;
    state_map_t *visited;
    state_t curr_state, child_state;
    unsigned long int n_nodes;
    int priority, ruleid, *curr_cost, h_value;
    
    p.Add(h.get_heuristic(state), 0, *state);
    
    visited = new_state_map();
    state_map_add(visited, state, 0); // we already visit the initial state
    
    n_nodes = 0;
    
    while (!p.Empty()) {
        curr_state = p.Top();
        
        priority = p.CurrentPriority() - h.get_heuristic(&curr_state);
        p.Pop();

        n_nodes++;

        curr_cost = state_map_get(visited, &curr_state); // if curr state was visited before, curr_cost == null

        if (curr_cost == nullptr || priority <= *curr_cost) {
            /* stop iteration if curr state is goal state*/
            if (is_goal(&curr_state)) {
                printf("goal reached at depth %d - nodes generated %lu\n", priority, n_nodes);
                destroy_state_map(visited);
                return;
            }

            // add curr state to visited
            state_map_add(visited, &curr_state, priority);
            // loop through the succesor of curr state
            init_fwd_iter(&iter, &curr_state);
            while((ruleid = next_ruleid(&iter)) >= 0) {
                apply_fwd_rule(ruleid, &curr_state, &child_state);
                h_value = h.get_heuristic(&child_state);
                if (h_value < INT_MAX) {
                    state_map_add(visited, &child_state, priority+get_fwd_rule_cost(ruleid)+h_value);
                    p.Add(priority+get_fwd_rule_cost(ruleid)+h_value, priority+get_fwd_rule_cost(ruleid)+h_value, child_state);
                }
            }
        }
    }
    p.Clear();
    destroy_state_map(visited);
    printf("goal never reached, max depth %d - nodes generated %lu", priority, n_nodes);
}

int main(int argc, char **argv) {
    char state_str[MAX_STR_LEN+1], *puzzle;
    ssize_t nchars;
    state_t init_state;

    puzzle = puzzle_name(argv[0]);
    
    printf("puzzle name: %s\n", puzzle);
    
    h.init_heuristic(puzzle);
    
    for (int i = 0; i < 10; i++) {
        // read state from std input
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
    h.destroy_heuristic();
}