// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// ** Gestión prácticas  (implementación)
// **
// *********************************************************************

#include "gestion_practicas.hpp"

static enum practicas PRACTICA_ACTUAL = P2;

void PX_DibujarObjetos(){
	switch(PRACTICA_ACTUAL){
		case P1:
			P1_DibujarObjetos();
			break;

		case P2:
			P2_DibujarObjetos();
			break;
	}
}

void PX_Inicializar( int argc, char *argv[] ){
	P1_Inicializar(argc, argv);
	P2_Inicializar(argc, argv);
}

void PX_CambiarVisualizacion(enum modo_visualizacion modo){
	P1_CambiarVisualizacion(modo);
	P2_CambiarVisualizacion(modo);
}

void PX_CambiarPracticaActual(enum practicas prac){
	PRACTICA_ACTUAL = prac;
}