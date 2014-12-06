#include <vector>

#include <GL/glew.h>
#include <GL/glut.h>

#include <iostream>

#include "Malla_TVT.hpp"

#include "tuplas.hpp"
#include "error-ogl.hpp"
#include "file_ply_stl.hpp"
#include "VBO.hpp"
#include "Matriz.hpp"

#define DIM_NORMALES 1.5

void Malla_TVT::GenerarVBO_vertices(){
	this->VBO_vertices					= VBO(GL_ARRAY_BUFFER, vertices);
}

void Malla_TVT::GenerarVBO_caras(){
	this->VBO_caras_pares				= VBO(GL_ARRAY_BUFFER, caras_pares);
	this->VBO_caras_impares				= VBO(GL_ARRAY_BUFFER, caras_impares);
}


void Malla_TVT::GenerarVBO_normales_vertices(){
	this->VBO_normales_vertices			= VBO(GL_ARRAY_BUFFER, normales_vertices);
}

void Malla_TVT::GenerarVBO_normales_caras(){
	this->VBO_normales_caras_pares		= VBO(GL_ARRAY_BUFFER, normales_caras_pares);
	this->VBO_normales_caras_impares	= VBO(GL_ARRAY_BUFFER, normales_caras_impares);
}

void Malla_TVT::GenerarVBO_colores_vertices(){
	this->VBO_colores_vertices			= VBO(GL_ARRAY_BUFFER, colores_vertices);
}

void Malla_TVT::GenerarVBO_TODO(){
	GenerarVBO_vertices();
	GenerarVBO_caras();
	GenerarVBO_normales_vertices();
	GenerarVBO_normales_caras();
	GenerarVBO_colores_vertices();
}

bool Malla_TVT::LeerPLY(char* archivo_PLY, enum modo_lectura lec){
   // Variables locales para la lectura del archivo PLY
   std::vector<float> vertices_raw;
   std::vector<int> caras_raw;

   // lectura del archivo PLY
   if(lec == TODO){
   	ply::read(archivo_PLY, vertices_raw, caras_raw);
   }
   else
   	ply::read_vertices(archivo_PLY, vertices_raw);

   // Para su mejor gestión, organizamos vértices y caras en vectores de Tuplas
   for (unsigned int i = 0; i < vertices_raw.size(); i += 3)
   {
		this->vertices.push_back( Tupla3f(vertices_raw[i+0], vertices_raw[i+1], vertices_raw[i+2]) );
   }

   if(lec == TODO){
	   // Separamos las cares pares e impares para gestionar de forma eficiente el modo ajedrez
	   for (unsigned int i = 0; i < caras_raw.size(); i += 6)
	   {
	      this->caras_pares.push_back(Tupla3i(caras_raw[i+0], caras_raw[i+1], caras_raw[i+2]));
	      this->caras_impares.push_back(Tupla3i(caras_raw[i+3], caras_raw[i+4], caras_raw[i+5]));
	   }
	}

   // TODO: Implementar una gestión de errores al leer/procesar los datos.
   // En caso de encontrarlos, devolver false.
   return true;
}

void Malla_TVT::cambiar_color(Tupla3f color){
	glColor3f(color[0], color[1], color[2]);
}

Malla_TVT::Malla_TVT(char* archivo_PLY,
		  enum modo_lectura lec,
		  Tupla3f color_principal_t,
		  Tupla3f color_secundario_t,
		  enum modo_visualizacion visualizacion_t)
{
	LeerPLY(archivo_PLY, lec);
	GenerarVBO_TODO();
	this->color_principal = color_principal_t;
	this->color_secundario = color_secundario_t;
	set_visualizacion(visualizacion_t);
}

