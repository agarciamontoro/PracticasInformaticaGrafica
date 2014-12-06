// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// **
// **
// ** Práctica 1  (declaraciones públicas)
// **
// *********************************************************************

#ifndef IG_PRACTICA1_HPP
#define IG_PRACTICA1_HPP

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

void P1_DibujarObjetos() ;
void P1_Inicializar( int argc, char *argv[] ) ;
void P1_CambiarVisualizacion(enum modo_visualizacion modo);
void P1_Conmutar_NormalesCaras();
void P1_Conmutar_NormalesVertices();


#endif
