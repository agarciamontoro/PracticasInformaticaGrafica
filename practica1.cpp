// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// ** Práctica 1  (implementación)
// **
// *********************************************************************

#include <stdio.h>
#include <GL/glut.h>
#include <vector>

#include "error-ogl.hpp"
#include "tuplas.hpp"   // Tupla3f, Tupla4f, Tupla3i
#include "practica1.hpp"
#include "file_ply_stl.hpp"

// ---------------------------------------------------------------------
// coordenadas de los vértices del cubo:

const unsigned num_verts_cubo = 8 ;
std::vector<struct Tupla3f> vertices;
std::vector<struct Tupla3i> caras_pares, caras_impares;
enum modo_visualizacion visualizacion_actual = ALAMBRE;
GLenum render_actual = GL_LINE;

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

void CambiarVisualizacion(enum modo_visualizacion modo){
   visualizacion_actual = modo;
   render_actual        = modo == ALAMBRE ? GL_LINE : GL_FILL;
}

// ---------------------------------------------------------------------
//  dibujar caras de malla TVT

void DibujarMallaTVT(/*std::vector<float> & vertices, std::vector<int> & caras*/)
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

void P1_Inicializar( int argc, char *argv[] )
{
   std::vector<float> vertices_raw;
   std::vector<int> caras_raw;

   ply::read(argv[1], vertices_raw, caras_raw);

   for (unsigned int i = 0; i < vertices_raw.size(); i += 3)
   {
      vertices.push_back(Tupla3f(vertices_raw[i+0], vertices_raw[i+1], vertices_raw[i+2]));
   }


   for (unsigned int i = 0; i < caras_raw.size(); i += 6)
   {
      caras_pares.push_back(Tupla3i(caras_raw[i+0], caras_raw[i+1], caras_raw[i+2]));
      caras_impares.push_back(Tupla3i(caras_raw[i+3], caras_raw[i+4], caras_raw[i+5]));
   }
}

// ---------------------------------------------------------------------
// Función a implementar en la práctica 1  para dibujar los objetos

void P1_DibujarObjetos() 
{
   //DibujarCuboPuntos() ;
   DibujarMallaTVT(/*vertices,caras*/);
}
