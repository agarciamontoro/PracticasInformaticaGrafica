// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// **
// **
// ** Práctica 3  (declaraciones públicas)
// **
// *********************************************************************

#ifndef IG_PRACTICA3_HPP
#define IG_PRACTICA3_HPP

#include <iostream>
#include <vector>
#include <assert.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include "tuplas.hpp"
#include "error-ogl.hpp"
#include "file_ply_stl.hpp"
#include "VBO.hpp"
#include "Malla_TVT.hpp"
#include "tipos.hpp"

void P3_DibujarObjetos() ;
void P3_Inicializar( int argc, char *argv[] ) ;
void P3_CambiarVisualizacion(enum modo_visualizacion modo);
void P3_Conmutar_NormalesCaras();
void P3_Conmutar_NormalesVertices();

void P3_Modificar_Grado_Libertad(enum grados_libertad grado, float cambio, Tupla3f cambio_tras = Tupla3f(0,0,0));
void P3_Modificar_Velocidad_Animacion(double incremento);
void P3_Establecer_Valores_Animacion();

bool P3_FGE_TeclaNormal( unsigned char tecla, int x_raton, int y_raton );
bool P3_FGE_TeclaEspecial( int tecla, int x_raton, int y_raton );

#endif
