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

abst1.c: ./abst1.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

abst2.c: ./abst2.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

abst3.c: ./abst3.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

abst4.c: ./abst4.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

abst5.c: ./abst5.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c
.PRECIOUS: %.c

abst1.distSummary: abst1.c 
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../global/distSummary.cpp -include $< -o $@
	@rm -f $*.c

abst2.distSummary: abst2.c 
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../global/distSummary.cpp -include $< -o $@
	@rm -f $*.c

abst3.distSummary: abst3.c 
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../global/distSummary.cpp -include $< -o $@
	@rm -f $*.c

abst4.distSummary: abst4.c 
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../global/distSummary.cpp -include $< -o $@
	@rm -f $*.c

abst5.distSummary: abst5.c 
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../global/distSummary.cpp -include $< -o $@
	@rm -f $*.c

abstractor:
	@echo "**** Constructing abstractor ..."
	@$(CXX) $(OPT) ../src/abstractor.cpp ../src/psvn.cpp -o $@


15_puzzle.a_star: 15_puzzle.c abstractor
	@cp ../puzzles/15_puzzle.psvn ./15_puzzle.psvn
	@cp ../abstractions/15_puzzle/abst1.txt ./abst1.txt
	@cp ../abstractions/15_puzzle/abst2.txt ./abst2.txt
	@cp ../abstractions/15_puzzle/abst3.txt ./abst3.txt

	@./abstractor 15_puzzle.psvn abst1 < abst1.txt > /dev/null
	@./abstractor 15_puzzle.psvn abst2 < abst2.txt > /dev/null
	@./abstractor 15_puzzle.psvn abst3 < abst3.txt > /dev/null

	@make abst1.distSummary
	@./abst1.distSummary abst1.pdb

	@make abst2.distSummary
	@./abst2.distSummary abst2.pdb

	@make abst3.distSummary
	@./abst3.distSummary abst3.pdb

	$(CXX) $(OPT) ../algorithms/a_star.cpp -include $< -o $@
	@rm -f *.distSummary 

24_puzzle.a_star: 24_puzzle.c abstractor
	@cp ../puzzles/24_puzzle.psvn ./24_puzzle.psvn
	@cp ../abstractions/24_puzzle/abst1.txt ./abst1.txt
	@cp ../abstractions/24_puzzle/abst2.txt ./abst2.txt
	@cp ../abstractions/24_puzzle/abst3.txt ./abst3.txt
	@cp ../abstractions/24_puzzle/abst4.txt ./abst4.txt
	@cp ../abstractions/24_puzzle/abst5.txt ./abst5.txt

	@./abstractor 24_puzzle.psvn abst1 < abst1.txt > /dev/null
	@./abstractor 24_puzzle.psvn abst2 < abst2.txt > /dev/null
	@./abstractor 24_puzzle.psvn abst3 < abst3.txt > /dev/null
	@./abstractor 24_puzzle.psvn abst4 < abst4.txt > /dev/null
	@./abstractor 24_puzzle.psvn abst5 < abst5.txt > /dev/null

	@make abst1.distSummary
	@./abst1.distSummary abst1.pdb

	@make abst2.distSummary
	@./abst2.distSummary abst2.pdb

	@make abst3.distSummary
	@./abst3.distSummary abst3.pdb

	@make abst4.distSummary
	@./abst4.distSummary abst4.pdb

	@make abst5.distSummary
	@./abst5.distSummary abst5.pdb

	$(CXX) $(OPT) ../algorithms/a_star.cpp -include $< -o $@
	@rm -f *.distSummary *.psvn *.txt *.c

topspin12_4.a_star: topspin12_4.c abstractor 
	@cp ../puzzles/topspin12_4.psvn ./topspin12_4.psvn
	@cp ../abstractions/topspin12_4/abst1.txt ./abst1.txt
	@cp ../abstractions/topspin12_4/abst2.txt ./abst2.txt

	@./abstractor topspin12_4.psvn abst1 < abst1.txt > /dev/null
	@./abstractor topspin12_4.psvn abst2 < abst2.txt > /dev/null

	@make abst1.distSummary
	@./abst1.distSummary abst1.pdb

	@make abst2.distSummary
	@./abst2.distSummary abst2.pdb

	$(CXX) $(OPT) ../algorithms/a_star.cpp -include $< -o $@
	@rm -f *.distSummary *.psvn *.txt *.c

