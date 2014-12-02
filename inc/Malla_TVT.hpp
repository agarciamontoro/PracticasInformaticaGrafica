#ifndef IG_MALLA_TVT_HPP
#define IG_MALLA_TVT_HPP

#include <vector>
#include <assert.h>
#include <cmath> //Uso de M_PI

#include <GL/glew.h>
#include <GL/glut.h>

#include "tuplas.hpp"
#include "error-ogl.hpp"
#include "file_ply_stl.hpp"
#include "VBO.hpp"

enum modo_visualizacion{
   ALAMBRE, 
   SOLIDO,
   AJEDREZ,
   PUNTO
};

enum modo_lectura{
   TODO,
   VERT
};

class Malla_TVT{
private:
	std::vector<Tupla3f>	vertices,
							normales_vertices,
							normales_caras_pares,
							normales_caras_impares;

	std::vector<Tupla3i>	caras_pares,
							caras_impares;

	VBO VBO_vertices,
		VBO_caras_pares,
		VBO_caras_impares,
		VBO_normales_vertices,
		VBO_normales_caras_pares,
		VBO_normales_caras_impares;

	enum modo_visualizacion visualizacion_actual;

	int visualizar_normales_vert = 0;
	int visualizar_normales_caras = 0;

	GLenum render_actual;

	Tupla3f color_principal;
	Tupla3f color_secundario;

	void GenerarVBO_TODO();
	void GenerarVBO_vertices();
	void GenerarVBO_caras();
	void GenerarVBO_normales_vertices();
	void GenerarVBO_normales_caras();

	bool LeerPLY(char* archivo_PLY, enum modo_lectura lec);
	void cambiar_color(Tupla3f color);

public:

	Malla_TVT(){};

	Malla_TVT(char* archivo_PLY,
			  enum modo_lectura lec = TODO,
			  Tupla3f color_principal_t = Tupla3f(1.0, 0.0, 0.0),
			  Tupla3f color_secundario_t = Tupla3f(1.0, 0.0, 0.0),
			  enum modo_visualizacion visualizacion_t = AJEDREZ);


	// ---------------------------------------------------------------------
	//  Constructor de copia
	Malla_TVT(const Malla_TVT& original);


	// ---------------------------------------------------------------------
	//  Operador de asignación
	const Malla_TVT& operator=(const Malla_TVT &original);

	// ---------------------------------------------------------------------
	//  Cambia el modo de visualización del modelo PLY
	void set_visualizacion(enum modo_visualizacion modo);

	// ---------------------------------------------------------------------
	//  Cambia el color principal de renderización
	void set_color_principal(Tupla3f color);

	// ---------------------------------------------------------------------
	//  Cambia el color principal de renderización
	void set_color_secundario(Tupla3f color);

	// ---------------------------------------------------------------------
	//  Genera un sólido de revolución una vez cargado el perfil en "vertices"
	void GenerarSolidoRevolucion(int caras);

	// ---------------------------------------------------------------------
	//  Genera un sólido de revolución una vez cargado el perfil en "vertices"
	void CalcularNormalesVertices();
	void CalcularNormalesCaras();
	void CalcularNormales();

	// ---------------------------------------------------------------------
	//  Visualiza la malla TVT
	void DibujarMalla_TVT();

	void Conmutar_NormalesVertices();
	void Conmutar_NormalesCaras();
};

//Funciones auxiliares de dibujo
void DibujarLinea(Tupla3f ori, Tupla3f fin, Tupla3f color = Tupla3f(1.0, 0.0, 0.0), float ancho = 1.0);

#endif