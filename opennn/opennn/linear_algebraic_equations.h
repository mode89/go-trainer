/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   L I N E A R   A L G E B R A I C   E Q U A T I O N S   C L A S S   H E A D E R                              */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - Making intelligent use of data                                                                 */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// $Id: linear_algebraic_equations.h 34 2014-12-29 18:55:48Z uwrobertolopez $

#ifndef __LINEARALGEBRAICEQUATIONS_H__
#define __LINEARALGEBRAICEQUATIONS_H__

// System includes

#include<iostream>

// OpenNN includes

#include "vector.h"
#include "matrix.h"

#include "../eigen/Eigen"

namespace OpenNN
{

/// This class contains methods for the solution of linear algebraic equations. 
/// In particular it implements the Gauss-Jordan eliminiation, LU decomposition and
/// Cholesky decomposition methods.

class LinearAlgebraicEquations 
{

public:

   // METHODS

   // Gauss Jordan methods

   Vector<double> perform_Householder_QR_decomposition(const Matrix<double>&, const Vector<double>&) const;


   // CONSTRUCTOR

   LinearAlgebraicEquations(void);

   // DESTRUCTOR

   ~LinearAlgebraicEquations(void);

   // ASSIGNMENT OPERATOR

   LinearAlgebraicEquations& operator = (const LinearAlgebraicEquations&);

   // EQUAL TO OPERATOR

   bool operator == (const LinearAlgebraicEquations&) const;

};

}

#endif


// OpenNN: Open Neural Networks Library.
// Copyright (c) 2005-2015 Roberto Lopez.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
