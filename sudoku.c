#include "sudoku.h"
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 300
#define BLANK 0


// set constraint bitmasks for each row, column and 3x3 block
void collapse_entropy(t_sudoku *sudoku, size_t val, size_t index)
{
    size_t mask = 1 << val;
    size_t col = index % N;
    size_t row = index / N;
    sudoku->row_constraints[row] |= mask;
    sudoku->col_constraints[col] |= mask;

    // map 0-8 row/col into the 9x(3x3) block linear index
    size_t block_index = (row / 3) * 3 + (col / 3); 
    sudoku->block_constraints[block_index] |= mask;
    printf(" - Setting: %d: %.10b, row: %d = %.10b", 
            val, mask, row, sudoku->row_constraints[row]);
    printf(", col: %d = %.10b, block: %d %.10b\n", 
            col, sudoku->col_constraints[col], block_index, sudoku->block_constraints[block_index]);
}


size_t count_freedoms(size_t row_constraints ,size_t col_constraints, size_t block_constraints)
{
    size_t freedoms_mask = 0;
    size_t all_ones = 0;
    --all_ones;
    // ~  is the bitwise unary NOT, turns each 1 to 0 and vice versa
    freedoms_mask |= ~row_constraints;
    freedoms_mask &= ~col_constraints;
    freedoms_mask &= ~block_constraints;
    freedoms_mask &= all_ones << 1;     // sets the least significant bit to 0 since we use 1-9th
    freedoms_mask &= ~(all_ones << 10); // should set all the more significant bits back to 0
    
    printf("Freedom mask: %.32b\n", freedoms_mask);
    size_t pop_count = 0;
    for (size_t i = 0; i < 10; ++i)
    {
        if (freedoms_mask & 1) 
        {
            ++pop_count;
        }
        freedoms_mask = freedoms_mask >> 1;
    }
    return pop_count;
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
    for (size_t i = 0; i < NN; ++i)
    {
    }

}

int main(int argc, char* argv[argc+1]) {
    t_sudoku sudoku = { 0 };
    handle_args(argc, argv, &sudoku);

    size_t all_ones = 0;
    --all_ones;
    all_ones = all_ones << 10;
    printf("All ones: %.32b\n", all_ones);
    size_t count = count_freedoms(all_ones, all_ones, all_ones);
    printf("Freedom count: %d\n", count);
    count = count_freedoms(sudoku.row_constraints[0], sudoku.col_constraints[0], sudoku.block_constraints[0]);
    printf("Freedom count: %d\n", count);
//    for (size_t row = 0; row < 9; ++row)
//    {
//        for (size_t col = 0; col < 9; ++col) 
//        {
//            size_t i = (row / 3) * 3;
//            size_t j = col / 3;
//            size_t index = i + j;
//            printf("row: %d, col: %d, index: %d \n", row, col, index);
//        }
//    }
    print_grid(&sudoku);
    solve(&sudoku);
    print_grid(&sudoku);
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
