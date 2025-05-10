# SPOTIFIND - Gestor de Canciones

Spotifind es una herramienta que permite a los usuarios cargar una base de datos de canciones desde un archivo CSV. Los usuarios podrán buscar canciones rápida y eficientemente ya sea por género, artista y tempo (BPM).

Cómo compilar y ejecuta

Este sistema ha sido desarrollado en lenguaje de C, recomiendo descargar Visual Studio Code para usar el sistema fácilmente (link VSC https://code.visualstudio.com). Una vez dentro de Visual necesitarás instalar una extensión de C/C++ como C/C++ Extension Pack de Microsoft.

Requisitos previos: Además de tener instalado VSC con su extensión, en necesario tener instalado un compilador gcc, recomiendo descargar MinGW (link para Windows: https://sourceforge.net/projects/mingw/)

Pasos para compilar: comienza descargando y descomprimiendo el archivo (.zip). Luego ábrelo dentro de Visual Studio Code. Una vez abierto el archivo necesitarás compilarlo antes de ejecutarlo, para esto:
1) Abre el archivo principal (en este caso spotifind.c)
2) Selecciona "Terminal" ubicada en la esquina superior izquierda y luego "Nueva Terminal".
3) Una vez dentro de la terminal seleccione la flecha que esta al lado del "+" y apretar git bash.
4) Debes ingresar el siguiente comando: gcc spotifind.c extra.c list.c map.c -o spotifind -Wall y despúes ./spotifind
5) La ruta del archivo de canciones es: data/song_dataset_.csv

¡Y ya estás listo(a) para utilizar Spotifind!

Funcionalidad

Funcionando Correctamente

- Cargar canciones: Importa canciones desde un archivo CSV.
- Buscar por género: Filtra canciones por género (ej. "pop", "rock").
- Buscar por artista: Muestra todas las canciones de un artista específico.
- Buscar por tempo: Clasifica canciones en lentas (<80 BPM), moderadas (80-120 BPM) o rápidas (>120 BPM).
- Salir: Cierra la aplicación.

Problemas Conocidos

- El archivo de canciones contiene demasiadas (+100k) por lo que Spotifind al cargar las canciones se demoras unos 6-7 segundos, así que no se asuste si no carga inmediatamente!
- Algunas canciones que estan el jápones o chino salen mal imprimidas, este problema fue corregido en este programa.

Funciones A Mejorar

- Añadir búsqueda por nombre de canción.
- Permitir a los usuarios crear una lista de reproducción personalizada, para que puedan agregar sus canciones favoritas a la lista.

Ejemplo de uso: SPOTIFIND
![image](https://github.com/user-attachments/assets/0688c84a-8de1-4bf6-9b09-3ff5d53b3bbf)


Paso 1: Cargar canciones

Se comienza ingresando la ruta de la base de canciones(archivo VSC). El programa cargarå todas las canciones.

Paso 2: Buscar por Género

El usuario ingresara el género de su preferencia y el programa mostrará todas las canciones que entren en esa categoria, justo con su ID, nombre de la canción, nombre de el(los) artista(s) y el nombre del álbum.

Paso 3: Buscar por Artista

Ádemas de poder buscarlas por género, el usuario podrá buscar canciones según su artista, facilitandole encontrar canciones de artistas especificos. Mostrando los detalles de cada canción.

Paso 4: Buscar por Tempo

Similar a las dos opciones anteriores, pero en este caso el usuario podrá buscar las canciones según su tempo, se separan en tres categorías: Rápidas, Moderadas y Lentas. Spotifind le dará las tres opciones y el usuario debe elegir la que este buscando (1, 2 o 3), despúes de haber escogido el programa mostrará aquellas canciones que entren dentro del rango del tempo elegido, junto con sus detalles.

Paso 5: Salir

Cuando ya no quiera seguir utilizando el programa, podrá salir rapidamente de el usando la opcion 5. 

