#include "textura.hpp"


Textura::Textura(char* img_text){
    CError();

    glEnable( GL_TEXTURE_2D );

    // cargar la imagen
    img = new jpg::Imagen(img_text);

    // Asignar identificador de textura
    glGenTextures( 1, &(this->id_text) );
    glBindTexture( GL_TEXTURE_2D, this->id_text );

    // Crear mipmaps de textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    // Enviar texels a GPU
    glTexImage2D(
        GL_TEXTURE_2D,
        0, // nivel de mipmap (para imágenes multiresolución)
        GL_RGB, // formato interno
        img->tamX(), // núm. de columnas (potencia de dos: 2n) (GLsizei)
        img->tamY(), // núm de filas (potencia de dos: 2m) (GLsizei)
        0, // tamaño del borde, usualmente es 0
        GL_RGB, // formato y orden de los texels en RAM
        GL_UNSIGNED_BYTE,// tipo de cada componente de cada texel
        img->leerPixels() // puntero a los bytes con texels (void *)
    );
    glBindTexture(GL_TEXTURE_2D, 0);

    Tupla4f cs_(1.0, 0.0, 0.0, 0.0);
    Tupla4f ct_(0.0, 1.0, 0.0, 0.0);

    this->cs = cs_;
    this->ct = ct_;

    CError();
}

// ---------------------------------------------------------------------
//  Operador de asignación
const Textura& Textura::operator=(const Textura &original){
    CError();

    this->id_text           = original.id_text;
    this->img               = original.img;
    this->mgct              = original.mgct;

    this->cs                = original.cs;
    this->ct                = original.ct;

    CError();

    return *this;
}

void Textura::activar(){
    CError();

    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, this->id_text );

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);

    CError();
}
