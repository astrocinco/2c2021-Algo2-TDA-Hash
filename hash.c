#include "funciones_hash.c"
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h> 
// NO SE SI ALGUNO DE ESTOS INCLUDES SOBRA
#define CAPACIDAD_INICIAL 97 // Numero primo
#define FACTOR_NVO_TAM 10
#define MAX_FACTOR_CARGA 0.8
#define MIN_FACTOR_CARGA 0.1
#define FUN_HASHING1 djb2 // NO SE SI ESTO FUNCIONA. VER hash_encontrar_pos_libre()
#define FUN_HASHING1 sdbm // NO SE SI ESTO FUNCIONA. VER hash_encontrar_pos_libre()
#define FUN_HASHING3 XXX // ELEGIR FUNCION DE HASHING
#define FUN_HASHING4 XXX // ELEGIR FUNCION DE HASHING

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

campo_t* crear_campo(char* clave, void* dato){
    campo->clave = clave;
    campo->dato = dato;
    return campo;
}

void destruir_campo(campo_t* campo_rip){
    free(campo_rip); // REVISAR NO FALTE ALGO MÁS ACÁ
}

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

bool hash_redimensionar(hash_t* hash, nueva_capacidad){

}

bool pos_esta_ocupada(hash_t *hash, int posicion){
    return (hash->lista[posicion] != NULL);
}

bool hash_guardar_aux(hash_t* hash, int posicion, char* clave, void* dato){
    campo_t* nuevo_campo = crear_campo(char* clave, void* dato);
    if (nuevo_campo == NULL) return false

    (hash->lista)[posicion] = nuevo_campo;
    (hash->cantidad_en_lista)++;
    return true;
}

bool hash_encontrar_pos_libre(hash_t *hash, const char *clave, void *dato){
    if (cantidad_en_lista / capacidad_en_lista > MAX_FACTOR_CARGA) hash_redimensionar(hash, hash->capacidad_lista * FACTOR_NVO_TAM); // CREO QUE TENGO QUE ARMAR UNA LISTA CON NUEVAS CAPACIDAD QUE SEAN NUMEROS PRIMOS, NO UN MULTIPLICADOR DE NUEVO TAMAÑO

    //int pos_fun_hash = djb2(clave) % hash->capacidad_lista; // EN CASO QUE FUN_HASHING° NO FUNCIONE
    int pos_fun_hash = FUN_HASHING1(clave) % hash->capacidad_lista;
    if (!pos_esta_ocupada(hash, pos_fun_hash)) return hash_guardar_aux(hash, pos_fun_hash, clave, dato);
    
    pos_fun_hash = FUN_HASHING2(clave) % hash->capacidad_lista;
    if (!pos_esta_ocupada(hash, pos_fun_hash)) return hash_guardar_aux(hash, pos_fun_hash, clave, dato);

    pos_fun_hash = FUN_HASHING3(clave) % hash->capacidad_lista;
    if (!pos_esta_ocupada(hash, pos_fun_hash)) return hash_guardar_aux(hash, pos_fun_hash, clave, dato);

    pos_fun_hash = FUN_HASHING4(clave) % hash->capacidad_lista;
    if (!pos_esta_ocupada(hash, pos_fun_hash)) return hash_guardar_aux(hash, pos_fun_hash, clave, dato);

    return false; // ESTO DEBERÍA SER UN RETURN FALSE O UNA LLAMADA A REDIMENSIONAR E INTENTAR TODA LA FUNCION DE NUEVO?
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){ // FINISH
    if (hash_obtener(XXX) != NULL) {
        hash_borrar(XXX);
    }
    return hash_encontrar_pos_libre();
}

void *hash_borrar(hash_t *hash, const char *clave){
    void* dato_resultado = hash_obtener(hash, clave);
    if (dato == NULL) return dato;

    int pos_a_eliminar = FUN_HASHING1(clave) % hash->capacidad_lista;
    if (hash->lista[pos_a_eliminar]->dato == dato_resultado) hash->lista[pos_a_eliminar] = NULL; // Puede que este == sea incorrecto

    pos_a_eliminar = FUN_HASHING2(clave) % hash->capacidad_lista;
    if (hash->lista[pos_a_eliminar]->dato == dato_resultado) hash->lista[pos_a_eliminar] = NULL;

    pos_a_eliminar = FUN_HASHING3(clave) % hash->capacidad_lista;
    if (hash->lista[pos_a_eliminar]->dato == dato_resultado) hash->lista[pos_a_eliminar] = NULL;

    pos_a_eliminar = FUN_HASHING4(clave) % hash->capacidad_lista;
    if (hash->lista[pos_a_eliminar]->dato == dato_resultado) hash->lista[pos_a_eliminar] = NULL;
}

void *hash_obtener(const hash_t *hash, const char *clave_ingresada){
    if (!hash_pertenece(hash, clave)) return NULL;

    int hashing_clave = FUN_HASHING1(clave) % hash->capacidad_lista;
    if (stgcmp((hash->lista)[hashing_clave]->clave, clave_ingresada) == 0) return (hash->lista)[hashing_clave]->dato;

    hashing_clave = FUN_HASHING2(clave) % hash->capacidad_lista;
    if (stgcmp((hash->lista)[hashing_clave]->clave, clave_ingresada) == 0) return (hash->lista)[hashing_clave]->dato;

    hashing_clave = FUN_HASHING3(clave) % hash->capacidad_lista;
    if (stgcmp((hash->lista)[hashing_clave]->clave, clave_ingresada) == 0) return (hash->lista)[hashing_clave]->dato;

    hashing_clave = FUN_HASHING4(clave) % hash->capacidad_lista;
    if (stgcmp((hash->lista)[hashing_clave]->clave, clave_ingresada) == 0) return (hash->lista)[hashing_clave]->dato;

    printf("REVISAR HASH_OBTENER hash.c");
    return NULL; // NUNCA DEBERÍA LLEGAR AQUI 
}

bool hash_pertenece(const hash_t *hash, const char *clave_ingresada){
    int hashing_clave = FUN_HASHING1(clave);
    if (hash->lista[hashing_clave] != NULL) {
        if ((hash->lista[hashing_clave])->clave == clave_ingresada) return true;
    } // Revisar si lista vacía retorna NULL

    int hashing_clave = FUN_HASHING2(clave);
    if (hash->lista[hashing_clave] != NULL) {
        if ((hash->lista[hashing_clave])->clave == clave_ingresada) return true;
    } // Revisar si lista vacía retorna NULL

    int hashing_clave = FUN_HASHING3(clave);
    if (hash->lista[hashing_clave] != NULL) {
        if ((hash->lista[hashing_clave])->clave == clave_ingresada) return true;
    } // Revisar si lista vacía retorna NULL

    int hashing_clave = FUN_HASHING4(clave);
    if (hash->lista[hashing_clave] != NULL) {
        if ((hash->lista[hashing_clave])->clave == clave_ingresada) return true;
    } // Revisar si lista vacía retorna NULL

    return false;
}

size_t hash_cantidad(const hash_t *hash){
    return hash->cantidad_en_lista;
}

void hash_destruir(hash_t *hash){
    // free(CADA CAMPO QUE QUEDO EN LA LISTA?);
    free(hash->lista);
    free(hash);
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
