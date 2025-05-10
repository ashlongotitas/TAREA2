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

Funcionando Correctamente:
- Cargar canciones: Importa canciones desde un archivo CSV.
- Buscar por género: Filtra canciones por género (ej. "pop", "rock").
- Buscar por artista: Muestra todas las canciones de un artista específico.
- Buscar por tempo: Clasifica canciones en lentas (<80 BPM), moderadas (80-120 BPM) o rápidas (>120 BPM).
- Salir: Cierra la aplicación.

