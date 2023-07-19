#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "lista_palabras.h"
//#include "lista_palabras_abb.h"
//#include "lista_palabras_avl.h"
#include "lista_palabras_hash_da.h"
//#include "lista_palabras_hash_e.h"
#include "menu.h"

void inicializar(char*, int);
int juego(int, char*);
int contar_palabras_archivo(int);

int juego(int max, char* palabra_al){
    int valido=0,ganar=0,i=0,j=0,opcion=0;
    char mas[max],menos[max],asterisco[max];
    char palabra[max];
    int vidas,tamano=0;
    
    vidas = cantidad_vidas(); //el usuario elige cuantas vidas tendra para esta partida
    
    inicializar(mas,max);
    inicializar(menos,max);   				//se inicializan las variables
    inicializar(asterisco,max);
    
    FILE *archivo;
    archivo = fopen("registro_juego.txt", "w");	 // se inicia el respaldo de la partida
    fprintf(archivo, "Registro del juego:\n");
    
    while(ganar==0 && vidas>0){
    	inicializar(asterisco,max);
    	inicializar(mas,max);
   		inicializar(menos,max);   				//se inicializan las variables
        valido=0;
        printf("Te quedan %i vidas",vidas);
        while(valido==0){
            printf("\nEs tu momento de adivinar, ingresa una palabra de %i letras o ingrese 0 para finalizar el programa: ",max);
            scanf("%s",palabra);
            if(palabra[0]=='0'){ // si la palabra ingresada resulta ser 0 entonces se finaliza la partida
                fclose(archivo);
                return 1;
            }
            if(datos_base_datos(palabra)==1){ // se revisa si la palabra ingresada esta en la base de datos
                tamano = strlen(palabra);
                if(tamano==max){ //se comprueba que la palabra ingresada sea de tama�o max
                    printf("\n%s\n",palabra);
                   // printf("%s\n",palabra_al);
                    valido=1;
                    vidas--;
                    
                    // Escribir en el archivo
                    fprintf(archivo, "Palabra introducida: %s\n", palabra);
                }else{
                    printf("\nIngrese una palabra valida\n");
                }   
            }else{
                valido=0;
            }
        }
        
        if(strcmp(palabra,palabra_al)==0){ganar=1;} //si la palabra coincide con la palabra a adivinar gana la partida
        
        for(i=0;i<max;i++){
            for(j=0;j<max;j++){                       //se revisa si las letras de la palabra ingresada coincide con la palabra a adivinar
                if(palabra[i]==palabra_al[j]){
                    if(i==j){
                        asterisco[i]='*';
                    }else if(i!=j){
                        mas[i]='+';
                    }
                }
                menos[i]='-';
            }
        }
        //printf("%s\n",palabra);
        fprintf(archivo, "                     ");
        for(i=0;i<max;i++){
            if(asterisco[i]!=' '){					// se imprime las coincidencias que hubo en la palabra
                printf("%c",asterisco[i]);			// asterisco(*) es en el caso de haber adivinado la ubicacion correcta de la letra
                fprintf(archivo, "%c", asterisco[i]);
            }else if(mas[i]!=' '){					// mas(+) es en el caso de que la letra este en la palabra pero no en su posicion correcta
                printf("%c",mas[i]);
                fprintf(archivo, "%c", mas[i]);
            }else{
                printf("%c",menos[i]);				// menos(-) es en el caso de que la letra en cuestion no este en la palabra a adivinar
                fprintf(archivo, "%c", menos[i]);
            }
        }
        printf("\n");
        fprintf(archivo, "\n");
    }
    
    // Escribir en el archivo
    if(ganar==1){
        fprintf(archivo, "El usuario ha ganado el juego.\n");
        printf("\nFelicidades has adivinado la palabra!\n");
        printf("\nDesea guardar su partida? \n");
    	printf("Si[1]  No[2]\n\nIngrese respuesta: ");
    	scanf("%i", &opcion);											// aqui se pregunta si quiere guardar su partida en un archivo
    	if(opcion == 1){
    		fclose(archivo);
		}else{
			fclose(archivo);
			remove("registro_juego.txt");
		}

    }else{
        fprintf(archivo, "El usuario ha perdido el juego.\nLa palabra era %s.\n",palabra_al);
        printf("\nMala suerte se te han acabado las vidas :(\nLa palabra era %s\n",palabra_al);		// aqui se pregunta si quiere guardar su partida en un archivo
        printf("\nDesea guardar su partida? \n");
	    printf("Si[1]  No[2]\n\nIngrese respuesta: ");
	    scanf("%i", &opcion);
	    if(opcion == 1){
    		fclose(archivo);
		}else{
			fclose(archivo);
			remove("registro_juego.txt");
		}
    }
    return 0;
}

void inicializar(char mas[], int max){	//se inicializan las variables
    int i;
    for(i=0;i<max;i++){				
        mas[i]=' ';
    }
}

int contar_palabras_archivo(int max){
    FILE *archivo;
    int cont = 0, aux = 0;
    char contenido[100];

    archivo = fopen("palabras.txt","r");
    if(archivo == NULL){
        printf("El archivo no existe");
    }else{
        while(fgets(contenido, 100, archivo) != NULL){
            contenido[strcspn(contenido, "\n")] = '\0';
            aux = strlen(contenido);
            if(aux == max){
                cont++;
            }
        }
        return cont;
    }
    return 0;
}