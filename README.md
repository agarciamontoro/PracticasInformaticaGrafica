Prácticas de Informática Gráfica
=============================

Proyecto cuatrimestral para la asignatura de Informática Gráfica, cuyo objetivo principal
es el aprendizaje de OpenGL.

## Estructura

El proyecto se estructura en prácticas sucesivas, cada una de las cuales se apoya en la anterior.
Hasta ahora, este repositorio contiene:

* **Práctica 1 - Visualización de modelos PLY**: Visualización de modelos almacenados en archivos PLY.
* **Práctica 2 - Modelos poligonales**: Creación de modelos mediante revolución de perfiles.
* **Práctica 3 - Modelos jerárquicos**: Creación de modelos jerárquicos con algunos grados de libertad.

## Instalación y uso

Para la compilación del proyecto es necesaria las librerías freeglut y libjpeg (en su versión de desarrollo), que se encuentran disponibles en la mayoría de las distribuciones Linux usuales. La compilación y ejecución por defecto se realiza con la siguiente órden:

    make

Una vez compilado, se ejecuta con la siguiente órden:

    ./bin/prac <ruta_archivo_PLY> <ruta_perfil_PLY> <num_caras>

Donde *\<ruta_archivo_PLY\>* es la ruta al archivo PLY que cargará la práctica 1 y *\<ruta_perfil_PLY\>* es la ruta al archivo PLY que cargará la práctica 2 para generar el sólido por revolución, con un número de caras igual a *\<num_caras\>*. Si no se especifica ningún parámetro, se cargarán el proyecto por defecto.

### Teclas disponibles

* Tecla F1: Muestra la primera práctica.
* Tecla F2: Muestra la segunda práctica.
* Tecla F3: Muestra la tercera práctica.
* Tecla A: El modelo se visualiza en modo ALAMBRE. (Este es el modo por defecto).
* Tecla S: El modelo se visualiza en modo SÓLIDO.
* Tecla Z: El modelo se visualiza en modo AJEDREZ.
* Tecla P: El modelo se visualiza en modo PUNTO.
* Tecla F: Conmuta la visualización de las normales de caras.
* Tecla V: Conmuta la visualización de las normales de vértices.
* Tecla Q: Finaliza el programa

Además, en el modo Práctica 3, se pueden usar las siguientes teclas para manipular el modelo:

* Teclas Z/z: Control del primer grado de libertad.
* Teclas X/x: Control del segundo grado de libertad.
* Teclas C/c: Control del tercer grado de libertad.
* Teclas B/b: Control automático del cuarto grado de libertad. La tecla B aumenta la velocidad
del movimiento rotatorio de todo el modelo alrededor del origen de coordenadas. La tecla b lo disminuye.

## Capturas de pantalla

Práctica 1 - Modelo PLY de Beethoven en modo AJEDREZ:

![Beethoven](https://cloud.githubusercontent.com/assets/3924815/5709707/60023f28-9a9c-11e4-866d-be10715fa5d6.png)

Práctica 1 - Modelo PLY de un coche en modo AJEDREZ:

![Coche](https://cloud.githubusercontent.com/assets/3924815/5709708/6006d61e-9a9c-11e4-8630-ec637b8f5689.png)

Práctica 3 - Modelo jerárquico de un dalek creado desde cero.

![Dalek](https://cloud.githubusercontent.com/assets/3924815/5709861/871ca930-9a9d-11e4-8c0f-6813928e04c7.png)
[EXTERMINATE, EXTERMINAAAAAAAAAAAAAAAAAATE!](http://en.wikipedia.org/wiki/Dalek)

Práctica 2 - Sólidos generados por revolución y coloreados según las normales de los vértices.

![Origen](https://cloud.githubusercontent.com/assets/3924815/5709710/604d2998-9a9c-11e4-807d-593ed9681b98.png)

![Peón](https://cloud.githubusercontent.com/assets/3924815/5709711/60508926-9a9c-11e4-87b2-bc552060f34b.png)


=============================
Doble Grado de Ingeniería Informática y Matemáticas. Universidad de Granada.
