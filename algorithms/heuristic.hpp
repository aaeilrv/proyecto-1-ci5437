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

class heuristics_t {
    char *problem;
    abstraction_t *abs1, *abs2, *abs3, *abs4, *abs5;
    state_map_t *map1, *map2, *map3, *map4, *map5;

    public:
        heuristics() {};
        void init_heuristic(char *p) {
            problem = p;
            FILE *file;

            /*
                read abstraction and pdbs depending on the problem
            */

            if (problem != '15_puzzle_manhattan') {
                
                /*
                    every puzzle have at least 2 abstractions
                */
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

                /*
                    check for puzzles that have at least 3 abstractions
                */
                if (problem == '15_puzzle' || problem == '24_puzzles') {
                    abs3 = read_abstraction_from_file("abs3.abst");
                    if (abs1 == nullptr) {
                        cout << "file abs3.abst not found" << endl;
                        return;
                    }

                    file = fopen("abs3.pdb", "r");
                    if (file == nullptr) {
                        cout << "file abs3.pdb not found" << endl;
                        return;
                    }
                    map3 = read_state_map(file);
                    fclose(file);
                }

                if (problem == '24_puzzle') {
                    abs4 = read_abstraction_from_file("abs4.abst");
                    if (abs1 == nullptr) {
                        cout << "file abs3.abst not found" << endl;
                        return;
                    }

                    file = fopen("abs4.pdb", "r");
                    if (file == nullptr) {
                        cout << "file abs4.pdb not found" << endl;
                        return;
                    }
                    map4 = read_state_map(file);
                    fclose(file);

                    abs5 = read_abstraction_from_file("abs5.abst");
                    if (abs1 == nullptr) {
                        cout << "file abs5.abst not found" << endl;
                        return;
                    }

                    file = fopen("abs5.pdb", "r");
                    if (file == nullptr) {
                        cout << "file abs5.pdb not found" << endl;
                        return;
                    }
                    map5 = read_state_map(file);
                    fclose(file);
                }
            }
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

        int hanoi(state_t *state) {
            state_t *abs_state = new state_t;
            int h1, h2;

            abstract_state(abs1, state, abs_state);
            h1 = *state_map_get(map1, abs_state);

            abstract_state(abs2, state, abs_state);
            h2 = *state_map_get(map2, abs_state);

            return max(h1, h2);
        }

        int puzzle15_manhattan(state_t *state) {
            /*
                ver como mapear las posiciones con su estimado ajsjas
            */
            return 0;
        }
        
        int puzzle15(state_t *state) {
            state_t *abs_state = new state_t;
            int h1, h2, h3;

            abstract_state(abs1, state, abs_state);
            h1 = *state_map_get(map1, abs_state);

            abstract_state(abs2, state, abs_state);
            h2 = *state_map_get(map2, abs_state);

            abstract_state(abs3, state, abs_state);
            h3 = *state_map_get(map3, abs_state);

            return h1+h2+h3;
        }

        int puzzle24(state_t *state) {
            state_t *abs_state = new state_t;
            int h1, h2, h3, h4, h5;

            abstract_state(abs1, state, abs_state);
            h1 = *state_map_get(map1, abs_state);

            abstract_state(abs2, state, abs_state);
            h2 = *state_map_get(map2, abs_state);

            abstract_state(abs3, state, abs_state);
            h3 = *state_map_get(map3, abs_state);

            abstract_state(abs4, state, abs_state);
            h4 = *state_map_get(map3, abs_state);

            abstract_state(abs5, state, abs_state);
            h5 = *state_map_get(map3, abs_state);
            
            return h1+h2+h3+h4+h5;
        }

        int rubik3(state_t *state) {
            state_t *abs_state = new state_t;
            int h1, h2;

            abstract_state(abs1, state, abs_state);
            h1 = *state_map_get(map1, abs_state);

            abstract_state(abs2, state, abs_state);
            h2 = *state_map_get(map2, abs_state);

            return max(h1, h2);
        }

        int get_heuristic(state_t *state) {
            if (problem == "hanoi4_12" || problem == "hanoi4_14" || problem == "hanoi4_17") {
                return hanoi(state);
            }

            if (problem == "topspin12_4" || problem == "topspin14_4" || problem == "topspin17_4") {
                return top_spin(state);
            }

            if (problem == "15_puzzle_manhattan") {
                return puzzle15_manhattan(state);
            }

            if (problem == "15_puzzle") {
                return puzzle15(state);
            }

            if (problem == "24_puzzle") {
                return puzzle24(state);
            }

            return -1;
        }

        void destroy_heuristic() {
            destroy_state_map(map1);
            destroy_state_map(map2);
            destroy_state_map(map3);
            destroy_state_map(map4);
            destroy_state_map(map5);
        }
};