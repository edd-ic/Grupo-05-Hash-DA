#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partida.h"
#include <ctype.h> 


int main(){
	int opcion=0,max=0,resultado=0, limite=0, cont=0,flag=1;	//En esta linea se inicializan variables
	char* palabra_al;
	char palabra_aux[100];
	if(menu_ficha()==1){	//En esta linea se decide que hacer con ficha igual a 1
		srand(time(NULL));

		max = tamano_palabra(); //se escoge el tamano de la palabra para el resto de la partida y se le asigna a max ;
		lista_pal *lista_aux = crear_lista_aux(max);
		lista_pal *lista1 = crear_lista(max);//se crea un archivo de tipo lista llamado lista_pal y se escanea el archivo palabras.txt para hacer una lista con las palabras de tama�o max
		palabra_al = escoger_pal(lista1);//se elige la palabra al azar de tamano max
		printf("%s", palabra_al);
		strcpy(palabra_aux,palabra_al);
		printf("%s",palabra_aux);
		palabras_usadas(lista_aux,palabra_aux);
		cont++;
		limite = contar_palabras_archivo(max);
										//cambiossss le doy lista a juego para poder usar datos base datos en "juego" de partida.h!!!
    	resultado = juego(max,palabra_al,lista1); //se inicia el juego y se le pasan el tamano maximo de letras de la palabra y la palabra a adivinar
		if(resultado == 0){
				//mientras valido igual a 0 se realizan impresiones y otras acciones

				while(flag==1){	
					printf("\nDesea jugar de nuevo? \n");	//imprime si desea jugar de nuevo
					printf("Si[1]  No[2]\n\nIngrese respuesta: ");	//imprime si el jugador quiere o no jugar de nuevo
					scanf("%i", &opcion);				//lee la opcion elegida por el usuario
					if(opcion==1){	//si la opcion elegida es 1
					palabra_al = escoger_pal(lista1);//se elige la palabra al azar de tamano max
					if(cont==limite){
						printf("Ya no quedan palabras de tamano %i",max);
						flag=0;
					}
					printear(lista_aux);
					system("pause");				
					while(buscar_usada(lista_aux,palabra_al) == 1){
						printear(lista_aux);
						palabra_al = escoger_pal(lista1);//se elige la palabra al azar de tamano max
					}
					cont++;
					strcpy(palabra_aux,palabra_al);
					palabras_usadas(lista_aux, palabra_aux);
					juego(max,palabra_al,lista1); //se inicia el juego y se le pasan el tamano maximo de letras de la palabra y la palabra a adivinar

					}else if(opcion==2){
						flag=0;
					}else{
						flag=1;
						opcion=0;
								// Vaciar el búfer de entrada
						int ch;
						while ((ch = getchar()) != '\n' && ch != EOF);
					}
				}	//si opcion es distinta de 1 retorna un valor 0	
			
		}	
	}else{
		return 0; //si menu_ficha es distinto de 1, retorna un valor 0
	}
	return 0;
}