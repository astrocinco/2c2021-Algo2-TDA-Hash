#include "funciones_hash.c"
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h> 
// NO SE SI ALGUNO DE ESTOS INCLUDES SOBRA
#define CAPACIDAD_INICIAL = 100 

// ESTRUCTURAS
typedef struct hash {
    void* lista;
    int capacidad_lista;
    int cantidad_en_lista;
} hash_t;

typedef struct campo {
    char* clave;
    void* contenido;
} campo_t;

typedef struct hash_iter {
    // TO DO
} hash_iter_t;

typedef void (*hash_destruir_dato_t)(void *){
    // TO DO
} 

// PRIMITIVAS HASH
hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t* hash = malloc(sizeof(hash_t));
    if (hash == NULL) return NULL;

    hash->lista = malloc(sizeof(campo_t) * CAPACIDAD_INICIAL);
    hash->cantidad_en_lista = 0;
    hash->capacidad_lista =  = CAPACIDAD_INICIAL;

    return hash;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){

}

void *hash_borrar(hash_t *hash, const char *clave){

}

void *hash_obtener(const hash_t *hash, const char *clave){

}

bool hash_pertenece(const hash_t *hash, const char *clave){

}

size_t hash_cantidad(const hash_t *hash){

}

void hash_destruir(hash_t *hash){

}

// PRIMITIVAS ITERADOR
hash_iter_t *hash_iter_crear(const hash_t *hash){

}

bool hash_iter_avanzar(hash_iter_t *iter){

}

const char *hash_iter_ver_actual(const hash_iter_t *iter){

}

bool hash_iter_al_final(const hash_iter_t *iter){

}

void hash_iter_destruir(hash_iter_t* iter){

}
