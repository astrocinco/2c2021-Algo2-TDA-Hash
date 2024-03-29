#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h>
#include "funciones_hash.h"
#include "hash.h"

// NO SE SI ALGUNO DE ESTOS INCLUDES SOBRA
const int CAPACIDAD_INICIAL = 97; // Numero primo
const int FACTOR_NVO_TAM = 10;
const double MAX_FACTOR_CARGA = 0.8;
const double MIN_FACTOR_CARGA = 0.2;
#define FUN_HASHING1 djb2
#define FUN_HASHING2 sdbm
#define FUN_HASHING3 paul 
//#define FUN_HASHING4 djb_hash
// Hacer que todas las funciones retornen unsigned long? Y asegurarse que en todos lados esté unsigned long (o al menos hasta que se haga modulo)

// ----ESTRUCTURAS----

typedef struct hash {
    void** lista;
    int capacidad_lista;
    int cantidad_lista;
} hash_t;

typedef struct campo {
    const char* clave;
    void* dato;
} campo_t;

typedef struct hash_iter {
    hash_t* hash;
    int altura_actual_lista;
    bool al_final;
} hash_iter_t;

typedef void (*hash_destruir_dato_t)(void *);
typedef unsigned long (*func_hashing_t)(const char* str);

// ----PRIMITIVAS----
// PRIMITIVAS ITERADOR
int hash_iter_conseguir_prox_campo(const hash_iter_t* iter); 

hash_iter_t *hash_iter_crear(const hash_t *hash){
    hash_iter_t* iterador = malloc(sizeof(hash_iter_t));
    if (hash->cantidad_lista == 0) {
        iterador->altura_actual_lista = -1;
        iterador->al_final = true;
    } else{
        iterador->altura_actual_lista = hash_iter_conseguir_prox_campo(iterador);
        iterador->al_final = false;
    }
    return iterador;
}

bool hash_iter_quedan_campos(const hash_iter_t* iter){
    for(int i = iter->altura_actual_lista; i < iter->hash->capacidad_lista; i++){
        if (iter->hash->lista[i] != NULL){
            return true;
        }
    }
    return false;
}

int hash_iter_conseguir_prox_campo(const hash_iter_t* iter){
    for (int i = iter->altura_actual_lista; i < iter->hash->capacidad_lista; i++){
        if (iter->hash->lista[i] != NULL){
            return i;
        }
    }   
    return -1;
}

bool hash_iter_avanzar(hash_iter_t *iter){
    if (iter->al_final){ 
        return false;
    }
    if (!hash_iter_quedan_campos(iter)) {
        iter->altura_actual_lista = -1;
        iter->al_final = true;
    }
    iter->altura_actual_lista = hash_iter_conseguir_prox_campo(iter);
    return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
    if (iter->al_final) return NULL;
    campo_t* campo = iter->hash->lista[iter->altura_actual_lista];
    return campo->clave;
}

bool hash_iter_al_final(const hash_iter_t *iter){
    return iter->al_final;
}

void hash_iter_destruir(hash_iter_t* iter){
    free(iter);
}

// PRIMITIVAS CAMPO
campo_t* crear_campo(const char* clave, void* dato){
    campo_t* campo = malloc(sizeof(campo_t));
    if (campo == NULL){
        return NULL;
    } 
    void* copia = dato;
    campo->clave = clave;
    campo->dato = copia;

    return campo;
}

void destruir_campo(campo_t* campo_rip){
    free(campo_rip); // REVISAR NO FALTE ALGO MÁS ACÁ
}



// PRIMITIVAS HASH
hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t* hash = malloc(sizeof(hash_t));
    if (hash == NULL){
        return NULL;
    }
    void** lista_din = malloc(sizeof(campo_t) * CAPACIDAD_INICIAL);
    if (lista_din == NULL){
        return NULL;
    }

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
    if (nueva_lista == NULL){
        return false;
    }

    for (int i = 0; i < nueva_capacidad; i++){
        nueva_lista[i] = NULL;
    }

    hash_iter_t* iterador = hash_iter_crear(hash);
    const char* clave_actual;
    size_t pos_hash;
    size_t nueva_pos_hash;
    campo_t* campo_observado;

    while(!hash_iter_al_final(iterador)){
        clave_actual = hash_iter_ver_actual(iterador);

        pos_hash = FUN_HASHING1(clave_actual) % hash->capacidad_lista;
        campo_observado = hash->lista[pos_hash];
        if (strcmp(campo_observado->clave, clave_actual) == 0) {
            nueva_pos_hash = FUN_HASHING1(clave_actual) % nueva_capacidad;
            nueva_lista[nueva_pos_hash] = campo_observado;
            hash_iter_avanzar(iterador);
        }
    }
    free(hash->lista);
    hash->lista = nueva_lista;
    hash_iter_destruir(iterador);
    return true;
}

bool pos_esta_ocupada(const hash_t *hash, size_t posicion){
    return (hash->lista[posicion] != NULL);
}

