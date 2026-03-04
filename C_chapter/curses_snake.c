#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char snake[] = "Snake";
#define LEN (sizeof(snake) - 1)
#define MAX_LEN 1000
enum { key_escape = 27 };

typedef struct {
    int y, x;
} Point;

Point apple;
int len;
char body[MAX_LEN];

void place_apple(int my, int mx) {
    apple.y = rand() % (my + 1);
    apple.x = rand() % (mx + 1);
}

void show_apple(int count) {
    move(apple.y, apple.x);
    addch('@');
    move(0, 0);
    printw("COUNT: %d   ", count);
    refresh();
}

void hide_apple() {
    move(apple.y, apple.x);
    addch(' ');
    refresh();
}

void show_snake(Point segs[]) {
    for (int i = 0; i < len; i++) {
        move(segs[i].y, segs[i].x);
        addch(body[i]);
    }
    refresh();
}

void hide_snake(Point segs[]) {
    for (int i = 0; i < len; i++) {
        move(segs[i].y, segs[i].x);
        addch(' ');
    }
    refresh();
}

int check(int *coord, int max) {
    if (*coord < 0 || *coord > max)
        return 1;
    return 0;
}

void grow_snake(Point segs[]) {
    if (len >= MAX_LEN)
        return;
    segs[len] = segs[len - 1];
    body[len] = 'e';
    len++;
}

void game_over(int count) {
    clear();
    int row, col;
    getmaxyx(stdscr, row, col);
    move(row / 2, (col - 20) / 2);
    printw("GAME OVER! Score: %d", count);
    move(row / 2 + 1, (col - 24) / 2);
    printw("Press any key to exit...");
    refresh();
    timeout(-1);
    getch();
    endwin();
}

void start_menu() {}

int move_snake(Point segs[], int my, int mx, int shift_y, int shift_x,
               int *count) {
    hide_snake(segs);

    for (int i = len - 1; i > 0; i--) {
        segs[i] = segs[i - 1];
    }

    segs[0].x += shift_x;
    segs[0].y += shift_y;

    if (check(&segs[0].x, mx) || check(&segs[0].y, my)) {
        return 1;
    }

    for (int i = 1; i < len; i++) {
        if (segs[0].y == segs[i].y && segs[0].x == segs[i].x) {
            return 1;
        }
    }

    if (segs[0].y == apple.y && segs[0].x == apple.x) {
        hide_apple();
        place_apple(my, mx);
        (*count)++;
        grow_snake(segs);
    }

    show_apple(*count);
    show_snake(segs);
    return 0;
}

void handle_resize(Point segs[], int *my, int *mx, int count) {
    int row, col;
    getmaxyx(stdscr, row, col);
    *mx = col - 1;
    *my = row - 1;
    hide_snake(segs);
    for (int i = 0; i < len; i++) {
        check(&segs[i].x, *mx);
        check(&segs[i].y, *my);
    }
    check(&apple.x, *mx);
    check(&apple.y, *my);
    show_apple(count);
    show_snake(segs);
}

int main() {
    int row, col, max_x, max_y, key;
    int shift_x = 0, shift_y = 0, count = 0;

    srand(time(NULL));
    len = LEN;
    memcpy(body, snake, LEN);

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, 1);
    curs_set(0);
    timeout(100);

    getmaxyx(stdscr, row, col);
    max_x = col - 1;
    max_y = row - 1;

    Point segs[MAX_LEN];
    for (int i = 0; i < LEN; i++) {
        segs[i].y = row / 2;
        segs[i].x = col / 2 + i;
    }

    place_apple(max_y, max_x);
    show_apple(count);
    show_snake(segs);

    while ((key = getch()) != key_escape) {
        switch (key) {
        case KEY_LEFT:
            if (shift_x != 1) {
                shift_y = 0;
                shift_x = -1;
            }
            break;
        case KEY_RIGHT:
            if (shift_x != -1) {
                shift_y = 0;
                shift_x = 1;
            }
            break;
        case KEY_UP:
            if (shift_y != 1) {
                shift_x = 0;
                shift_y = -1;
            }
            break;
        case KEY_DOWN:
            if (shift_y != -1) {
                shift_x = 0;
                shift_y = 1;
            }
            break;
        case KEY_RESIZE:
            handle_resize(segs, &max_y, &max_x, count);
            break;
        }

        if (shift_x != 0 || shift_y != 0) {
            if (move_snake(segs, max_y, max_x, shift_y, shift_x, &count)) {
                game_over(count);
                return 0;
            }
        }
    }

    endwin();
    return 0;
}
