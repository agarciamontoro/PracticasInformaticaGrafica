#include <vector>
#include <assert.h>
#include <cmath> //Uso de M_PI
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
