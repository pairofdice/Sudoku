#include "sudoku.h"

void print_grid(t_sudoku* sudoku) {
    printf("\nprint_grid\n");
    for (size_t i = 0; i < 81; ++i)
    {
        if (i > 0 && i % 9 != 0 && i % 3 == 0)
            printf("| ");
        if (i > 0 && i % 9 == 0)
        {

            printf("%.10b %d ", sudoku->row_neighbours_known[i / N - 1], i/N -1);
            printf("\n");
        }
        if (i > 0 && i % 27 == 0 ) 
            printf("----------------------\n");
        if (sudoku->grid[i] == 0)
            printf("- ");
        else
            printf("%ld ", sudoku->grid[i]);
    }
    printf("%.10b %d ", sudoku->row_neighbours_known[8], 8);
}
