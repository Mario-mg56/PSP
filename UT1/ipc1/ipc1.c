#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

// 1. Crear un programa en C ipc1.c que realice las siguientes funciones:
// i. Dos procesos que se comunican mediante un pipe
// ii. El proceso padre deberá escribir en el pipe la fecha y la hora
// iii. El proceso hijo mostrará por pantalla lo enviado por el proceso padre

void main(){

    char date[60];
    int fd[2]; //Array de llaves
    pipe(fd); //Introduzco las llaves de escritura/lectura

    if (fork() != 0){
        time_t t; //Variable en la que vamos a introducir información relativa al tiempo
        time(&t); //Obtiene los segundos transcurridos desde el 1/1/1970 hasta ahora
        //Guardo la referencia del string de la fecha para luego introducirlo en el array
        char *str = ctime(&t); //ctime(&t) formatea esa fecha en un string más legible
        strcpy(date, str); //strcpy copia el segundo parámetro en el primer parámetro
        close(fd[0]); //Cierro la llave de lectura
        write(fd[1], date, strlen(date));
    }

    else {
        close(fd[1]); //Cierro la llave de escritura
        read(fd[0], date, 60);
        printf("Fecha actual: %s \n", date);
    }
}