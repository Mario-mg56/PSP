#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// 2. Crear un programa en C fork2.c que simule un árbol de procesos como el de la figura:
// p1>p2>p3>p4
// i. Los procesos padre siempre esperarán a que terminen los procesos hijo
// ii. Cada proceso mostrará su pid, el pid del padre y la suma de ambos pids

void main(){
    pid_t fk = 0;
    for (int i=0; i<3 && fk == 0; i++){
        fk = fork();
        if (fk != 0) wait(NULL);
    }
    printf("pid = %d, ppid = %d, pid+ppid = %d \n", getpid(), getppid(), (getpid()+getppid()));
}