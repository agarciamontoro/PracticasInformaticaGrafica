#include <vector>
#include <assert.h>
#include <cmath> //Uso de M_PI
#include <iostream>
#include "tuplas.hpp"

#include "Matriz.hpp"

template <unsigned int ROWS, unsigned int COLS, class T>
Matriz<ROWS,COLS,T>::Matriz( T val_inicial ){
   for ( unsigned int i = 0; i < ROWS; ++i)
   {
      for ( unsigned int j = 0; j < COLS; ++j)
      {
         this->matriz[i][j] = val_inicial;
      }
   }
}

template <unsigned int ROWS, unsigned int COLS, class T>
Matriz<ROWS,COLS,T>::Matriz( const T datos[ROWS][COLS]){
   for ( unsigned int i = 0; i < ROWS; ++i)
   {
      for ( unsigned int j = 0; j < COLS; ++j)
      {
         this->matriz[i][j] = datos[i][j];
      }
   }
}


template <unsigned int ROWS, unsigned int COLS, class T>
Matriz<ROWS,COLS,T>::Matriz( const std::vector< std::vector<T> >& datos){
   assert(datos.size() == ROWS);

   for ( unsigned int i = 0; i < datos.size(); ++i){
      assert(datos[i].size() == COLS);

      for ( unsigned int j = 0; j < datos[i].size(); ++j){
         this->matriz[i][j] = datos[i][j];
      }
   }

}

template <unsigned int ROWS, unsigned int COLS, class T>
const T* Matriz<ROWS,COLS,T>::operator[](unsigned int i) const{
   assert(i >= 0 && i < ROWS);

   return this->matriz[i];
}

template <unsigned int ROWS, unsigned int COLS, class T>
T* Matriz<ROWS,COLS,T>::operator[](unsigned int i){
   assert(i >= 0 && i < ROWS);

   return this->matriz[i];
}

template<unsigned int ROWS , unsigned int COLS, class T>
T* Matriz<ROWS,COLS,T>::data(){
    return matriz[0];
}

// ---------------------------------------------------------------------
//  Operador de asignación
template <unsigned int ROWS, unsigned int COLS, class T>
const Matriz<ROWS,COLS,T>& Matriz<ROWS,COLS,T>::operator=(const Matriz<ROWS,COLS,T> &original){
   for ( unsigned int i = 0; i < ROWS; ++i)
   {
      for ( unsigned int j = 0; j < COLS; ++j)
      {
         this->matriz[i][j] = original[i][j];
      }
   }

   return *this;
}

// ---------------------------------------------------------------------
// matriz = matriz+matriz
template <unsigned int ROWS, unsigned int COLS, class T>
Matriz<ROWS,COLS,T> Matriz<ROWS,COLS,T>::operator + ( const Matriz<ROWS,COLS,T> & m1 ){
   Matriz<ROWS,COLS,T> resultado;

   for ( unsigned int i = 0; i < ROWS; ++i)
   {
      for ( unsigned int j = 0; j < COLS; ++j)
      {
         resultado[i][j] = this->matriz[i][j] + m1[i][j];
      }
   }

   return resultado;
}

// ---------------------------------------------------------------------
// matriz = matriz-matriz
template <unsigned int ROWS, unsigned int COLS, class T>
Matriz<ROWS,COLS,T> Matriz<ROWS,COLS,T>::operator - ( const Matriz<ROWS,COLS,T> & m1 ){
   Matriz<ROWS,COLS,T> resultado;

   for ( unsigned int i = 0; i < ROWS; ++i)
   {
      for ( unsigned int j = 0; j < COLS; ++j)
      {
         resultado[i][j] = this->matriz[i][j] - m1[i][j];
      }
   }

   return resultado;
}

// ---------------------------------------------------------------------
// matriz = matriz*float
template <unsigned int ROWS, unsigned int COLS, class T>
Matriz<ROWS,COLS,T> Matriz<ROWS,COLS,T>::operator * ( float a ){
   Matriz<ROWS,COLS,T> resultado;

   for ( unsigned int i = 0; i < ROWS; ++i)
   {
      for ( unsigned int j = 0; j < COLS; ++j)
      {
         resultado[i][j] = this->matriz[i][j] * a;
      }
   }

   return resultado;
}

