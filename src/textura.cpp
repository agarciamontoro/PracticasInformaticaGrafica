#include "textura.hpp"


Textura::Textura(char* img_text){
    // cargar la imagen
    img = new jpg::Imagen(img_text);

    // Asignar identificador de textura
    glGenTextures( 1, &(this->id_text) );

    // Enviar texels a GPU
    gluBuild2DMipmaps(
    GL_TEXTURE_2D,
        GL_RGB,             // formato interno
        img->tamX(),        // núm. de columnas (arbitrario) (GLsizei)
        img->tamY(),        // núm de filas (arbitrario) (GLsizei)
        GL_RGB,             // formato y orden de los texels en RAM
        GL_UNSIGNED_BYTE,   // tipo de cada componente de cada texel
        img->leerPixels()   // puntero a los bytes con texels (void *)
    );
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
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, this->id_text );
}
