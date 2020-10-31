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
    char *p2 = "/tmp/pipe2";
    char *p3 = "/tmp/pipe3";

    mkfifo(p2, 0666);
    mkfifo(p3, 0666);

    struct DATA *data;
    data = (struct DATA *)malloc(sizeof(struct DATA));
    char category[5][5];

    fd = open(p2, O_RDONLY);
    read(fd, data, sizeof(struct DATA));
    close(fd);

    for(int i=0; i<5; i++) {
        if(data->arr[i] == data->avg)
            strcpy(category[i], "Cat0");
        else if(data->arr[i] > data->avg + data->sd)
            strcpy(category[i], "Cat1");
        else if(data->arr[i] > data->avg && data->arr[i] < data->avg + data->sd)
            strcpy(category[i], "Cat2");
        else if(data->arr[i] < data->avg && data->arr[i] > data->avg - data->sd)
            strcpy(category[i], "Cat3");
        else
            strcpy(category[i], "Cat4");
    }

    for(int i=0; i<5; i++) {
        printf("L%d : %s\n", i+1, category[i]);
    }

    fd = open(p3, O_WRONLY);
    write(fd, category, sizeof(category));
    close(fd);
    return 0;
}
