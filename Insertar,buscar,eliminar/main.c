#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define T_TABLA 56

struct s_nodo
{
    char* texto;
    struct s_nodo* siguiente;
};
typedef struct s_nodo* t_nodo;

void agregar_lista(t_nodo* lista, char* palabra);
void imprimir(t_nodo lista);
void buscar(t_nodo lista, char* palabra, int index);
void eliminar(t_nodo* lista, char* palabra, int index);
int numIndex(char* palabra);
void leer_insertar(t_nodo* tabla);
int cantidad_nodos(t_nodo lista);

int main()
{
    t_nodo tabla[T_TABLA] = {0};
    leer_insertar(tabla);

    int l;
    int buckets_llenos = 0;
    int buckets_vacios = 0;
    int nodosXbucket[T_TABLA];


      char buscar_palabra[30];// = "Perro";
    printf("Ingrese palabra a buscar:");
    gets(buscar_palabra);
    int index_buscar = numIndex(buscar_palabra);
    clock_t begin = clock();

    buscar(tabla[index_buscar], buscar_palabra, index_buscar);

    clock_t end = clock();
     printf("\nTiempo que tardo en buscar: %f\n", (double)(end - begin) / CLOCKS_PER_SEC);

    for(l = 0; l < T_TABLA ; l++)
    {
        if(tabla[l] != 0)
        {
            printf("\nPOSICION = %d\n", l);
            imprimir(tabla[l]);
            buckets_llenos = buckets_llenos + 1;
        }
        else
        {
            printf("Bucket vacio = %d\n", l);
            buckets_vacios = buckets_vacios + 1;
        }
        printf("\n");
    }

    printf("Cantidad de buckets llenos: %d\n", buckets_llenos);
    printf("Cantidad de buckets vacios: %d\n", buckets_vacios);

    printf("Distribucion buckets:\n");
    for(l = 0; l < T_TABLA ; l++)
    {
        nodosXbucket[l] = cantidad_nodos(tabla[l]);
        printf("%d ", nodosXbucket[l]);
    }
char el_palabra[30];
printf("Ingrese palabra a eliminar: ");
gets(el_palabra);
int index_eliminar = numIndex(el_palabra);

    eliminar(&tabla[index_eliminar], el_palabra, index_eliminar);

 for(l = 0; l < T_TABLA ; l++)
    {
        if(tabla[l] != 0)
        {
            printf("POSICION = %d\n", l);
            imprimir(tabla[l]);
            buckets_llenos = buckets_llenos + 1;
        }
        else
        {
            printf("Bucket vacio = %d\n", l);
            buckets_vacios = buckets_vacios + 1;
        }
        printf("\n");
    }

    printf("Cantidad de buckets llenos: %d\n", buckets_llenos);
    printf("Cantidad de buckets vacios: %d\n", buckets_vacios);

    printf("Distribucion buckets:\n");
    for(l = 0; l < T_TABLA ; l++)
    {
        nodosXbucket[l] = cantidad_nodos(tabla[l]);
        printf("%d ", nodosXbucket[l]);
    }
    return 0;
}

void agregar_lista(t_nodo* lista, char* palabra)
{
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
    while(lista != NULL)
    {
        printf("%s\n", lista->texto);
        lista = lista->siguiente;
    }
}

int numIndex(char* palabra)
{
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

void buscar(t_nodo lista, char* palabra, int index)
{int flag=0;
    while(lista != NULL)
    {
        if(strcmp(lista->texto, palabra) == 0)
        {
            printf("'%s' encontrado en la posicion %d", palabra, index);
            flag=1;
        }
        lista = lista->siguiente;
    }
    if(flag==0)
        printf("No se encontro la siguiente palabra: &s",palabra);
}

int cantidad_nodos(t_nodo lista)
{
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
{   t_nodo aux=NULL;
    if (*lista == NULL)
        return 0;
    else if (strcmp((*lista)->texto, palabra) == 0)
    {
        aux=*lista;
        (*lista) =(*lista)->siguiente;
        free(aux);
    }
    else
        eliminar(&(*lista)->siguiente, palabra,index);
}


