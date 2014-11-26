#include <vector>

#include <GL/glew.h>
#include <GL/glut.h>

#include "tuplas.hpp"
#include "error-ogl.hpp"
#include "file_ply_stl.hpp"
#include "VBO.hpp"
#include "Malla_TVT.hpp"

void Malla_TVT::InicializarTabla(char* archivo_PLY){

	if( LeerPLY(archivo_PLY) ){
		VBO_vertices		= VBO(GL_ARRAY_BUFFER, vertices);
		VBO_caras_pares		= VBO(GL_ARRAY_BUFFER, caras_pares);
		VBO_caras_impares	= VBO(GL_ARRAY_BUFFER, caras_impares);
	}
}

bool Malla_TVT::LeerPLY(char* archivo_PLY){
   // Variables locales para la lectura del archivo PLY
   std::vector<float> vertices_raw;
   std::vector<int> caras_raw;

   // lectura del archivo PLY
   ply::read(archivo_PLY, vertices_raw, caras_raw);

   // Para su mejor gestión, organizamos vértices y caras en vectores de Tuplas
   for (unsigned int i = 0; i < vertices_raw.size(); i += 3)
   {
		this->vertices.push_back( Tupla3f(vertices_raw[i+0], vertices_raw[i+1], vertices_raw[i+2]) );
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

void Malla_TVT::cambiar_color(Tupla3f color){
	glColor3f(color[0], color[1], color[2]);
}

Malla_TVT::Malla_TVT(char* archivo_PLY,
		  Tupla3f color_principal_t,
		  Tupla3f color_secundario_t,
		  enum modo_visualizacion visualizacion_t)
{
	InicializarTabla(archivo_PLY);
	this->color_principal = color_principal_t;
	this->color_secundario = color_secundario_t;
	set_visualizacion(visualizacion_t);
}

Malla_TVT::Malla_TVT(const Malla_TVT& original){
	if( this != &original ){
		this->vertices = original.vertices;
		this->caras_pares = original.caras_pares;
		this->caras_impares = original.caras_impares;

		this->color_principal = original.color_principal;
		this->color_secundario = original.color_secundario;

		set_visualizacion(original.visualizacion_actual);

		this->VBO_vertices = VBO(GL_ARRAY_BUFFER, this->vertices);
		this->VBO_caras_pares = VBO(GL_ARRAY_BUFFER, this->caras_pares);
		this->VBO_caras_impares = VBO(GL_ARRAY_BUFFER, this->caras_impares);
	}
}

const Malla_TVT& Malla_TVT::operator=(const Malla_TVT& original){
	if( this != &original ){
		this->vertices = original.vertices;
		this->caras_pares = original.caras_pares;
		this->caras_impares = original.caras_impares;

		this->color_principal = original.color_principal;
		this->color_secundario = original.color_secundario;

		set_visualizacion(original.visualizacion_actual);

		this->VBO_vertices = VBO(GL_ARRAY_BUFFER, this->vertices);
		this->VBO_caras_pares = VBO(GL_ARRAY_BUFFER, this->caras_pares);
		this->VBO_caras_impares = VBO(GL_ARRAY_BUFFER, this->caras_impares);
	}

	return *this;
}

// ---------------------------------------------------------------------
//  Cambia el modo de visualización del modelo PLY

void Malla_TVT::set_visualizacion(enum modo_visualizacion modo){
   this->visualizacion_actual = modo;
   
   switch(modo){
   	case ALAMBRE:
   		render_actual = GL_LINE;
   		break;
   		
   	case PUNTO:
   		render_actual = GL_POINT;
   		break;
   		
   	case SOLIDO:
   	case AJEDREZ:
   		render_actual = GL_FILL;
   		break;
   	}
}

// ---------------------------------------------------------------------
//  Cambia el color principal de renderización

void Malla_TVT::set_color_principal(Tupla3f color){
   this->color_principal = color;
}

// ---------------------------------------------------------------------
//  Cambia el color principal de renderización

void Malla_TVT::set_color_secundario(Tupla3f color){
   this->color_secundario = color;
}

void Malla_TVT::DibujarMalla_TVT(){
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