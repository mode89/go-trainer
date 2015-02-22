/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   D A T A   S E T   C L A S S   H E A D E R                                                                  */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - Making intelligent use of data                                                                 */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// $Id: data_set.h 58 2015-01-26 17:19:45Z uwrobertolopez $

#ifndef __DATASET_H__
#define __DATASET_H__

// System includes

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <ctime>
#include <exception>

// OpenNN includes

#include "vector.h"
#include "matrix.h"

#include "missing_values.h"
#include "variables.h"
#include "instances.h"

// TinyXml includes

#include "tinyxml2.h"

namespace OpenNN
{

/// This class represents the concept of data set for data modelling problems, 
/// such as function regression, pattern recognition and time series prediction.
/// It basically consists of a data matrix plus a variables and an instances objects. 

class DataSet 
{

public:  

    // DEFAULT CONSTRUCTOR

    explicit DataSet(void);

    // DATA CONSTRUCTOR

    explicit DataSet(const Matrix<double>&);

   // VARIABLES AND INSTANCES CONSTRUCTOR

   explicit DataSet(const size_t&, const size_t&);

   // INPUTS, TARGETS AND INSTANCES NUMBERS CONSTRUCTOR

   explicit DataSet(const size_t&, const size_t&, const size_t&);

   // XML CONSTRUCTOR

   explicit DataSet(const tinyxml2::XMLDocument&);

   // FILE CONSTRUCTOR

   explicit DataSet(const std::string&);

   // COPY CONSTRUCTOR

   DataSet(const DataSet&);

   // DESTRUCTOR

   virtual ~DataSet(void);

   // ASSIGNMENT OPERATOR

   DataSet& operator = (const DataSet&);

   // EQUAL TO OPERATOR

   bool operator == (const DataSet&) const;

   // ENUMERATIONS

   /// Enumeration of available methods for scaling and unscaling the data.  
   
   enum ScalingUnscalingMethod{MinimumMaximum, MeanStandardDeviation};

   /// Enumeration of the units used for angular variables.

   enum AngularUnits{Radians, Degrees};

   // METHODS

   // Get methods

   const std::string& get_data_file_name(void) const;

   const bool& get_header(void) const;

   const std::string& get_separator(void) const;

   const std::string& get_missing_values_label(void) const;

   const size_t& get_lags_number(void) const;
   const bool& get_autoassociation(void) const;

   const Vector<size_t>& get_angular_variables(void) const;
   const AngularUnits& get_angular_units(void) const;

   static ScalingUnscalingMethod get_scaling_unscaling_method(const std::string&);

   const MissingValues& get_missing_values(void) const;
   MissingValues* get_missing_values_pointer(void);

   const Variables& get_variables(void) const;
   Variables* get_variables_pointer(void);

   const Instances& get_instances(void) const;
   Instances* get_instances_pointer(void);

   const bool& get_display(void) const;

   // Data methods

   bool empty(void) const;

   const Matrix<double>& get_data(void) const;

   Matrix<double> arrange_training_data(void) const;
   Matrix<double> arrange_generalization_data(void) const;
   Matrix<double> arrange_testing_data(void) const;

   Matrix<double> arrange_input_data(void) const;
   Matrix<double> arrange_target_data(void) const;

   Matrix<double> arrange_training_input_data(void) const;
   Matrix<double> arrange_training_target_data(void) const;  
   Matrix<double> get_generalization_input_data(void) const;
   Matrix<double> get_generalization_target_data(void) const;
   Matrix<double> arrange_testing_input_data(void) const;
   Matrix<double> arrange_testing_target_data(void) const;

   // Instance methods

   Vector<double> get_instance(const size_t&) const;
   Vector<double> get_instance(const size_t&, const Vector<size_t>&) const;

   // Variable methods

   Vector<double> get_variable(const size_t&) const;
   Vector<double> get_variable(const size_t&, const Vector<size_t>&) const;

   // Set methods

   void set(void);
   void set(const Matrix<double>&);
   void set(const size_t&, const size_t&);
   void set(const size_t&, const size_t&, const size_t&);
   void set(const DataSet&);
   void set(const tinyxml2::XMLDocument&);
   void set(const std::string&);

   // Data methods

   void set_data(const Matrix<double>&);

   void set_instances_number(const size_t&);
   void set_variables_number(const size_t&);

   void set_data_file_name(const std::string&);

   void set_header(const bool&);

   void set_separator(const std::string&);

   void set_missing_values_label(const std::string&);

   void set_lags_number(const size_t&);
   void set_autoassociation(const bool&);

   void set_angular_variables(const Vector<size_t>&);
   void set_angular_units(AngularUnits&);

   // Utilities

   void set_display(const bool&);

   void set_default(void);

   // Instance methods

   void set_instance(const size_t&, const Vector<double>&);

   // Data resizing methods

   void add_instance(const Vector<double>&);
   void subtract_instance(const size_t&);

   void append_variable(const Vector<double>&);
   void subtract_variable(const size_t&);

   Vector<size_t> unuse_constant_variables(void);
   Vector<size_t> unuse_repeated_instances(void);

   // Initialization methods

   void initialize_data(const double&);

   void randomize_data_uniform(const double& minimum = -1.0, const double& maximum = 1.0);
   void randomize_data_normal(const double& mean = 0.0, const double& standard_deviation = 1.0);

   // Statistics methods

   Vector< Statistics<double> > calculate_data_statistics(void) const;

