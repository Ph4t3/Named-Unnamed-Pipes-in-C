#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

struct DATA {
    double arr[5];
    double avg;
    double sd;
};

int main()
{
    int fd;
    char *p1 = "/tmp/pipe1";
    char *p2 = "/tmp/pipe2";

    mkfifo(p1, 0666);
    mkfifo(p2, 0666);

    struct DATA *data;
    data = (struct DATA *)malloc(sizeof(struct DATA));

    fd = open(p1, O_RDONLY);
    read(fd, data->arr, sizeof(data->arr));
    close(fd);

    data->avg = 0;
    for(int i=0; i<5; i++)
        data->avg += data->arr[i];
    data->avg /= 5;

    data->sd = 0;
    for(int i=0; i<5; i++)
        data->sd += pow(data->arr[i] - data->avg, 2);
    data->sd /= 5;
    data->sd = sqrt(data->sd);

    printf("Avg: %lf", data->avg);
    printf("\nSD: %lf", data->sd);

    fd = open(p2, O_WRONLY);
    write(fd, data, sizeof(struct DATA));
    close(fd);
    return 0;
}
