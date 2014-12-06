#include <GL/glew.h>
#include <assert.h>

#include <iostream>

#include "VBO.hpp"

GLuint VBO::Inicializar(){
	GLenum tipo_t = get_tipo_dato();
	GLuint tam_t = get_tam();
	GLvoid* puntero_datos_t = get_puntero();

	GLuint id_vbo ; // resultado: identificador de VBO

	assert( tipo_t == GL_ARRAY_BUFFER || tipo_t == GL_ELEMENT_ARRAY_BUFFER );

	glGenBuffers( 1, &id_vbo ); // crear nuevo VBO, obtener identificador

	glBindBuffer( tipo_t, id_vbo ); // activar el VBO usando su identificador
	glBufferData( tipo_t, tam_t, puntero_datos_t, GL_STATIC_DRAW ); // transferencia RAM –> GPU
	glBindBuffer( tipo_t, 0 ); // desactivación del VBO (activar 0)

	return id_vbo ;
}

///Crea una nueva instancia de VBO en RAM de manera que se crea un nuevo VBO en la GPU,
// pero que apunta a los MISMOS datos en memoria que original.
VBO::VBO(const VBO& original){
	if( this != &original ){
		this->num_datos = original.num_datos;
		this->tam = original.tam;
		this->puntero_datos = original.puntero_datos;

		this->identificador = Inicializar();
	}
}

///Crea un nuevo VBO en la GPU que apunta a los MISMOS datos en memoria que original.
const VBO& VBO::operator=(const VBO& original){
	if( this != &original ){
		this->num_datos = original.num_datos;
		this->tam = original.tam;
		this->puntero_datos = original.puntero_datos;

		this->identificador = Inicializar();
	}

	return *this;
}

template<class T>
VBO::VBO( std::vector< Tupla<3,T> >& datos_t ){
	this->num_datos = 3 * datos_t.size();
	this->tam = get_tam_dato() * 3 * datos_t.size();
	this->puntero_datos = datos_t[0].get_ptr();

	this->identificador = Inicializar();
}

int VBO::get_num_datos(){
	return this->num_datos;
}

GLenum VBO::get_tipo_dato(){
	return GL_ARRAY_BUFFER;
}

GLsizeiptr VBO::get_tam_dato(){
	return sizeof(GL_FLOAT);
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

//-----------------------------------------------------------------------------------------------------------------------------

bool VBO_Normales::Activar(){
	bool activado;

	if( get_tam() != 0){
		glBindBuffer( get_tipo_dato(), get_id() );
		glNormalPointer( GL_FLOAT, 0, 0 );
		glBindBuffer( get_tipo_dato(), 0 );

		glEnableClientState( GL_NORMAL_ARRAY );

		activado = true;
	}
	else{
		activado = false;
	}

	return activado;
};

bool VBO_Colores::Activar(){
	bool activado;

	if( get_tam() != 0){
		glBindBuffer( get_tipo_dato(), get_id() );
		glColorPointer( 3, GL_FLOAT, 0, 0 );
		glBindBuffer( get_tipo_dato(), 0 );

		glEnableClientState( GL_COLOR_ARRAY );

		activado = true;
	}
	else{
		activado = false;
	}

	return activado;
};

void VBO_Vertices::Activar(){
	glBindBuffer( get_tipo_dato(), get_id() );
	glVertexPointer( 3, GL_FLOAT, 0, 0 );
	glBindBuffer( get_tipo_dato(), 0 );

	glEnableClientState( GL_VERTEX_ARRAY );
};

GLenum VBO_Caras::get_tipo_dato(){
	return GL_ELEMENT_ARRAY_BUFFER;
}

GLsizeiptr VBO_Caras::get_tam_dato(){
	return sizeof(GL_UNSIGNED_INT);
}

void VBO_Caras::Dibujar(enum modo_visualizacion modo, Tupla3f color_sec){
	glBindBuffer( get_tipo_dato(), get_id() );

	if( modo == AJEDREZ){
		int num_pares = get_num_datos() / 2;
		int num_impares = get_num_datos() - num_pares;

		glDrawElements( GL_TRIANGLES, num_pares, GL_UNSIGNED_INT, NULL ) ;
		glColor3f(color_sec[0], color_sec[1], color_sec[2]);
		glDrawElements( GL_TRIANGLES, num_impares, GL_UNSIGNED_INT, (const void*) (num_pares * get_tam_dato()) ) ;
	}
	else{
		glDrawElements( GL_TRIANGLES, get_num_datos(), GL_UNSIGNED_INT, NULL ) ;
	}

	glBindBuffer( get_tipo_dato(), 0 );
}

template VBO::VBO<float>( std::vector< Tupla3f >& datos_t );
template VBO::VBO<int>( std::vector< Tupla3i >& datos_t );
