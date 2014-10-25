// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// ** Práctica 1  (implementación)
// **
// *********************************************************************

// ---------------------------------------------------------------------
// coordenadas de los vértices del cubo:

#include "practica1.hpp"
#include <stdio.h>

const unsigned num_verts_cubo = 8 ;

// Objeto de la clase Malla_TVT que contendrá las primitivas
Malla_TVT malla;

GLfloat coords_verts_cubo[num_verts_cubo][3] = 
   {  { -0.5, -0.5, +0.5 } ,
      { +0.5, -0.5, +0.5 } ,
      { +0.5, +0.5, +0.5 } ,
      { -0.5, +0.5, +0.5 } ,
      { -0.5, -0.5, -0.5 } ,
      { +0.5, -0.5, -0.5 } ,
      { +0.5, +0.5, -0.5 } ,
      { -0.5, +0.5, -0.5 }
   };
   
// ---------------------------------------------------------------------
//  dibujar vértices del cubo en modo inmediato con begin/end

void DibujarCuboPuntos()
{
   glColor3f( 0.10, 0.15, 0.40 );
   glPointSize(4);

   glBegin(GL_POINTS);
   for ( unsigned i= 0 ; i < num_verts_cubo ; i++ )
      glVertex3fv( &( coords_verts_cubo[i][0] ) );
   glEnd();
}


// ---------------------------------------------------------------------
//  Cambia el modo de visualización del modelo PLY

void CambiarVisualizacion(enum modo_visualizacion modo){
   malla.set_visualizacion(modo);
}

// ---------------------------------------------------------------------
// Función para implementar en la práctica 1 para inicialización.
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
// Función a implementar en la práctica 1  para dibujar los objetos

void P1_DibujarObjetos() 
{
   malla.set_color_principal(Tupla3f(0.5, 0.0, 0.0));
   malla.set_color_secundario(Tupla3f(0.0, 0.0, 0.3));

   malla.DibujarMallaTVT();
}