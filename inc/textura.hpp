#ifndef IG_TEXTURA_HPP
#define IG_TEXTURA_HPP

#include <GL/glew.h>
#include <GL/glut.h>

#include "tipos.hpp"
#include "tuplas.hpp"
#include "VBO.hpp"
#include "jpg_imagen.hpp"

class Textura{
private:
    GLuint          id_text;    // identificador OpenGL de la textura
    jpg::Imagen*    img = NULL; // puntero a imagen con los texels
    enum modo_text  mgct;       // modo de gen. cc.tt. (0 = desactivado, 1 = objeto, 2 = camara)

    Tupla4f         cs,         // coeficientes para generación de coords. de textura
                    ct;

    VBO_Textura     VBO_coord_textura;

public:
    Textura():
        id_text(0){}

    Textura(char* img_text);

    void activar();          // activa textura en el cauce fijo

    // ---------------------------------------------------------------------
    //  Operador de asignación
    const Textura& operator=(const Textura &original);

};

#endif
