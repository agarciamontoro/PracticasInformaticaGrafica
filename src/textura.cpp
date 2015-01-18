#include "textura.hpp"


Textura::Textura(char* img_text, enum modo_text modo, Tupla4f cs, Tupla4f ct){
    CError();

    glEnable( GL_TEXTURE_2D );

    // cargar la imagen
    this->img = new jpg::Imagen(img_text);

    //Ajustar el modo
    this->mgct = modo;

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

    this->cs = cs;
    this->ct = ct;

    glDisable( GL_TEXTURE_2D );

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

enum modo_text Textura::activar(){
    CError();

    //Activamos el modo de textura y la textura actual
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, this->id_text );

    //Definimos el tipo de generación de coordenadas según mgct
    GLuint tipo_funcion_generacion, tipo_especificacion_coeficientes;

    switch( this->mgct ){
        case OBJETO:
            tipo_funcion_generacion             = GL_OBJECT_LINEAR;
            tipo_especificacion_coeficientes    = GL_OBJECT_PLANE;
            break;

        case CAMARA:
            tipo_funcion_generacion             = GL_EYE_LINEAR;
            tipo_especificacion_coeficientes    = GL_EYE_PLANE;
            break;

        default:
            break;
    }

    //Configuramos la textura con la definición anterior
    if( this->mgct != DESACTIVADO ){
        glEnable( GL_TEXTURE_GEN_S );
        glEnable( GL_TEXTURE_GEN_T );

        glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, tipo_funcion_generacion );
        glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, tipo_funcion_generacion );

        glTexGenfv( GL_S, tipo_especificacion_coeficientes, this->cs.get_ptr() );
        glTexGenfv( GL_T, tipo_especificacion_coeficientes, this->ct.get_ptr() );
    }
    else{
        glDisable( GL_TEXTURE_GEN_S );
        glDisable( GL_TEXTURE_GEN_T );
    }

    CError();

    return this->mgct;
}
