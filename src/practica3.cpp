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

static Malla_TVT *cubo, *esfera, *cilindro;

static Matriz_Traslacion    *mat_tras_esfera[4],
                            *mat_tras_tabla[8],
                            *mat_tras_cuello,
                            *mat_tras_cabeza_base,
                            *mat_tras_cabeza;

static Matriz_Rotacion      *mat_rot_tabla[8];

static Matriz_Escalado      *mat_esc_tabla,
                            *mat_esc_cuello,
                            *mat_esc_cabeza_base,
                            *mat_esc_cabeza;

static Celda_Nodo           *esferas_tabla[4], *tabla,
                            *tablas_falda[8], *falda,
                            *cabeza_base, *cabeza,
                            *cuello,
                            *escena;

// ---------------------------------------------------------------------
//  Cambia el modo de visualización del modelo PLY

void P3_CambiarVisualizacion(enum modo_visualizacion modo){
   cubo->set_visualizacion(modo);
   esfera->set_visualizacion(modo);
   cilindro->set_visualizacion(modo);
}

// ---------------------------------------------------------------------
// Función para implementar en la práctica 2 para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e
// incializado OpenGL. El PLY se debe cargar aquí.

void P3_Inicializar( int argc, char *argv[] )
{
   char archivo_cubo[] = "./PLY/cube.ply";
   char archivo_esfera[] = "./PLY/sphere.ply";
   char archivo_cilindro[] = "./PLY/cilinder.ply";
   int num_caras = 100;

   //////////////////////////////////////////////////////////////////
   ///////////////////////                   ////////////////////////
   /////////////////////// DEFINICIÓN MALLAS ////////////////////////
   ///////////////////////                   ////////////////////////
   //////////////////////////////////////////////////////////////////

   // MALLA CUBO
   cubo = new Malla_TVT(archivo_cubo);
   cubo->set_visualizacion(AJEDREZ);

   Celda_Malla* malla_cubo = new Celda_Malla(cubo);

   // MALLA ESFERA
   Malla_TVT esfera_aux(archivo_esfera, VERT);
   esfera = new Malla_TVT(esfera_aux.GenerarSolidoRevolucion(num_caras));
   esfera->set_visualizacion(AJEDREZ);

   Celda_Malla* malla_esfera = new Celda_Malla(esfera);

   // MALLA CILINDRO
   Malla_TVT cilindro_aux(archivo_cilindro, VERT);
   cilindro = new Malla_TVT(cilindro_aux.GenerarSolidoRevolucion(num_caras));
   cilindro->set_visualizacion(AJEDREZ);

   Celda_Malla* malla_cilindro = new Celda_Malla(cilindro);

   //////////////////////////////////////////////////////////////////
   ///////////////////////                  /////////////////////////
   ///////////////////////    NODO TABLA    /////////////////////////
   ///////////////////////                  /////////////////////////
   //////////////////////////////////////////////////////////////////

   const double ALTURA_FALDA = 3.5;

   /////////////////////// NODOS AUXILIARES /////////////////////////

   // 4 NODOS ESFERA
   Celda_Transformacion* trans_esfera[4];

   for(int i = 0; i < 4; i++){
       mat_tras_esfera[i] = new Matriz_Traslacion(0.0, (i*ALTURA_FALDA/4.0)-(3*ALTURA_FALDA/8), 0.0);
       trans_esfera[i] = new Celda_Transformacion( mat_tras_esfera[i] );

       esferas_tabla[i] = new Celda_Nodo();
       esferas_tabla[i]->push_back( trans_esfera[i] );
       esferas_tabla[i]->push_back( malla_esfera );
   }

   // NODO TABLA
   //Transformación tabla
   mat_esc_tabla = new Matriz_Escalado(0.1, ALTURA_FALDA, 1.0);
   Celda_Transformacion* trans_tabla = new Celda_Transformacion(mat_esc_tabla);

   //Inicializacion del nodo tabla con las celdas
   tabla = new Celda_Nodo();
   for(int i = 0; i < 4; i++){
       tabla->push_back( esferas_tabla[i] );
   }
   tabla->push_back( trans_tabla );
   tabla->push_back( malla_cubo );

   //////////////////////////////////////////////////////////////////
   ///////////////////////                  /////////////////////////
   ///////////////////////    NODO FALDA    /////////////////////////
   ///////////////////////                  /////////////////////////
   //////////////////////////////////////////////////////////////////

   // NODO FALDA

   falda = new Celda_Nodo();

   // 8 NODOS TABLA
   Celda_Transformacion* tras_tabla_falda[8];
   Celda_Transformacion* rot_tabla_falda[8];

   for(int i = 0; i < 8; i++){
       mat_tras_tabla[i] = new Matriz_Traslacion(1.255*sin(i*M_PI/4), 0.0, 1.255*cos(i*M_PI/4));
       tras_tabla_falda[i] = new Celda_Transformacion( mat_tras_tabla[i] );

       mat_rot_tabla[i] = new Matriz_Rotacion(i*M_PI/4+M_PI/2, Y);
       rot_tabla_falda[i] = new Celda_Transformacion( mat_rot_tabla[i] );

       tablas_falda[i] = new Celda_Nodo();
       tablas_falda[i]->push_back( tras_tabla_falda[i] );
       tablas_falda[i]->push_back( rot_tabla_falda[i] );
       tablas_falda[i]->push_back( tabla );

       falda->push_back( tablas_falda[i] );
   }


   //////////////////////////////////////////////////////////////////
   ///////////////////////                  /////////////////////////
   ///////////////////////   NODO  CUELLO   /////////////////////////
   ///////////////////////                  /////////////////////////
   //////////////////////////////////////////////////////////////////

   const double ALTURA_CUELLO = ALTURA_FALDA-1.3;

   //Transformación cuello
   mat_tras_cuello = new Matriz_Traslacion(0.0, ALTURA_CUELLO, 0.0);
   Celda_Transformacion* tras_cuello = new Celda_Transformacion(mat_tras_cuello);

   mat_esc_cuello = new Matriz_Escalado(2.75, 1.0, 2.75);
   Celda_Transformacion* esc_cuello = new Celda_Transformacion(mat_esc_cuello);

   //Inicializacion del nodo tabla con las celdas
   cuello = new Celda_Nodo();
   cuello->push_back( tras_cuello );
   cuello->push_back( esc_cuello );
   cuello->push_back( malla_cilindro );

   //////////////////////////////////////////////////////////////////
   ///////////////////////                  /////////////////////////
   ///////////////////////   NODO  CABEZA   /////////////////////////
   ///////////////////////                  /////////////////////////
   //////////////////////////////////////////////////////////////////

   const double ALTURA_CABEZA = ALTURA_CUELLO;

   //Transformación cabeza
   mat_tras_cabeza = new Matriz_Traslacion(0.0, ALTURA_CABEZA+0.5, 0.0);
   Celda_Transformacion* tras_cabeza = new Celda_Transformacion(mat_tras_cabeza);

   mat_esc_cabeza = new Matriz_Escalado(2.*2.75, 2*2.75, 2*2.75);
   Celda_Transformacion* esc_cabeza = new Celda_Transformacion(mat_esc_cabeza);

   //Inicializacion del nodo tabla con las celdas
   cabeza = new Celda_Nodo();
   cabeza->push_back( tras_cabeza );
   cabeza->push_back( esc_cabeza );
   cabeza->push_back( malla_esfera );

   //////////////////////////////////////////////////////////////////
   ///////////////////////                  /////////////////////////
   ///////////////////////    NODO  RAÍZ    /////////////////////////
   ///////////////////////                  /////////////////////////
   //////////////////////////////////////////////////////////////////

   //Inicialización del nodo escena con todas las celdas nodo
   escena = new Celda_Nodo();
   escena->push_back( falda );
   escena->push_back( cuello );
   escena->push_back( cabeza );

}

