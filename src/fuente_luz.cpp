#include "fuente_luz.hpp"

//DEFINICIÓN DEL ATRIBUTO ESTÁTICO
bool FuenteLuz::luz_ocupada[8] = {false};

FuenteLuz::FuenteLuz(unsigned int id, enum tipo_luz tipo, Tupla4f vec, Tupla3f ambiental, Tupla3f difuso, Tupla3f especular){
    assert(id >= 0 && id <= 7);
    assert(luz_ocupada[id] == false);
    assert(vec[W] == 0 || vec[W] == 1);

    luz_ocupada[id] = true;

    this->id_luz = id;

    this->colores[0] = ambiental;
    this->colores[1] = difuso;
    this->colores[2] = especular;
}

void FuenteLuz::activar(){
    glEnable(id_luz); // activa evaluacion de la luz GL_LIGHT<id_luz>

    glLightfv( this->id_luz, GL_AMBIENT,  this->colores[0].get_ptr() ); // hace SiA := (ra, ga, ba)
    glLightfv( this->id_luz, GL_DIFFUSE,  this->colores[1].get_ptr() ); // hace SiD := (rd, gd, bd)
    glLightfv( this->id_luz, GL_SPECULAR, this->colores[2].get_ptr() ); // hace SiS := (rs, gs, bs)

    if( this->tipo == DIRECCIONAL )
        activar_direccion_polares();
    else
        glLightfv( this->id_luz, GL_POSITION, this->posvec.get_ptr() );

}

void FuenteLuz::activar_direccion_polares(){
    Tupla4f ejeZ = { 0.0, 0.0, 1.0, 0.0 };

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
        glLoadIdentity(); // hacer M = Ide

        glRotatef( this->alpha, 0.0, 1.0, 0.0 ); // (3) rotación alpha grados en torno a eje Y
        glRotatef( this->beta, -1.0, 0.0, 0.0 ); // (2) rotación β grados en torno al eje X

        glLightfv( this->id_luz, GL_POSITION, ejeZ.get_ptr() );// (1) hacer li:= (0, 0, 1) (paralela eje Z+)
    glPopMatrix() ;
}
