#include "sudoku.h"
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 300
void reduce_freedoms_row(t_sudoku *sudoku, size_t i)  { }
void reduce_freedoms_col(t_sudoku *sudoku, size_t i)  { }
void reduce_freedoms_block(t_sudoku *sudoku, size_t i)  { }

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
    load_sudoku(sudoku, fd,  argv[1]);
}

void collapse_entropy(t_sudoku * sudoku) {
    for (size_t i = 0; i < NN; ++i) {
       reduce_freedoms_row(sudoku, i); 
       reduce_freedoms_col(sudoku, i); 
       reduce_freedoms_block(sudoku, i); 
    }


}

int main(int argc, char* argv[argc+1]) {
    t_sudoku sudoku; 
    // handle_args(argc, argv, &sudoku);
    // print_grid(&sudoku);
    size_t i = 0b0000000001;
    printf("%09b %d\n", i, i);
    i = 0b0000000010;
    printf("%09b %d\n", i, i);
    i = 0b0000000100;
    printf("%09b %d\n", i, i);
    i = 0b0000001000;
    printf("%09b %d\n", i, i);
    i = 0b0000010000;
    printf("%09b %d\n", i, i);
    i = 0b0000100000;
    printf("%09b %d\n", i, i);
    i = 0b0001000000;
    printf("%09b %d\n", i, i);
    i = 0b0010000000;
    printf("%09b %d\n", i, i);
    i = 0b0100000000;
    printf("%09b %d\n", i, i);

    printf("--\n");
    printf("%d\n", 1 << 1);
    printf("%d\n", 1 << 2);
    printf("%d\n", 1 << 3);
    printf("%d\n", 1 << 4);
    printf("%d\n", 1 << 5);
    printf("%d\n", 1 << 6);
    printf("%d\n", 1 << 7);
    printf("%d\n", 1 << 8);
    printf("%d\n", 1 << 9);


}



void load_sudoku(t_sudoku *sudoku, int fd,  char* filename) {
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
        if (buffer[i] == ' ')
        {
            ++i;
            continue ;
        }
        if (buffer[i] >= '0' && buffer[i] <='9')
        {
            sudoku->grid[k] = buffer[i] - '0';
            ++k;
        }
        ++i;
    }
}
