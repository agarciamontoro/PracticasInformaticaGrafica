#include <GL/glew.h>
#include <assert.h>

#include "VBO.hpp"

GLuint VBO::Inicializar(){
	GLuint tipo_t, tam_t;
	GLvoid* puntero_datos_t;

	tipo_t = get_tipo_dato();
	tam_t = get_tam_dato();
	puntero_datos_t = get_puntero();

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
		this->tam = original.tam;
		this->puntero_datos = original.puntero_datos;

		this->identificador = Inicializar();
	}
}

///Crea un nuevo VBO en la GPU que apunta a los MISMOS datos en memoria que original.
const VBO& VBO::operator=(const VBO& original){
	if( this != &original ){
		this->tam = original.tam;
		this->puntero_datos = original.puntero_datos;

		this->identificador = Inicializar();
	}

	return *this;
}

template<class T>
VBO::VBO( std::vector< Tupla<3,T> >& datos_t ){
	this->tam = sizeof( get_tam_dato() ) * 3 * datos_t.size();
	this->puntero_datos = datos_t[0].get_ptr();

	this->identificador = Inicializar();
}

GLuint VBO::get_tipo_dato(){
	return GL_ARRAY_BUFFER;
}

GLuint VBO::get_tam_dato(){
	return GL_FLOAT;
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

void VBO_Normales::Activar(){
	glBindBuffer( get_tipo_dato(), get_id() );
	glNormalPointer( get_tam_dato(), 0, 0 );
	glEnableClientState( GL_NORMAL_ARRAY );
};

void VBO_Colores::Activar(){
	glBindBuffer( get_tipo_dato(), get_id() );
	glColorPointer( 3, get_tam_dato(), 0, 0 );
	glEnableClientState( GL_COLOR_ARRAY );
};

void VBO_Vertices::Activar(){
	glBindBuffer( get_tipo_dato(), get_id() );
	glVertexPointer( 3, get_tam_dato(), 0, 0 );
	glBindBuffer( get_tipo_dato(), 0 );
	glEnableClientState( GL_VERTEX_ARRAY );
};

GLuint VBO_Caras::get_tipo_dato(){
	return GL_ELEMENT_ARRAY_BUFFER;
}

GLuint VBO_Caras::get_tam_dato(){
	return GL_UNSIGNED_INT;
}

void VBO_Caras::Dibujar(GLenum modo_renderizado){
	glBindBuffer( get_tipo_dato(), get_id() );
	glDrawElements( GL_TRIANGLES, get_tam(), get_tam_dato(), NULL ) ;
	glBindBuffer( get_tipo_dato(), 0 );
}

template VBO::VBO<float>( std::vector< Tupla3f >& datos_t );
template VBO::VBO<int>( std::vector< Tupla3i >& datos_t );
