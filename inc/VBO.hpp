#ifndef IG_VBO_HPP
#define IG_VBO_HPP

#include <vector>

#include <GL/glut.h>

#include "tuplas.hpp"
#include "tipos.hpp"

class VBO{

private:
	int num_datos;
	GLuint tam;
	GLvoid* puntero_datos;
	GLuint identificador;

	GLuint Inicializar();

public:
	VBO(){}

	template<class T>
	VBO( std::vector< Tupla<3,T> >& datos_t );

	VBO(const VBO& original);

	const VBO& operator=(const VBO& original);

	int get_num_datos();
	GLenum get_tipo_dato();
	GLsizeiptr get_tam_dato();
	GLuint get_tam();
	GLvoid* get_puntero();
	GLuint get_id();
};

class VBO_Normales: public VBO{
public:
	VBO_Normales(){}
	VBO_Normales( std::vector<Tupla3f>& datos_t ):
		VBO( datos_t ){}
	void Activar();
};

class VBO_Colores: public VBO{
public:
	VBO_Colores(){}
	VBO_Colores( std::vector<Tupla3f>& datos_t ):
		VBO( datos_t ){}
	void Activar();
};

class VBO_Vertices: public VBO{
public:
	VBO_Vertices(){}
	VBO_Vertices( std::vector<Tupla3f>& datos_t ):
		VBO( datos_t ){}
	void Activar();
};

class VBO_Caras: public VBO{
private:
public:
	VBO_Caras(){}
	VBO_Caras( std::vector<Tupla3i>& datos_t ):
		VBO( datos_t ){}
	GLenum get_tipo_dato();
	GLsizeiptr get_tam_dato();
	void Dibujar(enum modo_visualizacion modo, Tupla3f color_sec);
};

#endif
