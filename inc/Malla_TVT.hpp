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
#include "tipos.hpp"
#include "material.hpp"

class Malla_TVT{
private:
	std::vector<Tupla3f>	vertices,
							normales_vertices,
							normales_caras,
                            colores_vertices;


	std::vector<Tupla3i>	caras;

	VBO_Vertices	VBO_vertices;
    VBO_Caras		VBO_caras;
	VBO_Normales	VBO_normales_vertices,
					VBO_normales_caras;
    VBO_Colores		VBO_colores_vertices;
	VBO_Textura     VBO_coord_textura;

	std::vector<Tupla2f>	coordenadas_textura;
	Material*				material = NULL;

	enum modo_visualizacion visualizacion_actual;

	float dimension;

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
    void GenerarVBO_colores_vertices();
	void GenerarVBO_coord_textura();

	bool LeerPLY(char* archivo_PLY, enum modo_lectura lec);
	void cambiar_color(Tupla3f color);

	void ObtenerDimension();

    void DibujarNormales_Vertices(Tupla3f color = Tupla3f(1.0, 0.0, 0.0), float ancho = 0.5);
    void DibujarNormales_Caras(Tupla3f color = Tupla3f(0.0, 1.0, 0.0), float ancho = 0.5);

public:

	// ---------------------------------------------------------------------
	//  Constructor por defecto
	Malla_TVT(){};

	// ---------------------------------------------------------------------
	//  Constructor completo
	Malla_TVT(char* archivo_PLY,
			  enum modo_lectura lec = TODO,
			  Tupla3f color_principal_t = Tupla3f(1.0, 0.0, 0.0),
			  Tupla3f color_secundario_t = Tupla3f(1.0, 0.0, 0.0),
			  enum modo_visualizacion visualizacion_t = AJEDREZ);

	// ---------------------------------------------------------------------
	//  Constructor a partir de vectores
	Malla_TVT(std::vector<Tupla3f> vertices, std::vector<Tupla3i> caras);

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
	Malla_TVT GenerarSolidoRevolucion(int num_caras, bool calcular_coordenadas = false);

	// ---------------------------------------------------------------------
	//  Genera un sólido de revolución una vez cargado el perfil en "vertices" (no genera coord de textura)
	Malla_TVT GenerarSolidoRevolucion_old(int num_caras);

	// ---------------------------------------------------------------------
	//  Calcula las normales a los vértices, las caras y a ambos
	void CalcularNormalesVertices();
	void CalcularNormalesCaras();
	void CalcularNormales();

	// Asigna colores a los vértices mediante un array de colores
	void AsignarColores( std::vector<Tupla3f> colores );
	//Asigna a cada vértice un color según su normal
	void AsignarColoresVert();

	void AsignarCoordenadasTextura( std::vector<Tupla2f> coordenadas );
	void AsignarMaterial( Material* material );

	// ---------------------------------------------------------------------
	//  Visualiza la malla TVT
	void DibujarMalla_TVT();

	void Conmutar_NormalesVertices();
	void Conmutar_NormalesCaras();
};

//Funciones auxiliares de dibujo
void DibujarLinea(Tupla3f ori, Tupla3f fin, Tupla3f color = Tupla3f(1.0, 0.0, 0.0), float ancho = 1.0);

#endif
