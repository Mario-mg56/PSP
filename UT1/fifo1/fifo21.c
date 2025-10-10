#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int num;
    char buffer[32];

    // Crear FIFO1 (para enviar número)
    mkfifo("FIFO1", 0666);

    srand(time(NULL));
    num = rand() % 11; // número aleatorio entre 0 y 10

    // Abrir FIFO1 para escritura
    int fd1 = open("FIFO1", O_WRONLY);
    if (fd1 < 0) {
        perror("Error al abrir FIFO1");
        exit(1);
    }

    // Enviar número al otro proceso
    sprintf(buffer, "%d", num);
    write(fd1, buffer, strlen(buffer) + 1);
    close(fd1);
    printf("[fifo11] Enviado número: %d\n", num);

    // Esperar a que el otro proceso cree FIFO2
    int fd2;
    while ((fd2 = open("FIFO2", O_RDONLY)) < 0) {
        usleep(100000); // Esperar 0.1 s
    }

    // Leer el resultado del factorial
    read(fd2, buffer, sizeof(buffer));
    printf("El factorial de %d es %s\n", num, buffer);
    close(fd2);

    // Eliminar los FIFOs al final
    unlink("FIFO1");
    unlink("FIFO2");

    return 0;
}
