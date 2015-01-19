#include "fuente_luz.hpp"

GLuint equivalencia[8] = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};

//DEFINICIÓN DEL ATRIBUTO ESTÁTICO
bool FuenteLuz::luz_ocupada[8] = {false};

FuenteLuz::FuenteLuz(unsigned int id, enum tipo_luz tipo, Tupla4f vec, Tupla4f ambiental, Tupla4f difuso, Tupla4f especular){
    assert(id >= 0 && id <= 7);
    assert(luz_ocupada[id] == false);
    assert(vec[W] == 0 || vec[W] == 1);

    luz_ocupada[id] = true;

    this->id_luz = equivalencia[id];

    this->colores[0] = ambiental;
    this->colores[1] = difuso;
    this->colores[2] = especular;

    this->alpha = 0;
    this->beta  = 0;

    this->posvec = vec;

    this->tipo = tipo;
}

void FuenteLuz::activar(){
    CError();

    glEnable(this->id_luz); // activa evaluacion de la luz GL_LIGHT<id_luz>

    if( this->tipo == DIRECCIONAL )
        activar_direccion_polares();
    else
        glLightfv( this->id_luz, GL_POSITION, this->posvec.get_ptr() );

    glLightfv( this->id_luz, GL_AMBIENT,  this->colores[0].get_ptr() ); // hace SiA := (ra, ga, ba)
    glLightfv( this->id_luz, GL_DIFFUSE,  this->colores[1].get_ptr() ); // hace SiD := (rd, gd, bd)
    glLightfv( this->id_luz, GL_SPECULAR, this->colores[2].get_ptr() ); // hace SiS := (rs, gs, bs)


    CError();
}

void FuenteLuz::desactivar(){
    glDisable(this->id_luz);
}

void FuenteLuz::set_direccion( float alpha, float beta ){
    this->alpha = alpha;
    this->beta  = beta;
}


void FuenteLuz::modificar_direccion( float alpha, float beta ){
    set_direccion(this->alpha + alpha, this->beta + beta);
}

void FuenteLuz::activar_direccion_polares(){
    Tupla4f ejeZ(cosf(alpha)*sinf(beta),sinf(alpha)*sinf(beta),cosf(beta),0.0);
    glLightfv( this->id_luz, GL_POSITION, ejeZ.get_ptr() );//(1)hacer li:(0,0,1)(paral. eje Z+)
}
