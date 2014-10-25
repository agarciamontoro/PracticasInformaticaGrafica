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
/*
// Variables para la Malla TVT
std::vector<struct Tupla3f> vertices;
std::vector<struct Tupla3i> caras_pares, caras_impares;

// Variables para gestionar el modo de visualización
enum modo_visualizacion visualizacion_actual = ALAMBRE;
GLenum render_actual = GL_LINE;
*/

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

/*
// ---------------------------------------------------------------------
//  dibujar caras de malla TVT

void DibujarMallaTVT()
{
   glColor3f( 0.20, 0.15, 0.40 );
   glPointSize(4);

   // habilitar ’vertex arrays’
   glEnableClientState( GL_VERTEX_ARRAY );

   // especificar puntero a tabla de coords. de vértices
   glVertexPointer( 3, GL_FLOAT, 0, vertices[0].coo );

   // especificar modo de visualizacion
   glPolygonMode(GL_FRONT_AND_BACK,render_actual);

   // renderizar las primitivas, separando la visualización de las pares e impares
   glDrawElements( GL_TRIANGLES, 3*caras_pares.size(), GL_UNSIGNED_INT, caras_pares[0].idx );
   
   // cambiar el color de las caras si el modo de visualización es ajedrez
   if(visualizacion_actual == AJEDREZ)
      glColor3f( 0.80, 0.55, 0.60 );

   glDrawElements( GL_TRIANGLES, 3*caras_impares.size(), GL_UNSIGNED_INT, caras_impares[0].idx );

   glDisableClientState( GL_VERTEX_ARRAY );
}

// ---------------------------------------------------------------------
// Función para implementar en la práctica 1 para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e 
// incializado OpenGL. El PLY se debe cargar aquí.
*/
void P1_Inicializar( int argc, char *argv[] )
{
   /*
   // Variables locales para la lectura del archivo PLY
   std::vector<float> vertices_raw;
   std::vector<int> caras_raw;
   char ruta_archivo[256];

   // si no se ha proporcionado un archivo PLY se carga el archivo beethoven.ply por defecto
   if(argc < 2)
      sprintf(ruta_archivo, "./PLY/beethoven.ply");
   else
      sprintf(ruta_archivo, "%s", argv[1]);

   // lectura del archivo PLY
   ply::read(ruta_archivo, vertices_raw, caras_raw);

   // Para su mejor gestión, organizamos vértices y caras en vectores de Tuplas
   for (unsigned int i = 0; i < vertices_raw.size(); i += 3)
   {
      vertices.push_back(Tupla3f(vertices_raw[i+0], vertices_raw[i+1], vertices_raw[i+2]));
   }

   // Separamos las cares pares e impares para gestionar de forma eficiente el modo ajedrez
   for (unsigned int i = 0; i < caras_raw.size(); i += 6)
   {
      caras_pares.push_back(Tupla3i(caras_raw[i+0], caras_raw[i+1], caras_raw[i+2]));
      caras_impares.push_back(Tupla3i(caras_raw[i+3], caras_raw[i+4], caras_raw[i+5]));
   }*/
   if(argc >= 2)
      malla = Malla_TVT(argv[1], Tupla3f(0.20, 0.15, 0.40), Tupla3f(1.0, 0.0, 0.0));
   else
      malla = Malla_TVT("PLY/beethoven.ply", Tupla3f(0.20, 0.15, 0.40), Tupla3f(1.0, 0.0, 0.0));

   std::cout << "holi" << std::endl;
}

// ---------------------------------------------------------------------
// Función a implementar en la práctica 1  para dibujar los objetos

void P1_DibujarObjetos() 
{
   malla.DibujarMallaTVT();
}