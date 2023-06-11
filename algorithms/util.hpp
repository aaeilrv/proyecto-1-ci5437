char* puzzle_name(char* name) {
    char* puzzle = (char*) malloc(100);
    char* token = strtok(name, "/");

    strcpy(puzzle, strtok(NULL, "."));

    return puzzle;
}