/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   L I N E A R   A L G E B R A I C   E Q U A T I O N S   C L A S S                                            */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - Making intelligent use of data                                                                 */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// $Id: linear_algebraic_equations.cpp 34 2014-12-29 18:55:48Z uwrobertolopez $

// OpenNN includes

#include "linear_algebraic_equations.h"


namespace OpenNN
{

// GENERAL CONSTRUCTOR

/// General constructor.

LinearAlgebraicEquations::LinearAlgebraicEquations(void)
{	

}


// DESTRUCTOR

/// Destructor.

LinearAlgebraicEquations::~LinearAlgebraicEquations(void)
{

}


// ASSIGNMENT OPERATOR

// LinearAlgebraicEquations& operator = (const LinearAlgebraicEquations&) method

/// Assignment operator. 
/// Assigns the members of another object to this object.

LinearAlgebraicEquations& LinearAlgebraicEquations::operator = (const LinearAlgebraicEquations&)
{
   return(*this);
}


// EQUAL TO OPERATOR

// bool operator == (const LinearAlgebraicEquations&) const method

/// Equal to operator. 
/// Compares this object with anothe object.
/// It returns true if both objects are equal and false otherwise. 

bool LinearAlgebraicEquations::operator == (const LinearAlgebraicEquations&) const
{
   return(true);
}


// METHODS


// Vector<double> perform_Householder_QR_decomposition(Matrix<double>&, Matrix<double>&) const method

Vector<double> LinearAlgebraicEquations::perform_Householder_QR_decomposition(const Matrix<double>& A, const Vector<double>& b) const
{
    const size_t n = A.get_rows_number();

    Vector<double> x(n);

    const Eigen::Map<Eigen::MatrixXd> A_eigen((double*)A.data(), n, n);
    const Eigen::Map<Eigen::VectorXd> b_eigen((double*)b.data(), n);
    Eigen::Map<Eigen::VectorXd> x_eigen(x.data(), n);

    x_eigen = A_eigen.colPivHouseholderQr().solve(b_eigen);

    return(x);
}

}


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
