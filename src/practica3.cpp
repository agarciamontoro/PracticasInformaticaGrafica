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

///////////////////////      MALLAS      /////////////////////////

static Malla_TVT *cubo, *esfera, *cilindro, *copa;

///////////////    MATRICES DE TRANSFORMACIÓN    /////////////////

static Matriz_Traslacion    *mat_tras_esfera[4],
                            *mat_tras_tabla[8],
                            *mat_tras_cuello,
                            *mat_tras_ojo_palo,
                            *mat_tras_ojo_deco[5],
                            *mat_tras_ojo_bola,
                            *mat_tras_ojo,
                            *mat_tras_cabeza_base,
                            *mat_tras_cabeza,
                            *mat_tras_pecho_arma[2],
                            *mat_tras_pecho_arma_copa,
                            *mat_tras_pecho;

static Matriz_Rotacion      *mat_rot_tabla[8],
                            *mat_rot_cabeza,
                            *mat_rot_ojo,
                            *mat_rot_pecho_arma,
                            *mat_rot_pecho_arma_copa,
                            *mat_rot_pecho;


static Matriz_Escalado      *mat_esc_tabla,
                            *mat_esc_cuello,
                            *mat_esc_ojo_palo,
                            *mat_esc_ojo_deco[3],
                            *mat_esc_ojo_bola,
                            *mat_esc_ojo,
                            *mat_esc_cabeza_base,
                            *mat_esc_cabeza,
                            *mat_esc_pecho_base,
                            *mat_esc_pecho_arma[2];

///////////////////////       NODOS      /////////////////////////

static Celda_Nodo           *esferas_tabla[4], *tabla,
                            *tablas_falda[8], *falda,
                            *ojo_palo, *ojo_deco[5], *ojo,
                            *cabeza_base, *cabeza,
                            *pecho_base, *pecho_arma[2], *pecho_arma_copa, *pecho,
                            *cuello,
                            *dalek;

/////////////////////   GRADOS DE LIBERTAD   ///////////////////////

static Matriz_Rotacion      *grado_libertad_cabeza,
                            *grado_libertad_ojo,
                            *grado_libertad_armas;

static Matriz_Traslacion    *grado_libertad_cabeza_altura;

/////////////////////  VARIABLES  ANIMACIÓN  ///////////////////////

static float velocidad_animacion    = 0;
static float angulo_animacion       = 0;

static Matriz_Traslacion  *animacion_tras;
static Matriz_Rotacion    *animacion_rot;


// ---------------------------------------------------------------------
//  Cambia el modo de visualización del modelo PLY

void P3_CambiarVisualizacion(enum modo_visualizacion modo){
   cubo->set_visualizacion(modo);
   esfera->set_visualizacion(modo);
   cilindro->set_visualizacion(modo);
   copa->set_visualizacion(modo);
}

// ---------------------------------------------------------------------
// Función para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e
// incializado OpenGL. El PLY se debe cargar aquí.

