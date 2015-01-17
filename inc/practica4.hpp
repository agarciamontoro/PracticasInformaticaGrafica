// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// **
// **
// ** Práctica 4  (declaraciones públicas)
// **
// *********************************************************************

#ifndef IG_PRACTICA4_HPP
#define IG_PRACTICA4_HPP

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
#include "fuente_luz.hpp"
#include "material.hpp"

void P4_DibujarObjetos() ;
void P4_Inicializar( int argc, char *argv[] ) ;
void P4_CambiarVisualizacion(enum modo_visualizacion modo);
void P4_Conmutar_NormalesCaras();
void P4_Conmutar_NormalesVertices();

void P4_Modificar_Grado_Libertad(enum grados_libertad grado, float cambio);
void P4_Modificar_Velocidad_Animacion(double incremento);
void P4_Establecer_Valores_Animacion();

bool P4_FGE_TeclaNormal( unsigned char tecla, int x_raton, int y_raton );
bool P4_FGE_TeclaEspecial( int tecla, int x_raton, int y_raton );

#endif