// ---------------------------------------------------------------------
// matriz = matriz/float
template <unsigned int ROWS, unsigned int COLS, class T>
Matriz<ROWS,COLS,T> Matriz<ROWS,COLS,T>::operator / ( float a ) const{
   Matriz<ROWS,COLS,T> resultado;

   for ( unsigned int i = 0; i < ROWS; ++i)
   {
      for ( unsigned int j = 0; j < COLS; ++j)
      {
         resultado[i][j] = this->matriz[i][j] / a;
      }
   }

   return resultado;
}

// ---------------------------------------------------------------------
//  = matriz*tupla (producto matriz tupla)
template <unsigned int ROWS, unsigned int COLS, class T>
Matriz<ROWS,1,T> Matriz<ROWS,COLS,T>::operator * ( const Tupla<COLS,T> & t1 ){
   std::vector< std::vector<T> > vector_tras;

   for ( unsigned int i = 0; i < ROWS; ++i)
   {
      vector_tras.push_back(std::vector<T>());
      vector_tras[i].push_back(t1[i]);
   }

   Matriz<COLS,1,T> vector_mat = Matriz<COLS,1,T>(vector_tras);

   return *this * vector_mat;
}

// ---------------------------------------------------------------------
//  = tupla*matriz (producto tupla matriz)
template <unsigned int ROWS, unsigned int COLS, class T>
Matriz<1,COLS,T> operator * ( const Tupla<COLS,T> & t1, const Matriz<ROWS,COLS,T> & m1 ){
   std::vector< std::vector<T> > vector_tras;

   vector_tras.push_back(std::vector<T>());

   for ( unsigned int i = 0; i < ROWS; ++i)
   {
      vector_tras[0].push_back(t1[i]);
   }

   Matriz<COLS,1,T> vector_mat = Matriz<COLS,1,T>(vector_tras);

   return vector_mat * m1;
}

//----------------------------------------------------------------------
//                   ESPECIALIZACIONES
//----------------------------------------------------------------------
// Posibles especializaciones. Tienen que declararse aquí para que el
// compilador sea capaz de enlazar sus definiciones luego.

template class Matriz<1,1,float>;

template class Matriz<3,1,float>;
template class Matriz<1,3,float>;
template class Matriz<3,3,float>;

template class Matriz<4,1,float>;
template class Matriz<1,4,float>;
template class Matriz<4,4,float>;

////////////////////////////
//     Clases   hijas     //
////////////////////////////

Matriz_Rotacion::Matriz_Rotacion(float angulo, enum coord eje){
    assert( eje != W );
    this->angulo    = angulo;
    this->eje       = eje;

    float c = cosf( angulo );
    float s = sinf( angulo );

    switch( eje ){
        case X:
            matriz[0][0] = 1; matriz[1][0] = 0; matriz[2][0] = 0;  matriz[3][0] = 0;
            matriz[0][1] = 0; matriz[1][1] = c; matriz[2][1] = -s; matriz[3][1] = 0;
            matriz[0][2] = 0; matriz[1][2] = s; matriz[2][2] = c;  matriz[3][2] = 0;
            matriz[0][3] = 0; matriz[1][3] = 0; matriz[2][3] = 0;  matriz[3][3] = 1;
            break;

        case Y:
            matriz[0][0] = c;  matriz[1][0] = 0; matriz[2][0] = s; matriz[3][0] = 0;
            matriz[0][1] = 0;  matriz[1][1] = 1; matriz[2][1] = 0; matriz[3][1] = 0;
            matriz[0][2] = -s; matriz[1][2] = 0; matriz[2][2] = c; matriz[3][2] = 0;
            matriz[0][3] = 0;  matriz[1][3] = 0; matriz[2][3] = 0; matriz[3][3] = 1;
            break;

        case Z:
            matriz[0][0] = c; matriz[1][0] = -s; matriz[2][0] = 0; matriz[3][0] = 0;
            matriz[0][1] = s; matriz[1][1] = c;  matriz[2][1] = 0; matriz[3][1] = 0;
            matriz[0][2] = 0; matriz[1][2] = 0;  matriz[2][2] = 1; matriz[3][2] = 0;
            matriz[0][3] = 0; matriz[1][3] = 0;  matriz[2][3] = 0; matriz[3][3] = 1;
            break;

        default:
            break;
    }

}

