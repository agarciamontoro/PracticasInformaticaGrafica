// *********************************************************************
// **
// ** Comprobación de errores de OpenGL (implementacion)
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
// *********************************************************************

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>

#include "error-ogl.hpp"

// *********************************************************************
// gestion de errores
   
void GestionarError( const char * msg, const char * donde, const char * nomArchivo, int linea )
{
   std::cout
         << std::endl
         << "-----------------------------------------------------------" << std::endl
         << "Error detectado:" << std::endl
         << "   descripción : " << msg  << "." << std::endl
         << "   archivo     : " << nomArchivo << std::endl  
         << "   lugar       : " << donde << std::endl 
         << "   línea       : " << linea << std::endl
         << "-----------------------------------------------------------" << std::endl
         << "programa abortado." << std:: endl
         << std::flush ;
         
    exit(1) ;
}

void CompruebaErrorOpenGL( const char * nomArchivo, int linea )
{
   const GLint codigoError = glGetError() ;
   
   if ( codigoError != GL_NO_ERROR )
   {  std::cout 
         << std::endl
         << "Detectado error de OpenGL. Programa abortado." << std::endl 
         << "   línea       : "  << linea << std::endl
         << "   archivo     : " << nomArchivo << std::endl 
         << "   descripción : " << gluErrorString(codigoError)  << "." << std::endl
         << std::endl << std::flush ;
      exit(1);
   }
}




   

   
   




