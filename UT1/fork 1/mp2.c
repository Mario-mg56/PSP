#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// 2. Crear un programa en C mp2.c que simule un árbol de procesos como el de la figura:
//     i. El proceso P1 es padre de P2 y abuelo de P3
//     ii. El proceso P2 es padre de P3 e hijo de P1
//     iii. El proceso P3 es hijo de P2 y nieto de P1
//     iv. El proceso P3 deberá mostrar por pantalla su pid y el de su padre, indicando que es el proceso P3
//     v. El proceso P2 deberá mostrar por pantalla su pid y el de su padre, indicando que es el proceso P2
//     vi. El proceso P1 deberá mostrar por pantalla su pid y el de su hijo, indicando que es el proceso P1
//     vii. Los procesos padres deberán esperar a que sus hijos terminen


void main(){
    pid_t p1pid = getpid();
    pid_t p2pid = fork();
    if (p2pid == 0) {
        p2pid = getpid();
        pid_t p3pid = fork();
        if (p3pid == 0)
            printf("Soy el proceso P3, mi pid es %d y el del P2 es %d \n", getpid(), p2pid);
        else if (p3pid > 0) {
            wait(NULL);
            printf("Soy el proceso P2, mi pid es %d y el del P1 es %d \n", p2pid, p1pid);
        }
        else printf("Error al crear el proceso P3 \n");
    }
    else if (p2pid > 0) {
        wait(NULL);
        printf("Soy el proceso P1, mi pid es %d y el del P2 es %d \n", p1pid, p2pid);
    }
    else printf("Error en la creación del proceso P2 \n");
    exit(0);
}