#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

// 4. Crear un programa en C ipc4.c que realice las siguientes funciones:
// i. Deberá responder al esquema de la figura
// ii. El proceso padre P1 generará un número aleatorio entre 0 y 10 en el pipe1
// iii. El proceso hijo P2 deberá calcular el resultado del factorial de dicho número y escribir el resultado
// en el pipe2
// iv. El proceso padre se encargará de mostrar por pantalla el resultado del cálculo.

void main(){
    char buffer[2], buffer2[8];
    int fd[2], fd2[2], num;
    pipe(fd); //Introduzco las llaves de escritura/lectura
    pipe(fd2);

    if (fork() != 0){
        time_t t;
        srand((unsigned) time(&t));
        num = rand() % 10;
        num = 10;
        sprintf(buffer, "%d", num);
        close(fd[0]); //Cierro la llave de lectura del pipe 1
        write(fd[1], buffer, strlen(buffer));
        close(fd2[1]); //Cierro la llave de escritura del pipe 2 
        read(fd2[0], buffer2, 8);
        printf("EL factorial de %d es %d \n", num, atoi(buffer2));
    }

    else {
        close(fd[1]); //Cierro la llave de escritura del pipe 1
        read(fd[0], buffer, 8);
        num = atoi(buffer);
        for (int i = num-1; i>1; i--) {num *= i;}
        sprintf(buffer2, "%d", num);
        close(fd2[0]); //Cierro la llave de lectura del pipe 2 
        write(fd2[1], buffer2, strlen(buffer2));
    }
}