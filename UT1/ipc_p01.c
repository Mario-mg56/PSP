#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char buffer[60];
    int fd[2]; //Array de llaves
    pipe(fd);
    if (fork() != 0) { //Proceso P1
        printf("Proceso P1 pid: %d \n", getpid());
        printf("--Calculadora--\n");
        printf("1. Sumar\n");
        printf("2. Restar\n");
        printf("3. Multiplicar\n");
        printf("4. Dividir\n");
        int choice, num1, num2;
        printf("Introduzca la opción deseada: \n");
        scanf("%d", &choice);
        printf("Introduzca el primer operando\n");
        scanf("%d", &num1);
        printf("Introduzca el segundo operando\n");
        scanf("%d", &num2);
        sprintf(buffer, "%d,%d,%d", choice, num1, num2);        
        close(fd[0]); //Cierro llave de lectura
        write(fd[1], buffer, strlen(buffer));
        wait(NULL);
        printf("Fin P1 \n");
    }
    else {
        int fd2[2]; //2do array de llaves
        pipe(fd2);
        if (fork() != 0) { //Proceso P2
            close(fd[1]); //Cierro llave de escritura del pipe 1
            read(fd[0], buffer, 60);
            printf("Proceso P2 pid: %d, ppid %d \n", getpid(), getppid());
            printf("buffer: %s\n", buffer);
            int choice, num1, num2, count = 0;
            char currentDigit[2], currentNumber[30], operator;
            for(int i = 0; i<=strlen(buffer); i++){
                if(buffer[i] != ',') {
                    currentDigit[0] = buffer[i];
                    strcat(currentNumber, currentDigit);
                }
                else {
                    if (count == 0) choice = atoi(currentNumber);
                    else num1 = atoi(currentNumber);
                    strcpy(currentNumber, "");
                    count++;
                }
            }
            num2 = atoi(currentNumber);
            int result;
            switch(choice){
                case 1:
                    operator = '+';
                    result = num1+num2;
                    break;
                case 2:
                    operator = '-';
                    result = num1-num2;
                    break;
                case 3:
                    operator = 'x';
                    result = num1*num2;
                    break;
                case 4:
                    operator = '/';
                    result = num1/num2;
                    break;
            }
            printf("Operación %d %c %d = %d \n", num1, operator, num2, result);
            close(fd2[0]); //Cierro llave de lectura del pipe 2
            strcpy(buffer, "");
            sprintf(buffer, "%d", result); 
            write(fd2[1], buffer, strlen(buffer));
            wait(NULL);
            printf("Fin P2 \n");
        }
        else { //Proceso P3
            close(fd2[1]); //Cierro llave de escritura del pipe 2
            read(fd2[0], buffer, 60);
            printf("Proceso P3 pid: %d, ppid %d \n", getpid(), getppid());
            int result = atoi(buffer);
            printf("%d, el resutado de la operación es %s \n",
                 result, (result%2 == 0) ? "par" : "impar");
            printf("Fin P3 \n");
        }
    }
    return 0; 
}