void P3_Inicializar( int argc, char *argv[] )
{
   char archivo_cubo[]      = "./PLY/cube.ply";
   char archivo_esfera[]    = "./PLY/sphere.ply";
   char archivo_cilindro[]  = "./PLY/cilinder.ply";
   char archivo_copa[]      = "./PLY/cup.ply";

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

   // MALLA copa
   Malla_TVT copa_aux(archivo_copa, VERT);
   copa = new Malla_TVT(copa_aux.GenerarSolidoRevolucion(num_caras));
   copa->set_visualizacion(AJEDREZ);

   Celda_Malla* malla_copa = new Celda_Malla(copa);

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
   ///////////////////////    NODO   OJO    /////////////////////////
   ///////////////////////                  /////////////////////////
   //////////////////////////////////////////////////////////////////

   const double LONG_OJO_PALO = 2.0;

   /////////////////////// NODOS AUXILIARES /////////////////////////

   // NODO PALO OJO

   //Transformación palo
   mat_tras_ojo_palo = new Matriz_Traslacion(0.0, LONG_OJO_PALO/4, 0.0);
   Celda_Transformacion* tras_ojo_palo = new Celda_Transformacion(mat_tras_ojo_palo);

   mat_esc_ojo_palo = new Matriz_Escalado(0.2, LONG_OJO_PALO, 0.2);
   Celda_Transformacion* esc_ojo_palo = new Celda_Transformacion(mat_esc_ojo_palo);

   ojo_palo = new Celda_Nodo();
   ojo_palo->push_back(esc_ojo_palo);
   ojo_palo->push_back(tras_ojo_palo);
   ojo_palo->push_back(malla_cilindro);

   // NODO DECORACIONES OJO

   //Transformación decoraciones
   Celda_Transformacion *tras_ojo_deco[5], *esc_ojo_deco[3];

   for(int i = 0; i < 3; ++i){
       mat_tras_ojo_deco[i] = new Matriz_Traslacion(0.0, LONG_OJO_PALO/2 + (0.1*i) + LONG_OJO_PALO/8, 0.0);
       tras_ojo_deco[i] = new Celda_Transformacion(mat_tras_ojo_deco[i]);

       mat_esc_ojo_deco[i] = new Matriz_Escalado(0.5 + 0.1*i, 0.02, 0.5 + 0.1*i);
       esc_ojo_deco[i] = new Celda_Transformacion(mat_esc_ojo_deco[i]);

       ojo_deco[i] = new Celda_Nodo();
       ojo_deco[i]->push_back(tras_ojo_deco[i]);
       ojo_deco[i]->push_back(esc_ojo_deco[i]);
       ojo_deco[i]->push_back(malla_cilindro);
   }

   for(int i = 3; i < 5; ++i){
       mat_tras_ojo_deco[i] = new Matriz_Traslacion(0.0, LONG_OJO_PALO/2 + (0.1*i) + LONG_OJO_PALO/8, 0.0);
       tras_ojo_deco[i] = new Celda_Transformacion(mat_tras_ojo_deco[i]);

       ojo_deco[i] = new Celda_Nodo();
       ojo_deco[i]->push_back(tras_ojo_deco[i]);
       ojo_deco[i]->push_back(esc_ojo_deco[4-i]); //El 3 tiene la misma escala que el 1 y el 4 la misma que el 0
       ojo_deco[i]->push_back(malla_cilindro);
   }

   // NODO OJO

   //Transformación bola

   mat_tras_ojo_bola = new Matriz_Traslacion(0.0, LONG_OJO_PALO+0.3, 0.0);
   Celda_Transformacion* tras_ojo_bola = new Celda_Transformacion(mat_tras_ojo_bola);

   mat_esc_ojo_bola = new Matriz_Escalado(1.3, 1.3, 1.3);
   Celda_Transformacion* esc_ojo_bola = new Celda_Transformacion(mat_esc_ojo_bola);

   //Transformacion ojo entero

   mat_esc_ojo = new Matriz_Escalado(0.15, 0.15, 0.15);
   Celda_Transformacion* esc_ojo = new Celda_Transformacion(mat_esc_ojo);

   mat_tras_ojo = new Matriz_Traslacion(0.0, 0.75, 1.4);
   Celda_Transformacion* tras_ojo = new Celda_Transformacion(mat_tras_ojo);

   mat_rot_ojo = new Matriz_Rotacion(M_PI/2.0, X);
   Celda_Transformacion* rot_ojo = new Celda_Transformacion(mat_rot_ojo);

   ojo = new Celda_Nodo();
   ojo->push_back(esc_ojo);
   ojo->push_back(tras_ojo);
   ojo->push_back(rot_ojo);
   ojo->push_back(ojo_palo);
   for(size_t i = 0; i < 5; i++)
   {
       ojo->push_back(ojo_deco[i]);
   }
   ojo->push_back(tras_ojo_bola);
   ojo->push_back(esc_ojo_bola);
   ojo->push_back(malla_esfera);

   //////////////////////////////////////////////////////////////////
   ///////////////////////                  /////////////////////////
   ///////////////////////   NODO  CABEZA   /////////////////////////
   ///////////////////////                  /////////////////////////
   //////////////////////////////////////////////////////////////////

   const double ALTURA_CABEZA_BASE = ALTURA_CUELLO + 0.5;
   const double ALTURA_CABEZA = ALTURA_CABEZA_BASE + 0.5;

   /////////////////////// NODOS AUXILIARES /////////////////////////

   // NODO BASE CABEZA

   //Transformación base cabeza
   mat_tras_cabeza_base = new Matriz_Traslacion(0.0, ALTURA_CABEZA_BASE, 0.0);
   Celda_Transformacion* tras_cabeza_base = new Celda_Transformacion(mat_tras_cabeza_base);

   mat_esc_cabeza_base = new Matriz_Escalado(2.5, 1.0, 2.5);
   Celda_Transformacion* esc_cabeza_base = new Celda_Transformacion(mat_esc_cabeza_base);

   //Inicializacion del nodo tabla con las celdas
   cabeza_base = new Celda_Nodo();
   cabeza_base->push_back( tras_cabeza_base );
   cabeza_base->push_back( esc_cabeza_base );
   cabeza_base->push_back( malla_cilindro );

   // NODO CABEZA

   //Transformación cabeza
   mat_tras_cabeza = new Matriz_Traslacion(0.0, ALTURA_CABEZA, 0.0);
   Celda_Transformacion* tras_cabeza = new Celda_Transformacion(mat_tras_cabeza);

   mat_rot_cabeza = new Matriz_Rotacion(M_PI/4, Y);
   Celda_Transformacion* rot_cabeza = new Celda_Transformacion(mat_rot_cabeza);

   mat_esc_cabeza = new Matriz_Escalado(2*2.5, 2*2.5, 2*2.5);
   Celda_Transformacion* esc_cabeza = new Celda_Transformacion(mat_esc_cabeza);

   //Inicializacion del nodo tabla con las celdas
   cabeza = new Celda_Nodo();
   cabeza->push_back( cabeza_base );
   cabeza->push_back( rot_cabeza );
   cabeza->push_back( tras_cabeza );
   cabeza->push_back( esc_cabeza );
   cabeza->push_back( malla_esfera );
   cabeza->push_back( ojo );

   //////////////////////////////////////////////////////////////////
   ///////////////////////                  /////////////////////////
   ///////////////////////    NODO PECHO    /////////////////////////
   ///////////////////////                  /////////////////////////
   //////////////////////////////////////////////////////////////////

   const double ALTURA_PECHO = ALTURA_CUELLO - 0.1;
   const double ANCHURA_PECHO = 2.3;

   /////////////////////// NODOS AUXILIARES /////////////////////////

   // NODO BASE PECHO

   //Transformación base del pecho

   mat_esc_pecho_base = new Matriz_Escalado(ANCHURA_PECHO, 0.75, 1.5);
   Celda_Transformacion* esc_pecho_base = new Celda_Transformacion(mat_esc_pecho_base);

   pecho_base = new Celda_Nodo();
   pecho_base->push_back( esc_pecho_base );
   pecho_base->push_back( malla_cubo );

   // NODOS ARMAS

   Celda_Transformacion *tras_pecho_arma[2], *esc_pecho_arma[2], *rot_pecho_arma;

   for(int i = 0; i < 2; ++i){
       //Transformación
       mat_tras_pecho_arma[i] = new Matriz_Traslacion( pow(-1,i)*ANCHURA_PECHO/3, 1.5, 0.0);
       tras_pecho_arma[i] = new Celda_Transformacion(mat_tras_pecho_arma[i]);

       mat_esc_pecho_arma[i] = new Matriz_Escalado(0.2, 1.5 + 1.5*i, 0.2);
       esc_pecho_arma[i] = new Celda_Transformacion(mat_esc_pecho_arma[i]);

       mat_rot_pecho_arma = new Matriz_Rotacion(M_PI/2, X);
       rot_pecho_arma = new Celda_Transformacion(mat_rot_pecho_arma);

       pecho_arma[i] = new Celda_Nodo();
       pecho_arma[i]->push_back( rot_pecho_arma );
       pecho_arma[i]->push_back( tras_pecho_arma[i] );
       pecho_arma[i]->push_back( esc_pecho_arma[i] );
       pecho_arma[i]->push_back( malla_cilindro );
   }

   //Transformación
   mat_tras_pecho_arma_copa = new Matriz_Traslacion( -ANCHURA_PECHO/3, -3.2, 0.0);
   Celda_Transformacion* tras_pecho_arma_copa = new Celda_Transformacion(mat_tras_pecho_arma_copa);

   mat_rot_pecho_arma_copa = new Matriz_Rotacion(3*M_PI/2, X);
   Celda_Transformacion* rot_pecho_arma_copa = new Celda_Transformacion(mat_rot_pecho_arma_copa);

   pecho_arma_copa = new Celda_Nodo();
   pecho_arma_copa->push_back( rot_pecho_arma_copa );
   pecho_arma_copa->push_back( tras_pecho_arma_copa );
   pecho_arma_copa->push_back( malla_copa );

   // NODO PECHO

   mat_tras_pecho = new Matriz_Traslacion(0.0, ALTURA_PECHO, 0.5);
   Celda_Transformacion* tras_pecho = new Celda_Transformacion(mat_tras_pecho);

   mat_rot_pecho = new Matriz_Rotacion(M_PI/2, Y);
   Celda_Transformacion* rot_pecho = new Celda_Transformacion(mat_rot_pecho);

   pecho = new Celda_Nodo();
   pecho->push_back( rot_pecho );
   pecho->push_back( tras_pecho );
   pecho->push_back(pecho_base);
   pecho->push_back(pecho_arma[0]);
   pecho->push_back(pecho_arma[1]);
   pecho->push_back(pecho_arma_copa);

   //////////////////////////////////////////////////////////////////
   ///////////////////////                  /////////////////////////
   ///////////////////////    NODO  RAÍZ    /////////////////////////
   ///////////////////////                  /////////////////////////
   //////////////////////////////////////////////////////////////////

   animacion_tras = new Matriz_Traslacion(6*sin(M_PI/4), 0.0, 6*cos(M_PI/4));
   Celda_Transformacion* celda_anim_tras = new Celda_Transformacion(animacion_tras);

   animacion_rot  = new Matriz_Rotacion(M_PI/4+M_PI/2, Y);
   Celda_Transformacion* celda_anim_rot  = new Celda_Transformacion(animacion_rot);

   //Inicialización del nodo escena con todas las celdas nodo
   dalek = new Celda_Nodo();
   dalek->push_back( celda_anim_tras );
   dalek->push_back( celda_anim_rot );
   dalek->push_back( falda );
   dalek->push_back( cuello );
   dalek->push_back( cabeza );
   dalek->push_back( pecho );



   //////////////////////////////////////////////////////////////////
   ///////////////////////                  /////////////////////////
   /////////////////////// GRADOS  LIBERTAD /////////////////////////
   ///////////////////////                  /////////////////////////
   //////////////////////////////////////////////////////////////////

   grado_libertad_cabeza    = mat_rot_cabeza;
   grado_libertad_ojo       = mat_rot_ojo;
   grado_libertad_armas     = mat_rot_pecho;
   grado_libertad_cabeza_altura = mat_tras_cabeza;

}

