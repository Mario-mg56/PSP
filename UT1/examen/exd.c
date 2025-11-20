#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

pid_t afork(){
    pid_t p = fork();
    if(p==-1){
        printf("error al crear el proceso");
        exit(0);
    }
    return p;
}
int main(){
    pid_t p2,p3;

    int fd12[2];
    int fd23[2];
    int fd32[2];

    pipe(fd12);
    pipe(fd23);
    pipe(fd32);

    p2 = afork();
    if(p2==0){
        //p2
        p3 = afork();
        if(p3==0){
            //p3
            close(fd23[1]);
            close(fd32[0]);
            int suma=0;
            int countNoMultiplos = 0;
            char buffer[100];
            while(read(fd23[0],buffer,sizeof(buffer))!=-1){
                int respuesta = atoi(buffer);

                if(respuesta%5==0){
                    suma+=respuesta;
                } else{
                    countNoMultiplos+=1;
                }
            }
            close(fd23[0]);

            char countChar[100];
            sprintf(countChar,"%d",countNoMultiplos);
            char sumaChar[100];
            sprintf(sumaChar,"%d",suma);

            write(fd32[1],sumaChar,strlen(sumaChar)+1);
            write(fd32[1],countChar,strlen(countChar)+1);
            close(fd32[1]);

            exit(0);
        } else {
            //p2
            close(fd12[1]);
            close(fd23[0]);
            close(fd32[1]);
            char buffer[100];
            read(fd12[0],buffer,sizeof(buffer));

            int count = atoi(buffer);
            for(int i = 0; i<count;i++){
                char numero[30];
                printf("Introduce numero: \n");
                scanf("%s", numero);
                write(fd23[1],numero,strlen(numero)+1);
            }
            close(fd23[1]);
            
            strcpy(buffer,"");
            read(fd32[0],buffer,sizeof(buffer));
            printf("La suma de los multiplos de 5 es igual a = %d \n",atoi(buffer));

            strcpy(buffer,"");
            read(fd32[0],buffer,sizeof(buffer));
            printf("Se han procesado %d numeros no multiplos de 5 \n",atoi(buffer));
            close(fd32[0]);
            exit(0);
        }
    } else {
        //p1
        close(fd12[0]);


        char input[30];
        printf("Introduce la cantidad de numeros a procesar: \n");
        scanf("%s", input);
        write(fd12[1],input,strlen(input)+1);
        close(fd12[1]);

        exit(0);
    }
    return 1 ;
}

