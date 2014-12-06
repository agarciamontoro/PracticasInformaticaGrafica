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
	this->VBO_vertices			=	VBO_Vertices( vertices );
}

void Malla_TVT::GenerarVBO_caras(){
	this->VBO_caras				=	VBO_Caras( caras );
}

void Malla_TVT::GenerarVBO_normales_vertices(){
	this->VBO_normales_vertices	=	VBO_Normales( normales_vertices );
}

void Malla_TVT::GenerarVBO_normales_caras(){
	this->VBO_normales_caras	=	VBO_Normales( normales_caras );
}

void Malla_TVT::GenerarVBO_colores_vertices(){
	this->VBO_colores_vertices	=	VBO_Colores( colores_vertices );
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

	std::vector<Tupla3i>::iterator principio;

	// lectura del archivo PLY
	if(lec == TODO){
		ply::read(archivo_PLY, vertices_raw, caras_raw);
	}
	else
		ply::read_vertices(archivo_PLY, vertices_raw);

		// Para su mejor gestión, organizamos vértices y caras en vectores de Tuplas
		for (unsigned int i = 0; i < vertices_raw.size(); i += 3){
			this->vertices.push_back( Tupla3f(vertices_raw[i+0], vertices_raw[i+1], vertices_raw[i+2]) );
		}

		if(lec == TODO){
			// Separamos las cares pares e impares de manera que las pares estén al principio y las impares al final,
			//para gestionar de forma eficiente el modo ajedrez
			for (unsigned int i = 0; i < caras_raw.size(); i += 6){
				this->caras.push_back( Tupla3i(caras_raw[i+0], caras_raw[i+1], caras_raw[i+2]) );

				principio = this->caras.begin();
				this->caras.insert( principio, Tupla3i(caras_raw[i+3], caras_raw[i+4], caras_raw[i+5]) );
			}
		}

		// TODO: Implementar una gestión de errores al leer/procesar los datos.
		// En caso de encontrarlos, devolver false.
		return true;
}

void Malla_TVT::cambiar_color(Tupla3f color){
	glColor3f(color[0], color[1], color[2]);
}

Malla_TVT::Malla_TVT( char* archivo_PLY,
					  enum modo_lectura lec,
					  Tupla3f color_principal_t,
					  Tupla3f color_secundario_t,
					  enum modo_visualizacion visualizacion_t)
{
	LeerPLY(archivo_PLY, lec);
	CalcularNormales();
	AsignarColoresVert();
	GenerarVBO_TODO();
	this->color_principal = color_principal_t;
	this->color_secundario = color_secundario_t;
	set_visualizacion(visualizacion_t);
}

Malla_TVT::Malla_TVT(std::vector<Tupla3f> vertices, std::vector<Tupla3i> caras){
	this->vertices = vertices;

	std::vector<Tupla3i>::iterator principio;

	for(unsigned int i = 0; i < caras.size(); i += 2){
		this->caras.push_back( caras[i] );

		principio = this->caras.begin();
		this->caras.insert( principio, caras[i+1] );
	}

	CalcularNormales();
	AsignarColoresVert();
	GenerarVBO_TODO();
}

Malla_TVT::Malla_TVT(const Malla_TVT& original){
	if( this != &original ){
		this->vertices = original.vertices;
		this->caras = original.caras;

		this->color_principal = original.color_principal;
		this->color_secundario = original.color_secundario;

		set_visualizacion(original.visualizacion_actual);

		this->VBO_vertices = VBO_Vertices( this->vertices );
		this->VBO_caras = VBO_Caras( this->caras );
	}
}

