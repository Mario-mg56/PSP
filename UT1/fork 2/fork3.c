#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// 3. Crear un programa en C fork3.c que simule un árbol de procesos como el de la figura:
// p1>p2>p3>p5
// p2>p4>p6

// iii. Los procesos padre siempre esperarán a que terminen los procesos hijo
// iv. Cada proceso mostrará su pid, el pid de su abuelo (si lo tuviera) 

void main(){
    int fk = 0, p1pid = getpid(), ppid = getppid(), gfpid = 0;
    double gen = 1;
    for (int i=1; i<4 && fk == 0; i++){
        fk = fork();
        //En la 2da vuelta el p2 empezará otro linaje
        if (i == 2 && getppid() == p1pid) {
            fork();
            if (fk != 0) wait(NULL); //p2 espera 2 veces por tener dos hijos
            else gen = gen + 0.1;
        }
        //printf(fk);
        if (fk != 0) wait(NULL);
        else { 
            printf("try \n");
            gen = gen + 1;
            gfpid = ppid; //El padre heredado de tu padre es tu abuelo
            ppid = getppid(); //Sustituyes el padre heredado por tu padre
        }
    }
    printf("Soy de la gen %f, mi pid es %d, el de mi padre %d ", gen, getpid(), getppid());
    if (getpid() == p1pid || getppid() == p1pid) printf("y no tengo abuelo \n");
    else printf("y el de mi abuelo %d \n", gfpid);
}