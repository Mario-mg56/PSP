#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>


// 1. Crear dos programas en C fifo11.c fifo12.c que realicen las siguientes funciones:
// i. Deberá responder al esquema de la figura. El proceso fifo11 se encargará de la gestión del pipe
// FIFO1 y el proceso fifo12 de la del pipe FIFO2
// ii. El proceso fifo11 generará un número aleatorio entre 0 y 10 en el pipe FIFO1
// iii. El proceso fifo12 deberá calcular el resultado del factorial de dicho número y escribir el resultado
// el pipe FIFO2
// iv. El proceso fifo11 se encargará de mostrar por pantalla el resultado del cálculo
// v. Al finalizar ambos procesos, se deberán eliminar los pipes.


void main(){
    mkfifo("FIFO1", 0666);
    printf("Fifo creado \n");

    int fd1;
    fd1 = open("FIFO1", 1);
    printf("fifo abierto: %d \n", fd1);

    time_t t;
    srand((unsigned) time(&t));
    char random[3];
    sprintf(random, "%d", rand() % 10);
    write(fd1, random, strlen(random));
    printf("random: %s \n", random);
    close(fd1);

    fd1 = open("FIFO1", 0);
    int bytes = -1;
    char buffer[3];
    while (bytes != 0){bytes = read(fd1, buffer, 1);}
    printf("El factorial de %s es %s \n", random, buffer);

    unlink("FIFO1");
}