#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    time_t t;
    struct tm *result;
    struct tm result_r;

    time(&t);
    printf("time is: %ld\n", t);

    result = gmtime(&t);
    printf("gmtime is : %02d:%02d:%02d\n", result->tm_hour, result->tm_min,
           result->tm_sec);

    localtime_r(&t, &result_r);
    printf("localtime_r is : %02d:%02d:%02d\n", result_r.tm_hour,
           result_r.tm_min, result_r.tm_sec);

    return 0;
}
