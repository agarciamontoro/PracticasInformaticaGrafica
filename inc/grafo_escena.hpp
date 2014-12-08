#ifndef IG_GRAFO_ESCENA_HPP
#define IG_GRAFO_ESCENA_HPP

#include <vector>
#include <iostream>
#include "Matriz.hpp"
#include "Malla_TVT.hpp"

//--------------------INTERFAZ-----------------------//

class Celda_NGE{
public:
    virtual ~Celda_NGE() {};
    virtual void procesar(){};
};

//----------------------NODO-------------------------//

typedef std::vector<Celda_NGE*> lista_celdas;

class Nodo{
private:
    lista_celdas escena;

public:
    void visualizar();

    const Celda_NGE* operator[](unsigned int i) const{ return this->escena[i]; };
    Celda_NGE* operator[](unsigned int i){ return this->escena[i]; };

    void push_back(Celda_NGE* celda){ escena.push_back(celda); };
    void pop_back(){ escena.pop_back(); };
};

//---------------------HIJOS-------------------------//

class Celda_Nodo : public Celda_NGE{
private:
    Nodo hijo;

public:
    Celda_Nodo(Nodo hijo_);
    virtual void procesar();
};

//---------------------------------------------------//

class Celda_Transformacion : public Celda_NGE{
private:
    Matriz4x4f matriz;

public:
    Celda_Transformacion(Matriz4x4f matriz_);
    virtual void procesar();
};

//-----------------OBJETOS SIMPLES--------------------//

class Celda_Malla : public Celda_NGE{
private:
    Malla_TVT malla;

public:
    Celda_Malla(Malla_TVT malla);
    virtual void procesar();
};

//---------------------------------------------------//

class Celda_SolidoGLUT : public Celda_NGE{
private:
    enum solidos_GLUT solido;

public:
    ~Celda_SolidoGLUT(){}
    Celda_SolidoGLUT(enum solidos_GLUT solido);
    virtual void procesar();
};

#endif
