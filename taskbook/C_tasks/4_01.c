#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("a: %d\n", '2' + 3);
    printf("b: %d\n", 3 + 'a');
    printf("c: %d\n", 'Z' - 'X');
    printf("d: %d\n", ' ' * 10);
    printf("i: %d\n", 23 >> 3);
    printf("m: %d\n", ~35);
    printf("o: %d\n", 21 ^ 15);
    return 0;
}
