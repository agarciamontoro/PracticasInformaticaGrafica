// *********************************************************************
// **
// ** Gestión de tuplas de coordenadas o colores
// ** (declaraciones e implementación 'inline')
// ** Copyright (C) 2014 Carlos Ureña
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
//


#ifndef TUPLAS_HPP
#define TUPLAS_HPP

#include <cmath>
#include <assert.h>
#include <vector>

#include <iostream>

template <unsigned int N, class T>
class Tupla{
private:
   T val[N];

public:

   Tupla(){}

   Tupla( const std::vector<T>& coot);
   Tupla( const T coot[N] );

   Tupla( T x, T y, T z );
   Tupla( T x, T y, T z, T w );

   const T& operator[](unsigned int i) const;
   T& operator[](unsigned int i);

   // ---------------------------------------------------------------------
   //  Operador de asignación
   const Tupla<N,T>& operator=(const Tupla<N,T> &original);

   // ---------------------------------------------------------------------
   //  Operador lógico de igualdad
   friend bool operator==(const Tupla<N,T>& t1, const Tupla<N,T>& t2){
      bool iguales = true;

      for(unsigned int i = 0; i < N && iguales; i++){
         iguales = (t1[i] == t2[i]);
      }

      return iguales;
   }

   // ---------------------------------------------------------------------
   //  Operador lógico de deigualdad
   friend bool operator!=(const Tupla<N,T>& t1, const Tupla<N,T>& t2){
       return !( t1 == t1 );
   }

   // ---------------------------------------------------------------------
   // tupla = tupla+tupla3
   Tupla<N,T> operator + ( const Tupla<N,T> & t1 );

   // ---------------------------------------------------------------------
   // tupla = tupla+tupla3
   Tupla<N,T>& operator += ( const Tupla<N,T> & t1 );

   // ---------------------------------------------------------------------
   // tupla = tupla-tupla
   Tupla<N,T> operator - ( const Tupla<N,T> & t1 );

   // ---------------------------------------------------------------------
   // tupla3 = tupla3*float
   Tupla<N,T> operator * ( float a );

   // ---------------------------------------------------------------------
   // tupla3 = float*tupla3
   friend Tupla<N,T> operator * ( float a, const Tupla<N,T> & v2 ){ return v2*a; }

   // ---------------------------------------------------------------------
   // tupla = tupla/float
   Tupla<N,T> operator / ( float a ) const;

   // ---------------------------------------------------------------------
   // float = tupla|tupla (producto escalar)
   float operator | ( const Tupla<N,T> & t1 ) const;

   // ---------------------------------------------------------------------
   //  = tupla*tupla (producto vectorial)
   Tupla<N,T> operator * ( const Tupla<N,T> & v1 );

   // ---------------------------------------------------------------------
   // float = lenSq(tupla)
   float lenSq();

   // ---------------------------------------------------------------------
   // float = len(tupla)
   float len();

   //----------------------------------------------------------------------
   // tupla3 = normalized(tupla3)
   Tupla<N,T> normalized();


   //----------------------------------------------------------------------
   // tupla3 = abs(tupla3)
   Tupla<N,T> abs();

   T* get_ptr(){
      return &(val[0]);
   }

};

typedef Tupla<2,float> Tupla2f;
typedef Tupla<3,float> Tupla3f;
typedef Tupla<3,int> Tupla3i;
typedef Tupla<4,float> Tupla4f;

#endif
