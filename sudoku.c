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
    sudoku->row_neighbours_known[row] |= 1 << val;
    sudoku->col_neighbours_known[col] |= 1 << val;
    printf(" - Setting: %d: %.10b, row: %d = %.10b\n", val, mask, row, sudoku->row_neighbours_known[row]);
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
        if (val <=9)
        {
            sudoku->grid[k] = val ;
            if (val > 0)
                collapse_entropy(sudoku, val, k);

            ++k;
        }
        ++i;
    }
}
