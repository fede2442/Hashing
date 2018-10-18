#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#define T_TABLA 25

int insertar(char tabla[][30], char* palabra);
int re_hash(char tabla[][30], char* palabra,int cont_rehash);
int numIndex(char* palabra);
int buscar(char tabla[][30], char* palabra, int index, int cont_rehash);
int reIndex(char* palabra, int cont_rehash);
int eliminar(char tabla[][30], char* palabra);
void leer_insertar(char tabla[][30]);

int main()
{
    char tabla[T_TABLA][30];
     leer_insertar(tabla);
    int i;
    for(i = 0; i < T_TABLA; i++){
        strcpy(tabla[i],"0");
    }
    char insertar_palabra[30];
    char buscar_palabra[30];
    char eliminar_palabra[30];
    int eleccion = 1;

    while (eleccion != 0){
        printf("--------------------------------------------------------------------\n");
        for(i = 0; i < T_TABLA; i++){
            printf("%s ",tabla[i]);
        }

        printf("\n1)Insertar \n2)Buscar \n3)Eliminar \n0)Terminar \nIngrese una opcion: ");
        scanf("%d",&eleccion);
        printf("--------------------------------------------------------------------\n");
        fflush(stdin);

        if(eleccion == 1){
            printf("\nIngrese palabra a ingresar:");
            gets(insertar_palabra);
            printf("Cantidad de rehashes: %d\n", insertar(tabla,insertar_palabra) );
        }


        else if(eleccion == 2){
                printf("\nIngrese palabra a buscar:");
                gets(buscar_palabra);
                int index = numIndex(buscar_palabra);
                int pos_busqueda = buscar(tabla, buscar_palabra, index, 0); //Devuelve la posicion o -1 si no encuentra la palabra.
                if(  pos_busqueda > 0 ){
                    printf("La palabra se encuentra en la posicion: %d.\n", pos_busqueda );
                }else
                {
                    printf("No se encontro la palabra. \n");
                }
        }
        else if(eleccion == 3){
                printf("\nIngrese palabra a eliminar:");
                gets(eliminar_palabra);
                int resul = eliminar(tabla, eliminar_palabra);
                if(resul == 1){
                    printf("La palabra se elimino con exito.\n");
                }else{printf("La palabra no estaba en la base de datos.\n");}
        }
        else if(eleccion == 0){break;}
    }
    return 0;
}

int insertar(char tabla[][30], char* palabra)
{
    /*Recibe un array de char* y un char* , calcula su indice y si esta vacio el lugar lo coloca ahi, de no ser asi llama a la funcion rehash.*/
    int index = numIndex(palabra);
    int cont = 0;
    if(strcmp(tabla[index], "0") == 0 || strcmp(tabla[index], "1") == 0  ){
        strcpy(tabla[index],palabra);
    }else{
        cont = 1;
        cont = re_hash(tabla, palabra, 1);
    }
    return cont;
}

int re_hash(char tabla[][30], char* palabra,int cont_rehash)
{
    int index = ( (numIndex(palabra)+cont_rehash) * cont_rehash ) % T_TABLA;

    if(strcmp(tabla[index], "0") == 0 || strcmp(tabla[index], "1") == 0 ){
        strcpy(tabla[index],palabra);
        return cont_rehash;
    }else{

        cont_rehash += 1;
         if (cont_rehash >= 25){
            printf("No hay mas lugar.\n");
            return 0;
        }
        return re_hash(tabla, palabra, cont_rehash);
    }
}

int buscar(char tabla[][30], char* palabra, int index, int cont_rehash){
    /*Busca la posicion de una palabra pasada por parametro, si no se encuentra devuelve -1*/

    if(strcmp(tabla[index],palabra) == 0){
        return index;
    }
    else if(strcmp(tabla[index], "0") == 0){
        return -1;
    }
    else{
        cont_rehash += 1;
        if(cont_rehash >= 25){return false;}
        return buscar(tabla,palabra,reIndex(palabra,cont_rehash),cont_rehash);
    }
}

int reIndex(char* palabra,int cont_rehash)
{
    return ( (numIndex(palabra)+cont_rehash) * cont_rehash ) % T_TABLA;
}

int numIndex(char* palabra)
{
    /*Es el algoritmo de hash en si, calcula el index recibiendo un string por parametro. */
    int i;
    int primo = 149; //primo mayor al tamaño del dicc (> 128)
    int n = 0;
    unsigned long sumaIndex = 0;
    int index = 0;
    for(i = 0; palabra[i] != '\0'; i++)
    {
        sumaIndex = sumaIndex + (((long)pow(primo, (strlen(palabra) - (n+1)))) * (palabra[i]));
        n++;
    }
    index = sumaIndex % T_TABLA;
    return index;
}

int eliminar(char tabla[][30], char* palabra){
    /*Busca la palabra dentro de la tabla, si la encuentra reemplaza la cadena por 1 que representa un elemento eliminado*/
    int index = numIndex(palabra);

    int posicion = buscar(tabla, palabra ,index,0);

    if(posicion != -1){
        strcpy(tabla[posicion],"1");
        return 1;
    }else{
        return -1;
    }

}
void leer_insertar(char tabla[][30])
{
    /* Lee de un archivo .txt con strings separados con \n y los agrega a una tabla de hash recibida por parametro.*/
    FILE* archivo = fopen("colores.txt", "r");
    int i, index;
    char c;
    c = fgetc(archivo);
    while(c != EOF)
    {
        char* palabra;
        palabra = malloc(sizeof(char));
        i = 0;
        while(c != '\n')
        {
            *(palabra + i) = c;
            i++;
            palabra = realloc(palabra, sizeof(char)*(i + 1));
            c = fgetc(archivo);
        }
        c = '\0';
        *(palabra + i) = c;
        c = fgetc(archivo);
        index = numIndex(palabra);

      strcpy(tabla[index],palabra);


    }

}

