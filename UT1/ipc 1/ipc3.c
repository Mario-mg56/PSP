#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

// 3. Modificar el programa anterior y genera un programa ipc3.c que realice las siguientes funciones:
// i. El proceso hijo deberá generar dos números aleatorios entre 1 y 50 y escribirlos en el pipe
// ii. El proceso padre mostrará por pantalla la suma, la diferencia, el producto y la división de los
// números recibidos.

void main(){
    char buffer[60];
    int fd[2]; //Array de llaves
    pipe(fd); //Introduzco las llaves de escritura/lectura

    if (fork() == 0){
        time_t t;
        char random1[4] = "", random2[4] = "";
        srand((unsigned) time(&t));
        //Generamos 2 numeros aleatorios entre 1 y 50
        sprintf(random1, "%d", rand() % 50);
        sprintf(random2, "%d", rand() % 50);
        strcat(random1, ",");
        strcat(random2, "f");
        strcat(random1, random2);
        strcpy(buffer, random1);
        close(fd[0]); //Cierro la llave de lectura
        write(fd[1], buffer, strlen(buffer));
    }

    else { 
        close(fd[1]); //Cierro la llave de escritura
        read(fd[0], buffer, 60);
        char currentNumber[3] = "";
        int num1 = 0, num2 = 0;
        int operating = 1;
        char temp[2] = ""; //string temporal para convertir char a string
        for (int i = 0; i<sizeof(buffer) && operating == 1; i++){
            if (buffer[i] == 'f'){
                num2 += atoi(currentNumber);
                operating = 0;
            }
            else if (buffer[i] == ',') {
                num1 += atoi(currentNumber);
                strcpy(currentNumber, "");
            }
            else {
                temp[0] = buffer[i];
                strcat(currentNumber, temp);
            }
            
        }
        printf("%d + %d = %d \n", num1, num2, num1+num2);
        printf("%d - %d = %d \n", num1, num2, num1-num2);
        printf("%d * %d = %d \n", num1, num2, num1*num2);
        printf("%d / %d = %d \n", num1, num2, num1/num2);
    }
}