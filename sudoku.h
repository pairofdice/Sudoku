#include <stddef.h>
#include <stdio.h>

#define N 9
typedef struct s_sudoku {
    size_t grid[N*N]; 
    size_t freedoms[N*N];
    size_t rows_known[N];
    size_t cols_known[N];
    size_t blocks_known[N];
} t_sudoku;

void load_sudoku(t_sudoku* grid, int fd, char* filename);
void print_grid(t_sudoku* sudoku);
void collapse_entropy(t_sudoku *sudoku);

