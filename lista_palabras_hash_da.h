#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct tabla_da{
    int tamano;
    char** tabla;
    char** tabla_aux;
}tabla_da;

typedef struct lista_pal{
    tabla_da* tabla_hash;
    tabla_da* tabla_pal_aux;
}lista_pal;

int hash(char palabra[100], int intento, int tamano){
    int largo = 0;
    int valor = 0, i = 0;

    largo = strlen(palabra);

    for(i = 0; i < largo; i++){
        valor += palabra[i];
    }
    int hash = ((valor % tamano) + intento) % tamano;
    return hash;
}

void iniciar_tabla_aux(lista_pal* tash){
    int i = 0;
    
    for(i = 0; i < tash->tabla_pal_aux->tamano; i++){
        tash->tabla_pal_aux->tabla_aux[i] = NULL;
    }
}

void iniciar_tabla(lista_pal* tash){
    int i = 0;

    for(i = 0; i < tash->tabla_hash->tamano; i++){
        tash->tabla_hash->tabla[i] = NULL;
    }
}

void agregar_aux(lista_pal* tash, char palabra[100]){
    int intento = 0;
    int num_aux = hash(palabra, intento, tash->tabla_pal_aux->tamano);

    if(tash->tabla_pal_aux->tabla_aux[num_aux] == NULL){
        tash->tabla_pal_aux->tabla_aux[num_aux] =  (char*)malloc(sizeof(char) * (strlen(palabra)+1));
        strcpy(tash->tabla_pal_aux->tabla_aux[num_aux], palabra);
    }else{
        while((intento < tash->tabla_pal_aux->tamano) && (tash->tabla_pal_aux->tabla_aux[num_aux] != NULL)){
            intento++;
            num_aux = hash(palabra, intento, tash->tabla_pal_aux->tamano);
        }
        tash->tabla_pal_aux->tabla_aux[num_aux] =  (char*)malloc(sizeof(char) * (strlen(palabra)+1));
        strcpy(tash->tabla_pal_aux->tabla_aux[num_aux], palabra);
    }
}



void agregar_tabla(lista_pal* tash, char palabra[100]){
    int intento = 0;
    int num = hash(palabra, intento, tash->tabla_hash->tamano);

    if(tash->tabla_hash->tabla[num] == NULL){
        tash->tabla_hash->tabla[num] =  (char*)malloc(sizeof(char) * (strlen(palabra)+1));
        strcpy(tash->tabla_hash->tabla[num], palabra);
    }else{
        while((intento < tash->tabla_hash->tamano) && (tash->tabla_hash->tabla[num] != NULL)){
            intento++;
            num = hash(palabra, intento, tash->tabla_hash->tamano);
        }
        tash->tabla_hash->tabla[num] =  (char*)malloc(sizeof(char) * (strlen(palabra)+1));
        strcpy(tash->tabla_hash->tabla[num], palabra);
    }
}

int pedir_tamano(int max){
    FILE* archivo;
    int cont = 0, aux = 0;
    char contenido[100];

    archivo = fopen("palabras.txt", "r");
    if(archivo == NULL){
        printf("El archivo no existe");
        return 0;
    }else{
        while(fgets(contenido, 100, archivo) != NULL){
            contenido[strcspn(contenido, "\n")] = '\0';
            aux = strlen(contenido);
            if(aux == max){
                cont++;
            }
        }
        fclose(archivo);
        return cont;
    }
}

lista_pal* crear_lista_aux(int max){
    int tamano = 0;
    tamano = pedir_tamano(max);
    lista_pal *tash = (lista_pal*)malloc(sizeof(lista_pal));
    tash->tabla_pal_aux = (tabla_da*)malloc(sizeof(tabla_da));
    tash->tabla_pal_aux->tamano = tamano;
    tash->tabla_pal_aux->tabla_aux = (char**)malloc(sizeof(char*) * tamano);
    iniciar_tabla_aux(tash);

    return tash;
}

lista_pal* crear_lista(int max){
    char palabra_archivo_txt[100];
    int num = 0, tamano = 0;

    FILE* archivo;
    archivo = fopen("palabras.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return NULL;
    }

    lista_pal* tash = (lista_pal*)malloc(sizeof(lista_pal));
    tash->tabla_hash = (tabla_da*)malloc(sizeof(tabla_da));
    tamano = pedir_tamano(max);
    tash->tabla_hash->tamano = tamano;
    //printf("\nTAMANO = %i\n",tash->tabla_hash->tamano);
    tash->tabla_hash->tabla = (char**)malloc(sizeof(char*) * tamano);
    iniciar_tabla(tash);

    while(fscanf(archivo, "%s", palabra_archivo_txt) == 1){
        num = strlen(palabra_archivo_txt);
        if (num == max) {
            agregar_tabla(tash, palabra_archivo_txt);
        }
    }
    fclose(archivo);
    return tash;
}

char* escoger_pal(lista_pal* tash) {
    int pal_al = rand() % tash->tabla_hash->tamano;

    while(tash->tabla_hash->tabla[pal_al] == NULL){
        pal_al = rand() % tash->tabla_hash->tamano;
    }

    return tash->tabla_hash->tabla[pal_al];

}

lista_pal* palabras_usadas(lista_pal* lista_aux, char palabra[100]){

    agregar_aux(lista_aux, palabra); // Actualización de la lista auxiliar
    return 0;
}

int buscar_usada(lista_pal* lista, char* palabra){
    int j;
    char aux[100];
    strcpy(aux,palabra);
    for(j = 0; j<lista->tabla_pal_aux->tamano; j++){
        if(lista->tabla_pal_aux->tabla_aux[j] != NULL){
            //printf("\nj=%i\n",j);
            //system("pause");
            //printf("aux=%s\ttabla_aux=%s",aux,lista->tabla_pal_aux->tabla_aux[j]);
            //system("pause");
            if(strcmp(aux,lista->tabla_pal_aux->tabla_aux[j])==0){
            //printf("aux=%s\ttabla_aux=%s",aux,lista->tabla_aux->tabla_aux);
            //system("pause");
            return 1;
            }            
        }
    }
    return 0;
}

void printear(lista_pal *lista1){
    int i=0;
    for(i=0; i<lista1->tabla_pal_aux->tamano; i++){
        if(lista1->tabla_pal_aux->tabla_aux[i]==NULL){
            printf("\t%i\t---\n",i);
        }else{
            printf("\t%i\t%s\n",i, lista1->tabla_pal_aux->tabla_aux[i]);
        }
    }
}