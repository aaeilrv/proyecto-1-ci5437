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
    float elapsed; 
    int ruleid, expected; 

    // start counting the time
    start = clock();
    q.push(*state);
    
    // initialize excepcted 
    expected = 1; // this variable is to show the elapsed time and the nodes genereated so far every 10 seconds

    n_child = 0;

    while (!q.empty()) {
        curr_state = q.front();
        q.pop();

        init_bwd_iter(&iter, &curr_state);
        // loop over the successor of curr_state
        while ( (ruleid = next_ruleid(&iter)) >= 0) {
            apply_bwd_rule(ruleid, &curr_state, &child_state);
            q.push(child_state);

            n_child++;
        }

        end = clock();

        elapsed = (end - start)/(double)CLOCKS_PER_SEC;

        // show elapsed time every 10 seconds
        if ((int)elapsed / 10 == expected) {
            printf("elapsed time: %f s, nodes generated = %ld \n", elapsed, n_child);
            expected++;
        }

        if (elapsed >= 60) {
            printf("nodes generated per second = %f\n", n_child/elapsed);
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