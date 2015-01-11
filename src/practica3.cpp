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
static Malla_TVT *cubo, *esfera;

static Matriz_Traslacion *mat_tras_esfera[4];
static Matriz_Escalado *mat_esc_tabla;

static Celda_Nodo *tabla, *esferas_tabla[4], *escena;

// ---------------------------------------------------------------------
//  Cambia el modo de visualización del modelo PLY

void P3_CambiarVisualizacion(enum modo_visualizacion modo){
   cubo->set_visualizacion(modo);
   esfera->set_visualizacion(modo);
}

// ---------------------------------------------------------------------
// Función para implementar en la práctica 2 para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e
// incializado OpenGL. El PLY se debe cargar aquí.

void P3_Inicializar( int argc, char *argv[] )
{
   char archivo_cubo[] = "./PLY/cube.ply";
   char archivo_esfera[] = "./PLY/sphere.ply";
   int num_caras = 100;

   //////////////////////////////////////////////////////////////////
   ///////////////////////                  /////////////////////////
   ///////////////////////    NODO TABLA    /////////////////////////
   ///////////////////////                  /////////////////////////
   //////////////////////////////////////////////////////////////////

   ///////////////////////      MALLAS      /////////////////////////

   // MALLA CUBO
   cubo = new Malla_TVT(archivo_cubo);
   cubo->set_visualizacion(AJEDREZ);

   Celda_Malla* malla_cubo = new Celda_Malla(cubo);

   // MALLA ESFERA
   Malla_TVT esfera_aux(archivo_esfera, VERT);
   esfera = new Malla_TVT(esfera_aux.GenerarSolidoRevolucion(num_caras));
   esfera->set_visualizacion(AJEDREZ);

   Celda_Malla* malla_esfera = new Celda_Malla(esfera);

   /////////////////////// NODOS AUXILIARES /////////////////////////

   // 4 NODOS ESFERA
   Celda_Transformacion* trans_esfera[4];

   for(int i = 0; i < 4; i++){
       mat_tras_esfera[i] = new Matriz_Traslacion(0.0, i-1.5, 0.0);
       trans_esfera[i] = new Celda_Transformacion( mat_tras_esfera[i] );

       esferas_tabla[i] = new Celda_Nodo();
       esferas_tabla[i]->push_back( trans_esfera[i] );
       esferas_tabla[i]->push_back( malla_esfera );
   }

   // NODO TABLA
   //Transformación tabla
   mat_esc_tabla = new Matriz_Escalado(0.1, 4.0, 0.8);
   Celda_Transformacion* tra_tabla = new Celda_Transformacion(mat_esc_tabla);

   //Inicializacion del nodo tabla con las celdas
   tabla = new Celda_Nodo();
   for(int i = 0; i < 4; i++){
       tabla->push_back( esferas_tabla[i] );
   }
   tabla->push_back( tra_tabla );
   tabla->push_back( malla_cubo );


   //////////////////////////////////////////////////////////////////
   ///////////////////////                  /////////////////////////
   ///////////////////////    NODO  RAÍZ    /////////////////////////
   ///////////////////////                  /////////////////////////
   //////////////////////////////////////////////////////////////////

   //Inicialización del nodo escena con todas las celdas nodo
   escena = new Celda_Nodo();
   escena->push_back( tabla );

}

// ---------------------------------------------------------------------
// Función a implementar en la práctica 2  para dibujar los objetos

void P3_DibujarObjetos()
{
   cubo->set_color_principal(Tupla3f(0.5, 0.0, 0.0));
   cubo->set_color_secundario(Tupla3f(0.0, 0.0, 0.3));

   esfera->set_color_principal(Tupla3f(0.5, 0.0, 0.0));
   esfera->set_color_secundario(Tupla3f(0.0, 0.0, 0.3));

   escena->visualizar();
}

void P3_Conmutar_NormalesCaras(){
   cubo->Conmutar_NormalesCaras();
   esfera->Conmutar_NormalesCaras();
}

void P3_Conmutar_NormalesVertices(){
   cubo->Conmutar_NormalesVertices();
   esfera->Conmutar_NormalesVertices();
}

bool P3_FGE_TeclaNormal( unsigned char tecla, int x_raton, int y_raton ){
    return false;
}

bool P3_FGE_TeclaEspecial( int tecla, int x_raton, int y_raton ){
    return false;
}
