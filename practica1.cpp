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
std::vector<float> vertices;
std::vector<struct Tupla3f> vertices_t;
std::vector<int> caras;
std::vector<struct Tupla3i> caras_t;
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

void DibujarMallaTVT(/*std::vector<float> & vertices, std::vector<int> & caras*/)
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
   glVertexPointer( 3, GL_FLOAT, 0, vertices_t[0].coo );
   // dibujar usando vértices indexados
   // params.: (1) tipo de primitivas (2) número de índices
   // (3) tipo de índices (4) puntero a tabla de triáng.
   glDrawElements( GL_TRIANGLES, caras.size(), GL_UNSIGNED_INT, caras_t[0].idx );
}

// ---------------------------------------------------------------------
// Función para implementar en la práctica 1 para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e 
// incializado OpenGL. El PLY se debe cargar aquí.

void P1_Inicializar( int argc, char *argv[] )
{
   ply::read(argv[1], vertices, caras);

   for (unsigned int i = 0; i < vertices.size(); i += 3)
   {
      vertices_t.push_back(Tupla3f(vertices[i+0], vertices[i+1], vertices[i+2]));
   }


   for (unsigned int i = 0; i < caras.size()-15; i += 3)
   {
      caras_t.push_back(Tupla3i(caras[i+0], caras[i+1], caras[i+2]));
   }

   struct Tupla3i aux;
   std::vector<struct Tupla3i>::iterator izqda, dcha;

   izqda = caras_t.begin();
   dcha = caras_t.size()%2 == 0 ? caras_t.end() : caras_t.end()-1;

   for (; izqda < dcha; izqda += 2, dcha -= 2)
   {
      aux = *izqda;
      *izqda = *dcha;
      *dcha = aux;
   }

}

// ---------------------------------------------------------------------
// Función a implementar en la práctica 1  para dibujar los objetos

void P1_DibujarObjetos() 
{
   //DibujarCuboPuntos() ;
   DibujarMallaTVT(/*vertices,caras*/);
}
