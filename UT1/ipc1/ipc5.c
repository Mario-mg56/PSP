#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

// 5. Crear un programa en C ipc5.c que realice las siguientes funciones:
// i. Deberá responder al esquema de la figura
// i. El proceso hijo P2 solicitará por pantalla el número de DNI (el usuario lo introducirá sin espacios y
// sin la letra)
// ii. El proceso padre P1, recibe el DNI por el pipe1, calculará la letra del NIF y escribirá el resultado
// por el pipe2
// iii. El proceso hijo P2 mostrará por pantalla la letra calculada

void main(){
    char buffer[9], buffer2[2];
    int fd[2], fd2[2], dni;
    pipe(fd); //Introduzco las llaves de escritura/lectura
    pipe(fd2);

    if (fork() == 0){
        time_t t;
        srand((unsigned) time(&t));
        dni = 12345678;
        printf("Introduce tu dni sin letra: ");
        scanf("%d", &dni);
        sprintf(buffer, "%d", dni);
        close(fd[0]); //Cierro la llave de lectura del pipe 1
        write(fd[1], buffer, strlen(buffer));
        close(fd2[1]); //Cierro la llave de escritura del pipe 2 +
        read(fd2[0], buffer2, 2);
        printf("La letra de tu dni es %s \n", buffer2);
    }

    else {
        close(fd[1]); //Cierro la llave de escritura del pipe 1
        read(fd[0], buffer, 8);
        dni = atoi(buffer);
        char letters[] = "TRWAGMYFPDXBNJZSQVHLCKE";
        dni %= 23;
        buffer2[0] = letters[dni];
        close(fd2[0]); //Cierro la llave de lectura del pipe 2 
        write(fd2[1], buffer2, 2);
    }
}