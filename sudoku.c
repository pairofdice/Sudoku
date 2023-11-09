#include "sudoku.h"
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 300
#define BLANK 0


void collapse_entropy(t_sudoku *sudoku, size_t val, size_t index)
{
    size_t mask = 1 << val;
    size_t col = index % N;
    size_t row = index / N;
    sudoku->row_constraints[row] |= mask;
    sudoku->col_constraints[col] |= mask;
    // map 0-9 row/col into the 9 3x3 block linear index
    sudoku->block_constraints[(row / 3) * 3 + (col / 3)] |= mask;
    printf(" - Setting: %d: %.10b, row: %d = %.10b\n", val, mask, row, sudoku->row_constraints[row]);
}

void handle_args(int argc, char **argv, t_sudoku *sudoku) {
    int fd;

    if (argc == 2) {
        fd = open(argv[1], O_RDONLY);
        if (fd < 0)
            exit(1);
    }
    else 
    {
        printf("Usage: ./sudoku <file>\n");
        exit(1);
    }
    load_sudoku(sudoku, fd);
}

void solve(t_sudoku *sudoku)
{

    if (sudoku) {}
}

int main(int argc, char* argv[argc+1]) {

    for (size_t row = 0; row < 9; ++row)
    {
        for (size_t col = 0; col < 9; ++col) 
        {
            size_t i = (row / 3) * 3;
            size_t j = col / 3;
            size_t index = i + j;
            printf("row: %d, col: %d, index: %d \n", row, col, index);
        }
    }
    t_sudoku sudoku = { 0 };
    handle_args(argc, argv, &sudoku);
    print_grid(&sudoku);
    solve(&sudoku);
}



void load_sudoku(t_sudoku *sudoku, int fd) {
    printf("In load_sudoku\n");
    ssize_t ret;
    char buffer[BUFF_SIZE];

    ret = read(fd, buffer, BUFF_SIZE);
    close(fd);
    if (ret <= 0)
    {
        exit (1);
    }

    size_t i = 0;
    size_t k = 0;
    while (buffer[i])
    {
        size_t val = buffer[i];
        if (val == ' ')
        {
            ++i;
            continue ;
        }
        val -= '0';
        if (val <= 9)
        {
            if (val > 0)
            {
                sudoku->grid[k] = val ;
                collapse_entropy(sudoku, val, k);
            }
            ++k;
        }
        ++i;
    }
}
