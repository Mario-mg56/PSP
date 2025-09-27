#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// 3. Crear un programa en C mp3.c que simule un árbol de procesos como el de la figura:
//     i. El proceso P1 es padre de P2 y de P3
//     ii. El proceso P2 deberá dormir 10 segundos y mostrar el mensaje “Despierto” al finalizar
//     iii. El proceso P3 deberá mostrar por pantalla su pid y el de su padre, indicando que es el proceso P3
//     iv. El/los proceso/s padre/s deberá/n esperar a que sus hijo/s termine/n

void main(){
    pid_t p1pid = getpid(), p2pid = fork();
    if (p2pid > 0) {
        pid_t p3pid = fork();
        if (p3pid == 0) 
            printf("Soy el proceso P3, mi pid es %d y el del P1 es %d \n", getpid(), p1pid);
        else if (p3pid > 0) {
            wait(NULL);
            wait(NULL);
        }
        else printf("Error en la creación del proceso P3 \n");
    }
    else if (p2pid == 0) {
        sleep(10);
        printf("Despierto \n");
    }
    else printf("Error en la creación del proceso P2 \n");
    exit(0);
}