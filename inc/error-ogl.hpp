// *********************************************************************
// **
// ** Comprobación de errores de OpenGL (declaraciones)
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

#ifndef ERROR_OGL_HPP
#define ERROR_OGL_HPP

// *********************************************************************
// comprobación de errores de OpenGL

#define CError() CompruebaErrorOpenGL(__FILE__,__LINE__)
void CompruebaErrorOpenGL( const char * nomArchivo, int linea ) ;

// *********************************************************************
// gestion de un error (revisar y quitar version en minusculas)

#define error(msg,donde)   GestionarError(msg,donde,__FILE__,__LINE__)
#define Error(msg,donde)   GestionarError(msg,donde,__FILE__,__LINE__)

void GestionarError( const char * msg, const char * donde, const char * nomArchivo, int linea ) ;

#endif // ERROR_OGL_HPP
