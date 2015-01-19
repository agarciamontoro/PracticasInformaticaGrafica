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

static Malla_TVT            *peon_madera, *peon_blanco, *peon_negro,
                            *lata_lateral, *lata_superior, *lata_inferior;

///////////////    MATRICES DE TRANSFORMACIÓN    /////////////////

static Matriz_Traslacion    *mat_tras_peon[3];

static Matriz_Escalado      *mat_esc_lata;

///////////////////////       NODOS      /////////////////////////

static Celda_Nodo           *nodo_escena,
                            *nodo_peon_madera,
                            *nodo_peon_blanco,
                            *nodo_peon_negro,
                            *nodo_lata;

static FuenteLuz            *luz_direccional,
                            *luz_posicional;

static Material             *material_peon_madera,
                            *material_peon_blanco,
                            *material_peon_negro,
                            *material_lata, *material_tapas;

static Textura              *madera,
                            *coca_cola;

// ---------------------------------------------------------------------
//  Cambia el modo de visualización del modelo PLY

void P4_CambiarVisualizacion(enum modo_visualizacion modo){
    //peon->set_visualizacion(modo);
    //lata_lateral->set_visualizacion(modo);
    //lata_superior->set_visualizacion(modo);
    //lata_inferior->set_visualizacion(modo);
}

// ---------------------------------------------------------------------
// Función para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e
// incializado OpenGL. El PLY se debe cargar aquí.

