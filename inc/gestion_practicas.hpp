// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// **
// ** Gestión prácticas
// **
// *********************************************************************

#ifndef IG_GESTION_PRACTICAS_HPP
#define IG_GESTION_PRACTICAS_HPP

#include "Malla_TVT.hpp"
#include "practica1.hpp"
#include "practica2.hpp"

enum practicas{
   P1,
   P2
};

void PX_DibujarObjetos() ; 
void PX_Inicializar( int argc, char *argv[] ) ;
void PX_CambiarVisualizacion(enum modo_visualizacion modo);
void PX_CambiarPracticaActual(enum practicas prac);
void PX_Conmutar_NormalesVertices();
void PX_Conmutar_NormalesCaras();

#endif
