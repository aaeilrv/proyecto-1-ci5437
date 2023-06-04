/*
    implementation of a A* algorithm 
    to find the optimal solution of a given problem
*/

#include <stdlib.h>
#include <stdio.h>
#include <priority_queue.hpp>

using namespace std;

void a_star(state_t state) {
    PriorityQueue<state_t> p;
    ruleid_iterator_t iter;
    state_t curr_state, child_state;
    int priority, ruleid;

    p.Add(state);

    while (!q.Empty()) {
        curr_state = q.Top();
        q.Pop();

        // todo
        if (curr_state) {
            if curr_state.is_goal() {
                return 0;
            }

            init_fwd_iter(&iter, &curr_state);

            whlie((ruleid = next_ruleid(&iter)) >= 0) {
                apply_fwd_rule(ruleid, &curr_satte, &child_state);
                if (h(child_state)) < inf {
                    q.Add(child_state);
                }
            }
        }
    }
}

int main(int argc; char **argv) {
    return 0;
}