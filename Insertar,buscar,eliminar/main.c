#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#define T_TABLA 56

struct s_nodo
{
    char* texto;
    struct s_nodo* siguiente;
};
typedef struct s_nodo* t_nodo;

void agregar_lista(t_nodo* lista, char* palabra);
void imprimir(t_nodo lista);
bool buscar(t_nodo lista, char* palabra, int index);
void eliminar(t_nodo* lista, char* palabra, int index);
void agregar_hash(t_nodo* tabla,char* palabra);
int numIndex(char* palabra);
void leer_insertar(t_nodo* tabla);
int cantidad_nodos(t_nodo lista);

int main()
{
    t_nodo tabla[T_TABLA] = {0}; //Crea la tabla de hash
    leer_insertar(tabla); //Toma los datos de colores.txt y los inserta en la tabla de hash.

    int l;
    int buckets_llenos = 0, buckets_vacios = 0, bucket_mayor = 0, bucket_colisiones = 0;
    int nodosXbucket;
    int eleccion = 1;
    char el_palabra[30];// = "Perro";
    char buscar_palabra[30];// = "Perro";
    char insertar_palabra[30];// = "Perro";

    while(eleccion != 0)
    {
        //Recorre todo el array y calcula los buckets vacios y los llenos. Además muestra la distribucion de los buckets.
        printf(".......................................................\n");

        printf("Distribucion buckets:\n");
        for(l = 0; l < T_TABLA ; l++)
        {
            if(tabla[l] != 0)
            {
                buckets_llenos = buckets_llenos + 1;
            }
            else
            {
                buckets_vacios = buckets_vacios + 1;
            }

            nodosXbucket = cantidad_nodos(tabla[l]);

            if(nodosXbucket > 1){bucket_colisiones += 1;}
            if(nodosXbucket > bucket_mayor){bucket_mayor = nodosXbucket;}
            printf("%d ", nodosXbucket);
        }
        printf("\nCantidad de buckets llenos: %d\n", buckets_llenos);
        printf("Cantidad de buckets vacios: %d\n", buckets_vacios);
        printf("Bucket de mayor longitud: %d\n",bucket_mayor);
        printf("Cantidad de colisiones: %d\n",bucket_colisiones);
        buckets_llenos = 0;buckets_vacios = 0; bucket_colisiones = 0; bucket_mayor =0;
        printf(".......................................................\n");
/*...............................................................................................................................................................................................*/
        printf("1)Buscar palabra \n2)Eliminar palabra \n3)Agregar palabra \n0)Salir \nElija lo que desea hacer: ");
        scanf("%d",&eleccion);

        system("cls"); //SI SE QUIERE VER LOS RESULTADOS ANTERIORES SACAR ESTO!!!
        fflush(stdin);
        if(eleccion == 1){
            printf("\nIngrese palabra a buscar:");
            gets(buscar_palabra);
            clock_t begin = clock();
            int index_buscar = numIndex(buscar_palabra);

            if( buscar(tabla[index_buscar], buscar_palabra, index_buscar)){
                printf("Se encontró la palabra en la posicion: %d\n", index_buscar);
            }
            else{
                printf("La palabra no se encuentra.\n");
            }
            clock_t end = clock();
            printf("\nTiempo que tardo en buscar: %f\n", (double)(end - begin) / CLOCKS_PER_SEC);
        }
        else if(eleccion ==2){
            printf("Ingrese palabra a eliminar: ");
            gets(el_palabra);
            int index_eliminar = numIndex(el_palabra);
            if( buscar(tabla[index_eliminar], el_palabra, index_eliminar) )
                {
                    eliminar(&tabla[index_eliminar], el_palabra, index_eliminar);
                    printf("Se elimino correctamente.\n");
                }else{
                    printf("La palabra no esta en la base de datos.\n");
                }
        }
        else if(eleccion ==3){
            printf("\nIngrese palabra a ingresar:");
            gets(insertar_palabra);
            agregar_hash(tabla,insertar_palabra);
        }

        else if(eleccion != 0){printf("No es una opcion válida, por favor intente de nuevo.\n");}
    }
    return 0;
}

void agregar_lista(t_nodo* lista, char* palabra)
{
    /*Recibe por parametro un puntero a una lista y un puntero a char e ingresa la palabra al final de la lista. Si esta vacía la crea. */
    if (*lista == NULL)
    {
        *lista = malloc(sizeof(struct s_nodo));
        (*lista)->texto = palabra;
        (*lista)->siguiente = NULL;
    }
    else
        agregar_lista(&(*lista)->siguiente, palabra);
}

void imprimir(t_nodo lista)
{
    /* Recibe por parametro el nodo de una lista e imprime toda la lista hasta el final. */
    while(lista != NULL)
    {
        printf("%s\n", lista->texto);
        lista = lista->siguiente;
    }
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

void leer_insertar(t_nodo* tabla)
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
        if(tabla[index] == 0)
        {
            t_nodo n_lista = NULL;
            agregar_lista(&n_lista, palabra);
            tabla[index] = n_lista;
        }
        else
            agregar_lista(&tabla[index] , palabra);
    }
}

bool buscar(t_nodo lista, char* palabra, int index)
{
    /*Recibe por parametro una lista, un puntero a char y un index donde se encuentra esa palabra en la lista. Lo que hace es ir a esa posicion
    y recorrer la lista que esta ahi dentro hasta encontrar la palabra. Si la encuentra devuelve true, de lo contrario false.*/
    while(lista != NULL)
    {
        if(strcmp(lista->texto, palabra) == 0)
        {
            return true;
        }
        lista = lista->siguiente;
    }
        return false;
}


int cantidad_nodos(t_nodo lista)
{
    /* Cuenta la cantidad de nodos en una lista recibida por parametro y devuelve la cantidad.*/
    int cont = 0;
    t_nodo actual = lista;
    while (actual != NULL)
    {
        cont++;
        actual = actual->siguiente;
    }
    return cont;
}


void eliminar(t_nodo* lista, char* palabra, int index)
{
    /*Recibe por parametro un puntero a lista, un puntero a char y un index donde se encuentra la palabra en la lista y lo que hace es eliminar esa palabra de la lista.*/
     t_nodo aux=NULL;
    if (*lista == NULL);
    else if (strcmp((*lista)->texto, palabra) == 0)
    {
        aux=*lista;
        (*lista) =(*lista)->siguiente;
        free(aux);
    }
    else{
        eliminar(&(*lista)->siguiente, palabra,index);
    }
}



void agregar_hash(t_nodo* tabla,char* palabra)
{
    int index;
    index = numIndex(palabra);
    if(tabla[index] == 0)
    {
        t_nodo n_lista = NULL;
        agregar_lista(&n_lista, palabra);
        tabla[index] = n_lista;
    }
    else{
        agregar_lista(&tabla[index] , palabra);
    }
}



