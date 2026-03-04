#include <fcntl.h>
#include <linux/cdrom.h>
#include <stdio.h>
#include <sys/ioctl.h>

int main(int argc, char *argv[]) {
    int fd = open("/dev/cdrom", O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        printf("Cant open file\n");
        return 1;
    }
    ioctl(fd, CDROMEJECT);
    ioctl(fd, CDROMCLOSETRAY);

    return 0;
}
