#ifndef IG_FUENTE_LUZ_HPP
#define IG_FUENTE_LUZ_HPP

#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>

#include "tipos.hpp"
#include "tuplas.hpp"
#include "error-ogl.hpp"

class FuenteLuz{
private:
    static bool luz_ocupada[8];

    GLuint id_luz;   //GL_LIGHT0, GL_LIGHT1, ..., GL_LIGHT7
    enum tipo_luz tipo;

    Tupla4f  posvec;       // posición (w=1) o vector (w=0)
    float alpha, beta;     // ángulos de rotación (fuente direccional modificable interactivamente)

    Tupla4f  colores[3];   // colores: 0=ambiental, 1=difuso, 2=especular.

    void activar_direccion_polares();

public:

    FuenteLuz(unsigned int id, enum tipo_luz tipo, Tupla4f vec,
                Tupla4f ambiental = Tupla4f(1.0, 1.0, 1.0, 1.0),
                Tupla4f difuso = Tupla4f(1.0, 1.0, 1.0, 1.0),
                Tupla4f especular = Tupla4f(1.0, 1.0, 1.0, 1.0)
             );

    void activar();
    void desactivar();

    void set_direccion( float alpha, float beta );
    void modificar_direccion( float alpha, float beta );

};

#endif