Malla_TVT::Malla_TVT(std::vector<Tupla3f> vertices, std::vector<Tupla3i> caras){
	this->vertices = vertices;

	for(unsigned int i = 0; i < caras.size(); i += 2){
		this->caras_pares.push_back(caras[i]);
		this->caras_impares.push_back(caras[i+1]);
	}

	GenerarVBO_TODO();
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
		this->normales_caras_pares = original.normales_caras_pares;
		this->normales_caras_impares = original.normales_caras_impares;
		this->normales_vertices = original.normales_vertices;

		this->color_principal = original.color_principal;
		this->color_secundario = original.color_secundario;

		set_visualizacion(original.visualizacion_actual);

		GenerarVBO_TODO();
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

void Malla_TVT::GenerarSolidoRevolucion(int caras){
	assert(this->vertices.size() > 0);
	assert(caras_pares.size() == 0 && caras_impares.size() == 0);

	///////////////////////////
	// Variables necesarias //
	///////////////////////////

	//Ángulo de rotación entre perfiles
	float angulo = 2*M_PI / caras;
	float c = cosf(angulo);
	float s = sinf(angulo);

	//Matriz de rotacion
	float mat[3][3] = {
		{c,0,s},
		{0,1,0},
		{-s,0,c}
	};
	Matriz3x3f matriz_rotacion(mat);

	///////////////////////
	// Preprocesamiento //
	///////////////////////

	//Procesamos el perfil para que el primer y último vértice no se repitan
	//durante la rotación y para asegurarnos de que tienen coordenada X = 0

	std::vector<Tupla3f>::iterator it_primero, it_ultimo;
	int pos_primero, pos_ultimo;
	Tupla3f primer_vertice, ultimo_vertice;

	//Iteradores para las posiciones primera y última
	it_primero = this->vertices.begin();
	pos_primero = 0;

	it_ultimo = this->vertices.end();
	pos_ultimo = this->vertices.size()-1;

	//Vértices que deben ser tratados por separado
	primer_vertice = this->vertices[pos_primero];
	ultimo_vertice = this->vertices[pos_ultimo];

	//Si el primer(resp. último) vértice tiene coordenada X = 0,
	//se borra del vector original. Si no, se actualiza la primer_vertice
	//(resp. ultimo_vertice) poniendo a cero la componente X.
	if(this->vertices[pos_primero][0] == 0.0){
		this->vertices.erase(it_primero);
	}
	else{
		primer_vertice[0] = 0.0;
	}

	if(this->vertices[pos_ultimo][0] == 0.0){
		this->vertices.erase(it_ultimo);
	}
	else{
		ultimo_vertice[0] = 0.0;
	}


	//////////////////////////////////////
	//  Generación de vértices y caras //
	//////////////////////////////////////

	//Variables para el bucle
	std::vector<Tupla3f> perfil_anterior, perfil_actual;
	unsigned int num_vert = this->vertices.size();
	Tupla3f vert_rotado;
	Tupla3i cara_par, cara_impar;

	//Primera iteración del siguiente bucle antes del mismo
	perfil_anterior = this->vertices;

	//Bucle de generación de todos los perfiles
	for (int i = 1; i < caras; ++i){

		//Primera iteración del siguiente bucle antes del mismo
		vert_rotado = toTupla(matriz_rotacion * perfil_anterior[0]);
		perfil_actual.push_back( vert_rotado );
		this->vertices.push_back( vert_rotado );

		//Bucle de generación de todos los vértices del perfil i
		for (unsigned int j = 1; j < num_vert; ++j){
			//Generación de perfiles
			vert_rotado = toTupla(matriz_rotacion * perfil_anterior[j]);

			//Generación de caras
			cara_par 	= Tupla3i(	num_vert * (i-1) + j,
									num_vert * (i-1) + (j-1),
									num_vert * (i) + (j-1)
								);
			cara_impar 	= Tupla3i(	num_vert * (i-1) + j,
									num_vert * (i) + (j-1),
									num_vert * (i) + j
								);

			//Actualizamos el nuevo perfil para la siguiente iteración
			perfil_actual.push_back( vert_rotado );

			//Asignación a la tupla actual de todo lo calculado
			this->vertices.push_back( vert_rotado );
			this->caras_pares.push_back(cara_par);
			this->caras_impares.push_back(cara_impar);
		} //Fin de generación de vértices para el perfil i

		//Actualización de las variables del bucle
		perfil_anterior = perfil_actual;
		perfil_actual.clear();

	} //Fin de generación de perfiles

	//Generación de la última cara
	for (unsigned int j = 1; j < num_vert; ++j){
		//Generación de caras
		cara_par 	= Tupla3i(	num_vert * (caras-1) + j,
								num_vert * (caras-1) + (j-1),
								num_vert * (0) + (j-1)
							);
		cara_impar 	= Tupla3i(	num_vert * (caras-1) + j,
								num_vert * (0) + (j-1),
								num_vert * (0) + j
							);

		this->caras_pares.push_back(cara_par);
		this->caras_impares.push_back(cara_impar);

	} //Fin de generación de la última cara

	///////////////////////////
	//  Generación de tapas //
	///////////////////////////

		////////////////////
		// Tapa inferior //
		////////////////////

	this->vertices.push_back(primer_vertice);

	int indice_centro_tapa_inferior = vertices.size()-1;

	for (int i = 0; i < caras-1; i += 2)
	{
		cara_par 	= Tupla3i(	num_vert * (i),
								indice_centro_tapa_inferior,
								num_vert * (i+1)
							);
		cara_impar 	= Tupla3i(	num_vert * (i+1),
								indice_centro_tapa_inferior,
								num_vert * (i+2)
							);

		this->caras_pares.push_back(cara_par);
		this->caras_impares.push_back(cara_impar);
	}

	// Última cara de la tapa inferior
	cara_impar = Tupla3i(	num_vert * (caras-1),
							indice_centro_tapa_inferior,
							0
						);

	this->caras_impares.push_back(cara_impar);

		////////////////////
		// Tapa superior //
		////////////////////

	this->vertices.push_back(ultimo_vertice);

	int indice_centro_tapa_superior = vertices.size()-1;

	for (int i = 0; i < caras-2; i += 2)
	{
		cara_par 	= Tupla3i(	num_vert * (i+1) + (num_vert - 1),
								indice_centro_tapa_superior,
								num_vert * (i) + (num_vert - 1)
							);
		cara_impar 	= Tupla3i(	num_vert * (i+2) + (num_vert - 1),
								indice_centro_tapa_superior,
								num_vert * (i+1) + (num_vert - 1)
							);

		this->caras_pares.push_back(cara_par);
		this->caras_impares.push_back(cara_impar);
	}

	// Última cara de la tapa superior
	cara_par 	= Tupla3i(	num_vert * (caras-1) + (num_vert - 1),
							indice_centro_tapa_superior,
							num_vert * (caras-2) + (num_vert - 1)
							);
	cara_impar = Tupla3i(	num_vert - 1,
							indice_centro_tapa_superior,
							num_vert * (caras-1)  + (num_vert - 1)
						);

	this->caras_pares.push_back(cara_par);
	this->caras_impares.push_back(cara_impar);

	//////////////////////////
	// Cálculo de normales //
	//////////////////////////

	CalcularNormales();

	//////////////////////////
	// Asignar colores a los vértices //
	//////////////////////////

	//Construimos el vector de colores con respecto al de normales de vértices
	std::vector<Tupla3f> colores_vertices;

	for(size_t i = 0; i < this->vertices.size(); i++){
		colores_vertices.push_back( this->vertices[i].abs() );
	}

	AsignarColores( colores_vertices );

	//////////////////////////
	//  Generación de VBOs //
	//////////////////////////

	GenerarVBO_TODO();
}

void Malla_TVT::CalcularNormalesCaras(){
	this->normales_caras_pares.resize(0);

	Tupla3f A, B, C, AB, BC, normal;

	for (unsigned int i = 0; i < caras_pares.size(); ++i)
	{
		A = this->vertices[ caras_pares[i][0] ];
		B = this->vertices[ caras_pares[i][1] ];
		C = this->vertices[ caras_pares[i][2] ];

		AB = B - A;
		BC = C - B;

		normal = AB * BC; //Producto vectorial

		this->normales_caras_pares.push_back( normal.normalized() );
	}


	this->normales_caras_impares.resize(0);

	for (unsigned int i = 0; i < caras_impares.size(); ++i)
	{
		Tupla3f A = this->vertices[ caras_impares[i][0] ];
		Tupla3f B = this->vertices[ caras_impares[i][1] ];
		Tupla3f C = this->vertices[ caras_impares[i][2] ];

		Tupla3f AB = B - A;
		Tupla3f BC = C - B;

		Tupla3f normal = AB * BC; //Producto vectorial

		this->normales_caras_impares.push_back( normal.normalized() );
	}
}

void Malla_TVT::CalcularNormalesVertices(){
	//Ponemos a cero todos los valores del vector de normales de vértices con un
	//pequeño artificio: lo hacemos de tamaño 0 para que, al agrandarlo hasta el
	//número de vertices con resize, podamos incluir un valor con el que se inicializen todos
	//Ver documentación de resize: "If val is specified, the NEW elements are
	//initialized as copies of val".
	this->normales_vertices.resize(0);
	this->normales_vertices.resize(this->vertices.size(), Tupla3f(0.0, 0.0, 0.0) );

	for (unsigned int i = 0; i < caras_pares.size(); ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			int indice = this->caras_pares[i][j];

			this->normales_vertices[indice] += this->normales_caras_pares[i];
		}
	}

	for (unsigned int i = 0; i < caras_impares.size(); ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			int indice = this->caras_impares[i][j];

			this->normales_vertices[indice] += this->normales_caras_impares[i];
		}
	}

	for (unsigned int i = 0; i < this->normales_vertices.size(); ++i)
	{
		this->normales_vertices[i] = this->normales_vertices[i].normalized();
	}
}

