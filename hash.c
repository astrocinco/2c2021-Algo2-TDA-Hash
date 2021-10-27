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
#define FUN_HASHING1 djb2
#define FUN_HASHING2 sdbm
#define FUN_HASHING3 func_vacia_1 // ELEGIR FUNCION DE HASHING
#define FUN_HASHING4 func_vacia_2 // ELEGIR FUNCION DE HASHING

// ----ESTRUCTURAS----

typedef struct hash {
    void** lista;
    int capacidad_lista;
    int cantidad_lista;
} hash_t;

typedef struct campo {
    char* clave;
    void* dato;
} campo_t;

typedef struct hash_iter {
    // TO DO
} hash_iter_t;
/*
typedef void (*hash_destruir_dato_t)(void *){
    // TO DO. WTF IS THIS
} 
*/
// ----PRIMITIVAS----
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

// PRIMITIVAS CAMPO
campo_t* crear_campo(const char* clave, void* dato){
    campo_t* campo = malloc(sizeof(campo));
    if (campo == NULL) return NULL;

    campo->clave = clave;
    campo->dato = dato;
    return campo;
}

void destruir_campo(campo_t* campo_rip){
    free(campo_rip); // REVISAR NO FALTE ALGO MÁS ACÁ
}

// PRIMITIVAS HASH
// hash_t *hash_crear(hash_destruir_dato_t destruir_dato){ // WTF IS THIS
hash_t *hash_crear(){
    hash_t* hash = malloc(sizeof(hash_t));
    if (hash == NULL) return NULL;

    void** lista_din = malloc(sizeof(campo_t) * CAPACIDAD_INICIAL);
    if (lista_din == NULL) return NULL;

    hash->lista = lista_din;
    hash->cantidad_lista = 0;
    hash->capacidad_lista = CAPACIDAD_INICIAL;

    for (int i = 0; i < CAPACIDAD_INICIAL; i++){
        hash->lista[i] = NULL;
    }

    return hash;
}

bool hash_redimensionar(hash_t* hash, int nueva_capacidad){
    void** nueva_lista = malloc(sizeof(campo_t) * nueva_capacidad);
    if (nueva_lista == NULL) return false;

    for (int i = 0; i < nueva_capacidad; i++){
        nueva_lista[i] = NULL;
    }

    hash_iter_t* iterador = hash_iter_crear();
    char* clave_actual;
    void* contenido_campo;
    int pos_hash;
    campo_t* campo_observado;

    while(!hash_iter_al_final(iterador)){
        clave_actual = hash_iter_ver_actual(iterador);

        pos_hash = FUN_HASHING1(clave) % hash->capacidad_lista;
        campo_observado = hash->lista[pos_hash];
        nueva_pos_hash = FUN_HASHING1(clave) % nueva_capacidad;
        if (strcmp(campo_observado->clave, clave_actual) == 0) {
            nueva_lista[nueva_pos_hash] = campo_observado;
            hash_iter_avanzar(iterador);
            continue;
        }

        pos_hash = FUN_HASHING2(clave) % hash->capacidad_lista;
        campo_observado = hash->lista[pos_hash];
        nueva_pos_hash = FUN_HASHING2(clave) % nueva_capacidad;
        if (strcmp(campo_observado->clave, clave_actual) == 0) {
            nueva_lista[nueva_pos_hash] = campo_observado;
            hash_iter_avanzar(iterador);
            continue;
        }

        pos_hash = FUN_HASHING3(clave) % hash->capacidad_lista;
        campo_observado = hash->lista[pos_hash];
        nueva_pos_hash = FUN_HASHING3(clave) % nueva_capacidad;
        if (strcmp(campo_observado->clave, clave_actual) == 0) {
            nueva_lista[nueva_pos_hash] = campo_observado;
            hash_iter_avanzar(iterador);
            continue;
        }

        pos_hash = FUN_HASHING4(clave) % hash->capacidad_lista;
        campo_observado = hash->lista[pos_hash];
        nueva_pos_hash = FUN_HASHING4(clave) % nueva_capacidad;
        if (strcmp(campo_observado->clave, clave_actual) == 0) {
            nueva_lista[nueva_pos_hash] = campo_observado;
            hash_iter_avanzar(iterador);
            continue;

        return false;
        }
    }
    free(hash->lista);
    hash->lista = nueva_lista;
    hash_iter_destruir(iterador);
    return true;
}

bool pos_esta_ocupada(hash_t *hash, int posicion){
    return (hash->lista[posicion] != NULL);
}

bool hash_guardar_aux(hash_t* hash, int posicion, const char* clave, void* dato){
    campo_t* nuevo_campo = crear_campo(clave, dato);
    if (nuevo_campo == NULL) return false;

    (hash->lista)[posicion] = nuevo_campo;
    (hash->cantidad_lista)++;
    return true;
}