bool hash_guardar_aux(hash_t* hash, size_t posicion, const char* clave, void* dato){
    campo_t* nuevo_campo = crear_campo(clave, dato);
    if (nuevo_campo == NULL){
        return false;
    }

    (hash->lista)[posicion] = nuevo_campo;
    hash->cantidad_lista++;
    return true;
}

bool hash_encontrar_pos_libre(hash_t *hash, const char *clave, void *dato){
    if (hash->cantidad_lista / hash->capacidad_lista > MAX_FACTOR_CARGA) hash_redimensionar(hash, hash->capacidad_lista * FACTOR_NVO_TAM);
     // CREO QUE TENGO QUE ARMAR UNA LISTA CON NUEVAS CAPACIDAD QUE SEAN NUMEROS PRIMOS, NO UN MULTIPLICADOR DE NUEVO TAMAÑO


    size_t pos_fun_hash = FUN_HASHING1(clave) % hash->capacidad_lista;
    if (!pos_esta_ocupada(hash, pos_fun_hash)){
        return hash_guardar_aux(hash, pos_fun_hash, clave, dato);
    }
    size_t pos_fun_hash2 = FUN_HASHING2(clave) % hash->capacidad_lista;
    if (!pos_esta_ocupada(hash, pos_fun_hash2)){
        return hash_guardar_aux(hash, pos_fun_hash2, clave, dato);
    }
    size_t pos_fun_hash3 = FUN_HASHING3(clave) % hash->capacidad_lista;
    if (!pos_esta_ocupada(hash, pos_fun_hash3)){
        return hash_guardar_aux(hash, pos_fun_hash3, clave, dato);
    }
    return false; 
    // ESTO DEBERÍA SER UN RETURN FALSE O UNA LLAMADA A hash_redimensionar E INTENTAR TODA LA FUNCION DE NUEVO?
}

bool hash_pertenece(const hash_t *hash, const char *clave_ingresada){
    size_t hashing_clave = FUN_HASHING1(clave_ingresada) % hash->capacidad_lista;
    if (!pos_esta_ocupada(hash,hashing_clave)){
        return false;
    }
    campo_t* campo_observado = hash->lista[hashing_clave];

    if (campo_observado != NULL) {
        if (campo_observado->clave == clave_ingresada){
            return true;    
        }
    } // Revisar si lista vacía retorna NULL

   

    return false;
}

void* verificar_clave(const hash_t *hash, func_hashing_t func,const char *clave_ingresada){
    if (!hash_pertenece(hash, clave_ingresada)){
        return NULL;
    }
    size_t hashing_clave = func(clave_ingresada) % hash->capacidad_lista;
    campo_t* campo_observado = hash->lista[hashing_clave];
    if (strcmp(campo_observado->clave, clave_ingresada) == 0){
        return campo_observado->dato;
    } else{
        return NULL;
    }
}

void *hash_obtener(const hash_t *hash, const char *clave_ingresada){
    void* func1 = verificar_clave(hash,FUN_HASHING1,clave_ingresada);
    if (func1 != NULL){
        return func1;
    }
    void* func2 = verificar_clave(hash,FUN_HASHING2,clave_ingresada);
    if (func2 != NULL){
        return func2;
    }
    void* func3 = verificar_clave(hash,FUN_HASHING3,clave_ingresada);
    if (func3 != NULL){
        return func3;
    }
    
    //printf("REVISAR HASH_OBTENER hash.c");
    return NULL; // NUNCA DEBERÍA LLEGAR AQUI 
}

void* borrar_aux(const hash_t *hash, func_hashing_t func,const char *clave){
    void* dato_resultado = hash_obtener(hash, clave);
    if (dato_resultado == NULL){
        return dato_resultado;
    }
    size_t pos_a_eliminar = func(clave) % hash->capacidad_lista;
    campo_t* campo_observado = hash->lista[pos_a_eliminar];

    if (campo_observado->dato == dato_resultado){
        hash->lista[pos_a_eliminar] = NULL; // Puede que este == sea incorrecto
        free(campo_observado);
    }
    return dato_resultado;
}

void *hash_borrar(hash_t *hash, const char *clave){
    void* dato_fun1 = borrar_aux(hash,FUN_HASHING1,clave);
    if (dato_fun1 != NULL){
        hash->cantidad_lista--;
        return dato_fun1;
    }
    void* dato_fun2 = borrar_aux(hash,FUN_HASHING2,clave);
    if (dato_fun2 != NULL){
        hash->cantidad_lista--;
        return dato_fun2;
    }
    void* dato_fun3 = borrar_aux(hash,FUN_HASHING3,clave);
    if (dato_fun3 != NULL){
        hash->cantidad_lista--;

        return dato_fun3;
    }
    return NULL;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){ // FINISH
    hash_borrar(hash, clave);
    bool hay_pos = hash_encontrar_pos_libre(hash, clave, dato);
    if (!hay_pos){
        return false;
    }else{
        return true;
    }
}

size_t hash_cantidad(const hash_t *hash){
    return hash->cantidad_lista;
}

void hash_destruir(hash_t *hash){
    // free(CADA CAMPO QUE QUEDO EN LA LISTA?);
    //con ir borrando primero;

    free(hash->lista);
    free(hash);
}
