// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// **
// ** Práctica 1  (declaraciones públicas)
// **
// *********************************************************************

#ifndef IG_PRACTICA1_HPP
#define IG_PRACTICA1_HPP

#include <iostream>
#include <vector>
#include <assert.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include "tuplas.hpp"
#include "error-ogl.hpp"
#include "practica1.hpp"
#include "file_ply_stl.hpp"

enum modo_visualizacion{
   ALAMBRE,
   SOLIDO,
   AJEDREZ
};

class VBO{

private:
	GLuint tipo;
	GLuint tam;
	GLvoid* puntero_datos;
	GLuint identificador;

	GLuint Inicializar(GLuint tipo_t, GLuint tam_t, GLvoid* puntero_datos_t){
		GLuint id_vbo ; // resultado: identificador de VBO

		assert( tipo_t == GL_ARRAY_BUFFER || tipo_t == GL_ELEMENT_ARRAY_BUFFER );

		glGenBuffers( 1, &id_vbo ); // crear nuevo VBO, obtener identificador

		glBindBuffer( tipo_t, id_vbo ); // activar el VBO usando su identificador
		glBufferData( tipo_t, tam_t, puntero_datos_t, GL_STATIC_DRAW ); // transferencia RAM –> GPU
		glBindBuffer( tipo_t, 0 ); // desactivación del VBO (activar 0)

		return id_vbo ;
	}

public:
	VBO(){}

	VBO(GLuint tipo_t, std::vector<Tupla3f>& datos_t){
		this->tipo = tipo_t;
		this->tam = sizeof(GLfloat) * 3 * datos_t.size();
		this->puntero_datos = datos_t[0].coo;

		this->identificador = Inicializar(tipo, tam, puntero_datos);
	}

	VBO(GLuint tipo_t, std::vector<Tupla3i>& datos_t){
		this->tipo = tipo_t;
		this->tam = sizeof(GLuint) * 3 * datos_t.size();
		this->puntero_datos = datos_t[0].idx;

		this->identificador = Inicializar(tipo, tam, puntero_datos);
	}

	GLuint get_tipo(){
		return this->tipo;
	}

	GLuint get_tam(){
		return this->tam;
	}

	GLvoid* get_puntero(){
		return this->puntero_datos;
	}

	GLuint get_id(){
		return this->identificador;
	}


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

	void InicializarTabla(char* archivo_PLY){

		if( LeerPLY(archivo_PLY) ){
			VBO_vertices		= VBO(GL_ARRAY_BUFFER, vertices);
			VBO_caras_pares		= VBO(GL_ARRAY_BUFFER, caras_pares);
			VBO_caras_impares	= VBO(GL_ARRAY_BUFFER, caras_impares);
		}
	}

	bool LeerPLY(char* archivo_PLY){
	   // Variables locales para la lectura del archivo PLY
	   std::vector<float> vertices_raw;
	   std::vector<int> caras_raw;

	   // lectura del archivo PLY
	   ply::read(archivo_PLY, vertices_raw, caras_raw);

	   // Para su mejor gestión, organizamos vértices y caras en vectores de Tuplas
	   for (unsigned int i = 0; i < vertices_raw.size(); i += 3)
	   {
	      this->vertices.push_back(Tupla3f(vertices_raw[i+0], vertices_raw[i+1], vertices_raw[i+2]));
	   }

	   // Separamos las cares pares e impares para gestionar de forma eficiente el modo ajedrez
	   for (unsigned int i = 0; i < caras_raw.size(); i += 6)
	   {
	      this->caras_pares.push_back(Tupla3i(caras_raw[i+0], caras_raw[i+1], caras_raw[i+2]));
	      this->caras_impares.push_back(Tupla3i(caras_raw[i+3], caras_raw[i+4], caras_raw[i+5]));
	   }

	   // TODO: Implementar una gestión de errores al leer/procesar los datos.
	   // En caso de encontrarlos, devolver false.
	   return true;
	}

	void cambiar_color(Tupla3f color){
		glColor3f(color.coo[0], color.coo[1], color.coo[2]);
	}

public:

	Malla_TVT(){};

	Malla_TVT(char* archivo_PLY,
			  Tupla3f color_principal_t = Tupla3f(1.0, 0.0, 0.0),
			  Tupla3f color_secundario_t = Tupla3f(1.0, 0.0, 0.0),
			  enum modo_visualizacion visualizacion_t = ALAMBRE)
	{
		InicializarTabla(archivo_PLY);
		this->color_principal = color_principal_t;
		this->color_secundario = color_secundario_t;
		set_visualizacion(visualizacion_t);
	}

	// ---------------------------------------------------------------------
	//  Cambia el modo de visualización del modelo PLY

	void set_visualizacion(enum modo_visualizacion modo){
	   this->visualizacion_actual = modo;
	   render_actual = modo == ALAMBRE ? GL_LINE : GL_FILL;
	}

	// ---------------------------------------------------------------------
	//  Cambia el color principal de renderización

	void set_color_principal(Tupla3f color){
	   this->color_principal = color;
	}

	// ---------------------------------------------------------------------
	//  Cambia el color principal de renderización

	void set_color_secundario(Tupla3f color){
	   this->color_secundario = color;
	}

	void DibujarMallaTVT(){
		CError();

		// Ajustes iniciales
		cambiar_color(color_principal);
		
		// especificar modo de visualizacion
		glPolygonMode(GL_FRONT_AND_BACK, render_actual);

		//Activar uso de vertex array
		glEnableClientState( GL_VERTEX_ARRAY );

		// especificar formato de los vértices en su VBO (y offset)
		glBindBuffer( GL_ARRAY_BUFFER, VBO_vertices.get_id() ); // act. VBO
		glVertexPointer( 3, GL_FLOAT, 0, 0 ); // formato y offset (0)
		glBindBuffer( GL_ARRAY_BUFFER, 0 ); // desact VBO.

		// visualizar con glDrawElements las caras pares (puntero a tabla == NULL)
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, VBO_caras_pares.get_id() );
		glDrawElements( GL_TRIANGLES, 3*caras_pares.size(), GL_UNSIGNED_INT, NULL ) ;
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

		// cambiar el color de las caras si el modo de visualización es ajedrez
		if(visualizacion_actual == AJEDREZ){
			cambiar_color(color_secundario);
		}

		// visualizar con glDrawElements las caras impares (puntero a tabla == NULL)
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, VBO_caras_impares.get_id() );
		glDrawElements( GL_TRIANGLES, 3*caras_impares.size(), GL_UNSIGNED_INT, NULL ) ;
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

		// desactivar uso de array de vértices
		glDisableClientState( GL_VERTEX_ARRAY );
		CError();
	}
};

void P1_DibujarObjetos() ; 
void P1_Inicializar( int argc, char *argv[] ) ;
void CambiarVisualizacion(enum modo_visualizacion modo);

#endif