// ---------------------------------------------------------------------
// Función a implementar en la práctica 2  para dibujar los objetos

void P3_DibujarObjetos()
{
   cubo->set_color_principal(Tupla3f(0.5, 0.0, 0.0));
   cubo->set_color_secundario(Tupla3f(0.0, 0.0, 0.3));

   esfera->set_color_principal(Tupla3f(0.5, 0.0, 0.0));
   esfera->set_color_secundario(Tupla3f(0.0, 0.0, 0.3));

   cilindro->set_color_principal(Tupla3f(0.5, 0.0, 0.0));
   cilindro->set_color_secundario(Tupla3f(0.0, 0.0, 0.3));

   escena->visualizar();
}

void P3_Conmutar_NormalesCaras(){
   cubo->Conmutar_NormalesCaras();
   esfera->Conmutar_NormalesCaras();
   cilindro->Conmutar_NormalesCaras();
}

void P3_Conmutar_NormalesVertices(){
   cubo->Conmutar_NormalesVertices();
   esfera->Conmutar_NormalesVertices();
   cilindro->Conmutar_NormalesVertices();
}

bool P3_FGE_TeclaNormal( unsigned char tecla, int x_raton, int y_raton ){
    return false;
}

bool P3_FGE_TeclaEspecial( int tecla, int x_raton, int y_raton ){
    return false;
}
