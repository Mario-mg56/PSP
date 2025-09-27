#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// 1. Crear un programa en C mp1.c que realice las siguientes funciones:
    // i. El proceso padre deberá crear un proceso hijo que mostrará el nombre del alumno.
    // ii. El proceso padre deberá esperar a que su hijo termine, y mostrará por pantalla el pid del hijo y el suyo propio


void main(){
    pid_t childPid = fork();
    if (childPid == 0) printf("El nombre del alumno es: Mario \n");
    else if (childPid > 0) {
        wait(NULL);
        printf("Soy el padre y mi hijo ya ha terminado su ejecución \n");
        printf("Mi pid es %d, y el de mi hijo es %d \n", getpid(), childPid);
    }
    else printf("Error en la creación del proceso hijo \n");
    exit(0);
}