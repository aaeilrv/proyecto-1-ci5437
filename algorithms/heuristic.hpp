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
#include <iostream>
using namespace std;

class heuristics {
    char *problem;
    abstraction_t *abs1, *abs2;
    state_map_t *map1, *map2;

    public:
        heuristics() {};
        void init_heuristic() {
            FILE *file;

            abs1 = read_abstraction_from_file("abs1.abst");
            if (abs1 == nullptr) {
                cout << "file abs1.abst not found" << endl;
                return;
            }
            
            abs2 = read_abstraction_from_file("abs2.abst");
            if (abs2 == nullptr) {
                cout << "file abs2.abst not found" << endl;
                return;
            }

            file = fopen("abs1.pdb", "r");
            if (file == nullptr) {
                cout << "file abs1.pdb not found" << endl;
                return;
            }
            map1 = read_state_map(file);
            fclose(file);

            file = fopen("abs2.pdb", "r");
            if (file == nullptr) {
                cout << "file abs2.pdb not found" << endl;
                return;
            }
            map2 = read_state_map(file);
            fclose(file);
        }


        int top_spin(state_t *state) {
            state_t *abs_state = new state_t;
            int h1, h2;

            abstract_state(abs1, state, abs_state);
            h1 = *state_map_get(map1, abs_state);

            abstract_state(abs2, state, abs_state);
            h2 = *state_map_get(map2, abs_state);

            return max(h1, h2);
        }

        void destroy_heuristic() {
            destroy_state_map(map1);
            destroy_state_map(map2);
        }
};