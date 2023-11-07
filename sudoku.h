#ifndef SUDOKU_H
# define SUDOKU_H

#include <stddef.h>
#include <stdio.h>

#define N 9
#define NN 81
typedef struct s_sudoku {
    size_t grid[NN]; 
    size_t freedoms[NN];
    size_t rows_known[N];
    size_t cols_known[N];
    size_t blocks_known[N];
} t_sudoku;

void load_sudoku(t_sudoku* grid, int fd, char* filename);
void print_grid(t_sudoku* sudoku);
void collapse_entropy(t_sudoku *sudoku);

#endif
