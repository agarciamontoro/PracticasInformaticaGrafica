#include "textura.hpp"


Textura::Textura(char* img_text){

}

// ---------------------------------------------------------------------
//  Operador de asignación
const Textura& Textura::operator=(const Textura &original){

    this->id_text           = original.id_text;
    this->img               = original.img;
    this->mgct              = original.mgct;

    this->cs                = original.cs;
    this->ct                = original.ct;

    this->VBO_coord_textura = original.VBO_coord_textura;

    return *this;
}

void Textura::activar(){
    if( this->id_text == 0 )
        glGenTextures( 1, &(this->id_text) );

    glBindTexture( GL_TEXTURE_2D, this->id_text );
}
