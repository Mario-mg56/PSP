#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <signal.h>

// 3. Programar utilizando señales signal3.c que guardará en un fichero salidas.txt los intentos de parar el
// programa utilizando CTRL+C

FILE *file;

void getTime(char *buffer, size_t size) {
    time_t t;
    time(&t);
    strftime(buffer, size, "%H:%M:%S", localtime(&t));
}

void endhandler(int signum) {
    fprintf(file, "SIGINT a las ");

    char timeStr[20];
    getTime(timeStr, 20);
    fprintf(file, "%s", timeStr);

    fprintf(file, "\n");
    fflush(file); //Guardo los cambios
}

void main(){
    file = fopen("salida.txt", "w"); // Abrir/crear el fichero en modo escritura (w)
    signal(SIGINT, endhandler);
    while(1) pause();
}