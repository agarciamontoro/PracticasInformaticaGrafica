#include "grafo_escena.hpp"

//---------------------HIJOS-------------------------//

Celda_Nodo::Celda_Nodo(Nodo* hijo_){
    this->hijo = hijo_;
}

void Celda_Nodo::procesar(){
    hijo->visualizar();
}

//---------------------------------------------------//

Celda_Transformacion::Celda_Transformacion(Matriz4x4f* matriz_){
    this->matriz = matriz_;
}

void Celda_Transformacion::procesar(){
    glMultMatrixf(this->matriz->data());
}

//---------------------------------------------------//

Celda_Malla::Celda_Malla(Malla_TVT* malla_){
    this->malla = malla_;
}

void Celda_Malla::procesar(){
    malla->DibujarMalla_TVT();
}

//---------------------------------------------------//

Celda_SolidoGLUT::Celda_SolidoGLUT(enum solidos_GLUT solido_){
    this->solido = solido_;
}

void Celda_SolidoGLUT::procesar(){
    switch( this->solido ){
        case ESFERA:
            glutSolidSphere(1.0, 100, 100);
            break;

        case CUBO:
            glutSolidCube(1.0);
            break;

        case CONO:
            glutSolidCone(1.0, 2.0, 100, 100);
            break;

        case TORO:
            glutSolidTorus(1.0, 2.0, 100, 100);
            break;

        case DODECAEDRO:
            glutSolidDodecahedron();
            break;

        case OCTAEDRO:
            glutSolidOctahedron();
            break;

        case TETRAEDRO:
            glutSolidTetrahedron();
            break;

        case ICOSAEDRO:
            glutSolidIcosahedron();
            break;

        case TETERA:
            glutSolidTeapot(1.0);
            break;
    }
}

//---------------------------------------------------//

void Nodo::visualizar(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    for(size_t i = 0; i < this->escena.size(); i++)
    {
        escena[i]->procesar();
    }

    glPopMatrix();
}
