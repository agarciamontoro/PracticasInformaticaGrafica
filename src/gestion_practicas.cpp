// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// **
// ** Gestión prácticas  (implementación)
// **
// *********************************************************************

#include "gestion_practicas.hpp"

static enum practicas PRACTICA_ACTUAL = P3;

void PX_DibujarObjetos(){
	switch(PRACTICA_ACTUAL){
		case P1:
			P1_DibujarObjetos();
			break;

		case P2:
			P2_DibujarObjetos();
			break;

		case P3:
			P3_DibujarObjetos();
			break;
	}
}

void PX_Inicializar( int argc, char *argv[] ){
	P1_Inicializar(argc, argv);
	P2_Inicializar(argc, argv);
	P3_Inicializar(argc, argv);

	PX_CambiarVisualizacion(AJEDREZ);
}

void PX_CambiarVisualizacion(enum modo_visualizacion modo){
	P1_CambiarVisualizacion(modo);
	P2_CambiarVisualizacion(modo);
	P3_CambiarVisualizacion(modo);
}

void PX_CambiarPracticaActual(enum practicas prac){
	PRACTICA_ACTUAL = prac;
}

enum practicas PX_ConsultarPracticaActual(){
	return PRACTICA_ACTUAL;
}

void PX_Conmutar_NormalesCaras(){
	P1_Conmutar_NormalesCaras();
	P2_Conmutar_NormalesCaras();
	P3_Conmutar_NormalesCaras();
}

void PX_Conmutar_NormalesVertices(){
	P1_Conmutar_NormalesVertices();
	P2_Conmutar_NormalesVertices();
	P3_Conmutar_NormalesVertices();
}
