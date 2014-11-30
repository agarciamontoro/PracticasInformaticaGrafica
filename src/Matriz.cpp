#include <vector>
#include <assert.h>
#include <cmath> //Uso de M_PI
#include "tuplas.hpp"

#include "Matriz.hpp"

template <unsigned int ROWS, unsigned int COLS, class T>
Matriz<ROWS,COLS,T>::Matriz( const std::vector< std::vector<T> >& datos){
   assert(datos.size() == ROWS);

   for (int i = 0; i < datos.size(); ++i){
      assert(datos[i].size() == COLS);

      for (int j = 0; j < datos[i].size(); ++j){
         this->matriz[i][j] = datos[i][j];
      }
   }

}

template <unsigned int ROWS, unsigned int COLS, class T>
const T* Matriz<ROWS,COLS,T>::operator[](unsigned int i) const{
   assert(i > 0 && i < ROWS);

   return this->matriz[i];
}

template <unsigned int ROWS, unsigned int COLS, class T>
T* Matriz<ROWS,COLS,T>::operator[](unsigned int i){
   assert(i > 0 && i < ROWS);

   return this->matriz[i];
}

// ---------------------------------------------------------------------
//  Operador de asignación
template <unsigned int ROWS, unsigned int COLS, class T>
const Matriz<ROWS,COLS,T>& Matriz<ROWS,COLS,T>::operator=(const Matriz<ROWS,COLS,T> &original){
   for (int i = 0; i < ROWS; ++i)
   {
      for (int j = 0; j < COLS; ++j)
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
   
   for (int i = 0; i < ROWS; ++i)
   {
      for (int j = 0; j < COLS; ++j)
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
   
   for (int i = 0; i < ROWS; ++i)
   {
      for (int j = 0; j < COLS; ++j)
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
   
   for (int i = 0; i < ROWS; ++i)
   {
      for (int j = 0; j < COLS; ++j)
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

   for (int i = 0; i < ROWS; ++i)
   {
      for (int j = 0; j < COLS; ++j)
      {
         resultado[i][j] = this->matriz[i][j] / a;
      }
   }

   return resultado;
}

// ---------------------------------------------------------------------
//  = matriz*matriz (producto matricial)
//template<unsigned int N>
/*template <unsigned int N, unsigned int ROWS, unsigned int COLS, class T>
Matriz<ROWS,N,T> Matriz<ROWS,COLS,T>::operator * ( const Matriz<COLS,N,T> & m1 ){
   Matriz<ROWS,N,T> producto;

   for (int i = 0; i < ROWS; ++i)
   {
      for (int k = 0; k < COLS; ++k)
      {
         for (int j = 0; j < N; ++j)
         {
            producto[i][j] += this->matriz[i][k] * m1[k][j];
         }
      }
   }

   return producto;
}*/

template<int N1, int N2, int M, class T>
Matriz<N1, N2, T> operator*(const Matriz<N1, M, T> &lhs, const Matriz<M, N2, T> &rhs){
   Matriz<N1,N2,T> producto;

   for (int i = 0; i < N1; ++i)
   {
      for (int k = 0; k < M; ++k)
      {
         for (int j = 0; j < N2; ++j)
         {
            producto[i][j] += lhs[i][k] * rhs[k][j];
         }
      }
   }

   return producto;
}

// ---------------------------------------------------------------------
//  = matriz*vector (producto matriz vector)
template <unsigned int ROWS, unsigned int COLS, class T>
Matriz<ROWS,COLS,T> Matriz<ROWS,COLS,T>::operator * ( const std::vector<T> & v1 ){
   std::vector< std::vector<T> > vector_tras;

   for (int i = 0; i < v1.size(); ++i)
   {
      vector_tras.push_back(std::vector<T>());
      vector_tras[i].push_back(v1[i]);
   }

   Matriz<ROWS,1,T> vector_mat = Matriz<ROWS,1,T>(vector_tras);

   return *this * vector_mat;
}

// ---------------------------------------------------------------------
//  = matriz*tupla (producto matriz tupla)
template <unsigned int ROWS, unsigned int COLS, class T>
Matriz<ROWS,COLS,T> Matriz<ROWS,COLS,T>::operator * ( const Tupla<COLS,T> & t1 ){
   Tupla<ROWS,T> resultado;

   for (int i = 0; i < ROWS; ++i)
   {
      //tupla[i] = 
   }
   std::vector< std::vector<T> > vector_tras;

   for (int i = 0; i < ROWS; ++i)
   {
      vector_tras.push_back(std::vector<T>());
      vector_tras[i].push_back(t1[i]);
   }

   Tupla<ROWS,T> vector_mat = Tupla<ROWS,T>(vector_tras);

   return *this * vector_mat;
}

//----------------------------------------------------------------------
//                   ESPECIALIZACIONES
//----------------------------------------------------------------------
// Posibles especializaciones. Tienen que declararse aquí para que el
// compilador sea capaz de enlazar sus definiciones luego.

/*template class Matriz<3,1,float>;
template class Matriz<1,3,float>;
template class Matriz<3,3,float>;
template class Matriz<4,1,float>;
template class Matriz<1,4,float>;
template class Matriz<4,4,float>;*/