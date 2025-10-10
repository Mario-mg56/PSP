#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int factorial(int n) {
    int fact = 1;
    for (int i = 2; i <= n; i++)
        fact *= i;
    return fact;
}

int main() {
    char buffer[32];

    // Crear FIFO2 (para enviar factorial)
    mkfifo("FIFO2", 0666);

    // Esperar a que el otro proceso cree FIFO1
    int fd1;
    while ((fd1 = open("FIFO1", O_RDONLY)) < 0) {
        usleep(100000); // Esperar 0.1 s
    }

    // Leer número desde FIFO1
    read(fd1, buffer, sizeof(buffer));
    int num = atoi(buffer);
    close(fd1);
    printf("[fifo12] Recibido número: %d\n", num);

    // Calcular factorial
    int result = factorial(num);
    sprintf(buffer, "%d", result);

    // Abrir FIFO2 para escritura y enviar resultado
    int fd2 = open("FIFO2", O_WRONLY);
    if (fd2 < 0) {
        perror("Error al abrir FIFO2");
        exit(1);
    }

    write(fd2, buffer, strlen(buffer) + 1);
    close(fd2);
    printf("[fifo12] Enviado factorial: %d\n", result);

    return 0;
}
