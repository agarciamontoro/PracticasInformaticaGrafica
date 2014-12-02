#ifndef IG_MATRIZ_HPP
#define IG_MATRIZ_HPP

#include <vector>
#include <assert.h>
#include <cmath> //Uso de M_PI
#include "tuplas.hpp"

///////////////////////////
// Declaraciones previas //
///////////////////////////

template <unsigned int ROWS, unsigned int COLS, class T>
class Matriz;

template <unsigned int ROWS, unsigned int COLS, class T>
Matriz<1,COLS,T> operator * ( const Tupla<COLS,T> & t1, const Matriz<ROWS,COLS,T> & m1 );

//////////////////
// Clase Matriz //
//////////////////

template <unsigned int ROWS, unsigned int COLS, class T>
class Matriz{
private:
   T matriz[ROWS][COLS];

public:

   Matriz(){}
   
   Matriz( T val_inicial );
   Matriz( const T datos[ROWS][COLS]);
   Matriz( const std::vector< std::vector<T> >& datos);

   const T* operator[](unsigned int i) const;
   T* operator[](unsigned int i);

   // ---------------------------------------------------------------------
   //  Operador de asignación
   const Matriz<ROWS,COLS,T>& operator=(const Matriz<ROWS,COLS,T> &original);

   // ---------------------------------------------------------------------
   // matriz = matriz+matriz
   Matriz<ROWS,COLS,T> operator + ( const Matriz<ROWS,COLS,T> & m1 );

   // ---------------------------------------------------------------------
   // matriz = matriz-matriz
   Matriz<ROWS,COLS,T> operator - ( const Matriz<ROWS,COLS,T> & m1 );

   // ---------------------------------------------------------------------
   // matriz = matriz*float
   Matriz<ROWS,COLS,T> operator * ( float a );

   // ---------------------------------------------------------------------
   // matriz = float*matriz
   friend Matriz<ROWS,COLS,T> operator * ( float a, const Matriz<ROWS,COLS,T> & m2 ){ return m2*a; }

   // ---------------------------------------------------------------------
   // matriz = matriz/float
   Matriz<ROWS,COLS,T> operator / ( float a ) const;

   // ---------------------------------------------------------------------
   //  = matriz*matriz (producto matricial) //TODO: Ver cómo definir esto en el cpp
   template<unsigned int N>
   Matriz<ROWS,N,T> operator * ( const Matriz<COLS,N,T> & m1 ){
      Matriz<ROWS,N,T> producto(0.0);

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
   }

   // ---------------------------------------------------------------------
   //  = matriz*tupla (producto matriz tupla)
   Matriz<ROWS,1,T> operator * ( const Tupla<COLS,T> & t1 );

   // ---------------------------------------------------------------------
   //  = tupla*matriz (producto tupla matriz)
   friend Matriz<1,COLS,T> operator * <>( const Tupla<COLS,T> & t1, const Matriz<ROWS,COLS,T> & m1 );
};

typedef Matriz<1,3,float> Matriz1x3f;
typedef Matriz<3,1,float> Matriz3x1f;
typedef Matriz<3,3,float> Matriz3x3f;
typedef Matriz<4,4,float> Matriz4x4f;

////////////////////////////
// Funciones relacionadas //
////////////////////////////

//TODO: Ver cómo definir esto en el cpp
template<unsigned int COLS, class T>
Tupla<COLS,T> toTupla( const Matriz<1,COLS,T>& m1){
   Tupla<COLS,T> tupla;

   for (int j = 0; j < COLS; ++j)
   {
      tupla[j] = m1[0][j];
   }

   return tupla;
}

//TODO: Ver cómo definir esto en el cpp
template<unsigned int ROWS, class T>
Tupla<ROWS,T> toTupla( const Matriz<ROWS,1,T>& m1){
   Tupla<ROWS,T> tupla;
      
   for (int i = 0; i < ROWS; ++i){
      tupla[i] = m1[i][0];
   }

   return tupla;
}

#endif
