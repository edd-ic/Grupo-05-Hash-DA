#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct tabla_da{
    int tamano;
    char** tabla;
    char** tabla_aux;
}tabla_da;

typedef struct lista_pal{
    tabla_da* tabla_hash;
    tabla_da* tabla_pal_aux;
}lista_pal;

int hash(char palabra[100], int intento, int tamano){//cambiar por notacion radix....listoo!!
    int largo = 0,i=0;
    int valor = 0;
    largo = strlen(palabra);
for (i = 0; i < largo; i++) {
    valor += palabra[i] * pow(tamano, largo - i - 1);
}
    int hash = ((valor % tamano) + intento) % tamano;
    //printf("palabra=%s\nvalor=%i\n\nhash===%i",palabra,valor,hash);
    //system("pause");
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
    int i=0;
    while(tash->tabla_hash->tabla[pal_al] == NULL && i!=tash->tabla_hash->tamano){//hacer una condicion adicional y un contador para que no siga infinitamente.
        pal_al = rand() % tash->tabla_hash->tamano;
        i++;
    }

    return tash->tabla_hash->tabla[pal_al];

}

lista_pal* palabras_usadas(lista_pal* lista_aux, char palabra[100]){

    agregar_aux(lista_aux, palabra); // Actualización de la lista auxiliar
    return 0;
}

int buscar_usada(lista_pal* tash, char* palabra){
    int intento=0,num_aux=0;
    char pal[100];
    strcpy(pal,palabra);
    num_aux = hash(palabra, intento, tash->tabla_pal_aux->tamano);
    if(tash->tabla_pal_aux->tabla_aux[num_aux] == NULL){
    }else{
        while((intento < tash->tabla_pal_aux->tamano) && (tash->tabla_pal_aux->tabla_aux[num_aux] != NULL)){
            if(strcmp(tash->tabla_pal_aux->tabla_aux[num_aux],pal)==0){
                    return 1;
            }else{
            intento++;
            num_aux = hash(palabra, intento, tash->tabla_pal_aux->tamano);
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
int datos_base_datos(char palabra[100],lista_pal *lista1){//cambiossss
    int intento=0,num_hash=0,i=0;
    for(i=0;i<lista1->tabla_hash->tamano;i++){
        num_hash=hash(palabra,intento,lista1->tabla_hash->tamano);    
        if(strcmp(lista1->tabla_hash->tabla[num_hash],palabra)==0){
            return 1;
        }
        intento++;
    }

    return 0;
}