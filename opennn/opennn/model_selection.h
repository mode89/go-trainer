/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   M O D E L   S E L E C T I O N   C L A S S   H E A D E R                                                    */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - Making intelligent use of data                                                                 */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// $Id: model_selection.h 30 2014-12-26 18:29:17Z uwrobertolopez $

#ifndef __MODELSELECTION_H__
#define __MODELSELECTION_H__

// System includes

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <ctime>

// OpenNN includes

#include "vector.h"
#include "matrix.h"

#include "performance_functional.h"

#include "training_strategy.h"

// TinyXml includes

#include "tinyxml2.h"

namespace OpenNN
{

/// This class represents the concept of model selection algorithm.
/// It is used for finding a network architecture with maximum generalization capabilities. 

class ModelSelection
{

public:  

   // DEFAULT CONSTRUCTOR

   explicit ModelSelection(void);

   // TRAINING STRATEGY CONSTRUCTOR

   explicit ModelSelection(TrainingStrategy*);

   // FILE CONSTRUCTOR

   explicit ModelSelection(const std::string&);

   // XML CONSTRUCTOR

   explicit ModelSelection(const tinyxml2::XMLDocument&);


   // DESTRUCTOR

   virtual ~ModelSelection(void);


    // ENUMERATIONS

    /// Enumeration of available methods for inputs selection.

    enum InputsSelectionMethod{MaximumLinearCorrelation, MaximumLogisticCorrelation, Exhaustive};


   // STRUCTURES

   ///
   /// This structure contains the results from the model selection process. 
   ///

   struct ModelSelectionResults
   {
      /// Parameters of the different neural networks. 

      Matrix< Vector<double> > parameters_data;

      /// Performance performance of the different neural networks. 

      Matrix<double> performance_data;

      /// Generalization performance of the different neural networks. 

      Matrix<double> generalization_performance_data;

	  /// Vector of parameters for the neural network with minimum generalization performance. 

	  Vector<double> minimal_parameters;

	  /// Statistics of the performance functional performance for the different neural networks.

	  Vector< Vector<double> > performance_data_statistics;

	  /// Statistics of the generalization performance for the different neural networks.

	  Vector< Vector<double> > generalization_performance_data_statistics; 
   };

   // METHODS

   // Get methods

   TrainingStrategy* get_training_strategy_pointer(void) const;

   const Vector<size_t>& get_hidden_perceptrons_numbers(void) const;
   const size_t& get_parameters_assays_number(void) const;

   const bool& get_reserve_parameters_data(void) const;
   const bool& get_reserve_performance_data(void) const;
   const bool& get_reserve_generalization_performance_data(void) const;
   const bool& get_reserve_minimal_parameters(void) const;
   const bool& get_reserve_performance_data_statistics(void) const;
   const bool& get_reserve_generalization_performance_data_statistics(void) const;
   const bool& get_reserve_model_order_selection_plot(void) const;

   const InputsSelectionMethod& get_inputs_selection_method(void) const;

   const bool& get_display(void) const;

   // Set methods

   void set_training_strategy_pointer(TrainingStrategy*);

   void set_default(void);

   void set_hidden_perceptrons_numbers(const Vector<size_t>&);
   void set_parameters_assays_number(const size_t&);

   void set_assays_numbers(const size_t&, const size_t&);

   void set_reserve_parameters_data(const bool&);
   void set_reserve_performance_data(const bool&);
   void set_reserve_generalization_performance_data(const bool&);
   void set_reserve_minimal_parameters(const bool&);
   void set_reserve_performance_data_statistics(const bool&);
   void set_reserve_generalization_performance_data_statistics(const bool&);
   void set_reserve_model_order_selection_plot(const bool&);

   void set_inputs_selection_method(const InputsSelectionMethod&);

   void set_display(const bool&);

   // Correlation methods

   Matrix<double> calculate_linear_correlations(void) const;
   Matrix<double> calculate_logistic_correlations(void) const;

   // Model order selection methods

   void check(void) const;

   void perform_maximum_linear_correlation_inputs_selection(void) const;
   void perform_maximum_logistic_correlation_inputs_selection(void) const;
   void perform_exhaustive_inputs_selection(void) const;

   void perform_inputs_selection(void) const;

   ModelSelectionResults perform_order_selection(void) const;

   ModelSelectionResults perform_model_selection(void) const;

   // Serialization methods

   tinyxml2::XMLDocument* to_XML(void) const;
   void from_XML(const tinyxml2::XMLDocument&);

   void print(void) const;
   void save(const std::string&) const;
   void load(const std::string&);

private: 

   // MEMBERS

   /// Pointer to a training strategy object.

   TrainingStrategy* training_strategy_pointer;

   /// Indices for selecting the input variables. 

   Vector< Vector<size_t> > inputs_indices;

   /// Complexities for selecting the network architecture. 

   Vector<size_t> hidden_perceptrons_numbers;

   /// Number of trials for each neural network. 

   size_t parameters_assays_number;

   // Model selection results

   /// True if the parameters of all neural networks are to be reserved. 

   bool reserve_parameters_data;

   /// True if the performance of all neural networks are to be reserved. 

   bool reserve_performance_data;

   /// True if the generalization performance of all neural networks are to be reserved. 

   bool reserve_generalization_performance_data;

   /// True if the vector parameters of the neural network presenting minimum generalization performance is to be reserved. 

   bool reserve_minimal_parameters;

   /// True if the statistics of the different performances are to be reserved. 

   bool reserve_performance_data_statistics;

   /// True if the statistics of the different generalization performances are to be reserved. 

   bool reserve_generalization_performance_data_statistics;

   /// True if the data needed to plot the results from the model selection plot is to be reserved. 

   bool reserve_model_order_selection_plot;

   /// Goal value for a single input-target correlation.

   double correlation_goal;

   /// Inputs selection method variable.

   InputsSelectionMethod inputs_selection_method;

   /// Display messages to screen.
   
   bool display;
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
