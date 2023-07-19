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
                valido=0;
                opcion=0;
				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF);
	        }
	    }
    return 0;
	}
	
int cantidad_vidas(){
    int vidas=0,valido=1;
    while(valido==1){
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
            vidas=0;
            valido=1;
            int ch;
			while ((ch = getchar()) != '\n' && ch != EOF);						
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
            error=1;
            int ch;
			while ((ch = getchar()) != '\n' && ch != EOF);            
        }
    }
    return 0;
}
//cambiossss datos base datos fue movido a lista_pal_hash_da.h
