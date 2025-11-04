#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <signal.h>

// 4. Programar utilizando señales signal4.c simulando la activación de una alarma como se muestra en al
// salida

int period, times;

void getTime(char *buffer, size_t size) {
    time_t t;
    time(&t);
    strftime(buffer, size, "%H:%M:%S", localtime(&t));
}

void alarmHandler(int signum){
    char timeStr[20];
    getTime(timeStr, 20);
    printf("Ha sonado la alarma a las %s \n", timeStr);
    if (times<=1) exit(0);
    alarm(period);
    times--;
}

void main(){
    printf("Cuántas veces sonará la alarma? \n");
    scanf("%d", &times);
    printf("Cada cuántos segundos sonará? \n");
    scanf("%d", &period);
    signal(SIGALRM, alarmHandler);
    alarm(period); 
    while(1) pause(); 
}