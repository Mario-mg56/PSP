#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*

b) ¿Qué salida genera este código? ¿Podría producirse otra salida? Justifica la respuesta

void main()
{
 pid_t pid1, pid2;
 printf("AAA \n");
 pid1 = fork();
 if (pid1==0)
 {
 printf("BBB \n");
 }
 else
 {
 pid2 = fork();
 printf("CCC \n");
 }
 exit(0);
}

-- En este código se pueden dar múltiples situaciones en función de que proceso vaya más rápido,
en todas ellas se imprimirá AAA al inicio. En el código el proceso padre tendrá 2 hijos y luego
imprimirá CCC, el primer hijo imprimira BBB y el segundo CCC. Las posibles salidas del código 
si asumimos que los hijos se crearán sin errores serán las combinaciones posibles de las
filas (BBB, CCC, CCC), en todos los casos antecedidas por AAA. Si ocurre un error durante la
creación del primer hijo no se imprimirá la linea BBB y si ocurre durante la creación del segundo
no se imprimirá CCC.


c) Añade el código necesario para que el orden de ejecución sea tal que los respectivos procesos
padre sean los últimos que se ejecuten.

*/

//Código modificado:

void main() {
    pid_t pid1, pid2;
    printf("AAA \n");
    pid1 = fork();
    if (pid1==0) printf("BBB \n");
    else {
        pid2 = fork();
        if (pid2 > 0){
            wait(NULL);
            wait(NULL);
        }
        printf("CCC \n");
    }
    exit(0);
}
