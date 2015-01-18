#include "material.hpp"

Material::Material(Tupla3f emision, Tupla3f ambiental, Tupla3f difuso, Tupla3f especular, float exponente, Textura* textura){
    this->textura   = textura;
    this->color[0]  = emision;
    this->color[1]  = ambiental;
    this->color[2]  = difuso;
    this->color[3]  = especular;
    this->exponente = exponente;
}

void Material::activar(){
    glEnable(GL_LIGHTING);

    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION,  this->color[0].get_ptr() );
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,   this->color[1].get_ptr() );
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,   this->color[2].get_ptr() );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,  this->color[3].get_ptr() );

    glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, &(this->exponente) ) ;

    if( hayTextura() ){
        textura->activar();
    }
    else{
        glDisable( GL_TEXTURE_2D );
    }
}

bool Material::hayTextura(){
    return this->textura != NULL;
}
