// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// ** Práctica 1  (implementación)
// **
// *********************************************************************


#include <GL/glut.h>
#include <vector>

#include "error-ogl.hpp"
#include "tuplas.hpp"   // Tupla3f, Tupla4f, Tupla3i
#include "practica1.hpp"
#include "file_ply_stl.hpp"

// ---------------------------------------------------------------------
// coordenadas de los vértices del cubo:

const unsigned num_verts_cubo = 8 ;
std::vector<float> vertices;
std::vector<int> caras;
enum modo_visualizacion modo_actual = ALAMBRE;

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
   modo_actual = modo;
}

// ---------------------------------------------------------------------
//  dibujar caras de malla TVT

void DibujarMallaTVT(std::vector<float> & vertices, std::vector<int> & caras)
{
   glColor3f( 0.20, 0.15, 0.40 );
   glPointSize(4);

   // habilitar ’vertex arrays’
   glEnableClientState( GL_VERTEX_ARRAY );
   // habilitar 'color array'
   glEnableClientState( GL_COLOR_ARRAY );

   switch(modo_actual){
      case AJEDREZ:
      case SOLIDO:
         glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
         break;

      default:
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         break;
   }


   // especificar puntero a tabla de coords. de vértices
   glVertexPointer( 3, GL_FLOAT, 0, &(vertices[0]) );
   // dibujar usando vértices indexados
   // params.: (1) tipo de primitivas (2) número de índices
   // (3) tipo de índices (4) puntero a tabla de triáng.
   glDrawElements( GL_TRIANGLES, caras.size(), GL_UNSIGNED_INT, &(caras[0]) );
}

// ---------------------------------------------------------------------
// Función para implementar en la práctica 1 para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e 
// incializado OpenGL. El PLY se debe cargar aquí.

void P1_Inicializar( int argc, char *argv[] )
{
   ply::read(argv[1], vertices, caras);
}

// ---------------------------------------------------------------------
// Función a implementar en la práctica 1  para dibujar los objetos

void P1_DibujarObjetos() 
{
   //DibujarCuboPuntos() ;
   DibujarMallaTVT(vertices,caras);
}
