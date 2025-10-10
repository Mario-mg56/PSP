#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// 2. Crear un programa en C ipc2.c que realice las siguientes funciones:
// i. Dos procesos que se comunican mediante un pipe
// ii. El proceso padre deberá escribir varios números en el pipe, para finalizar introducirá el carácter +
// iii. El proceso hijo mostrará por pantalla cada uno de los números recibidos y la suma de los mismos
// una vez recibido el carácter +

void main(){
    char buffer[60];
    int fd[2]; //Array de llaves
    pipe(fd); //Introduzco las llaves de escritura/lectura

    if (fork() != 0){
        strcpy(buffer, "45,299,234+");
        close(fd[0]); //Cierro la llave de lectura
        write(fd[1], buffer, strlen(buffer));
    }

    else { 
        close(fd[1]); //Cierro la llave de escritura
        read(fd[0], buffer, 60);
        char currentNumber[100] = "";
        int result = 0;
        int operating = 1;
        char temp[2] = ""; //string temporal para convertir char a string
        for (int i = 0; i<sizeof(buffer) && operating == 1; i++){
            if (buffer[i] == '+'){
                result += atoi(currentNumber);
                operating = 0;
            }
            else if (buffer[i] == ',') {
                result += atoi(currentNumber);
                strcpy(currentNumber, "");
            }
            else {
                temp[0] = buffer[i];
                strcat(currentNumber, temp);
            }
            
        }
        printf("El resultado es: %d \n", result);
    }
}