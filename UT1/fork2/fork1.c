#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// 1. Crear un programa en C fork1.c que simule un árbol de procesos como el de la figura:
//p1>p2>p4
//p1>p3

// i. Si el identificador de proceso es un número par, el proceso mostrará su pid y el de su padre
// ii. Si el identificador de proceso es un número impar, solo mostrará su pid
// iii. Los procesos padre siempre esperarán a que terminen los procesos hijo
// a) ¿Cuál será el orden de ejecución de los procesos?¿Será siempre el mismo? Justifica la respuesta

void main(){
    pid_t p1pid = getpid(); //pid de p1
    fork();
    pid_t pid = getpid(); //pid o ppid
    fork();

    if (p1pid == getpid()) {
        wait(NULL);
        wait(NULL);
    }
    if (p1pid == getppid() && pid == getpid()) wait(NULL);

    if (getpid()%2 == 0) printf("Mi pid es %d y el de mi padre es %d \n", getpid(), getppid());
    else printf("Mi pid es %d \n", getpid());
}

//El orden de ejecución de los procesos siempre empezará por p3 y p4 de forma aleatoria
//y seguido de p2 y p1 por último