const Malla_TVT& Malla_TVT::operator=(const Malla_TVT& original){
	if( this != &original ){
		this->vertices = original.vertices;
		this->caras = original.caras;
		this->normales_caras = original.normales_caras;
		this->normales_vertices = original.normales_vertices;
		this->colores_vertices = original.colores_vertices;

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

Malla_TVT Malla_TVT::GenerarSolidoRevolucion(int num_caras){
	///////////////////////////
	// Variables necesarias //
	///////////////////////////

	//Ángulo de rotación entre perfiles
	float angulo = 2*M_PI / num_caras;
	float c = cosf(angulo);
	float s = sinf(angulo);

	//Matriz de rotacion
	float mat[3][3] = {
		{c,0,s},
		{0,1,0},
		{-s,0,c}
	};
	Matriz3x3f matriz_rotacion(mat);

	std::vector<Tupla3f> vert_rev;
	std::vector<Tupla3i> caras_rev;

	///////////////////////
	// Preprocesamiento //
	///////////////////////

	//Inicializamos los vértices con los que ya tenemos
	vert_rev = this->vertices;

	//Procesamos el perfil para que el primer y último vértice no se repitan
	//durante la rotación y para asegurarnos de que tienen coordenada X = 0

	//Vértices que deben ser tratados por separado
	Tupla3f primer_vertice, ultimo_vertice;
	primer_vertice = vert_rev.front();
	ultimo_vertice = vert_rev.back();

	//Si el primer(resp. último) vértice tiene coordenada X = 0,
	//se borra del vector original. Si no, se actualiza primer_vertice
	//(resp. ultimo_vertice) poniendo a cero la componente X.
	if( primer_vertice[0] != 0.0 ){
		primer_vertice[0] = 0.0;
	}
	else{
		vert_rev.erase( vert_rev.begin() );
	}

	if( ultimo_vertice[0] != 0.0){
		ultimo_vertice[0] = 0.0;
	}
	else{
		vert_rev.pop_back();
	}


	//////////////////////////////////////
	//  Generación de vértices y caras //
	//////////////////////////////////////

	//Variables para el bucle
	unsigned int num_vert = vert_rev.size();
	std::vector<Tupla3f> perfil_anterior, perfil_actual;
	Tupla3f vert_rotado;
	Tupla3i cara_par, cara_impar;

	//Primera iteración del siguiente bucle antes del mismo
	perfil_anterior = vert_rev;

	//Bucle de generación de todos los perfiles
	for (int i = 1; i < num_caras; ++i){

		//Primera iteración del siguiente bucle antes del mismo
		vert_rotado = toTupla(matriz_rotacion * perfil_anterior[0]);
		perfil_actual.push_back( vert_rotado );
		vert_rev.push_back( vert_rotado );

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
			vert_rev.push_back( vert_rotado );
			caras_rev.push_back( cara_par );
			caras_rev.push_back( cara_impar );

		} //Fin de generación de vértices para el perfil i

		//Actualización de las variables del bucle
		perfil_anterior = perfil_actual;
		perfil_actual.clear();

	} //Fin de generación de perfiles

	//Generación de la última cara
	for (unsigned int j = 1; j < num_vert; ++j){
		//Generación de caras
		cara_par 	= Tupla3i(	num_vert * (num_caras-1) + j,
								num_vert * (num_caras-1) + (j-1),
								num_vert * (0) + (j-1)
							);
		cara_impar 	= Tupla3i(	num_vert * (num_caras-1) + j,
								num_vert * (0) + (j-1),
								num_vert * (0) + j
							);


		caras_rev.push_back( cara_par );
		caras_rev.push_back( cara_impar );

	} //Fin de generación de la última cara

	///////////////////////////
	//  Generación de tapas //
	///////////////////////////

	Tupla3i cara;

		////////////////////
		// Tapa inferior //
		////////////////////

	vert_rev.push_back(primer_vertice);

	int indice_centro_tapa_inferior = vert_rev.size()-1;

	for (int i = 0; i < num_caras-1; ++i)
	{
		cara = Tupla3i(	num_vert * (i),
						indice_centro_tapa_inferior,
						num_vert * (i+1) );

		caras_rev.push_back( cara );
	}

	// Última cara de la tapa inferior
	cara = Tupla3i(	num_vert * (num_caras-1),
					indice_centro_tapa_inferior,
					0 );

	caras_rev.push_back( cara );

		////////////////////
		// Tapa superior //
		////////////////////

	vert_rev.push_back(ultimo_vertice);

	int indice_centro_tapa_superior = vert_rev.size()-1;

	for (int i = 0; i < num_caras-1; ++i)
	{
		cara = Tupla3i(	num_vert * (i+1) + (num_vert - 1),
						indice_centro_tapa_superior,
						num_vert * (i) + (num_vert - 1) );

		caras_rev.push_back( cara );
	}

	// Última cara de la tapa superior
	cara = Tupla3i(	num_vert - 1,
					indice_centro_tapa_superior,
					num_vert * (num_caras-1)  + (num_vert - 1) );

	caras_rev.push_back( cara );

	//////////////////////////
	// Generación de la nueva malla //
	//////////////////////////

	Malla_TVT solido_revolucion( vert_rev, caras_rev );

	//////////////////////////
	// Asignar colores a los vértices //
	//////////////////////////

	solido_revolucion.AsignarColoresVert();

	return solido_revolucion;
}

void Malla_TVT::CalcularNormalesCaras(){
	Tupla3f A, B, C, AB, BC, normal;

	this->normales_caras.resize( caras.size() );

	for (unsigned int i = 0; i < caras.size(); ++i)
	{
		A = this->vertices[ caras[i][0] ];
		B = this->vertices[ caras[i][1] ];
		C = this->vertices[ caras[i][2] ];

		AB = B - A;
		BC = C - B;

		normal = AB * BC; //Producto vectorial

		this->normales_caras[i] = normal.normalized();
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

	for (unsigned int i = 0; i < this->normales_caras.size(); ++i){

		for (int j = 0; j < 3; ++j){
			int indice = this->caras[i][j];

			this->normales_vertices[indice] += this->normales_caras[i];
		}
	}

	for (unsigned int i = 0; i < this->normales_vertices.size(); ++i){
		this->normales_vertices[i] = this->normales_vertices[i].normalized();
	}
}

void Malla_TVT::CalcularNormales(){
	CalcularNormalesCaras();
	CalcularNormalesVertices();
}

void Malla_TVT::AsignarColores( std::vector<Tupla3f> colores ){
	assert( colores.size() == this->vertices.size() );
	this->colores_vertices = colores;
	GenerarVBO_colores_vertices();
}

void Malla_TVT::AsignarColoresVert(){
	//Construimos el vector de colores con respecto al de normales de vértices
	std::vector<Tupla3f> colores_vertices;
	colores_vertices.resize( this->vertices.size() );

	for(size_t i = 0; i < colores_vertices.size(); i++){
		colores_vertices[i] =  this->vertices[i].abs();
	}

	this->AsignarColores( colores_vertices );
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
	glShadeModel(GL_SMOOTH);

	//////////////////////
	// Enviar atributos //
	//////////////////////

	bool normales_activadas, colores_activados;

	normales_activadas = VBO_normales_vertices.Activar();

	if( visualizacion_actual != AJEDREZ ){
		colores_activados = VBO_colores_vertices.Activar();
	}
	else{
		colores_activados = false;
	}

	//////////////////////
	// Enviar vértices //
	//////////////////////

	VBO_vertices.Activar();

	///////////////////////
	// Visualizar caras //
	///////////////////////

	VBO_caras.Dibujar(visualizacion_actual, this->color_secundario);

	//////////////////////
	// Ajustes finales //
	//////////////////////

	// desactivar uso de array de normales
	if ( normales_activadas ){
		glDisableClientState( GL_NORMAL_ARRAY );
	}

	// desactivar uso de array de colores
	if( colores_activados ){
		glDisableClientState( GL_COLOR_ARRAY );
	}

	// desactivar uso de array de vértices
	glDisableClientState( GL_VERTEX_ARRAY );

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

	for (unsigned int i = 0; i < this->normales_caras.size(); ++i){
		A = this->vertices[ caras[i][0] ];
		B = this->vertices[ caras[i][1] ];
		C = this->vertices[ caras[i][2] ];

		origen[0] = (A[0] + B[0] + C[0]) / 3;
		origen[1] = (A[1] + B[1] + C[1]) / 3;
		origen[2] = (A[2] + B[2] + C[2]) / 3;

		extremo =  origen + ( this->normales_caras[i] * DIM_NORMALES );

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
