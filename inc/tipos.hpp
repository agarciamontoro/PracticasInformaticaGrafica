#ifndef IG_TIPOS_HPP
#define IG_TIPOS_HPP

enum modo_visualizacion{
   ALAMBRE,
   SOLIDO,
   AJEDREZ,
   PUNTO,
   ILUM_PLANO,
   ILUM_GOUROUD
};

enum modo_text{
    DESACTIVADO,
    OBJETO,
    CAMARA
};

enum tipo_luz{
    POSICIONAL,
    DIRECCIONAL
};

enum modo_lectura{
   TODO,
   VERT
};

enum practicas{
    P1,
    P2,
    P3,
    P4
};

enum coord{
    X = 0,
    Y = 1,
    Z = 2,
    W = 3
};

enum solidos_GLUT{
    ESFERA,
    CUBO,
    CONO,
    TORO,
    DODECAEDRO,
    OCTAEDRO,
    TETRAEDRO,
    ICOSAEDRO,
    TETERA
};

enum grados_libertad{
    CABEZA,
    OJO,
    ARMAS
};

#endif