void Malla_TVT::CalcularNormales(){
	CalcularNormalesCaras();
	CalcularNormalesVertices();
}

void Malla_TVT::AsignarColores( std::vector<Tupla3f> colores ){
	this->colores_vertices = colores;
	GenerarVBO_colores_vertices();
}

void Malla_TVT::DibujarMalla_TVT(){
	CError();

	////////////////////////
	// Ajustes iniciales //
	////////////////////////

	//Cambio de color general
	cambiar_color(color_principal);

	// especificar modo de visualizacion
	glPolygonMode(GL_FRONT_AND_BACK, render_actual);

	if( ! this->colores_vertices.empty() ){
		glShadeModel(GL_SMOOTH);

		glBindBuffer( GL_ARRAY_BUFFER, VBO_colores_vertices.get_id() ); // act. VBO
		glColorPointer( 3, GL_FLOAT, 0, 0 ); // formato y offset (0)
		glBindBuffer( GL_ARRAY_BUFFER, 0 ); // desact VBO.

		glEnableClientState( GL_COLOR_ARRAY );
	}

	//////////////////////
	// Enviar vértices //
	//////////////////////

	//Activar uso de vertex array
	glEnableClientState( GL_VERTEX_ARRAY );

	// especificar formato de los vértices en su VBO (y offset)
	glBindBuffer( GL_ARRAY_BUFFER, VBO_vertices.get_id() ); // act. VBO
	glVertexPointer( 3, GL_FLOAT, 0, 0 ); // formato y offset (0)
	glBindBuffer( GL_ARRAY_BUFFER, 0 ); // desact VBO.



	///////////////////////
	// Visualizar caras //
	///////////////////////

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

	//////////////////////
	// Ajustes finales //
	//////////////////////

	if( ! this->colores_vertices.empty() ){
		glDisableClientState( GL_COLOR_ARRAY );
	}

	// desactivar uso de array de vértices
	glDisableClientState( GL_VERTEX_ARRAY );

	/////////////////////////
	// Dibujos auxiliares //
	/////////////////////////

	///////////////////////////////
	// Dibujo normales vertices //
	///////////////////////////////

	if(visualizar_normales_vert){
		DibujarNormales_Vertices( color_principal + Tupla3f(0.5, 0.5, 0.5), 0.5 );
	}

	////////////////////////////
	// Dibujo normales caras //
	////////////////////////////

	if(visualizar_normales_caras){
		DibujarNormales_Caras( color_secundario + Tupla3f(0.5, 0.5, 0.5), 0.5 );
	}

	CError();
}

