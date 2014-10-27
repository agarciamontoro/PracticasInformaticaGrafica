#include <GL/glew.h>
#include <assert.h>

#include "VBO.hpp"

GLuint VBO::Inicializar(GLuint tipo_t, GLuint tam_t, GLvoid* puntero_datos_t){
	GLuint id_vbo ; // resultado: identificador de VBO

	assert( tipo_t == GL_ARRAY_BUFFER || tipo_t == GL_ELEMENT_ARRAY_BUFFER );

	glGenBuffers( 1, &id_vbo ); // crear nuevo VBO, obtener identificador

	glBindBuffer( tipo_t, id_vbo ); // activar el VBO usando su identificador
	glBufferData( tipo_t, tam_t, puntero_datos_t, GL_STATIC_DRAW ); // transferencia RAM –> GPU
	glBindBuffer( tipo_t, 0 ); // desactivación del VBO (activar 0)

	return id_vbo ;
}

VBO::VBO(GLuint tipo_t, std::vector<Tupla3f>& datos_t){
	this->tipo = tipo_t;
	this->tam = sizeof(GLfloat) * 3 * datos_t.size();
	this->puntero_datos = datos_t[0].coo;

	this->identificador = Inicializar(tipo, tam, puntero_datos);
}

VBO::VBO(GLuint tipo_t, std::vector<Tupla3i>& datos_t){
	this->tipo = tipo_t;
	this->tam = sizeof(GLuint) * 3 * datos_t.size();
	this->puntero_datos = datos_t[0].idx;

	this->identificador = Inicializar(tipo, tam, puntero_datos);
}

GLuint VBO::get_tipo(){
	return this->tipo;
}

GLuint VBO::get_tam(){
	return this->tam;
}

GLvoid* VBO::get_puntero(){
	return this->puntero_datos;
}

GLuint VBO::get_id(){
	return this->identificador;
}