#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <signal.h>

// 1. Programar signal1.c que muestre por pantalla la fecha y la hora a la que se inicia el 
// proceso junto con su pid. Al recibir la señal SIGINT deberá mostrar la fecha y hora de 
// finalización del programa.

void printDate(){
    char date[60];
    time_t t; 
    time(&t); 
    char *str = ctime(&t); 
    strcpy(date, str); 
    printf("%s", date);
}

void endHandler(int signum){
    printf("Fin del programa %d : ", getpid());
    printDate();
    printf("\n");
    exit(0);
}

void main(){
    signal(SIGINT, endHandler);
    printf("Inicio del programa %d : ", getpid());
    printDate();
    printf("\n");
    pause();
}


