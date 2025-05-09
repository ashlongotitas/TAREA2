
#include "extra.h"
#include "list.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <windows.h>

// Definición de la estructura Song que contiene información sobre cada canción
typedef struct 
{
  char id[30];                // Identificador único de la canción
  char artist[100];           // Artista de la canción
  char album_name[50];        // Nombre del álbum
  char track_name[50];        // Nombre de la canción
  float tempo;                // Tempo de la canción (BPM)
  char track_genre[50];       // Género de la canción
} Song;

// Menú principal
void mostrarMenuPrincipal() 
{
  limpiarPantalla();
  puts("========================================");
  puts("     Spotifind    ");
  puts("========================================");

  puts("1) Cargar Canciones");
  puts("2) Buscar por Genero");
  puts("3) Buscar por Artista");
  puts("4) Buscar por Tempo");
  puts("5) Salir");
}


// Función de comparación para claves de tipo cadena de caracteres
int is_equal_str(void *key1, void *key2) 
{
  return strcmp((char *)key1, (char *)key2) == 0;   // Compara las claves (strings)
}

// Función que carga canciones desde un archivo CSV y las inserta en los mapas
void cargar_canciones(Map *songs_by_id, Map *songs_by_genre, Map *songs_by_artist)
{
  char archivo[100];
  printf("Ingrese la ruta del archivo CSV: ");
  scanf("%s", archivo);     // Solicita la ruta del archivo CSV

  FILE *file = fopen(archivo, "r");
  if (file == NULL)
  {
  perror("Error al abrir el archivo"); 
  return;
  }

  char **campos;
  campos = leer_linea_csv(file, ',');     // Lee la primera línea (encabezado)

  // Lee las líneas restantes del archivo CSV
  /* 1. Solicita ruta del archivo CSV
     2. Procesa línea por línea:
        - Crea estructura Song en memoria dinámica
        - Llena campos con datos del CSV
        - Inserta en 3 mapas diferentes: Por ID, por género y por artista.
     3. Cierra archivo al finalizar
  */
  while ((campos = leer_linea_csv(file, ',')) != NULL) 
  {
     // Reserva memoria para unqa nueva cancion
    Song *cancion = (Song *)malloc(sizeof(Song));
    strcpy(cancion->id, campos[0]);        
    strcpy(cancion->artist, campos[2]);     
    strcpy(cancion->album_name, campos[3]); 
    strcpy(cancion->track_name, campos[4]);
    cancion->tempo = atof(campos[18]);
    strcpy(cancion->track_genre, campos[20]);
    
    // Inserta la canción en el mapa por su ID
    map_insert(songs_by_id, cancion->id, cancion);

    // Busca si ya existe una lista para este género
    MapPair *genre_pair = map_search(songs_by_genre, cancion->track_genre);

    if (genre_pair == NULL) 
    {
      // Si no existe, crea una nueva lista y agrega la canción
      List *genre_list = list_create();
      list_pushBack(genre_list, cancion);
      map_insert(songs_by_genre, cancion->track_genre, genre_list);
    } 
    else 
    {
      // Si existe, agrega la canción a la lista existente
      List *genre_list = (List *)genre_pair->value;
      list_pushBack(genre_list, cancion);
    }

    // Proceso similar para el mapa por artista
    MapPair *artista_pair = map_search(songs_by_artist, cancion->artist);
    if(artista_pair == NULL)
    {
      List *lista_artista = list_create();
      list_pushBack(lista_artista, cancion);
      map_insert(songs_by_artist, cancion->artist, lista_artista);
    }
    else
    {
      List *lista_artista = (List*) artista_pair->value;
      list_pushBack(lista_artista, cancion);
    }
  }
  fclose(file);    // Cierra el archivo
  printf("Canciones cargadas correctamente.\n");
}

// Función para buscar canciones por género
void buscar_por_genero(Map *songs_by_genre)
{
  // Verifica si hay canciones cargadas
  if(map_isEmpty(songs_by_genre))
  {
    puts("No hay canciones cargadas.");
    return;
  }

  // Solicita al usuario el género a buscar
  char genero[100];
  printf("Ingrese el genero a buscar: ");
  scanf("%s", genero);

  // Busca el género en el mapa
  MapPair *pair = map_search(songs_by_genre, genero);

  // Si no se encuentra el género, muestra un mensaje
  if (pair == NULL)
  {
    puts("No se encontraron canciones de ese genero.");
    return; 
  }

  // Obtiene la lista de canciones del género encontrado
  List *canciones_genero = (List *)pair->value;
  printf("Canciones de genero '%s' \n", genero);

  // Recorre e imprime todas las canciones del género
  Song *cancion = list_first(canciones_genero);
  while (cancion != NULL)
  {
    printf("ID: %s, Cancion: %s, Artista(s): %s, Album: %s \n", cancion->id ,cancion->track_name, cancion->artist, cancion->album_name);
    cancion = list_next(canciones_genero);
  }
}

