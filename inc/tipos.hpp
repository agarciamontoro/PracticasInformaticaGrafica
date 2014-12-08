#ifndef IG_TIPOS_HPP
#define IG_TIPOS_HPP

enum modo_visualizacion{
   ALAMBRE,
   SOLIDO,
   AJEDREZ,
   PUNTO
};

enum modo_lectura{
   TODO,
   VERT
};

enum practicas{
    P1,
    P2,
    P3
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

#endif
