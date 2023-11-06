#include "sudoku.h"
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 300

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
    }
    load_sudoku(sudoku, fd,  argv[1]);
}

void collapse_entropy(t_sudoku * sudoku) {

}

int main(int argc, char* argv[argc+1]) {
    t_sudoku sudoku; 
    handle_args(argc, argv, &sudoku);
    print_grid(&sudoku);
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
    printf("SUDOKU: \n%s", buffer);

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
        printf("%c", buffer[i]);
        ++i;
    }
}
