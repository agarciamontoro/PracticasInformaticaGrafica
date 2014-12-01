#include "tuplas.hpp"

#include <vector>

template <unsigned int N, class T>
Tupla<N,T>::Tupla( const std::vector<T>& coot){
	assert(coot.size() == N);

	for (int i = 0; i < N; ++i){
		val[i] = coot[i];
	}
}

template <unsigned int N, class T>
Tupla<N,T>::Tupla( const T coot[N] ){

	for (int i = 0; i < N; ++i){
		val[i] = coot[i];
	}

}


template <unsigned int N, class T>
Tupla<N,T>::Tupla( T x, T y, T z ){
	assert(N == 3);

	val[X] = x;
	val[Y] = y;
	val[Z] = z;
}

template <unsigned int N, class T>
Tupla<N,T>::Tupla( T x, T y, T z, T w ){
	assert(N == 4);

	val[X] = x;
	val[Y] = y;
	val[Z] = z;
	val[W] = w;
}

template <unsigned int N, class T>
const T& Tupla<N,T>::operator[](unsigned int i) const{
	return this->val[i];
}

template <unsigned int N, class T>
T& Tupla<N,T>::operator[](unsigned int i){
	return this->val[i];
}

/*template <unsigned int N, class T>
T& Tupla<N,T>::operator[](unsigned int i) {
	assert(i<N);

	return this->val[i];
}*/

// ---------------------------------------------------------------------
//  Operador de asignación
template <unsigned int N, class T>
const Tupla<N,T>& Tupla<N,T>::operator=(const Tupla<N,T> &original){

	for (int i = 0; i < N; ++i){
		this->val[i] = original[i];
	}

		return *this;
}

// ---------------------------------------------------------------------
// tupla = tupla+tupla3
template <unsigned int N, class T>
Tupla<N,T> Tupla<N,T>::operator + ( const Tupla<N,T> & t1 ){
	std::vector<T> suma;

	for (int i = 0; i < N; ++i)
	{
		suma.push_back(this->val[i] + t1[i]);
	}

	return Tupla<N,T>(suma);
}

// ---------------------------------------------------------------------
// tupla = tupla-tupla
template <unsigned int N, class T>
Tupla<N,T> Tupla<N,T>::operator - ( const Tupla<N,T> & t1 ){
	std::vector<T> resta;

	for (int i = 0; i < N; ++i)
	{
		resta.push_back(this->val[i] - t1[i]);
	}

	return Tupla<N,T>(resta);
}

// ---------------------------------------------------------------------
// tupla3 = float*tupla3
template <unsigned int N, class T>
Tupla<N,T> Tupla<N,T>::operator * ( float a ){
	std::vector<T> producto;

	for (int i = 0; i < N; ++i)
	{
		producto.push_back(this->val[i] * a);
	}

	return Tupla<N,T>(producto);
}

// ---------------------------------------------------------------------
// tupla = tupla/float
template <unsigned int N, class T>
Tupla<N,T> Tupla<N,T>::operator / ( float a ) const{
	std::vector<T> division;

	for (int i = 0; i < N; ++i)
	{
		division.push_back(this->val[i] / a);
	}

	return Tupla<N,T>(division);
}

// ---------------------------------------------------------------------
// float = tupla|tupla (producto escalar)
template <unsigned int N, class T>
T Tupla<N,T>::operator | ( const Tupla<N,T> & t1 ) const{
	T prod_escalar = 0;

	for (int i = 0; i < N; ++i)
	{
		prod_escalar += this->val[i] * t1[i];
	}

	return prod_escalar;
}

// ---------------------------------------------------------------------
//  = tupla*tupla (producto vectorial)
template <unsigned int N, class T>
Tupla<N,T> Tupla<N,T>::operator * ( const Tupla<N,T> & v2 ){
	assert(N == 3);

	return Tupla<N,T>(
		this->val[Y]*v2[Z] - this->val[Z]*v2[Y] ,
		this->val[Z]*v2[X] - this->val[X]*v2[Z] ,
		this->val[X]*v2[Y] - this->val[Y]*v2[X] 
	);
}

// ---------------------------------------------------------------------
// float = lenSq(tupla)
template <unsigned int N, class T>
float Tupla<N,T>::lenSq( const Tupla<N,T> & t ){
	return t|t;
}

// ---------------------------------------------------------------------
// float = len(tupla)
template <unsigned int N, class T>
float Tupla<N,T>::len( const Tupla<N,T> & t ){
   return float(sqrt( double(lenSq(t)) )) ;
}

//----------------------------------------------------------------------
// tupla3 = normalized(tupla3)
template <unsigned int N, class T>
Tupla<N,T> Tupla<N,T>::normalized( const Tupla<N,T> & t ){
	return t/len(t);
}


//----------------------------------------------------------------------
//						 	ESPECIALIZACIONES
//----------------------------------------------------------------------
// Posibles especializaciones. Tienen que declararse aquí para que el
// compilador sea capaz de enlazar sus definiciones luego.

template class Tupla<1,int>;
template class Tupla<1,float>;

template class Tupla<3,int>;
template class Tupla<3,float>;

template class Tupla<4,int>;
template class Tupla<4,float>;