// implementation a tree search using bfs
// and implicit representation for the graphs
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <queue>    // queue library
#include <ctime>
#define  MAX_LINE_LENGTH 999 

using namespace std;

void bread_first_search(state_t *state) {
    state_t curr_state, child_state; 
    queue<state_t> q; // fifo
    ruleid_iterator_t iter;
    clock_t start, end;
    unsigned long int n_child;
    int ruleid, elapsed; 

    // start counting the time
    start = clock();
    q.push(*state);
    
    n_child = 0;

    while (!q.empty()) {
        curr_state = q.front();
        q.pop();

        /*
        if (is_goal(&curr_state)) {
            printf("goal reached, nodes generated = %d \n", n_child);
            return;
        }
        */
        init_bwd_iter(&iter, &curr_state);
        // loop over the successor of curr_state
        while ( (ruleid = next_ruleid(&iter)) >= 0) {
            apply_bwd_rule(ruleid, &curr_state, &child_state);
            q.push(child_state);

            n_child++;
        }

        end = clock();

        elapsed = (end - start)/CLOCKS_PER_SEC;

        if (elapsed >= 300.0) {
            printf("elapesed time: 300 s, nodes generated = %ld \n", n_child);
            return;
        }
    }
}

int main(int argc, char **argv) {
    char str[MAX_LINE_LENGTH+1];
    ssize_t nchars;
    state_t state_0;
    int goal_num;

    first_goal_state(&state_0, &goal_num); // get first goal state
    
    printf("The goal state is: ");
    print_state(stdout, &state_0);
    printf("\n");

    bread_first_search(&state_0);
    
}