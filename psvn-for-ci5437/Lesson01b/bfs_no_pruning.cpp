// implementation a tree search using bfs
// and implicit representation for the graphs
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#define  MAX_LINE_LENGTH 999 

using namespace std;

void bread_first_search(state_t *state) {
    state_t curr_state, child_state; 
    queue<state_t> q; // fifo
    ruleid_iterator_t iter;
    int ruleid, depth; // curr depth of the search

    depth = 0;
    q.push(*state);

    while (!q.empty()) {
        curr_state = q.front();
        q.pop();

        if (is_goal(&curr_state)) {
            printf("goal reached in depth = %d \n", depth);
            return;
        }

        init_fwd_iter(&iter, &curr_state);
        // loop over the successor of curr_state
        while ( (ruleid = next_ruleid(&iter)) >= 0) {
            apply_fwd_rule(ruleid, &curr_state, &child_state);
            q.push(child_state);
        }

        depth++;
    }

    printf("goal is never reached");
}

int main(int argc, char **argv) {
    char str[MAX_LINE_LENGTH+1];
    ssize_t nchars;
    state_t state_0;

    // read a line from stdin
    printf("Please enter a state followed by ENTER: ");
    if( fgets(str, sizeof str, stdin) == NULL ) {
        printf("Error: empty input line.\n");
        return 0; 
    }


    // CONVERT THE STRING TO A STATE
    nchars = read_state(str, &state_0);
    if( nchars <= 0 ) {
        printf("Error: invalid state entered.\n");
        return 0; 
    }

    printf("The state you entered is: ");
    print_state(stdout, &state_0);
    printf("\n");

    bread_first_search(&state_0);

    
}