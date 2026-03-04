#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum { num_arr_size = 10 };

int main(int argc, char *argv[]) {
    char path[] = "/dev/random";
    int count = 1;

    if (argc < 3) {
        printf("Wrong usage. Type ./device_as_file <arr_size> <loop_count>\n");
        return 1;
    }

    int arr_size = atoi(argv[1]);
    int loop_count = atoi(argv[2]);
    char random_num[arr_size];

    if (arr_size < 0 || loop_count < 0) {
        printf("Arguments should be positive.\n");
        return 1;
    }

    if (arr_size == 0 || loop_count == 0) {
        printf("Invalid arguments.\n");
        return 1;
    }

    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        printf("Cant open file %s\n", path);
        return 1;
    }

    for (int i = 0; i < loop_count; i++) {
        int read_fd = read(fd, random_num, sizeof(random_num));
        if (read_fd != sizeof(random_num)) {
            printf("Cant read from %s\n", path);
            break;
        }
        for (int j = 0; j < arr_size; j++) {
            printf("Number %d is: %d\n", count, random_num[j]);
            count++;
        }
        printf("--------------------------------\n");
        sleep(1);
    }
    return 0;
}
