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
#include <string.h>
#include <iostream>
using namespace std;

class heuristics_t {
    abstraction_t *abs1, *abs2, *abs3, *abs4, *abs5;
    state_map_t *map1, *map2, *map3, *map4, *map5;
    char *problem;
    int rows_n_puzzle[16]; 
    int columns_n_puzzle[16];

    public:
        heuristics_t() {};
        void init_heuristic(char *p) {
            problem = p;
            FILE *file;

            map1 = new state_map_t;
            map2 = new state_map_t;
            map3 = new state_map_t;
            map4 = new state_map_t;
            map5 = new state_map_t;

            /*
                read abstraction and pdbs depending on the problem
            */

            if (strcmp(problem,"15_puzzle_manhattan") != 0) {
                
                /*
                    every puzzle have at least 2 abstractions
                */
                abs1 = read_abstraction_from_file("abst1.abst");
                if (abs1 == nullptr) {
                    cout << "file abst1.abst not found" << endl;
                    return;
                }
                
                abs2 = read_abstraction_from_file("abst2.abst");
                if (abs2 == nullptr) {
                    cout << "file abst2.abst not found" << endl;
                    return;
                }

                file = fopen("abst1.pdb", "r");
                if (file == nullptr) {
                    cout << "file abst1.pdb not found" << endl;
                    return;
                }
                map1 = read_state_map(file);
                fclose(file);

                file = fopen("abst2.pdb", "r");
                if (file == nullptr) {
                    cout << "file abst2.pdb not found" << endl;
                    return;
                }
                map2 = read_state_map(file);
                fclose(file);

                /*
                    check for puzzles that have at least 3 abstractions
                */
                if (strcmp(problem, "15_puzzle")==0 || strcmp(problem, "24_puzzles")==0 || strcmp(problem, "topspin12_4")==0 || strcmp(problem, "topspin14_4")==0 || strcmp(problem, "topspin17_4")==0) {
                    abs3 = read_abstraction_from_file("abst3.abst");
                    if (abs3 == nullptr) {
                        cout << "file abst3.abst not found" << endl;
                        return;
                    }

                    file = fopen("abst3.pdb", "r");
                    if (file == nullptr) {
                        cout << "file abst3.pdb not found" << endl;
                        return;
                    }
                    map3 = read_state_map(file);
                    fclose(file);
                }

                /*
                    check for puzzles that have at least 4 abstracoins
                */
                if (strcmp(problem, "24_puzzle")==0 || strcmp(problem, "topspin14_4")==0) {
                    abs4 = read_abstraction_from_file("abst4.abst");
                    if (abs4 == nullptr) {
                        cout << "file abst4.abst not found" << endl;
                        return;
                    }

                    file = fopen("abst4.pdb", "r");
                    if (file == nullptr) {
                        cout << "file abst4.pdb not found" << endl;
                        return;
                    }
                    map4 = read_state_map(file);
                    fclose(file);
                }

                /*
                    check for puzzles that have 5 abstractions
                */
                if (strcmp(problem, "24_puzzle")==0){
                    abs5 = read_abstraction_from_file("abst5.abst");
                    if (abs5 == nullptr) {
                        cout << "file abst5.abst not found" << endl;
                        return;
                    }

                    file = fopen("abst5.pdb", "r");
                    if (file == nullptr) {
                        cout << "file abst5.pdb not found" << endl;
                        return;
                    }
                    map5 = read_state_map(file);
                    fclose(file);
                }
            } else {
                /*
                    fill rows_n_puzzle and columns_n_puzzle arrays

                    rows_n_puzzle[i] = row in the puzzle grid of the i-th number
                    columns_n_puzzle[i] = colum in the puzzle grid of the i-th number
                */
                for (int i=0; i<16; i++) {
                    rows_n_puzzle[i] = div(i, 4).quot;
                    columns_n_puzzle[i] = i % 4;
                }
            }
        }

        int top_spin(state_t *state) {
            state_t *abs_state = new state_t;
            int h1, h2, h3, h4;

            abstract_state(abs1, state, abs_state);
            h1 = *state_map_get(map1, abs_state);

            abstract_state(abs2, state, abs_state);
            h2 = *state_map_get(map2, abs_state);

            abstract_state(abs3, state, abs_state);
            h3 = *state_map_get(map3, abs_state);
            
            if (strcmp(problem, "topspin14_4")==0 || strcmp(problem, "topspin17_4")) {
                abstract_state(abs4, state, abs_state);
                h4 = *state_map_get(map4, abs_state);

                return max(max(h1, h2), max(h3, h4));
            }

            return max(h1, max(h2, h3));
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
            var_t *values = state->vars;
            int num_value, h, x, y, grid_size;

            grid_size = 16;
            h = 0;
            x = -1;

            for (int i=0; i<grid_size; i++) {
                if ((char)values[i] != 'B') continue;
                num_value = (int)values[i];

                y = i % grid_size;
                if (y % grid_size == 0){
                    x++;
                }

                h += abs(x-rows_n_puzzle[num_value]) + abs(y-columns_n_puzzle[num_value]);
            }
            return h;
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
            h4 = *state_map_get(map4, abs_state);

            abstract_state(abs5, state, abs_state);
            h5 = *state_map_get(map5, abs_state);

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
            if (strcmp(problem, "hanoi4_12")==0 || strcmp(problem, "hanoi4_14")==0 || strcmp(problem, "hanoi4_17")==0) {
                return hanoi(state);
            }

            if (strcmp(problem, "topspin12_4")==0 || strcmp(problem, "topspin14_4")==0 || strcmp(problem, "topspin17_4")==0) {
                return top_spin(state);
            }

            if (strcmp(problem, "15_puzzle_manhattan")==0) {
                return puzzle15_manhattan(state);
            }

            if (strcmp(problem, "15_puzzle")==0) {
                return puzzle15(state);
            }

            if (strcmp(problem, "24_puzzle")==0) {
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
        };
};