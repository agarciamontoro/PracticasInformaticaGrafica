// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// **
// ** Práctica 4 (implementación)
// **
// *********************************************************************

#include "practica4.hpp"
#include "grafo_escena.hpp"

#include <stdio.h>

///////////////////////      MALLAS      /////////////////////////

static Malla_TVT *peon, *lata_lateral, *lata_superior, *lata_inferior;

///////////////    MATRICES DE TRANSFORMACIÓN    /////////////////

static Matriz_Traslacion    *mat_tras_esfera[4];

static Matriz_Rotacion      *mat_rot_tabla[8];

static Matriz_Escalado      *mat_esc_tabla;

///////////////////////       NODOS      /////////////////////////

static Celda_Nodo           *escena,
                            *lata;

static FuenteLuz            *luz_direccional;
static Material             *reflectante;

// ---------------------------------------------------------------------
//  Cambia el modo de visualización del modelo PLY

void P4_CambiarVisualizacion(enum modo_visualizacion modo){
    peon->set_visualizacion(modo);
    lata_lateral->set_visualizacion(modo);
    lata_superior->set_visualizacion(modo);
    lata_inferior->set_visualizacion(modo);
}

// ---------------------------------------------------------------------
// Función para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e
// incializado OpenGL. El PLY se debe cargar aquí.

void P4_Inicializar( int argc, char *argv[] ){
    char archivo_lata_lateral[]     = "./PLY/lata-pcue.ply";
    char archivo_lata_superior[]    = "./PLY/lata-psup.ply";
    char archivo_lata_inferior[]    = "./PLY/lata-pinf.ply";
    char archivo_peon[]             = "./PLY/perfil_peon.ply";

    int num_caras = 100;

    //////////////////////////////////////////////////////////////////
    ///////////////////////                   ////////////////////////
    /////////////////////// DEFINICIÓN MALLAS ////////////////////////
    ///////////////////////                   ////////////////////////
    //////////////////////////////////////////////////////////////////

    // MALLA PEÓN
    Malla_TVT peon_aux(archivo_peon, VERT);
    peon = new Malla_TVT(peon_aux.GenerarSolidoRevolucion(num_caras));
    peon->set_visualizacion(AJEDREZ);

    Celda_Malla* malla_peon = new Celda_Malla(peon);

    // MALLA LATA

    // Malla cuerpo
    Malla_TVT lata_lateral_aux(archivo_lata_lateral, VERT);
    lata_lateral = new Malla_TVT(lata_lateral_aux.GenerarSolidoRevolucion(num_caras));
    lata_lateral->set_visualizacion(AJEDREZ);

    Celda_Malla* malla_lata_lateral = new Celda_Malla(lata_lateral);

    // Malla tapa superior
    Malla_TVT lata_superior_aux(archivo_lata_superior, VERT);
    lata_superior = new Malla_TVT(lata_superior_aux.GenerarSolidoRevolucion(num_caras));
    lata_superior->set_visualizacion(AJEDREZ);

    Celda_Malla* malla_lata_superior = new Celda_Malla(lata_superior);

    // Malla inferior
    Malla_TVT lata_inferior_aux(archivo_lata_inferior, VERT);
    lata_inferior = new Malla_TVT(lata_inferior_aux.GenerarSolidoRevolucion(num_caras));
    lata_inferior->set_visualizacion(AJEDREZ);

    Celda_Malla* malla_lata_inferior = new Celda_Malla(lata_inferior);


    //////////////////////////////////////////////////////////////////
    ///////////////////////                   ////////////////////////
    /////////////////////// DEFINICIÓN  NODOS ////////////////////////
    ///////////////////////                   ////////////////////////
    //////////////////////////////////////////////////////////////////

    lata = new Celda_Nodo();
    lata->push_back(malla_lata_lateral);
    lata->push_back(malla_lata_superior);
    lata->push_back(malla_lata_inferior);

    escena = new Celda_Nodo();
    escena->push_back(lata);

    //////////////////////////////////////////////////////////////////
    ///////////////////////                   ////////////////////////
    /////////////////////// DEFINICIÓN  LUCES ////////////////////////
    ///////////////////////                   ////////////////////////
    //////////////////////////////////////////////////////////////////

    luz_direccional = new FuenteLuz(0, DIRECCIONAL, Tupla4f(3.0, 7.0, 0.0, 0.0));
    luz_direccional->activar();

    Tupla3f prueba(0.1, 0.2, 1.0);
    reflectante = new Material(prueba, prueba, prueba, prueba, 2.0);
    reflectante->activar();

}

void P4_DibujarObjetos(){
    escena->visualizar();
}

void P4_Conmutar_NormalesCaras(){
}

void P4_Conmutar_NormalesVertices(){
}

void P4_Modificar_Grado_Libertad(enum grados_libertad grado, float cambio){
}

void P4_Modificar_Velocidad_Animacion(double incremento){
}

void P4_Establecer_Valores_Animacion(){
}

bool P4_FGE_TeclaNormal( unsigned char tecla, int x_raton, int y_raton ){
    return false;
}

bool P4_FGE_TeclaEspecial( int tecla, int x_raton, int y_raton ){
    return false;
}