void P4_Inicializar( int argc, char *argv[] ){
    CError();
    char archivo_lata_lateral[]     = "./PLY/lata-pcue.ply";
    char archivo_lata_superior[]    = "./PLY/lata-psup.ply";
    char archivo_lata_inferior[]    = "./PLY/lata-pinf.ply";
    char archivo_peon[]             = "./PLY/perfil_peon.ply";

    int num_caras = 100;


    //////////////////////////////////////////////////////////////////
    ///////////////////////                       ////////////////////
    /////////////////////// DEFINICIÓN MATERIALES ////////////////////
    ///////////////////////                       ////////////////////
    //////////////////////////////////////////////////////////////////

    //Definición texturas
    coca_cola   = new Textura("IMG/text-lata-1.jpg");
    madera      = new Textura("IMG/text-madera.jpg", OBJETO);

    //Definición materiales
    material_lata = new Material(   Tupla4f(0.3, 0.3, 0.3, 1.0),
                                    Tupla4f(0.05, 0.05, 0.05, 1.0),
                                    Tupla4f(0.7, 0.7, 0.7, 1.0),
                                    Tupla4f(1.0, 1.0, 1.0, 1.0),
                                    6.0,
                                    coca_cola);


    material_tapas = new Material(  Tupla4f(0.3, 0.3, 0.3, 1.0),
                                    Tupla4f(0.05, 0.05, 0.05, 1.0),
                                    Tupla4f(0.7, 0.7, 0.7, 1.0),
                                    Tupla4f(1.0, 1.0, 1.0, 1.0),
                                    6.0);


    material_peon_madera = new Material(
                                    Tupla4f(0.3, 0.3, 0.3, 1.0),
                                    Tupla4f(0.05, 0.05, 0.05, 1.0),
                                    Tupla4f(0.7, 0.7, 0.7, 1.0),
                                    Tupla4f(1.0, 1.0, 1.0, 1.0),
                                    6.0,
                                    madera);


    material_peon_blanco = new Material(
                                    Tupla4f(0.6, 0.6, 0.6, 1.0),
                                    Tupla4f(0.05, 0.05, 0.05, 1.0),
                                    Tupla4f(0.5, 0.5, 0.5, 1.0),
                                    Tupla4f(0.0, 0.0, 0.0, 0.0),
                                    6.0);


    material_peon_negro = new Material(
                                    Tupla4f(0.0, 0.0, 0.0, 1.0),
                                    Tupla4f(0.02, 0.02, 0.02, 1.0),
                                    Tupla4f(0.0, 0.0, 0.0, 1.0),
                                    Tupla4f(1.0, 1.0, 1.0, 1.0),
                                    3.0);


    //////////////////////////////////////////////////////////////////
    ///////////////////////                   ////////////////////////
    /////////////////////// DEFINICIÓN MALLAS ////////////////////////
    ///////////////////////                   ////////////////////////
    //////////////////////////////////////////////////////////////////

    // MALLAS PEONES

    Malla_TVT peon_aux(archivo_peon, VERT);
    peon_madera = new Malla_TVT(peon_aux.GenerarSolidoRevolucion(num_caras));
    peon_madera->set_visualizacion(ILUM_GOUROUD);
    peon_madera->AsignarMaterial(material_peon_madera);

    peon_blanco = new Malla_TVT(*peon_madera);
    peon_blanco->AsignarMaterial(material_peon_blanco);

    peon_negro = new Malla_TVT(*peon_madera);
    peon_negro->AsignarMaterial(material_peon_negro);

    Celda_Malla* malla_peon_madera = new Celda_Malla( peon_madera );
    Celda_Malla* malla_peon_blanco = new Celda_Malla( peon_blanco );
    Celda_Malla* malla_peon_negro  = new Celda_Malla( peon_negro );

    // MALLA LATA

    // Malla cuerpo
    Malla_TVT lata_lateral_aux(archivo_lata_lateral, VERT);
    lata_lateral = new Malla_TVT(lata_lateral_aux.GenerarSolidoRevolucion(num_caras, true));
    lata_lateral->set_visualizacion(ILUM_GOUROUD);
    lata_lateral->AsignarMaterial(material_lata);

    Celda_Malla* malla_lata_lateral = new Celda_Malla(lata_lateral);

    // Malla tapa superior
    Malla_TVT lata_superior_aux(archivo_lata_superior, VERT);
    lata_superior = new Malla_TVT(lata_superior_aux.GenerarSolidoRevolucion(num_caras));
    lata_superior->set_visualizacion(ILUM_GOUROUD);
    lata_superior->AsignarMaterial(material_tapas);

    Celda_Malla* malla_lata_superior = new Celda_Malla(lata_superior);

    // Malla inferior
    Malla_TVT lata_inferior_aux(archivo_lata_inferior, VERT);
    lata_inferior = new Malla_TVT(lata_inferior_aux.GenerarSolidoRevolucion(num_caras));
    lata_inferior->set_visualizacion(ILUM_GOUROUD);
    lata_inferior->AsignarMaterial(material_tapas);

    Celda_Malla* malla_lata_inferior = new Celda_Malla(lata_inferior);


    ////////////////////////////////////////////////////////////////
    //////////////////                             /////////////////
    ////////////////// DEFINICIÓN TRANSFORMACIONES /////////////////
    //////////////////                             /////////////////
    ////////////////////////////////////////////////////////////////

    //Escalado lata
    mat_esc_lata = new Matriz_Escalado(5, 5, 5);
    Celda_Transformacion* trans_lata = new Celda_Transformacion(mat_esc_lata);

    //Traslación peones
    Celda_Transformacion* trans_peon[3];

    for(size_t i = 0; i < 3; ++i)
    {
        mat_tras_peon[i] = new Matriz_Traslacion(4*cosf(i*M_PI/4), 1.4, 4*sinf(i*M_PI/4));
        trans_peon[i] = new Celda_Transformacion(mat_tras_peon[i]);
    }


    //////////////////////////////////////////////////////////////////
    ///////////////////////                   ////////////////////////
    /////////////////////// DEFINICIÓN  NODOS ////////////////////////
    ///////////////////////                   ////////////////////////
    //////////////////////////////////////////////////////////////////

    nodo_lata = new Celda_Nodo();
    nodo_lata->push_back(trans_lata);
    nodo_lata->push_back(malla_lata_lateral);
    nodo_lata->push_back(malla_lata_superior);
    nodo_lata->push_back(malla_lata_inferior);

    nodo_peon_madera = new Celda_Nodo();
    nodo_peon_madera->push_back(trans_peon[0]);
    nodo_peon_madera->push_back(malla_peon_madera);

    nodo_peon_blanco = new Celda_Nodo();
    nodo_peon_blanco->push_back(trans_peon[1]);
    nodo_peon_blanco->push_back(malla_peon_blanco);

    nodo_peon_negro  = new Celda_Nodo();
    nodo_peon_negro->push_back(trans_peon[2]);
    nodo_peon_negro->push_back(malla_peon_negro);

    nodo_escena = new Celda_Nodo();
    nodo_escena->push_back(nodo_lata);
    nodo_escena->push_back(nodo_peon_madera);
    nodo_escena->push_back(nodo_peon_blanco);
    nodo_escena->push_back(nodo_peon_negro);

    //////////////////////////////////////////////////////////////////
    ///////////////////////                   ////////////////////////
    /////////////////////// DEFINICIÓN  LUCES ////////////////////////
    ///////////////////////                   ////////////////////////
    //////////////////////////////////////////////////////////////////

    luz_direccional = new FuenteLuz(0, DIRECCIONAL,
                                    Tupla4f(0.0, 0.0, 0.0, 0.0));

    luz_posicional  = new FuenteLuz(1, POSICIONAL,
                                    Tupla4f(0.0, 6.0, 0.0, 1.0),
                                    Tupla4f(0.2, 0.2, 0.7, 1.0),
                                    Tupla4f(0.2, 0.2, 0.7, 1.0),
                                    Tupla4f(0.2, 0.2, 0.7, 1.0));

    glEnable( GL_LIGHTING );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );
    glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR ) ;
    glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
}

void P4_DibujarObjetos(){
    glEnable( GL_LIGHTING );
    glEnable( GL_NORMALIZE );
    glDisable( GL_COLOR_MATERIAL );

    luz_direccional->activar();
    luz_posicional->activar();

    nodo_escena->visualizar();

    luz_direccional->desactivar();
    luz_posicional->desactivar();

    glDisable( GL_LIGHTING );
    glDisable( GL_NORMALIZE );
    glEnable( GL_COLOR_MATERIAL );
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
    std::cout << "TECLA" << std::endl;
    switch( toupper(tecla) ){
        case 'A':
        luz_direccional->modificar_direccion(0,+0.1);
        break;

        case 'Z':
        luz_direccional->modificar_direccion(0,-0.1);
        break;

        case 'X':
        luz_direccional->modificar_direccion(+0.1,0);
        break;

        case 'C':
        luz_direccional->modificar_direccion(-0.1,0);
        break;

    }
    return false;
}

bool P4_FGE_TeclaEspecial( int tecla, int x_raton, int y_raton ){
    return false;
}