// ---------------------------------------------------------------------
// Función para dibujar los objetos

void P3_DibujarObjetos()
{
   cubo->set_color_principal(Tupla3f(0.5, 0.0, 0.0));
   cubo->set_color_secundario(Tupla3f(0.0, 0.0, 0.3));

   esfera->set_color_principal(Tupla3f(0.5, 0.0, 0.0));
   esfera->set_color_secundario(Tupla3f(0.0, 0.0, 0.3));

   cilindro->set_color_principal(Tupla3f(0.5, 0.0, 0.0));
   cilindro->set_color_secundario(Tupla3f(0.0, 0.0, 0.3));

   copa->set_color_principal(Tupla3f(0.5, 0.0, 0.0));
   copa->set_color_secundario(Tupla3f(0.0, 0.0, 0.3));

   dalek->visualizar();
}

void P3_Conmutar_NormalesCaras(){
   cubo->Conmutar_NormalesCaras();
   esfera->Conmutar_NormalesCaras();
   cilindro->Conmutar_NormalesCaras();
   copa->Conmutar_NormalesCaras();
}

void P3_Conmutar_NormalesVertices(){
   cubo->Conmutar_NormalesVertices();
   esfera->Conmutar_NormalesVertices();
   cilindro->Conmutar_NormalesVertices();
   copa->Conmutar_NormalesVertices();
}

