// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// **
// ** Práctica 3  (implementación)
// **
// *********************************************************************

#include "practica3.hpp"

#include <stdio.h>

// Objeto global de la clase Malla_TVT que contendrá las primitivas
static Malla_TVT malla;

// ---------------------------------------------------------------------
//  Cambia el modo de visualización del modelo PLY

void P3_CambiarVisualizacion(enum modo_visualizacion modo){
   malla.set_visualizacion(modo);
}

// ---------------------------------------------------------------------
// Función para implementar en la práctica 2 para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e
// incializado OpenGL. El PLY se debe cargar aquí.

void P3_Inicializar( int argc, char *argv[] )
{
   char ruta_archivo[256];
   int num_caras;

   // si no se ha proporcionado un archivo PLY se carga el archivo perfil_inception.ply por defecto
   if(argc < 2)
      sprintf(ruta_archivo, "./PLY/perfil_peon.ply");
   else
      sprintf(ruta_archivo, "%s", argv[2]);

   // si no se ha proporcionado un numero de caras, se asignan 100 por defecto
   if(argc < 3)
      num_caras = 100;
   else
      num_caras = atoi(argv[3]);

   malla = Malla_TVT(ruta_archivo, VERT);
   malla = malla.GenerarSolidoRevolucion(num_caras);
}

// ---------------------------------------------------------------------
// Función a implementar en la práctica 2  para dibujar los objetos

void P3_DibujarObjetos()
{
   malla.set_color_principal(Tupla3f(0.5, 0.0, 0.0));
   malla.set_color_secundario(Tupla3f(0.0, 0.0, 0.3));

   malla.DibujarMalla_TVT();
}

void P3_Conmutar_NormalesCaras(){
   malla.Conmutar_NormalesCaras();
}

void P3_Conmutar_NormalesVertices(){
   malla.Conmutar_NormalesVertices();
}

bool P3_FGE_TeclaNormal( unsigned char tecla, int x_raton, int y_raton ){
    return false;
}

bool P3_FGE_TeclaEspecial( int tecla, int x_raton, int y_raton ){
    return false;
}