topspin14_4.a_star: topspin14_4.c abstractor 
	@cp ../puzzles/topspin14_4.psvn ./topspin14_4.psvn
	@cp ../abstractions/topspin14_4/abst1.txt ./abst1.txt
	@cp ../abstractions/topspin14_4/abst2.txt ./abst2.txt

	@./abstractor topspin14_4.psvn abst1 < abst1.txt > /dev/null
	@./abstractor topspin14_4.psvn abst2 < abst2.txt > /dev/null

	@make abst1.distSummary
	@./abst1.distSummary abst1.pdb

	@make abst2.distSummary
	@./abst2.distSummary abst2.pdb

	$(CXX) $(OPT) ../algorithms/a_star.cpp -include $< -o $@
	@rm -f *.distSummary *.psvn *.txt *.c

topspin17_4.a_star: topspin17_4.c abstractor 
	@cp ../puzzles/topspin17_4.psvn ./topspin17_4.psvn
	@cp ../abstractions/topspin17_4/abst1.txt ./abst1.txt
	@cp ../abstractions/topspin17_4/abst2.txt ./abst2.txt

	@./abstractor topspin17_4.psvn abst1 < abst1.txt > /dev/null
	@./abstractor topspin17_4.psvn abst2 < abst2.txt > /dev/null

	@make abst1.distSummary
	@./abst1.distSummary abst1.pdb

	@make abst2.distSummary
	@./abst2.distSummary abst2.pdb

	$(CXX) $(OPT) ../algorithms/a_star.cpp -include $< -o $@
	@rm -f *.distSummary *.psvn *.txt *.c

hanoi4_12.a_star: hanoi4_12.c abstractor 
	@cp ../puzzles/hanoi4_12.psvn ./hanoi4_12.psvn
	@cp ../abstractions/hanoi4_12/abst1.txt ./abst1.txt
	@cp ../abstractions/hanoi4_12/abst2.txt ./abst2.txt

	@./abstractor hanoi4_12.psvn abst1 < abst1.txt > /dev/null
	@./abstractor hanoi4_12.psvn abst2 < abst2.txt > /dev/null

	@make abst1.distSummary
	@./abst1.distSummary abst1.pdb

	@make abst2.distSummary
	@./abst2.distSummary abst2.pdb

	$(CXX) $(OPT) ../algorithms/a_star.cpp -include $< -o $@
	@rm -f *.distSummary *.psvn *.txt *.c

hanoi4_14.a_star: hanoi4_14.c abstractor 
	@cp ../puzzles/hanoi4_14.psvn ./hanoi4_14.psvn
	@cp ../abstractions/hanoi4_14/abst1.txt ./abst1.txt
	@cp ../abstractions/hanoi4_14/abst2.txt ./abst2.txt

	@./abstractor hanoi4_14.psvn abst1 < abst1.txt > /dev/null
	@./abstractor hanoi4_14.psvn abst2 < abst2.txt > /dev/null

	@make abst1.distSummary
	@./abst1.distSummary abst1.pdb

	@make abst2.distSummary
	@./abst2.distSummary abst2.pdb

	$(CXX) $(OPT) ../algorithms/a_star.cpp -include $< -o $@
	@rm -f *.distSummary *.psvn *.txt *.c

hanoi4_17.a_star: hanoi4_17.c abstractor 
	@cp ../puzzles/hanoi4_17.psvn ./hanoi4_17.psvn
	@cp ../abstractions/hanoi4_17/abst1.txt ./abst1.txt
	@cp ../abstractions/hanoi4_17/abst2.txt ./abst2.txt

	@./abstractor hanoi4_17.psvn abst1 < abst1.txt > /dev/null
	@./abstractor hanoi4_17.psvn abst2 < abst2.txt > /dev/null

	@make abst1.distSummary
	@./abst1.distSummary abst1.pdb

	@make abst2.distSummary
	@./abst2.distSummary abst2.pdb

	$(CXX) $(OPT) ../algorithms/a_star.cpp -include $< -o $@
	@rm -f *.distSummary *.psvn *.txt *.c

rubik3.a_star: rubik3.c abstractor 
	@cp ../puzzles/rubik3.psvn ./rubik3.psvn
	@cp ../abstractions/rubik3/abst1.txt ./abst1.txt
	@cp ../abstractions/rubik3/abst2.txt ./abst2.txt

	@./abstractor rubik3.psvn abst1 < abst1.txt > /dev/null
	@./abstractor rubik3.psvn abst2 < abst2.txt > /dev/null

	@make abst1.distSummary
	@./abst1.distSummary abst1.pdb

	@make abst2.distSummary
	@./abst2.distSummary abst2.pdb

	$(CXX) $(OPT) ../algorithms/a_star.cpp -include $< -o $@
	@rm -f *.distSummary *.psvn *.txt *.c
.PHONY: clean
clean:
	rm -fr *.a_star *.psvn *.txt *.pdb *.abst *.distSummary abstractor psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c *.dSYM *.o *~ *.c