void P3_Modificar_Grado_Libertad(enum grados_libertad grado, float cambio, Tupla3f cambio_tras){
    float angulo;

    switch(grado){
        case CABEZA:
            grado_libertad_cabeza->set_angulo( grado_libertad_cabeza->get_angulo() + cambio );
            break;

        case OJO:
            angulo = grado_libertad_ojo->get_angulo() + cambio;
            if( angulo < M_PI/1.5 && angulo > M_PI/3.0)
                grado_libertad_ojo->set_angulo(angulo);
            break;

        case ARMAS:
            grado_libertad_armas->set_angulo( grado_libertad_armas->get_angulo() + cambio );
                break;

        case CABEZA_ALTURA:
            grado_libertad_cabeza_altura->set_direccion( grado_libertad_cabeza_altura->get_direccion() + cambio_tras);

        default:
            break;
    }
}

void P3_Modificar_Velocidad_Animacion(double incremento){
  velocidad_animacion += incremento;
}

void P3_Establecer_Valores_Animacion(){
  float rotacion_actual, rotacion_nueva;

  rotacion_actual = animacion_rot->get_angulo();
  rotacion_nueva = rotacion_actual + velocidad_animacion;

  animacion_rot->set_angulo( rotacion_nueva );

  angulo_animacion += velocidad_animacion;

  animacion_tras->set_direccion(10*sin(angulo_animacion), 0.0, 10*cos(angulo_animacion));
}

