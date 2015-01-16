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
#include "practica3.hpp"
#include "practica4.hpp"
#include "tipos.hpp"

void PX_DibujarObjetos() ;
void PX_Inicializar( int argc, char *argv[] ) ;
void PX_CambiarVisualizacion(enum modo_visualizacion modo);
void PX_CambiarPracticaActual(enum practicas prac);
enum practicas PX_ConsultarPracticaActual();
void PX_Conmutar_NormalesVertices();
void PX_Conmutar_NormalesCaras();
bool PX_FGE_PulsarTeclaNormal( unsigned char tecla, int x_raton, int y_raton );
bool PX_FGE_PulsarTeclaEspecial( int tecla, int x_raton, int y_raton );

#endif
