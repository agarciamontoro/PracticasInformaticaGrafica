#ifndef IG_VBO_HPP
#define IG_VBO_HPP

#include <vector>

#include <GL/glut.h>

#include "tuplas.hpp"

class VBO{

private:
	GLuint tipo;
	GLuint tam;
	GLvoid* puntero_datos;
	GLuint identificador;

	GLuint Inicializar(GLuint tipo_t, GLuint tam_t, GLvoid* puntero_datos_t);

public:
	VBO(){}
	VBO(GLuint tipo_t, std::vector<Tupla3f>& datos_t);
	VBO(GLuint tipo_t, std::vector<Tupla3i>& datos_t);

	GLuint get_tipo();
	GLuint get_tam();
	GLvoid* get_puntero();
	GLuint get_id();
};

#endif