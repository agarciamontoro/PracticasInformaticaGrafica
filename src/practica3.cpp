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
static Malla_TVT* malla, *inception;

Matriz_Traslacion* mat_tra;
Matriz_Rotacion* mat_rot;
Matriz_Escalado* mat_esc;
Matriz_Cizalla* mat_ciz;

static Nodo peonza, peon, escena;

// ---------------------------------------------------------------------
//  Cambia el modo de visualización del modelo PLY

void P3_CambiarVisualizacion(enum modo_visualizacion modo){
   malla->set_visualizacion(modo);
   inception->set_visualizacion(modo);
}

// ---------------------------------------------------------------------
// Función para implementar en la práctica 2 para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e
// incializado OpenGL. El PLY se debe cargar aquí.

void P3_Inicializar( int argc, char *argv[] )
{
   char ruta_archivo[256] = "./PLY/perfil_peon.ply";
   int num_caras = 100;

   Malla_TVT peon_aux(ruta_archivo, VERT);
   Malla_TVT ince_aux("./PLY/perfil_inception.ply", VERT);

   malla = new Malla_TVT(peon_aux.GenerarSolidoRevolucion(num_caras));
   inception = new Malla_TVT(ince_aux.GenerarSolidoRevolucion(num_caras));

   malla->set_visualizacion(AJEDREZ);
   inception->set_visualizacion(AJEDREZ);

   mat_tra = new Matriz_Traslacion(1.5,1.5,1.5);
   mat_rot = new Matriz_Rotacion(M_PI/4, X);
   mat_esc = new Matriz_Escalado(1.5, 1.5, 1.5);
   mat_ciz = new Matriz_Cizalla(0.1, X, Y);

   Celda_Malla* malla_peon, *malla_inception;
   Celda_Transformacion* tra_peon, *rot_ince, *esc_peon, *ciz_ince;

   malla_peon = new Celda_Malla(malla);
   tra_peon = new Celda_Transformacion(mat_tra);
   esc_peon = new Celda_Transformacion(mat_esc);


   malla_inception = new Celda_Malla(inception);
   rot_ince = new Celda_Transformacion(mat_rot);
   ciz_ince = new Celda_Transformacion(mat_ciz);

   peon.push_back( tra_peon );
   peon.push_back( malla_peon );

   peon.push_back( tra_peon );
   peon.push_back( esc_peon );
   peon.push_back( malla_peon );

   peon.push_back( tra_peon );
   peon.push_back( esc_peon );
   peon.push_back( malla_peon );

   Celda_Nodo* nodo_peon = new Celda_Nodo( &peon );

   peonza.push_back( tra_peon );
   peonza.push_back( tra_peon );
   peonza.push_back( tra_peon );
   peonza.push_back( tra_peon );
   peonza.push_back( tra_peon );
   peonza.push_back( tra_peon );
   peonza.push_back( tra_peon );
   
   peonza.push_back( rot_ince );
   peonza.push_back( ciz_ince );
   peonza.push_back( malla_inception );

   Celda_Nodo* nodo_peonza = new Celda_Nodo( &peonza );

   escena.push_back( nodo_peon );
   escena.push_back( nodo_peonza );

}

// ---------------------------------------------------------------------
// Función a implementar en la práctica 2  para dibujar los objetos

void P3_DibujarObjetos()
{
   malla->set_color_principal(Tupla3f(0.5, 0.0, 0.0));
   malla->set_color_secundario(Tupla3f(0.0, 0.0, 0.3));

   inception->set_color_principal(Tupla3f(0.5, 0.0, 0.0));
   inception->set_color_secundario(Tupla3f(0.0, 0.0, 0.3));

   //malla->DibujarMalla_TVT();
   escena.visualizar();
}

void P3_Conmutar_NormalesCaras(){
   malla->Conmutar_NormalesCaras();
   inception->Conmutar_NormalesCaras();
}

void P3_Conmutar_NormalesVertices(){
   malla->Conmutar_NormalesVertices();
   inception->Conmutar_NormalesVertices();
}

bool P3_FGE_TeclaNormal( unsigned char tecla, int x_raton, int y_raton ){
    return false;
}

bool P3_FGE_TeclaEspecial( int tecla, int x_raton, int y_raton ){
    return false;
}