   Matrix<double> calculate_data_statistics_matrix(void) const;

   Vector< Statistics<double> > calculate_training_instances_statistics(void) const;
   Vector< Statistics<double> > calculate_generalization_instances_statistics(void) const;
   Vector< Statistics<double> > calculate_testing_instances_statistics(void) const;

   Vector< Statistics<double> > calculate_inputs_statistics(void) const;
   Vector< Statistics<double> > calculate_targets_statistics(void) const;

   Vector<double> calculate_training_target_data_mean(void) const;
   Vector<double> calculate_generalization_target_data_mean(void) const;
   Vector<double> calculate_testing_target_data_mean(void) const;

   // Correlation methods

   Matrix<double> calculate_linear_correlations(void) const;

   // Histrogram methods

   Vector< Histogram<double> > calculate_data_histograms(const size_t& = 10) const;

   // Data scaling

   void scale_data_minimum_maximum(const Vector< Statistics<double> >&);
   void scale_data_mean_standard_deviation(const Vector< Statistics<double> >&);

   Vector< Statistics<double> > scale_data_minimum_maximum(void);
   Vector< Statistics<double> > scale_data_mean_standard_deviation(void);

   void scale_data(const std::string&, const Vector< Statistics<double> >&);

   Vector< Statistics<double> > scale_data(const std::string&);

   // Input variables scaling

   void scale_inputs_minimum_maximum(const Vector< Statistics<double> >&);
   Vector< Statistics<double> > scale_inputs_minimum_maximum(void);

   void scale_inputs_mean_standard_deviation(const Vector< Statistics<double> >&);
   Vector< Statistics<double> > scale_inputs_mean_standard_deviation(void);

   Vector< Statistics<double> > scale_inputs(const std::string&);
   void scale_inputs(const std::string&, const Vector< Statistics<double> >&);

   // Target variables scaling

   void scale_targets_minimum_maximum(const Vector< Statistics<double> >&);
   Vector< Statistics<double> > scale_targets_minimum_maximum(void);

   void scale_targets_mean_standard_deviation(const Vector< Statistics<double> >&);
   Vector< Statistics<double> > scale_targets_mean_standard_deviation(void);

   Vector< Statistics<double> > scale_targets(const std::string&);
   void scale_targets(const std::string&, const Vector< Statistics<double> >&);

   // Data unscaling

   void unscale_data_minimum_maximum(const Vector< Statistics<double> >&);
   void unscale_data_mean_standard_deviation(const Vector< Statistics<double> >&);

   // Input variables unscaling

   void unscale_inputs_minimum_maximum(const Vector< Statistics<double> >&);
   void unscale_inputs_mean_standard_deviation(const Vector< Statistics<double> >&);

   // Target variables unscaling

   void unscale_targets_minimum_maximum(const Vector< Statistics<double> >&);
   void unscale_targets_mean_standard_deviation(const Vector< Statistics<double> >&);

   // Pattern recognition methods

   Vector<size_t> calculate_target_class_distribution(void) const;

   Vector<double> calculate_distances(void) const;

   void balance_data(const double&);

   void balance_target_class_distribution(void);

   // Serialization methods

   std::string to_string(void) const;

   void print(void) const;
   void print_summary(void) const;

   tinyxml2::XMLDocument* to_XML(void) const;
   void from_XML(const tinyxml2::XMLDocument&);

   void save(const std::string&) const;
   void load(const std::string&);

   void print_data(void) const;
   void print_data_preview(void) const;

   void save_data(void) const;
   void save_data(const std::string&) const;


   bool has_data(void) const;

   void filter_data(const Vector<double>&, const Vector<double>&);

   // Data load methods

   Vector< Vector<std::string> > set_from_data_file(void);
   void read_from_data_file(const Vector< Vector<std::string> >&);

   void load_data(void);

   Vector<std::string> arrange_time_series_names(const Vector<std::string>&) const;

   Vector<std::string> arrange_autoassociation_names(const Vector<std::string>&) const;

   void convert_time_series(void);
   void convert_autoassociation(void);

   void convert_angular_variable_degrees(const size_t&);
   void convert_angular_variable_radians(const size_t&);

   void convert_angular_variables_degrees(const Vector<size_t>&);
   void convert_angular_variables_radians(const Vector<size_t>&);

   void convert_angular_variables(void);

   // String utilities

   size_t count_tokens(std::string&) const;

   Vector<std::string> get_tokens(std::string&) const;

   bool is_numeric(const std::string&) const;

   void trim(std::string&) const;

   std::string get_trimmed(const std::string&) const;

   std::string prepend(const std::string&, const std::string&) const;


private:

   // MEMBERS

   /// Data file name

   std::string data_file_name;

   /// Header which contains variables name.

   bool header;

   /// Separator character.

   std::string separator;

   /// Missing values label.

   std::string missing_values_label;

   /// Number of lags.

   size_t lags_number;

   /// Autoassociation flag.

    bool autoassociation;

    /// Indices of angular variables.

    Vector<size_t> angular_variables;

    /// Units of angular variables.

    AngularUnits angular_units;

   /// Data Matrix.
   /// The number of rows is the number of instances.
   /// The number of columns is the number of variables.

   Matrix<double> data;

   /// Variables object (inputs and target variables).

   Variables variables;

   /// Instances  object (training, generalization and testing instances).

   Instances instances;

   /// Missing values object.

   MissingValues missing_values;

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
