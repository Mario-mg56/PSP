#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <signal.h>

// 2. Programar utilizando señales, signal2.c que mostrará por pantalla cada 5 segundos el tiempo
// transcurrido.
int secs = 0;

void alarmHandler(int signum){
    secs += 5;
    printf("Han pasado %d \n", secs);
    alarm(5);

}

void main(){
    signal(SIGALRM, alarmHandler);
    alarm(5);
    while(1) {pause();}
}


