#ifndef IG_TEXTURA_HPP
#define IG_TEXTURA_HPP

#include <GL/glew.h>
#include <GL/glut.h>

#include "tipos.hpp"
#include "tuplas.hpp"
#include "VBO.hpp"
#include "jpg_imagen.hpp"

#include "error-ogl.hpp"

class Textura{
private:
    GLuint          id_text = 0;    // identificador OpenGL de la textura
    jpg::Imagen*    img = NULL; // puntero a imagen con los texels
    enum modo_text  mgct;       // modo de gen. cc.tt. (0 = desactivado, 1 = objeto, 2 = camara)

    Tupla4f         cs,         // coeficientes para generación de coords. de textura
                    ct;

public:
    Textura(){}

    Textura(char* img_text,
            enum modo_text modo = DESACTIVADO,
            Tupla4f cs = Tupla4f(1.0, 0.0, 0.0, 0.0),
            Tupla4f ct = Tupla4f(0.0, 1.0, 0.0, 0.0)
            );

    enum modo_text activar();          // activa textura en el cauce fijo

    // ---------------------------------------------------------------------
    //  Operador de asignación
    const Textura& operator=(const Textura &original);

};

#endif
