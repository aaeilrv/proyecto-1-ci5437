CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable -std=c++11
PSVNOPT = --state_map --abstraction --fordward_moves --history_len=0

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

%.a_star: %.c
	$(CXX) $(OPT) ../algorithms/a_star.cpp -include $< -o $@ 
	rm -f $*.c

.PHONY: clean
clean:
	rm -fr *.a_star psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c *.dSYM *.o *~ *.c
