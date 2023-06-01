/* implementation a tree search using iddfs
   and implicit representation for the graphs
   
   the idea is expand the tree by depth and store de number
   of nodes generated in each depth (bound)
*/
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <ctime>

void bounded_dfs_visit(state_t state, int curr_depth, int max_depth, unsigned long int *nodes, int hist) {
    state_t child_state;
    ruleid_iterator_t iter;
    int ruleid;
    
    if (curr_depth>=max_depth) {
        return;
    }

    init_bwd_iter(&iter, &state);

    // loop over the successor of state
    while ((ruleid = next_ruleid(&iter)) >= 0) {

        // if the ruleid should not be aplied
        if(bwd_rule_valid_for_history(hist, ruleid)==0) continue;
        apply_bwd_rule(ruleid, &state, &child_state);
        *nodes = *nodes + 1;
        bounded_dfs_visit(child_state, curr_depth+1, max_depth, nodes, next_bwd_history(hist, ruleid));
    }

    return ;
}

void iddfs(state_t state) {
    int depth;
    unsigned long int n_nodes;
    
    depth = 0;
    n_nodes = 0;
    while (1) {
        
        bounded_dfs_visit(state, 0, depth, &n_nodes, init_history);

        printf("depth: %d. nodes %ld\n", depth, n_nodes);

        depth++;
    }
}

int main(int argc, char **argv) {
    state_t state_0;
    int goal_num;

    first_goal_state(&state_0, &goal_num); // get first goal state
    
    printf("The goal state is: ");
    print_state(stdout, &state_0);
    printf("\n");

    iddfs(state_0);
    
}