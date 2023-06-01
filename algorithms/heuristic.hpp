/*
    class to calculate heuristics

    the value of the heuristic is calculated depending on the problem.
    the problem is specified when an object is created,

    the heuristics in the class are
        - 15_puzzle manhattan distance and additive PDB's
        - 24_puzzle additive PDB's
        - rubik3 max corner PDB and 2_edge PDB
        - Top spin: max of differents PDB's
        - Hanoi: max of differentes PDB's
*/
#include <string>

class heuristics {
    char *problem
    int arr_15_puzzle_rows[16];
    int arr_15_puzzle_cols[16];

    void init_heuristic(char *p) {
        problem = p;
        

        if (strcmp(problem, "15_puzzle_manhatan") == 0) {
            // fill the rows and cols arrays
            for (int i = 0; i < 16; i++) {
                arr_15_puzzle_rows[i] = div(i, 4).quot()
                arr_15_puzzle_rows[i] = i % 4;
            }
        }
        /*
            some code to manipulate the abs
        */
    }

    public:
        heuristics() {};

        int get_15_puzzle_manhatan_heuristic(state_t *state) {
            int heuristic = 0, size = 4;
            // value of each variable in the state
            var_t *arr = state->vars
            int num, dist, x, y;

            for (int i = 0; i < size*size; i++) {
                num = (int) arr[i];

                y = i % size;

                if (y % size == 0) x++;
                if (num == 0) continue;

                dist = abs(x-arr_15_puzzle_rows[num]) + abs(y-arr_15_puzzle_cols[num])
                heuristic += dist;
            }

            return heuristic;
        }


        int get_heuristic(state_t *state) {
            if (strcmp(problem, "15_puzzle_manhatan") == 0) {
                return get_15_puzzle_manhatan_heuristic(state);
            }

            return -1;
        }
}