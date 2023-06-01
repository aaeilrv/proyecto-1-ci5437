CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --no_state_map --no_abstraction --backwards_moves --history_len=0

psvn2c_core.c:
	cp ../src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: ../puzzles/%.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.from_goal_no_pruning: %.c ../algorithms/bfs.cpp
	$(CXX) $(OPT) ../algorithms/bfs.cpp -include $< -o $@
	rm -f $*.c

.PHONY: clean
clean:
	rm -fr *.from_goal_no_pruning psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c *.dSYM *.o *~ *.c
