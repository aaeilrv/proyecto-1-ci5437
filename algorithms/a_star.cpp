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
    abstraction_t *abs1, *abs2; 
    state_map_t *visited, *map1, *map2; // eliminar los map_i
    ruleid_iterator_t iter;
    state_t curr_state, child_state, *abs_state;
    unsigned long int n_nodes;
    int priority, ruleid, *curr_cost, child_cost, h1, h2, h;
    FILE *file;

    // eliminar este bloque de codigo e implementar en heuristica
    abs1 = read_abstraction_from_file("abs1.abst");
    if (abs1 == nullptr) {
        printf("file abs1.abst doesnt exist\n");
        return;
    }

    file = fopen("abs1.pdb", "r");
    if (file == nullptr) {
        printf("pdb doesnt exist");
        return;
    }

    map1 = read_state_map(file);

    fclose(file);

    abs2 = read_abstraction_from_file("abs2.abst");
    if (abs2 == nullptr) {
        printf("file abs2.abst doesnt exist\n");
        return;
    }

    file = fopen("abs2.pdb", "r");
    if (file == nullptr) {
        printf("pdb doesnt exist");
        return;
    }
    map2 = read_state_map(file);
    fclose(file);

    
    p.Add(0, 0, *state);
    visited = new_state_map();
    state_map_add(visited, state, 0); // we already visit the initial state
    n_nodes = 0;
    while (!p.Empty()) {
        priority = p.CurrentPriority();
        curr_state = p.Top();
        p.Pop();

        n_nodes++;

        curr_cost = state_map_get(visited, &curr_state); // if curr state was visited before, curr_cost == null

        if (curr_cost == nullptr || priority <= *curr_cost) {
            /* stop iteration if curr state is goal state*/
            if (is_goal(&curr_state)) {
                printf("goal reached at depth %d - nodes generated %lu\n", priority, n_nodes);
                destroy_state_map(map1);
                destroy_state_map(map2);
                destroy_state_map(visited);
                return;
            }

            // add curr state to visited
            state_map_add(visited, &curr_state, priority);
            // loop through the succesor of curr state
            init_fwd_iter(&iter, &curr_state);
            while((ruleid = next_ruleid(&iter)) >= 0) {
                apply_fwd_rule(ruleid, &curr_state, &child_state);

                // calculamos la heuristica
                abs_state = new state_t;
                abstract_state(abs1, &child_state, abs_state);
                h1 = *state_map_get(map1, abs_state);
                
                abstract_state(abs2, &child_state, abs_state);
                h2 = *state_map_get(map2, abs_state);

                h = max(h1, h2);
                if (h < INT_MAX) {
                    state_map_add(visited, &child_state, priority+get_fwd_rule_cost(ruleid)+h);
                    p.Add(priority+get_fwd_rule_cost(ruleid)+h, priority+get_fwd_rule_cost(ruleid)+h, child_state);
                }
            }
        }
    }

    destroy_state_map(map1);
    destroy_state_map(map2);
    destroy_state_map(visited);
    printf("goal never reached, max depth %d - nodes generated %lu", priority, n_nodes);
}

int main(int argc, char **argv) {
    char state_str[MAX_STR_LEN+1];
    ssize_t nchars;
    state_t init_state;
    
    for (int i = 0; i < 10; i++) {
        // read
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
}