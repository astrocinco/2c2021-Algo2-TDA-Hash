// AQUI TODAS LAS FUNCIONES DE HASH QUE PODRIAMOS USAR
// https://softwareengineering.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed Acá hay muchas opciones
// http://www.cse.yorku.ca/~oz/hash.html
// https://stackoverflow.com/questions/34595/what-is-a-good-hash-function
// http://burtleburtle.net/bob/hash/doobs.html
// ????????como importamos esto????????? https://github.com/sindresorhus/fnv1a
// ????????como importamos esto????????? https://github.com/aappleby/smhasher
// ---------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>

// FUNCION DJB2
// https://stackoverflow.com/questions/7666509/hash-function-for-string
unsigned long
djb2fun(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

// FUNCION SDBM
// http://www.cse.yorku.ca/~oz/hash.html
static unsigned long
sdbm(str)
unsigned char *str;
{
    unsigned long hash = 0;
    int c;

    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

// .C para probar funciones de hashing. Compilar y llamar como: ./NOMBRE_COMPILADO NOMBRE_FUNCION TEXTO
// Ejemplo: astrocinco$ ./prueba_funciones djb2 hola  ----->  Resultado: hola -> 6385302889
// Si escribiste una función que no está retorna 0 en la terminal.
int main(int argc, char* argv[]){
  long resultado = 0;

  if (strcmp(argv[1], "djb2") == 0){
    resultado = djb2fun(argv[2]);
  }

  if (strcmp(argv[1], "sdbm") == 0){
    resultado = sdbm(argv[2]);
  }

  printf("Resultado: %s -> %li\n", argv[2], resultado);
  return 0;
}