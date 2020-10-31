#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;
    char *p1 = "/tmp/pipe1";
    char *p3 = "/tmp/pipe3";

    mkfifo(p1, 0666);
    mkfifo(p3, 0666);

    double arr[5];
    int i = 0;
    char category[5][5];
    printf("Enter location temperatures (Value b/w 15 deg Celsius & 45 deg Celsius)\n");
    while(i<5) {
       printf("L%d : ", i+1);
       scanf("%lf", arr+i);
       if(arr[i] < 15 || arr[i] > 45) {
           printf("\nInvalid Value");
           continue;
       }
       i += 1;
    }

    fd = open(p1, O_WRONLY);
    write(fd, arr, sizeof(arr));
    close(fd);

    fd = open(p3, O_RDONLY);
    read(fd, category, sizeof(category));
    close(fd);

    for(int j=0; j<5; j++) {
        if(!strcmp(category[j], "Cat1"))
            arr[j] -= 3;
        else if(!strcmp(category[j], "Cat2"))
            arr[j] -= 1.5;
        else if(!strcmp(category[j], "Cat3"))
            arr[j] += 2;
        else if(!strcmp(category[j], "Cat4"))
            arr[j] += 2.5;
    }

    printf("Modified temparature at locations\n");
    for(int j=0; j<5; j++) {
       printf("L%d : %.2lf\n", j+1, arr[j]);
    }
    return 0;
}
