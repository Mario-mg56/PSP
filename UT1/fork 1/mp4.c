#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*

b) ¿Qué salida genera este código? ¿Podría producirse otra salida? Justifica la respuesta

void main()
 {
  printf("CCC \n");
  if (fork()!=0)
  {
  printf("AAA \n");
  } else printf("BBB \n");
  exit(0);
 }

--Hay 3 posibles situaciones (En todas imprimieéndose inicialmente CCC):
    --1 El proceso hijo no se crea correctamente provocando que en la linea 12 (-1 != 0)
        devuelva true, imprimiéndose una única vez AAA. Resultado:
        CCC
        AAA

    --2 Se crea correctamente el hijo ejecutando se por un lado el código del padre (AAA)
        y por otro el del hijo (BBB). En este caso el print del padre se imprimirá antes.
        Resultado:
        CCC
        AAA
        BBB

    --3 Mismo caso que el anterior, pero en este caso se ejecutará antes el código del hijo.
        Resultado:
        CCC
        BBB
        AAA

c) Modificar el código para que la salida por pantalla sea:
 CCC
 BBB
 AAA

Para que la salida por pantalla siempre sea así, tenemos que asegurarnos de que se ejecuta primero
el hijo y después el padre, para ello añadiremos un wait(NULL) al código del padre antes del print

*/

//Código modificado:

void main()
 {
  printf("CCC \n");
  if (fork()!=0)
  {
    printf("");
    wait(NULL);
    printf("AAA \n");
  } else printf("BBB \n");
  exit(0);
 }