#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

//Examen G01 Crear un programa ex1.c que realice las siguientes funciones:
    //1. Debe seguir el siguiente esquema P1>P2>P3. Los padres deben esperar a que sus hijos terminen
    //2. P1 solicitará al usuario una cantidad de números a procesar, enviándoselos a P2 por el pipe1
    //3. P2 solicitará al usuario los números y los comunicará por el pipe2 a P3 que será el encargado de procesarlos
    //4. P3 calculará sumará los números múltiplos de 5 y contará cuantos números NO son múltiplos de 5
    //5. P3 enviará por el pipe3 a P2 los datos y P2 los mostrará por pantalla

int main(){
    int fd1[2], fk, input;
    char buffer[60];
    pipe(fd1);
    fk = fork();
    if (fk == -1) {
        printf("Error al crear el proceso 2 \n");
        return 1;
    }
    if (fk != 0){ //P1
        printf("Introduce la cantidad de números a procesar: ");
        scanf("%d", &input);
        sprintf(buffer, "%d", input);  
        close(fd1[0]); //Cerramos la llave de lectura del pipe1
        //Pasamos a write la llave de escritura, el buffer y el tamaño del buffer
        //al que le sumamos 1 porque sizeof no coje el char nulo del final y es importante cerrar el string
        write(fd1[1], buffer, sizeof(buffer)+1); 
        wait(NULL); //P1 espera a que P2 muera, para morirse él
        printf("Fin de P1 \n");
    }
    else{
        int fd2[2], fd3[2], size;
        pipe(fd2);
        pipe(fd3);
        fk = fork();
        if (fk == -1) {
            printf("Error al crear el proceso 3 \n");
            return 1;
        }
        if (fk != 0) { //P2
            close(fd1[1]); //Cerramos la llave de escritura del pipe1
            read(fd1[0], buffer, 60);
            printf("P2 recibe %s \n", buffer); //db
            char temp[10];
            size = atoi(buffer); 
            strcpy(buffer, ""); // Vaciamos el buffer
            //Guardo los números del usuario en el buffer en formato "num1, num2, num3"
            for (int i = 0; i<size; i++) {
                printf("Introduce número: ");
                scanf("%d", &input);
                if (i == size-1) sprintf(temp, "%d", input); //Si es la última vuelta no ponemos coma
                else sprintf(temp, "%d,", input); 
                strcat(buffer, temp);
            }
            close(fd2[0]); //Cerramos la llave de lectura del pipe2
            write(fd2[1], buffer, sizeof(buffer)+1);

            close(fd3[1]); //Cerramos la llave de escritura del pipe3
            read(fd3[0], buffer, 60);
            printf("P2 recibe %s \n", buffer); //db
            //Separamos en 2 cadenas el buffer
            char noMults5[10], sum[30], currentChar[2] = "";
            int jump = 0; //Booleano que separa las dos cadenas
            for (int i = 0; i<strlen(buffer); i++) {
                currentChar[0] = buffer[i];
                if (buffer[i] == ';') jump = 1;
                else if (!jump) strcat(noMults5, currentChar);
                else strcat(sum, currentChar);
            }
            printf("Se han procesado %s números no múltiplos de 5 \n", noMults5);
            printf("La suma de los múltiplos de 5 es %s \n", sum);
            wait(NULL);
        }
        else { //P3
            close(fd2[1]); //Cerramos la llave de escritura del pipe2
            read(fd2[0], buffer, 60);
            printf("P3 recibe %s \n", buffer); //db
            //Sumatorio de los múltiplos de 5, recuento de los que no lo son, número actual
            int sum = 0, numNotMults5 = 0, currentNum;
            char currentDigit[2] = "", currentNumber[30] = ""; //Dígito y números actuales en string
            for (int i = 0; i<strlen(buffer); i++) {
                if (buffer[i] != ','){
                    currentDigit[0] = buffer[i];
                    strcat(currentNumber, currentDigit);
                }
                if (buffer[i] == ',' || i == strlen(buffer)-1) {
                    currentNum = atoi(currentNumber);
                    if (currentNum%5 == 0) sum += currentNum;
                    else numNotMults5++;
                    strcpy(currentNumber, "");
                }
            }
            strcpy(buffer, ""); // Vaciamos el buffer
            sprintf(buffer, "%d;%d", numNotMults5, sum); //Metemos los valores en el buffer en formato "num;sum"
            close(fd3[0]); //Cerramos la llave de lectura del pipe3
            write(fd3[1], buffer, sizeof(buffer)+1);
        }
    }

}