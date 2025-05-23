#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "list.h"

typedef struct 
{
    char id[100];
    char artists[100];
    char album_name[300];
    char track_name[100];
    float tempo;
    char track_genre[100];
} musica;

int lower_than_str(void* key1, void* key2) {
    return strcmp((char*)key1, (char*)key2) < 0;
}

/*Esta función compara dos punteros a float (usando void* para generalidad), 
y determina si el valor apuntado por key1 es menor que el de key2.*/
int lower_than_float(void* key1, void* key2) {
    return *(float*)key1 < *(float*)key2;
}

void mostrarMenu()
{
    limpiarPantalla();
    puts("========================================");
    puts("     Base de Datos de Canciones");
    puts("========================================");
  
    puts("1) Cargar Canciones");
    puts("2) Buscar por ID");
    puts("3) Buscar por género");
    puts("4) Buscar por artista");
    puts("5) Buscar por tempo");
    puts("8) Salir");
}

char **leer_linea_csv(FILE *archivo, char delimitador) 
{
    char **campos = NULL;// Empezamos con NULL para la lista de campos
    char linea[1024];//para la línea leída
    int index = 0;
    size_t capacidad = 10;//Una capacidad inicial para 10 campos
    campos = malloc(sizeof(char*) * capacidad);//Reserva memoria inicial

    //Leer una línea del archivo
    if (fgets(linea, sizeof(linea), archivo) == NULL) 
    {
        return NULL;//Si no hay más líneas, retornamos NULL
    }

    //Dividir la línea por el delimitador
    char *campo = strtok(linea, &delimitador);
    while (campo != NULL) {
        if (index >= capacidad) 
        {  //Si hemos alcanzado la capacidad, ampliamos el arreglo
            capacidad *= 2;//se dobla la capacidad
            campos = realloc(campos, sizeof(char*) * capacidad);//Redimensionamos el arreglo
        }

        campos[index] = malloc(strlen(campo) + 1);//Reservamos memoria para el campo
        strcpy(campos[index], campo);
        index++;

        //Leer el siguiente campo
        campo = strtok(NULL, &delimitador);
    }
    campos[index] = NULL;//Finaliza el arreglo con NULL
    return campos;
}

void cargar_canciones(Map *canciones_id, Map *canciones_genero)
{
    //Intentar abrir archivo CSV
    FILE *archivo = fopen("song_dataset_.csv", "r");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    char **campos;
    campos = leer_linea_csv(archivo, ',');
    while (campos = leer_linea_csv(archivo, ',' ))

}


int main()
{
    char opcion;
    Map *canciones_id = map_create(is_equal_str); //mapa de ID
    Map *canciones_genero = map_create(is_equal_str); //mapa de genero
    Map *canciones_artistas = map_create(is_equal_str); //mapa de artistas
    //crear un arreglo con tempos lentas, moderadas y rapidas, siendo solo 3.
    //crear una lista de canciones vacia, donde se deba guardar canciones a gusto de uno.

    do
    {
        mostrarMenu();
        printf("Ingrese la opción");
        scanf(" %c", &opcion);

        switch(opcion) 
        {
            case '1':
                system("cls");  // Limpia la pantalla
                cargar_canciones(canciones_id, canciones_genero);
                break;
            default:
                printf("Saliendo");
                break;
        }
    } while(opcion != 8);

    return 0;
}