void Malla_TVT::DibujarNormales_Vertices(Tupla3f color, float ancho){
	Tupla3f origen, extremo;

	for (unsigned int i = 0; i < this->normales_vertices.size(); ++i){
		origen = this->vertices[i];
		extremo = origen + ( this->normales_vertices[i] * DIM_NORMALES );

		DibujarLinea(origen, extremo, color, ancho);
	}
}

void Malla_TVT::DibujarNormales_Caras(Tupla3f color, float ancho){
	Tupla3f A, B, C;
	Tupla3f origen, extremo;

	for (unsigned int i = 0; i < this->normales_caras_pares.size(); ++i){
		A = this->vertices[ caras_pares[i][0] ];
		B = this->vertices[ caras_pares[i][1] ];
		C = this->vertices[ caras_pares[i][2] ];

		origen[0] = (A[0] + B[0] + C[0]) / 3;
		origen[1] = (A[1] + B[1] + C[1]) / 3;
		origen[2] = (A[2] + B[2] + C[2]) / 3;

		extremo =  origen + ( this->normales_caras_pares[i] * DIM_NORMALES );

		DibujarLinea(origen, extremo, color, ancho);
	}

	for (unsigned int i = 0; i < this->normales_caras_impares.size(); ++i){
		A = this->vertices[ this->caras_impares[i][0] ];
		B = this->vertices[ this->caras_impares[i][1] ];
		C = this->vertices[ this->caras_impares[i][2] ];

		origen[0] = (A[0] + B[0] + C[0]) / 3;
		origen[1] = (A[1] + B[1] + C[1]) / 3;
		origen[2] = (A[2] + B[2] + C[2]) / 3;

		extremo = origen + ( this->normales_caras_impares[i] * DIM_NORMALES );

		DibujarLinea(origen, extremo, color, ancho);
	}
}

void Malla_TVT::Conmutar_NormalesVertices(){
	visualizar_normales_vert += 1;
	visualizar_normales_vert %= 2;
}

void Malla_TVT::Conmutar_NormalesCaras(){
	visualizar_normales_caras += 1;
	visualizar_normales_caras %= 2;
}


void DibujarLinea(Tupla3f ori, Tupla3f fin, Tupla3f color, float ancho){
	CError();

	// Ajustes iniciales
	glColor3f(color[0], color[1], color[2]);
	glLineWidth(ancho);

	// especificar modo de visualizacion
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBegin(GL_LINES);
		glVertex3fv( ori.get_ptr() );
		glVertex3fv( fin.get_ptr() );
	glEnd();

	CError();
}