bool hash_encontrar_pos_libre(hash_t *hash, const char *clave, void *dato){
    if (hash->cantidad_lista / hash->capacidad_lista > MAX_FACTOR_CARGA) hash_redimensionar(hash, hash->capacidad_lista * FACTOR_NVO_TAM); // CREO QUE TENGO QUE ARMAR UNA LISTA CON NUEVAS CAPACIDAD QUE SEAN NUMEROS PRIMOS, NO UN MULTIPLICADOR DE NUEVO TAMAÑO

    //int pos_fun_hash = djb2(clave) % hash->capacidad_lista; // EN CASO QUE FUN_HASHING° NO FUNCIONE
    int pos_fun_hash = FUN_HASHING1(clave) % hash->capacidad_lista;
    if (!pos_esta_ocupada(hash, pos_fun_hash)) return hash_guardar_aux(hash, pos_fun_hash, clave, dato);
    
    pos_fun_hash = FUN_HASHING2(clave) % hash->capacidad_lista;
    if (!pos_esta_ocupada(hash, pos_fun_hash)) return hash_guardar_aux(hash, pos_fun_hash, clave, dato);

    pos_fun_hash = FUN_HASHING3(clave) % hash->capacidad_lista;
    if (!pos_esta_ocupada(hash, pos_fun_hash)) return hash_guardar_aux(hash, pos_fun_hash, clave, dato);

    pos_fun_hash = FUN_HASHING4(clave) % hash->capacidad_lista;
    if (!pos_esta_ocupada(hash, pos_fun_hash)) return hash_guardar_aux(hash, pos_fun_hash, clave, dato);

    return false; // ESTO DEBERÍA SER UN RETURN FALSE O UNA LLAMADA A hash_redimensionar E INTENTAR TODA LA FUNCION DE NUEVO?
}

bool hash_pertenece(const hash_t *hash, const char *clave_ingresada){
    int hashing_clave = FUN_HASHING1(clave_ingresada);
    campo_t* campo_observado = hash->lista[hashing_clave];
    if (campo_observado != NULL) {
        if (campo_observado->clave == clave_ingresada) return true;
    } // Revisar si lista vacía retorna NULL

    hashing_clave = FUN_HASHING2(clave_ingresada);
    campo_observado = hash->lista[hashing_clave];
    if (campo_observado != NULL) {
        if (campo_observado->clave == clave_ingresada) return true;
    } // Revisar si lista vacía retorna NULL

    hashing_clave = FUN_HASHING3(clave_ingresada);
    campo_observado = hash->lista[hashing_clave];
    if (campo_observado != NULL) {
        if (campo_observado->clave == clave_ingresada) return true;
    } // Revisar si lista vacía retorna NULL

    hashing_clave = FUN_HASHING4(clave_ingresada);
    campo_observado = hash->lista[hashing_clave];
    if (campo_observado != NULL) {
        if (campo_observado->clave == clave_ingresada) return true;
    } // Revisar si lista vacía retorna NULL

    return false;
}

void *hash_obtener(const hash_t *hash, const char *clave_ingresada){
    if (!hash_pertenece(hash, clave_ingresada)) return NULL;

    int hashing_clave = FUN_HASHING1(clave_ingresada) % hash->capacidad_lista;
    campo_t* campo_observado = hash->lista[hashing_clave];
    if (strcmp(campo_observado->clave, clave_ingresada) == 0) return campo_observado->dato;

    hashing_clave = FUN_HASHING2(clave_ingresada) % hash->capacidad_lista;
    campo_observado = hash->lista[hashing_clave];
    if (strcmp(campo_observado->clave, clave_ingresada) == 0) return campo_observado->dato;

    hashing_clave = FUN_HASHING3(clave_ingresada) % hash->capacidad_lista;
    campo_observado = hash->lista[hashing_clave];
    if (strcmp(campo_observado->clave, clave_ingresada) == 0) return campo_observado->dato;

    hashing_clave = FUN_HASHING4(clave_ingresada) % hash->capacidad_lista;
    campo_observado = hash->lista[hashing_clave];
    if (strcmp(campo_observado->clave, clave_ingresada) == 0) return campo_observado->dato;

    printf("REVISAR HASH_OBTENER hash.c");
    return NULL; // NUNCA DEBERÍA LLEGAR AQUI 
}

void *hash_borrar(hash_t *hash, const char *clave){
    void* dato_resultado = hash_obtener(hash, clave);
    if (dato_resultado == NULL) return dato_resultado;

    int pos_a_eliminar = FUN_HASHING1(clave) % hash->capacidad_lista;
    campo_t* campo_observado = hash->lista[pos_a_eliminar];
    if (campo_observado->dato == dato_resultado) hash->lista[pos_a_eliminar] = NULL; // Puede que este == sea incorrecto

    pos_a_eliminar = FUN_HASHING2(clave) % hash->capacidad_lista;
    if (campo_observado->dato == dato_resultado) hash->lista[pos_a_eliminar] = NULL;

    pos_a_eliminar = FUN_HASHING3(clave) % hash->capacidad_lista;
    if (campo_observado->dato == dato_resultado) hash->lista[pos_a_eliminar] = NULL;

    pos_a_eliminar = FUN_HASHING4(clave) % hash->capacidad_lista;
    if (campo_observado->dato == dato_resultado) hash->lista[pos_a_eliminar] = NULL;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){ // FINISH
    hash_borrar(hash, clave);
    return hash_encontrar_pos_libre(hash, clave, dato);
}

size_t hash_cantidad(const hash_t *hash){
    return hash->cantidad_lista;
}

void hash_destruir(hash_t *hash){
    // free(CADA CAMPO QUE QUEDO EN LA LISTA?);
    free(hash->lista);
    free(hash);
}

