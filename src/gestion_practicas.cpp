// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// **
// ** Gestión prácticas  (implementación)
// **
// *********************************************************************

#include "gestion_practicas.hpp"

static enum practicas PRACTICA_ACTUAL = P4;

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

		case P4:
			P4_DibujarObjetos();
			break;
	}
}

void PX_Inicializar( int argc, char *argv[] ){
	P1_Inicializar(argc, argv);
	P2_Inicializar(argc, argv);
	P3_Inicializar(argc, argv);
	P4_Inicializar(argc, argv);

	PX_CambiarVisualizacion(AJEDREZ);
}

void PX_CambiarVisualizacion(enum modo_visualizacion modo){
	P1_CambiarVisualizacion(modo);
	P2_CambiarVisualizacion(modo);
	P3_CambiarVisualizacion(modo);
	P4_CambiarVisualizacion(modo);
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
	P4_Conmutar_NormalesCaras();
}

void PX_Conmutar_NormalesVertices(){
	P1_Conmutar_NormalesVertices();
	P2_Conmutar_NormalesVertices();
	P3_Conmutar_NormalesVertices();
	P4_Conmutar_NormalesVertices();
}

bool PX_FGE_PulsarTeclaNormal( unsigned char tecla, int x_raton, int y_raton ){
	bool redisp = true;

	switch( PRACTICA_ACTUAL ){
		case P3:
			redisp = P3_FGE_TeclaNormal( tecla, x_raton, y_raton );
			break;
		case P4:
			redisp = P4_FGE_TeclaNormal( tecla, x_raton, y_raton );
			break;
		default:
			redisp = false;
		break;
	}

	return redisp;
}


bool PX_FGE_PulsarTeclaEspecial( int tecla, int x_raton, int y_raton ){
	bool redisp = true;

	switch( PRACTICA_ACTUAL ){
		case P3:
			redisp = P3_FGE_TeclaEspecial( tecla, x_raton, y_raton );
			break;
		case P4:
			redisp = P4_FGE_TeclaEspecial( tecla, x_raton, y_raton );
			break;
		default:
			redisp = false;
			break;
	}

	return redisp;
}
