#ifndef IG_MALLA_TVT_HPP
#define IG_MALLA_TVT_HPP

#include <vector>
#include <assert.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include "tuplas.hpp"
#include "error-ogl.hpp"
#include "file_ply_stl.hpp"
#include "VBO.hpp"

enum modo_visualizacion{
   ALAMBRE, 
   SOLIDO,
   AJEDREZ
};

class Malla_TVT{
private:
	std::vector<struct Tupla3f> vertices;
	std::vector<struct Tupla3i> caras_pares,
								caras_impares;

	VBO VBO_vertices,
		VBO_caras_pares,
		VBO_caras_impares;

	enum modo_visualizacion visualizacion_actual;
	GLenum render_actual;

	Tupla3f color_principal;
	Tupla3f color_secundario;

	void InicializarTabla(char* archivo_PLY);
	bool LeerPLY(char* archivo_PLY);
	void cambiar_color(Tupla3f color);

public:

	Malla_TVT(){};

	Malla_TVT(char* archivo_PLY,
			  Tupla3f color_principal_t = Tupla3f(1.0, 0.0, 0.0),
			  Tupla3f color_secundario_t = Tupla3f(1.0, 0.0, 0.0),
			  enum modo_visualizacion visualizacion_t = ALAMBRE);


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
	//  Visualiza la malla TVT
	void DibujarMalla_TVT();
};

#endif