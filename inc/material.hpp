#ifndef IG_MATERIAL_HPP
#define IG_MATERIAL_HPP

#include <GL/glew.h>
#include <GL/glut.h>

#include "tuplas.hpp"
#include "textura.hpp"

class Material{
private:
    Textura * textura = NULL;  // puntero a la textura (NULL si no hay)
    Tupla4f   color[4] ;    // colores: 0=emisión, 1=ambiental, 2=difuso, 3=especular
    float     exponente ;   // exponente para la componente pseudo-especular

public:
    Material(Tupla4f emision, Tupla4f ambiental, Tupla4f difuso, Tupla4f especular, float exponente, Textura* textura = NULL);

    void activar();       // activa material en el cauce fijo
    bool hayTextura();
} ;

#endif
