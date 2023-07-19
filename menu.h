#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int menu_ficha(){
	int opcion,valido=0;
	
	    while(valido==0){
	        system("cls");
	        printf("\n    MENU\n\n1) Jugar.\n\n2) Salir.\n\nElija una opcion: \n");	//Muestra el men� principal del juego dandole la opcion si quiere jugar o salir.
	        scanf("%i",&opcion);		//1 significa que el usuario eligi� jugar y 2 si el usuario eligi� salir.
	        if(opcion>=1 && opcion<=2){
	            if(opcion==1){
	                valido=1;
	                 return 1;
	            }else if(opcion==2){return 0;}		//Si no elige 1 ni 2 le saltara un error y le dira que elija una opcion valida.
	        }else{
	            printf("Elija una opcion valida\n");
	            system("pause");
	        }
	    }
    return 0;
	}
	
int cantidad_vidas(){
    int vidas,valido=0;
    while(valido!=1){
        system("cls");
        printf("Elija el numero de vidas: ");
        scanf("%i",&vidas);		//Lee la cantidad de vidas que el ususario eligio
        system("cls");
        if(vidas>0){	//Revisa si la cantidad de vidas que eligio el usuario es mayor que 0.
		valido=0;
		return vidas;
		}
        else{
            printf("\nElija una cantidad de vidas valida (Mayor a 0)\n");	//Salta un error si la cantidad de vidas que eligio el ususario no es valida.
            system("pause");
        }
    }
    return 0;
}

int tamano_palabra(){	
	int max,error=1;
    while(error == 1){
        printf("ingrese el tamano de la palabra a adivinar\n");
        scanf("\n%i",&max);		//Lee el tama�o de la palabra que el usuario quiere adivinar.
        if(max>=3 && max<=7){	//Verifica si el tama�o de la palabra es valido entre los parametros entregados donde se especifica que se pueden ocupar palabras entre 3 y 7 letras.
            error=0;
            return max;
        }else{
            printf("\nIngrese un valor valido (entre 3 y 7)\n");	//Salta un error si el tama�o de la palabra no cumple con los requisitos.
        }
    }
    return 0;
}

int datos_base_datos(char palabra_al[100]){
    char  contenido[100];//defino las variables que usare
    FILE *datos;//declarar uso de archivo 
    
    datos = fopen("palabras.txt", "r");//abre el archivo en modo lectura

    if (datos == NULL){//comprobar que existe el archivo
        printf("No se pudo abrir el archivo.");
    } else {
		while (fgets(contenido, 100, datos) != NULL){//lee la primera linea del archivo .txt
            contenido[strcspn(contenido, "\n")] = '\0';//elimina el salto de liena para que no interfiera en la comparacion
            if (strcmp(palabra_al, contenido) == 0) {//compara para ver si las palabras son iguales
                fclose(datos);//cierra el archivo
				return 1;   //rompe el ciclo while
            }
        }    
        printf("La palabra no esiste en la base de datos");
        fclose(datos);
        return 0;
    }
    return 0;
}
