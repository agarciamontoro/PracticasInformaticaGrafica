// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// **
// ** Práctica 2  (declaraciones públicas)
// **
// *********************************************************************

#ifndef IG_PRACTICA2_HPP
#define IG_PRACTICA2_HPP

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

void P2_DibujarObjetos() ; 
void P2_Inicializar( int argc, char *argv[] ) ;
void P2_CambiarVisualizacion(enum modo_visualizacion modo);
void P2_Conmutar_NormalesCaras();
void P2_Conmutar_NormalesVertices();

#endif
