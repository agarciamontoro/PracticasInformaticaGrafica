// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// **
// ** Práctica 3  (implementación)
// **
// *********************************************************************

#include "practica3.hpp"
#include "grafo_escena.hpp"

#include <stdio.h>

// Objeto global de la clase Malla_TVT que contendrá las primitivas
static Malla_TVT* malla;

static Matriz_Traslacion* mat_tra;
static Celda_Nodo* peon, *escena;

// ---------------------------------------------------------------------
//  Cambia el modo de visualización del modelo PLY

void P3_CambiarVisualizacion(enum modo_visualizacion modo){
   malla->set_visualizacion(modo);
}

// ---------------------------------------------------------------------
// Función para implementar en la práctica 2 para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e
// incializado OpenGL. El PLY se debe cargar aquí.

void P3_Inicializar( int argc, char *argv[] )
{
   char ruta_archivo[] = "./PLY/perfil_peon.ply";
   int num_caras = 100;

   //Malla de peón por revolución.
   Malla_TVT peon_aux(ruta_archivo, VERT);
   malla = new Malla_TVT(peon_aux.GenerarSolidoRevolucion(num_caras));
   malla->set_visualizacion(AJEDREZ);

   //Matriz de traslación.
   mat_tra = new Matriz_Traslacion(1.5,1.5,1.5);

   //Creación de las celdas con objetos/transformaciones
   Celda_Malla* malla_peon = new Celda_Malla(malla);
   Celda_Transformacion* tra_peon = new Celda_Transformacion(mat_tra);

   //Inicialización del nodo con las celdas
   peon = new Celda_Nodo();
   peon->push_back( tra_peon );
   peon->push_back( malla_peon );

   //Creación de la celda nodo
   //Celda_Nodo* nodo_peon = new Celda_Nodo( &peon );

   //Inicialización del nodo escena con todas las celdas nodo
   escena = new Celda_Nodo();
   escena->push_back( peon );

}

// ---------------------------------------------------------------------
// Función a implementar en la práctica 2  para dibujar los objetos

void P3_DibujarObjetos()
{
   malla->set_color_principal(Tupla3f(0.5, 0.0, 0.0));
   malla->set_color_secundario(Tupla3f(0.0, 0.0, 0.3));

   //malla->DibujarMalla_TVT();
   escena->visualizar();
}

void P3_Conmutar_NormalesCaras(){
   malla->Conmutar_NormalesCaras();
}

void P3_Conmutar_NormalesVertices(){
   malla->Conmutar_NormalesVertices();
}

bool P3_FGE_TeclaNormal( unsigned char tecla, int x_raton, int y_raton ){
    return false;
}

bool P3_FGE_TeclaEspecial( int tecla, int x_raton, int y_raton ){
    return false;
}