bool P3_FGE_TeclaNormal( unsigned char tecla, int x_raton, int y_raton ){
    bool redisp = true ;

    switch (tecla){
        case 'Z':
            P3_Modificar_Grado_Libertad(CABEZA, +0.1);
            break;

        case 'z':
            P3_Modificar_Grado_Libertad(CABEZA, -0.1);
            break;

        case 'X':
            P3_Modificar_Grado_Libertad(OJO, +0.1);
            break;

        case 'x':
            P3_Modificar_Grado_Libertad(OJO, -0.1);
            break;

        case 'C':
            P3_Modificar_Grado_Libertad(ARMAS, +0.1);
            break;

        case 'c':
            P3_Modificar_Grado_Libertad(ARMAS, -0.1);
            break;

        case 'Y':
            P3_Modificar_Grado_Libertad(CABEZA_ALTURA, 0, Tupla3f(0.0, +0.1, 0.0));
            break;

        case 'y':
            P3_Modificar_Grado_Libertad(CABEZA_ALTURA, 0, Tupla3f(0.0, -0.1, 0.0));
            break;

        case 'B':
            P3_Modificar_Velocidad_Animacion(+0.01);
            break;

        case 'b':
            P3_Modificar_Velocidad_Animacion(-0.01);
            break;


        default:
            redisp = false;
            break;
    }

    return redisp;
}

bool P3_FGE_TeclaEspecial( int tecla, int x_raton, int y_raton ){
    return false;
}
