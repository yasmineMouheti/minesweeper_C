#ifndef MINESWEEPER_H
#define MINESWEEPER_H

typedef struct {
    int value;
    int is_mine;
    int is_boombed;
    int is_visited;
    int is_flagged;
} Node;

#endif /* MINESWEEPER_H */
