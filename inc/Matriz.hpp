#ifndef IG_MATRIZ_HPP
#define IG_MATRIZ_HPP

#include <vector>
#include <assert.h>
#include <cmath> //Uso de M_PI
#include "tuplas.hpp"

template <unsigned int ROWS, unsigned int COLS, class T>
class Matriz{
private:
   T matriz[ROWS][COLS];

public:

   Matriz(){}
   
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
   //  = matriz*matriz (producto matricial)
   //template<unsigned int N>
   //Matriz<ROWS,N,T> operator * ( const Matriz<COLS,N,T> & m1 );
   //Matriz<ROWS,COLS,T> operator * ( const Matriz<ROWS,COLS,T> & m1 );
   template<int N1, int N2, int M>
   friend Matriz<N1, N2, T> operator*(const Matriz<N1, M, T> &lhs, const Matriz<M, N2, T> &rhs);

   // ---------------------------------------------------------------------
   //  = matriz*vector (producto matriz vector)
   Matriz<ROWS,COLS,T> operator * ( const std::vector<T> & v1 );

   // ---------------------------------------------------------------------
   //  = vector*matriz (producto vector matriz)
   friend Matriz<1,COLS,T> operator * ( const std::vector<T> & v1, const Matriz<ROWS,COLS,T> & m1 ){
      Matriz<1,3,float> matriz;
      return matriz;
   }

   // ---------------------------------------------------------------------
   //  = matriz*tupla (producto matriz tupla)
   Matriz<ROWS,COLS,T> operator * ( const Tupla<COLS,T> & t1 );

   // ---------------------------------------------------------------------
   //  = tupla*matriz (producto tupla matriz)
   friend Matriz<1,COLS,T> operator * ( const Tupla<COLS,T> & t1, const Matriz<ROWS,COLS,T> & m1 ){
      Matriz<1,3,float> matriz;
      return matriz;
   }
};


typedef Matriz<3,3,float> Matriz3x3f;
typedef Matriz<4,4,float> Matriz4x4f;

#endif