float Matriz_Rotacion::get_angulo(){
    return this->angulo;
}

void Matriz_Rotacion::set_angulo(float angulo){
    if( this->angulo != angulo)
        *this = Matriz_Rotacion(angulo, this->eje);
}

enum coord Matriz_Rotacion::get_eje(){
    return this->eje;
}
void Matriz_Rotacion::set_eje(enum coord eje){
    if( this->eje != eje)
        *this = Matriz_Rotacion(this->angulo, eje);
}





void Matriz_Traslacion::Inicializar( Tupla3f direccion ){
    this->direccion = direccion;

    matriz[0][0] = 1; matriz[1][0] = 0; matriz[2][0] = 0; matriz[3][0] = direccion[0];
    matriz[0][1] = 0; matriz[1][1] = 1; matriz[2][1] = 0; matriz[3][1] = direccion[1];
    matriz[0][2] = 0; matriz[1][2] = 0; matriz[2][2] = 1; matriz[3][2] = direccion[2];
    matriz[0][3] = 0; matriz[1][3] = 0; matriz[2][3] = 0; matriz[3][3] = 1;
}

Tupla3f Matriz_Traslacion::get_direccion(){
    return this->direccion;
}

void Matriz_Traslacion::set_direccion( Tupla3f direccion ){
    if( this->direccion != direccion){
        *this = Matriz_Traslacion(direccion);
    }
}

void Matriz_Traslacion::set_direccion( float dir_x, float dir_y, float dir_z ){
    this->set_direccion( Tupla3f(dir_x, dir_y, dir_z) );
}





void Matriz_Escalado::Inicializar( Tupla3f escala ){
    this->escala = escala;

    float x,y,z;

    x = escala[0]; y = escala[1]; z = escala[2];

    matriz[0][0] = x; matriz[1][0] = 0; matriz[2][0] = 0; matriz[3][0] = 0;
    matriz[0][1] = 0; matriz[1][1] = y; matriz[2][1] = 0; matriz[3][1] = 0;
    matriz[0][2] = 0; matriz[1][2] = 0; matriz[2][2] = z; matriz[3][2] = 0;
    matriz[0][3] = 0; matriz[1][3] = 0; matriz[2][3] = 0; matriz[3][3] = 1;

}

Tupla3f Matriz_Escalado::get_escala(){
    return this->escala;
}

void Matriz_Escalado::set_escala( Tupla3f escala ){
    if( this->escala != escala ){
        *this = Matriz_Escalado(escala);
    }
}
void Matriz_Escalado::set_escala( float esc_x, float esc_y, float esc_z ){
    Tupla3f esc = Tupla3f(esc_x, esc_y, esc_z);

    this->set_escala(esc);
}





void Matriz_Cizalla::Inicializar( float sesgo, ParCoord eje ){
    this->sesgo = sesgo;

    matriz[0][0] = 1; matriz[1][0] = 0; matriz[2][0] = 0; matriz[3][0] = 0;
    matriz[0][1] = 0; matriz[1][1] = 1; matriz[2][1] = 0; matriz[3][1] = 0;
    matriz[0][2] = 0; matriz[1][2] = 0; matriz[2][2] = 1; matriz[3][2] = 0;
    matriz[0][3] = 0; matriz[1][3] = 0; matriz[2][3] = 0; matriz[3][3] = 1;

    matriz[eje.first][eje.second] = sesgo;
}

float Matriz_Cizalla::get_sesgo(){
    return this->sesgo;
}

void Matriz_Cizalla::set_sesgo( float sesgo ){
    if( this->sesgo != sesgo ){
        *this = Matriz_Cizalla(sesgo, this->eje);
    }
}

ParCoord Matriz_Cizalla::get_eje(){
    return this->eje;
}

void Matriz_Cizalla::set_eje( ParCoord eje ){
    if( this->eje != eje ){
        *this = Matriz_Cizalla(this->sesgo, eje);
    }
}
void Matriz_Cizalla::set_eje( enum coord eje_1, enum coord eje_2 ){
    this->set_eje( ParCoord(eje_1, eje_2) );
}
