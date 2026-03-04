#include <stdio.h>

enum en25 { alpha = 25, beta, gamma = beta * 10, delta };

int main(int argc, char *argv[]) {
    enum en25 x = delta;
    printf("delta is %d\n", x);
    return 0;
}