// Función para buscar canciones por artista
void buscar_por_artista(Map *songs_by_artist)
{
  // Verifica si hay canciones cargadas
  if(map_isEmpty(songs_by_artist))
  {
    puts("No hay canciones cargadas.");
    return;
  }

  // Solicita al usuario el artista a buscar
  char artista[100];
  printf("Ingrese el artista a buscar: ");
  scanf("%s", artista);

  // Busca el artista en el mapa
  MapPair *pair = map_search(songs_by_artist, artista);

  // Si no se encuentra el artista, muestra un mensaje
  if (pair == NULL)
  {
    puts("No se encontraron canciones de ese artista.");
    return;
  }

  // Obtiene la lista de canciones del artista encontrado
  List *canciones_artista = (List *)pair->value;
  printf("Canciones del artista '%s' \n", artista);

   // Recorre e imprime todas las canciones del artista
  Song *cancion = list_first(canciones_artista);
  while (cancion != NULL)
  {
    printf("ID: %s, Cancion: %s, Album: %s \n", cancion->id ,cancion->track_name, cancion->album_name);
    cancion = list_next(canciones_artista);
  }
}

// Función para buscar canciones por tempo (BPM)
void buscar_por_tempo(Map *songs_by_id)
{
  // Verifica si hay canciones cargadas
  if(map_isEmpty(songs_by_id))
  {
    puts("No hay canciones cargadas.");
    return;
  }
  
  // Muestra opciones de tempo
  printf("Seleccione el tempo a buscar\n");
  printf("1) Lentas (menos de 80 BPM)\n");
  printf("2) Moderadas (entre 80 y 120 BPM)\n");
  printf("3) Rapidas (mayor a 120 BPM)\n");

  int opcion;
  scanf("%d", &opcion);
  MapPair *pair;

  // Procesa según la opción seleccionada
  switch(opcion)
  {
    case 1:   // Canciones lentas (<80 BPM)
      printf("Canciones lentas encontradas: \n");

       // Obtenemos el primer par clave-valor del mapa
      pair = map_first(songs_by_id);

      // Bucle para recorrer todas las entradas del mapa
      while(pair != NULL)
      {
        Song *cancion = (Song *)pair->value;
        // Verificamos si el tempo está en el rango deseado
        if(cancion->tempo < 80)
        {
          printf("ID: %s, Cancion: %s, Artista(s): %s, Album: %s \n", cancion->id ,cancion->track_name, cancion->artist, cancion->album_name);
        }
        // Avanzamos al siguiente elemento del mapa
        pair = map_next(songs_by_id);
      }
      break;
    case 2:   // Canciones moderadas (80-120 BPM)
      printf("Canciones moderadas encontradas: \n");
      pair = map_first(songs_by_id);
      while(pair != NULL)
      {
        Song *cancion = (Song *)pair->value;
        if(cancion->tempo >= 80 && cancion->tempo <= 120)
        {
          printf("ID: %s, Cancion: %s, Artista(s): %s, Album: %s \n", cancion->id ,cancion->track_name, cancion->artist, cancion->album_name);
        }
        pair = map_next(songs_by_id);
      }
      break;
    case 3:  // Canciones rápidas (>120 BPM)
      printf("Canciones rapidas encontradas: \n");
      pair = map_first(songs_by_id);
      while(pair != NULL)
      {
        Song *cancion = (Song *)pair->value;
        if(cancion->tempo > 120)
        {
          printf("ID: %s, Cancion: %s, Artista(s): %s, Album: %s \n", cancion->id ,cancion->track_name, cancion->artist, cancion->album_name);
        }
        pair = map_next(songs_by_id);
      }
      break;
    default:    // Caso para opciones no válidas
      puts("Opcion no valida.");
      return;
  }
}


// Función principal
int main() {
  SetConsoleOutputCP(CP_UTF8); 
  setlocale(LC_ALL, "en_US.UTF-8");
  char opcion;     
  Map *songs_by_id = map_create(is_equal_str);
  Map *songs_by_artist = map_create(is_equal_str);
  Map *songs_by_genre = map_create(is_equal_str);

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opcion: ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
      cargar_canciones(songs_by_id, songs_by_genre, songs_by_artist);
      break;
    case '2':
      buscar_por_genero(songs_by_genre);
      break;
    case '3':
      buscar_por_artista(songs_by_artist);
      break;
    case '4':
      buscar_por_tempo(songs_by_id);
      break;
    case '5':
      puts("Saliendo de Spotifind...");
      break;
    default:
      puts("Opcion no valida.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '5');

  return 0;
}

/* CODIGOS DEL PROGRAMA:
Para compilar: gcc spotifind.c extra.c list.c map.c -o spotifind -Wall 
Para ejecutar: ./spotifind  
Ruta del archivo CSV: data/song_dataset_.csv */

