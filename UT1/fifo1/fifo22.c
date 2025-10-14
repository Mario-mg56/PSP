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
    int fd1;
    fd1 = -1;
    while (fd1 == -1) {
        fd1 = open("FIFO1", 0);
        sleep(1);
        printf("intento abrir %d \n", fd1);
    }

    int bytes = -1;
    char buffer[3];
    while (bytes != 0){bytes = read(fd1, buffer, 1);}
    close(fd1);

    int fact = 1;
    for (int i = atoi(buffer); i>1; i--) {fact *= i;}
    if (fact == 0) fact = 1;
    sprintf(buffer, "%d", fact);

    fd1 = open("FIFO1", 1);
    write(fd1, buffer, strlen(buffer));
}