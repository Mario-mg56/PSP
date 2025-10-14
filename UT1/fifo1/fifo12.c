#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>

void main(){
    const char *fifo1 = "FIFO1";
    const char *fifo2 = "FIFO2";
    mkfifo(fifo2, 0666);
    int fd1, fd2;
    fd1 = -1;
    fd2 = open(fifo2, O_WRONLY);
    while (fd1 == -1) {
        fd1 = open(fifo1, O_RDONLY);
    }

    int bytes = -1;
    char buffer[3];
    while (bytes != 0){bytes = read(fd1, buffer, 1);}

    int fact = 1;
    for (int i = atoi(buffer); i>1; i--) {fact *= i;}
    if (fact == 0) fact = 1;

    sprintf(buffer, "%d", fact);
    write(fd2, buffer, strlen(buffer));
    unlink(fifo2);
}