#IFNDEF FUNCIONES_HASH_H
#DEFINE FUNCIONES_HASH_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>

// FUNCION DJB2
// https://stackoverflow.com/questions/7666509/hash-function-for-string
unsigned long
djb2(unsigned char *str)
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

// Paul Larson's
// Originalmente era de c++ y recibía una seed. Reemplazar/ rehacer
// https://stackoverflow.com/questions/98153/whats-the-best-hashing-algorithm-to-use-on-a-stl-string-when-using-hash-map
unsigned int
paul(
    const char* s)
{
    unsigned int seed = 0;
    unsigned int hash = seed;
    while (*s)
    {
        hash = hash * 101  +  *s++;
    }
    return hash;
}

/* D. J. Bernstein hash function */
// Muy similar a djb2?
// https://codereview.stackexchange.com/questions/85556/simple-string-hashing-algorithm-implementation
static size_t djb_hash(const char* cp)
{
    size_t hash = 5381;
    while (*cp)
        hash = 33 * hash ^ (unsigned char) *cp++;
    return hash;
}
/* FUNCION SIN USAR POR RETORNAR NUMEROS NEGATIVOS
// Fowler/Noll/Vo (FNV) hash function, variant 1a
// https://codereview.stackexchange.com/questions/85556/simple-string-hashing-algorithm-implementation
// La palabra meme da negativo pero el hash<0 no funciona
static size_t fnv1a_hash(const char* cp)
{
    size_t hash = 0x811c9dc5;
    while (*cp) {
        hash ^= (unsigned char) *cp++;
        hash *= 0x01000193;
    }
    // Esto lo agregó Santiago:
    if (hash<0) {
      printf("Trigger\n");
      hash = hash * (-1);
    };
    return hash;
}
*/

#ENDIF