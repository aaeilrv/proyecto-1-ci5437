// implementation a tree search using bfs
// and implicit representation for the graphs
#include <stdlib.h>
#include <stdio.h>
#include <queue>    // queue library

using namespace std;

void bread_first_search(state_t *state) {
    state_t curr_state, child_state; 
    queue<state_t> q; // fifo
    ruleid_iterator_t iter;
    unsigned long int n_child, n_child_at_depth;
    int ruleid, curr_depth = 0;

    q.push(*state);
    

    while (!q.empty()) {
        n_child_at_depth = q.size();
        n_child = 0;


        // loop over the successor of curr_state
        for (int i = 0; i < n_child_at_depth; i++) {
            curr_state = q.front();
            q.pop();
            init_bwd_iter(&iter, &curr_state);
            while ((ruleid = next_ruleid(&iter)) >= 0) {
                apply_bwd_rule(ruleid, &curr_state, &child_state);
                q.push(child_state);

                n_child++;
            }
        }

        printf("depth %d - nodes generated: %ld - branch factor %.2f\n", curr_depth, n_child_at_depth, (float)n_child/n_child_at_depth);
        curr_depth++;
    }
}

int main(int argc, char **argv) {
    state_t state_0;
    int goal_num;

    first_goal_state(&state_0, &goal_num); // get first goal state
    
    printf("The goal state is: ");
    print_state(stdout, &state_0);
    printf("\n");

    bread_first_search(&state_0);
    
}