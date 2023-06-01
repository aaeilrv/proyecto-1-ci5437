#!bin/bash

echo "\nrunning rubik3"
./rubik3.from_goal_no_pruning

echo "running 15_puzzle"
./15_puzzle.from_goal_no_pruning

echo "running 24_puzzle"
./24_puzzle.from_goal_no_pruning

echo "\nrunning hanoi4_12"
./hanoi4_12.from_goal_no_pruning

echo "\nrunning hanoi4_14"
./hanoi4_14.from_goal_no_pruning

echo "\nrunning hanoi4_17"
./hanoi4_17.from_goal_no_pruning

echo "\nrunning topspin12_4"
./topspin12_4.from_goal_no_pruning

echo "\nrunning topspin14_4"
./topspin14_4.from_goal_no_pruning

echo "\nrunning topspin17_4"
./topspin17_4.from_goal_no_pruning