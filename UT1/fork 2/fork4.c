#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// 4. Crear un programa en C fork4.c que simule un árbol de procesos como el de la figura:
//p1>p2>p5
//p1>p3>p4

// i. El/los proceso/s padre/s deberá/n esperar a que sus hijo/s termine/n
// ii. El proceso P1 define una variable acumulado igual al número de su pid
// iii. Cada proceso hijo mostrará por pantalla el valor de dicha variable incrementado en 10 si su pid es
// par o decrementado en 100 si es impar.

void main(){
    pid_t fk = 0, acumulado = getpid();
    for (int i=1; i<3 && fk == 0; i++){
        fk = fork();
        //En la 1era vuelta empezará otro linaje
        if (i == 1 && getpid() == acumulado) {
            fk = fork();
            if (fk != 0) wait(NULL); //p1 espera 2 veces por tener dos hijos
        }
        if (fk != 0) wait(NULL);
        else { 
            if (getpid()%2 == 0) acumulado += 10;
            else acumulado -= 100;
        }
    }
    printf("Soy %d, mi padre es %d y mi valor acumulado es %d \n", getpid(), getppid(), acumulado);
}

