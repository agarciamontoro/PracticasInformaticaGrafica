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

#define X 0
#define Y 0
#define Z 0


template <unsigned int N, class T>
class Tupla{
private:
   unsigned int dim;
   T coo[N];

public:

   Tupla():
      dim(N)
      {}
   
   Tupla( const std::vector<T>& coot);
   Tupla( const T coot[N] );

   Tupla( T x, T y, T z );
   Tupla( T x, T y, T z, T w );

   T& operator[](unsigned int i) { assert(i<N); return coo[i]; }

   // ---------------------------------------------------------------------
   //  Operador de asignación
   const T& operator=(const T &original);

   // ---------------------------------------------------------------------
   // tupla = tupla+tupla3
   Tupla<N,T> operator + ( const Tupla<N,T> & t1 );

   // ---------------------------------------------------------------------
   // tupla = tupla-tupla
   Tupla<N,T> operator - ( const Tupla<N,T> & t1 );

   // ---------------------------------------------------------------------
   // tupla3 = float*tupla3
   Tupla operator * ( float a );

   // ---------------------------------------------------------------------
   // tupla = tupla/float
   Tupla<N,T> operator / ( float a );

   // ---------------------------------------------------------------------
   // float = tupla|tupla (producto escalar)
   T operator | ( const Tupla<N,T> & t1 );

   // ---------------------------------------------------------------------
   //  = tupla*tupla (producto vectorial)
   Tupla<N,T> operator * ( const Tupla<N,T> & v1 );

   // ---------------------------------------------------------------------
   // float = lenSq(tupla)
   float lenSq( const Tupla<N,T> & t );

   // ---------------------------------------------------------------------
   // float = len(tupla)
   float len( const Tupla<N,T> & t );

   //----------------------------------------------------------------------
   // tupla3 = normalized(tupla3)
   Tupla<N,T> normalized( const Tupla<N,T> & t );

};

typedef Tupla<3,float> Tupla3f;
typedef Tupla<3,int> Tupla3i;
typedef Tupla<4,float> Tupla4f;

/*
// ---------------------------------------------------------------------
// índices de los ejes X,Y Z
                        
const unsigned int 
   X=0, Y=1, Z=2, W=3 ;      // indices de los ejes

// *********************************************************************
// tuplas con tres valores de tipo float
 
struct Tupla3f          // tupla con 3 valores floates que representan coordenas
{                       
   float coo[3] ;       
   
   inline Tupla3f( const float x, const float y, const float z );
   inline Tupla3f( const float coot[3] );
   Tupla3f() {};
} ;

// ---------------------------------------------------------------------
inline Tupla3f::Tupla3f( const float x, const float y, const float z )
{
   coo[X] = x ;
   coo[Y] = y ;
   coo[Z] = z ;
}
// ---------------------------------------------------------------------
inline Tupla3f::Tupla3f( const float coot[3] )
{
   coo[X] = coot[X] ;
   coo[Y] = coot[Y] ;
   coo[Z] = coot[Z] ;
}

// ---------------------------------------------------------------------
// tupla = tupla+tupla
inline Tupla3f operator + ( const Tupla3f & t1, const Tupla3f & t2 )
{
   return Tupla3f(t1.coo[0]+t2.coo[0],
                  t1.coo[1]+t2.coo[1],
                  t1.coo[2]+t2.coo[2]);
}

// ---------------------------------------------------------------------
// tupla = tupla-tupla
inline Tupla3f operator - ( const Tupla3f & t1, const Tupla3f & t2 )
{
   return Tupla3f(t1.coo[0]-t2.coo[0],
                  t1.coo[1]-t2.coo[1],
                  t1.coo[2]-t2.coo[2]);
}

// ---------------------------------------------------------------------
// tupla3 = float*tupla3
inline Tupla3f operator * ( float a, const Tupla3f & t )
{
   return Tupla3f(a*t.coo[0],a*t.coo[1],a*t.coo[2]);
}

// ---------------------------------------------------------------------
// tupla = tupla*float
inline Tupla3f operator * ( const Tupla3f & t, float a )
{
   return Tupla3f(a*t.coo[0],a*t.coo[1],a*t.coo[2]);
}

// ---------------------------------------------------------------------
// tupla = tupla/float
inline Tupla3f operator / ( const Tupla3f & t, float a )
{
   return Tupla3f( t.coo[0]/a, t.coo[1]/a, t.coo[2]/a );
}

// ---------------------------------------------------------------------
// float = tupla|tupla (producto escalar)
inline float operator | ( const Tupla3f & t1, const Tupla3f & t2 )
{
   return   t1.coo[0]*t2.coo[0] +
            t1.coo[1]*t2.coo[1] +
            t1.coo[2]*t2.coo[2] ;
}

// ---------------------------------------------------------------------
//  = tupla*tupla (producto vectorial)
inline Tupla3f operator * ( const Tupla3f & v1, const Tupla3f & v2 )
{
   return Tupla3f
         (  v1.coo[Y]*v2.coo[Z] - v1.coo[Z]*v2.coo[Y] ,
            v1.coo[Z]*v2.coo[X] - v1.coo[X]*v2.coo[Z] ,
            v1.coo[X]*v2.coo[Y] - v1.coo[Y]*v2.coo[X] 
         );
}

// ---------------------------------------------------------------------
// float = lenSq(tupla)
inline float lenSq( const Tupla3f & t )
{
   return t|t ;
}
// ---------------------------------------------------------------------
// float = len(tupla)
inline float len( const Tupla3f & t )
{
   return float(sqrt(double(lenSq(t)))) ;
}

//----------------------------------------------------------------------
// tupla3 = normalized(tupla3)

inline Tupla3f normalized( const Tupla3f & t )
{
   return  t/len(t) ;
}

// *********************************************************************
// tuplas con cuatro valores de tipo float
 
struct Tupla4f          // tupla con 3 valores floates que representan coordenas
{                       
   float coo[4] ;       
   
   inline Tupla4f( const float x, const float y, const float z, const float w );
   inline Tupla4f( const float coot[4] );
   Tupla4f() {};
} ;

// ---------------------------------------------------------------------
inline Tupla4f::Tupla4f( const float x, const float y, const float z, const float w  )
{
   coo[X] = x ;
   coo[Y] = y ;
   coo[Z] = z ;
   coo[W] = w ;
}
// ---------------------------------------------------------------------
inline Tupla4f::Tupla4f( const float coot[4] )
{
   coo[0] = coot[0] ;
   coo[1] = coot[1] ;
   coo[2] = coot[2] ;
   coo[3] = coot[3] ;
}

// *********************************************************************
// tuplas con tres valores int

struct Tupla3i
{
   int idx[3] ;

   inline Tupla3i( const float x, const float y, const float z );
   inline Tupla3i( const float idxt[3] );
   Tupla3i() {};
} ;

// ---------------------------------------------------------------------
inline Tupla3i::Tupla3i( const float x, const float y, const float z )
{
   idx[X] = x ;
   idx[Y] = y ;
   idx[Z] = z ;
}
// ---------------------------------------------------------------------
inline Tupla3i::Tupla3i( const float idxt[3] )
{
   idx[X] = idxt[X] ;
   idx[Y] = idxt[Y] ;
   idx[Z] = idxt[Z] ;
}


*/

#endif
