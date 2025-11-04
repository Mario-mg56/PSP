#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <signal.h>

// 5. Programar utilizando señales signal5.c simulando el esquema de procesos de la figura
// El proceso P1 solicitará por pantalla números que escribirá en el pipe. En el caso de que el número
// sea par el proceso que deberá leerlo y mostrarlo por pantalla será el P2, en caso de ser impar será
// el proceso P3 el que lo haga. El programa finaliza cuando el número introducido sea el 0.



void readingHandler(int signum){}

int main(){
    int fd[2];
    char buffer[30];
    pipe(fd);
    pid_t fk3, fk2;
    fk3 = fork();
    if (fk3 != 0){ //P1
        fk2 = fork();
        if (fk2 != 0){ //P1
            int input;
            close(fd[0]);
            while(1){
                printf("Introduce número: \n");
                scanf("%d", &input);
                sprintf(buffer, "%d", input);
                if(input==0){
                    printf("Mandando señal de terminación al proceso hijo P2 con pid: %d \n", (int) fk3);
                    kill(fk3, SIGUSR2);
                    printf("Mandando señal de terminación al proceso hijo P3 con pid: %d \n", (int) fk2);
                    kill(fk2, SIGUSR2);
                    wait(NULL);
                    wait(NULL);
                    printf("Fin del padre P1 con pid: %d \n", (int) getpid());
                    exit(0);
                }
                else if (input%2 == 0) kill(fk2, SIGUSR1);
                else kill(fk3, SIGUSR1);
                write(fd[1], buffer, strlen(buffer) + 1);
            }
        }
        else { //P2
            signal(SIGUSR1, readingHandler);
            close(fd[1]);
            while(1) {
                pause();
                read(fd[0], buffer, sizeof(buffer));
                printf("Soy P2 de pid %d y he leído el número par: %s\n", (int) getpid(), buffer);
            }
        }
    }
    else { //P3
        signal(SIGUSR1, readingHandler);
        close(fd[1]);
        while(1) {
            pause();
            read(fd[0], buffer, 5);
            printf("Soy P3 de pid %d y he leído el número impar: %s\n", (int) getpid(), buffer);
        }
    }
}