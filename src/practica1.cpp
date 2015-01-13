// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// **
// ** Práctica 1  (implementación)
// **
// *********************************************************************

#include "practica1.hpp"

#include <stdio.h>

// Objeto global de la clase Malla_TVT que contendrá las primitivas
static Malla_TVT malla;

// ---------------------------------------------------------------------
//  Cambia el modo de visualización del modelo PLY

void P1_CambiarVisualizacion(enum modo_visualizacion modo){
   malla.set_visualizacion(modo);
}

// ---------------------------------------------------------------------
// Función para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e
// incializado OpenGL. El PLY se debe cargar aquí.

void P1_Inicializar( int argc, char *argv[] )
{
   char ruta_archivo[256];

   // si no se ha proporcionado un archivo PLY se carga el archivo beethoven.ply por defecto
   if(argc < 2)
      sprintf(ruta_archivo, "./PLY/beethoven.ply");
   else
      sprintf(ruta_archivo, "%s", argv[1]);

   malla = Malla_TVT(ruta_archivo);
}

// ---------------------------------------------------------------------
// Función para dibujar los objetos

void P1_DibujarObjetos()
{
   malla.set_color_principal(Tupla3f(0.5, 0.0, 0.0));
   malla.set_color_secundario(Tupla3f(0.0, 0.0, 0.3));

   malla.DibujarMalla_TVT();
}

void P1_Conmutar_NormalesCaras(){
      malla.Conmutar_NormalesCaras();
}

void P1_Conmutar_NormalesVertices(){
      malla.Conmutar_NormalesVertices();
}
