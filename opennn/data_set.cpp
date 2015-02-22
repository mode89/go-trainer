/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   D A T A   S E T   C L A S S                                                                                */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - Making intelligent use of data                                                                 */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// $Id: data_set.cpp 67 2015-01-28 17:37:03Z uwrobertolopez $

// OpenNN includes

#include "data_set.h"


namespace OpenNN
{

// DEFAULT CONSTRUCTOR

/// Default constructor. It creates a data set object with zero instances and zero inputs and target variables. 
/// It also initializes the rest of class members to their default values.

DataSet::DataSet(void)
{
   set();  

   set_default();
}


// DATA CONSTRUCTOR

/// Data constructor. It creates a data set object from a data matrix.
/// It also initializes the rest of class members to their default values.
/// @param data Data matrix.

DataSet::DataSet(const Matrix<double>& data)
{
   set(data);

   set_default();
}


// GENERAL CONSTRUCTOR

/// Instances and variables number constructor. 
/// It creates a data set object with given instances and variables numbers.
/// All the variables are set as inputs. 
/// It also initializes the rest of class members to their default values.
/// @param new_variables_number Number of variables.
/// @param new_instances_number Number of instances in the data set.

DataSet::DataSet(const size_t& new_variables_number, const size_t& new_instances_number)
{
   set(new_variables_number, new_instances_number);

   set_default();
}


// INSTANCES, INPUTS AND TARGETS NUMBERS CONSTRUCTORS

/// Instances number, input variables number and target variables number constructor. 
/// It creates a data set object with given instances and inputs and target variables numbers.
/// It also initializes the rest of class members to their default values.
/// @param new_inputs_number Number of input variables.
/// @param new_targets_number Number of target variables.
/// @param new_instances_number Number of instances in the data set.

DataSet::DataSet(const size_t& new_inputs_number, const size_t& new_targets_number, const size_t& new_instances_number)
{
   set(new_inputs_number, new_targets_number, new_instances_number);

   set_default();
}


// XML CONSTRUCTOR

/// Sets the data set members from a XML document.
/// @param data_set_document TinyXML document containing the member data.

DataSet::DataSet(const tinyxml2::XMLDocument& data_set_document)
{
   set_default();

   from_XML(data_set_document);
}


// FILE CONSTRUCTOR

/// File constructor. It creates a data set object by loading the object members from a XML-type file. 
/// Please mind about the file format. This is specified in the User's Guide.
/// @param file_name Data set file name.

DataSet::DataSet(const std::string& file_name)
{
   set();

   set_default();

   load(file_name);

}


// COPY CONSTRUCTOR

/// Copy constructor. 
/// It creates a copy of an existing inputs targets data set object. 
/// @param other_data_set Data set object to be copied.

DataSet::DataSet(const DataSet& other_data_set)
{
   set_default();

   set(other_data_set);
}


// DESTRUCTOR

/// Destructor. 

DataSet::~DataSet(void)
{
}


// ASSIGNMENT OPERATOR

/// Assignment operator. 
/// It assigns to the current object the members of an existing data set object.
/// @param other_data_set Data set object to be assigned.

DataSet& DataSet::operator = (const DataSet& other_data_set)
{
   if(this != &other_data_set) 
   {
      data_file_name = other_data_set.data_file_name;

      // Data matrix

      data = other_data_set.data;

      // Variables

      variables = other_data_set.variables;

      // Instances

      instances = other_data_set.instances;

      // Utilities

      display = other_data_set.display;
   }

   return(*this);
}


// EQUAL TO OPERATOR

// bool operator == (const DataSet&) const method

/// Equal to operator. 
/// It compares this object with another object of the same class. 
/// It returns true if the members of the two objects have the same values, and false otherwise.
/// @ param other_data_set Data set object to be compared with.

bool DataSet::operator == (const DataSet& other_data_set) const
{
   if(data_file_name == other_data_set.data_file_name
   && data == other_data_set.data
   && variables == other_data_set.variables
   && instances == other_data_set.instances
   && display == other_data_set.display)
   {
      return(true);
   }
   else
   {
      return(false);
   }
}


// METHODS

// const Variables& get_variables(void) const

/// Returns a constant reference to the variables object composing this data set object. 

const Variables& DataSet::get_variables(void) const
{
   return(variables);
}


// Variables* get_variables_pointer(void) const

/// Returns a pointer to the variables object composing this data set object. 

Variables* DataSet::get_variables_pointer(void) 
{
   return(&variables);
}


// const Instances& get_instances(void) const

/// Returns a constant reference to the instances object composing this data set object. 

const Instances& DataSet::get_instances(void) const
{
   return(instances);
}


// Instances* get_instances_pointer(void)

/// Returns a pointer to the variables object composing this data set object. 

Instances* DataSet::get_instances_pointer(void) 
{
   return(&instances);
}


// const bool& get_display(void) const method

/// Returns true if messages from this class can be displayed on the screen,
/// or false if messages from this class can't be displayed on the screen.

const bool& DataSet::get_display(void) const
{
   return(display);   
}


// bool empty(void) const method

/// Returns true if the data matrix is empty, and false otherwise.

bool DataSet::empty(void) const
{
   return(data.empty());
}


// const Matrix<double>& get_data(void) const method

/// Returns a reference to the data matrix in the data set. 
/// The number of rows is equal to the number of instances.
/// The number of columns is equal to the number of variables. 

const Matrix<double>& DataSet::get_data(void) const
{
   return(data);
}


// const MissingValues& get_missing_values(void) const method

/// Returns a reference to the missing values object in the data set.

const MissingValues& DataSet::get_missing_values(void) const
{
   return(missing_values);
}


// MissingValues* get_missing_values_pointer(void) method

/// Returns a pointer to the missing values object in the data set.

MissingValues* DataSet::get_missing_values_pointer(void)
{
   return(&missing_values);
}


// const std::string& get_data_file_name(void) const method

/// Returns the name of the data file. 

const std::string& DataSet::get_data_file_name(void) const
{
   return(data_file_name);
}


// const bool& get_header(void) const

/// Returns true if the first line of the data file has a header with the names of the variables, and false otherwise.

const bool& DataSet::get_header(void) const
{
    return(header);
}


// const std::string& get_separator(void) const

/// Returns the string which will be used as separator in the data file.

const std::string& DataSet::get_separator(void) const
{
    return(separator);
}


// const std::string& get_missing_values_label(void) const

/// Returns the string which will be used as label for the missing values in the data file.

const std::string& DataSet::get_missing_values_label(void) const
{
    return(missing_values_label);
}


// const size_t& get_lags_number(void) const

/// Returns the number of lags to be used in a time series prediction application.

const size_t& DataSet::get_lags_number(void) const
{
    return(lags_number);
}


// const bool& get_autoassociation(void) const

/// Returns true if the data set will be used for an autoassociation application, and false otherwise.
/// In an autoassociation problem the target data is equal to the input data.

const bool& DataSet::get_autoassociation(void) const
{
    return(autoassociation);
}


// const Vector<size_t>& get_angular_variables(void) const method

/// Returns the indices of the angular variables in the data set.
/// When loading a data set with angular variables,
/// a transformation of the data will be performed in order to avoid discontinuities (from 359 degrees to 1 degree).

const Vector<size_t>& DataSet::get_angular_variables(void) const
{
    return(angular_variables);
}


// const AngularUnits& get_angular_units(void) const method

/// Returns the units used for the angular variables (Radians or Degrees).

const DataSet::AngularUnits& DataSet::get_angular_units(void) const
{
    return(angular_units);
}


// static ScalingUnscalingMethod get_scaling_unscaling_method(const std::string&) method

/// Returns a value of the scaling-unscaling method enumeration from a string containing the name of that method.
/// @param scaling_unscaling_method String with the name of the scaling and unscaling method.

DataSet::ScalingUnscalingMethod DataSet::get_scaling_unscaling_method(const std::string& scaling_unscaling_method)
{
    if(scaling_unscaling_method == "MinimumMaximum")
    {
        return(MinimumMaximum);
    }
    else if(scaling_unscaling_method == "MeanStandardDeviation")
    {
        return(MeanStandardDeviation);
    }
    else
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: DataSet class.\n"
               << "static ScalingUnscalingMethod get_scaling_unscaling_method(const std::string).\n"
               << "Unknown scaling-unscaling method: " << scaling_unscaling_method << ".\n";

        throw std::logic_error(buffer.str());
    }
}


// Matrix<double> arrange_training_data(void) const method

/// Returns a matrix with the training instances in the data set. 
/// The number of rows is the number of training instances.
/// The number of columns is the number of variables. 

Matrix<double> DataSet::arrange_training_data(void) const
{
   const size_t variables_number = variables.get_variables_number();
   
   Vector<size_t> variables_indices(0, 1, (int)variables_number-1);

   const Vector<size_t> training_indices = instances.arrange_training_indices();

   return(data.arrange_submatrix(training_indices, variables_indices));
}


// Matrix<double> arrange_generalization_data(void) const method

/// Returns a matrix with the generalization instances in the data set. 
/// The number of rows is the number of generalization instances.
/// The number of columns is the number of variables. 

Matrix<double> DataSet::arrange_generalization_data(void) const
{
   const size_t variables_number = variables.get_variables_number();

   const Vector<size_t> generalization_indices = instances.arrange_generalization_indices();

   Vector<size_t> variables_indices(0, 1, (int)variables_number-1);

   return(data.arrange_submatrix(generalization_indices, variables_indices));
}


// Matrix<double> arrange_testing_data(void) const method

/// Returns a matrix with the testing instances in the data set. 
/// The number of rows is the number of testing instances.
/// The number of columns is the number of variables. 

Matrix<double> DataSet::arrange_testing_data(void) const
{
   const size_t variables_number = variables.get_variables_number();
   Vector<size_t> variables_indices(0, 1, (int)variables_number-1);

   const Vector<size_t> testing_indices = instances.arrange_testing_indices();

   return(data.arrange_submatrix(testing_indices, variables_indices));
}


// Matrix<double> arrange_input_data(void) const method

/// Returns a matrix with the input variables in the data set.
/// The number of rows is the number of instances.
/// The number of columns is the number of input variables. 

Matrix<double> DataSet::arrange_input_data(void) const
{
   const size_t instances_number = instances.get_instances_number();
   Vector<size_t> indices(0, 1, (int)instances_number-1);

   const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();

   return(data.arrange_submatrix(indices, inputs_indices));
}


// Matrix<double> arrange_target_data(void) const method

/// Returns a matrix with the target variables in the data set.
/// The number of rows is the number of instances.
/// The number of columns is the number of target variables. 

Matrix<double> DataSet::arrange_target_data(void) const
{
   const size_t instances_number = instances.get_instances_number();
   Vector<size_t> indices(0, 1, (size_t)instances_number-1);

   const Vector<size_t> targets_indices = variables.arrange_targets_indices();

   return(data.arrange_submatrix(indices, targets_indices));
}


// Matrix<double> arrange_training_input_data(void) const method

/// Returns a matrix with training instances and input variables.
/// The number of rows is the number of training instances.
/// The number of columns is the number of input variables. 

Matrix<double> DataSet::arrange_training_input_data(void) const
{
   const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();

   const Vector<size_t> training_indices = instances.arrange_training_indices();

   return(data.arrange_submatrix(training_indices, inputs_indices));
}


// Matrix<double> arrange_training_target_data(void) const method

/// Returns a matrix with training instances and target variables.
/// The number of rows is the number of training instances.
/// The number of columns is the number of target variables. 

Matrix<double> DataSet::arrange_training_target_data(void) const 
{
   const Vector<size_t> training_indices = instances.arrange_training_indices();

   const Vector<size_t> targets_indices = variables.arrange_targets_indices();

   return(data.arrange_submatrix(training_indices, targets_indices));
}


// Matrix<double> get_generalization_input_data(void) const method

/// Returns a matrix with generalization instances and input variables.
/// The number of rows is the number of generalization instances.
/// The number of columns is the number of input variables. 

Matrix<double> DataSet::get_generalization_input_data(void) const
{
   const Vector<size_t> generalization_indices = instances.arrange_generalization_indices();

   const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();

   return(data.arrange_submatrix(generalization_indices, inputs_indices));
}


// Matrix<double> get_generalization_target_data(void) const method

/// Returns a matrix with generalization instances and target variables.
/// The number of rows is the number of generalization instances.
/// The number of columns is the number of target variables. 

Matrix<double> DataSet::get_generalization_target_data(void) const
{
   const Vector<size_t> generalization_indices = instances.arrange_generalization_indices();

   const Vector<size_t> targets_indices = variables.arrange_targets_indices();

   return(data.arrange_submatrix(generalization_indices, targets_indices));
}


// Matrix<double> arrange_testing_input_data(void) const method

/// Returns a matrix with testing instances and input variables.
/// The number of rows is the number of testing instances.
/// The number of columns is the number of input variables. 

Matrix<double> DataSet::arrange_testing_input_data(void) const
{
   const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();

   const Vector<size_t> testing_indices = instances.arrange_testing_indices();

   return(data.arrange_submatrix(testing_indices, inputs_indices));
}


// Matrix<double> arrange_testing_target_data(void) const method

/// Returns a matrix with testing instances and target variables.
/// The number of rows is the number of testing instances.
/// The number of columns is the number of target variables. 

Matrix<double> DataSet::arrange_testing_target_data(void) const
{
   const Vector<size_t> targets_indices = variables.arrange_targets_indices();

   const Vector<size_t> testing_indices = instances.arrange_testing_indices();

   return(data.arrange_submatrix(testing_indices, targets_indices));
}


// Vector<double> get_instance(const size_t&) const method

/// Returns the inputs and target values of a single instance in the data set. 
/// @param i Index of the instance. 

Vector<double> DataSet::get_instance(const size_t& i) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const size_t instances_number = instances.get_instances_number();

   if(i >= instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<double> get_instance(const size_t&) const method.\n"
             << "Index of instance must be less than number of instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   // Get instance

   return(data.arrange_row(i));
}


// Vector<double> get_instance(const size_t&, const Vector<size_t>&) const method

/// Returns the inputs and target values of a single instance in the data set.
/// @param instance_index Index of the instance.
/// @param variables_indices Indices of the variables.

Vector<double> DataSet::get_instance(const size_t& instance_index, const Vector<size_t>& variables_indices) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG

   const size_t instances_number = instances.get_instances_number();

   if(instance_index >= instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<double> get_instance(const size_t&, const Vector<size_t>&) const method.\n"
             << "Index of instance must be less than number of instances.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Get instance

   return(data.arrange_row(instance_index, variables_indices));
}


// Vector<double> get_variable(const size_t&) const method

/// Returns all the instances of a single variable in the data set. 
/// @param i Index of the variable. 

Vector<double> DataSet::get_variable(const size_t& i) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const size_t variables_number = variables.get_variables_number();

   if(i >= variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<double> get_variable(const size_t&) const method.\n"
             << "Index of variable must be less than number of instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   // Get variable

   return(data.arrange_column(i));
}


// Vector<double> get_variable(const size_t&, const Vector<size_t>&) const method

/// Returns a given set of instances of a single variable in the data set.
/// @param variable_index Index of the variable.
/// @param instances_indices Indices of the instances.

Vector<double> DataSet::get_variable(const size_t& variable_index, const Vector<size_t>& instances_indices) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG

   const size_t variables_number = variables.get_variables_number();

   if(variable_index >= variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<double> get_variable(const size_t&, const Vector<double>&) const method.\n"
             << "Index of variable must be less than number of instances.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Get variable

   return(data.arrange_column(variable_index, instances_indices));
}


// void set(void) method

/// Sets zero instances and zero variables in the data set. 

void DataSet::set(void)
{

   data_file_name = "";

   data.set();

   variables.set();
   instances.set();

   display = true;
}


// void set(const Matrix<double>&) method

/// Sets all variables from a data matrix.
/// @param new_data Data matrix.

void DataSet::set(const Matrix<double>& new_data)
{
   data_file_name = "";

   const size_t variables_number = new_data.get_columns_number();
   const size_t instances_number = new_data.get_rows_number();

   data = new_data;

   variables.set(variables_number);
   instances.set(instances_number);

   display = true;
}


// void set(const size_t&, const size_t&) method

/// Sets new numbers of instances and variables in the inputs targets data set. 
/// All the instances are set for training. 
/// All the variables are set as inputs. 
/// @param new_variables_number Number of variables.
/// @param new_instances_number Number of instances.

void DataSet::set(const size_t& new_variables_number, const size_t& new_instances_number)
{
    // Control sentence (if debug)

    #ifndef NDEBUG

    if(new_variables_number == 0)
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception: DataSet class.\n"
              << "void set(const size_t&, const size_t&) method.\n"
              << "Number of variables must be greater than zero.\n";

       throw std::logic_error(buffer.str());
    }

    if(new_instances_number == 0)
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception: DataSet class.\n"
              << "void set(const size_t&, const size_t&) method.\n"
              << "Number of instances must be greater than zero.\n";

       throw std::logic_error(buffer.str());
    }

    #endif

   data.set(new_instances_number, new_variables_number);

   instances.set(new_instances_number);

   variables.set(new_variables_number);
}


// void set(const size_t&, const size_t&, const size_t&) method

/// Sets new numbers of instances and inputs and target variables in the data set.
/// The variables in the data set are the number of inputs plus the number of targets. 
///
/// @param new_inputs_number Number of input variables.
/// @param new_targets_number Number of target variables.
/// @param new_instances_number Number of instances.

void DataSet::set(const size_t& new_inputs_number, const size_t& new_targets_number, const size_t& new_instances_number)
{   
   data_file_name = "";

   const size_t new_variables_number = new_inputs_number + new_targets_number;

   data.set(new_instances_number, new_variables_number);

   // Variables

   variables.set(new_inputs_number, new_targets_number);

   // Instances

   instances.set(new_instances_number);

   display = true;
}


// void set(const DataSet& other_data_set)

/// Sets the members of this data set object with those from another data set object. 
/// @param other_data_set Data set object to be copied. 

void DataSet::set(const DataSet& other_data_set)
{
   data_file_name = other_data_set.data_file_name;

   header = other_data_set.header;

   separator = other_data_set.separator;

   missing_values_label = other_data_set.missing_values_label;

   data = other_data_set.data;

   variables = other_data_set.variables;

   instances = other_data_set.instances;

   display = other_data_set.display;
}


// void set(const tinyxml2::XMLDocument&) method

/// Sets the data set members from a XML document.
/// @param data_set_document TinyXML document containing the member data.

void DataSet::set(const tinyxml2::XMLDocument& data_set_document)
{
    set_default();

   from_XML(data_set_document);
}


// void set(const std::string&) method

/// Sets the data set members by loading them from a XML file. 
/// @param file_name Data set XML file_name.

void DataSet::set(const std::string& file_name)
{
   load(file_name);
}


// void set_display(const bool&) method

/// Sets a new display value. 
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.

void DataSet::set_display(const bool& new_display)
{
   display = new_display;
}


// void set_default(void) method

/// Sets the default member values:
/// <ul>
/// <li> Display: True.
/// </ul>

void DataSet::set_default(void)
{
    header = false;

    separator = " ";

    missing_values_label = "?";

    lags_number = 0;

    autoassociation = false;

    angular_units = Degrees;

    display = true;
}


// void set_data(const Matrix<double>&) method

/// Sets a new data matrix. 
/// The number of rows must be equal to the number of instances.
/// The number of columns must be equal to the number of variables. 
/// Indices of all training, generalization and testing instances and inputs and target variables do not change.
/// @param new_data Data matrix.

void DataSet::set_data(const Matrix<double>& new_data)
{
   // Control sentence (if debug)
/*
   #ifndef NDEBUG 

   const size_t rows_number = new_data.get_rows_number();
   const size_t instances_number = instances.get_instances_number();

   if(rows_number != instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_data(const Matrix<double>&) method.\n"
             << "Number of rows (" << rows_number << ") must be equal to number of instances (" << instances_number << ").\n";

	  throw std::logic_error(buffer.str());
   }

   const size_t columns_number = new_data.get_columns_number();
   const size_t variables_number = variables.get_variables_number();

   if(columns_number != variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_data(const Matrix<double>&) method.\n"
             << "Number of columns (" << columns_number << ") must be equal to number of variables (" << variables_number << ").\n";

	  throw std::logic_error(buffer.str());
   }

   #endif
*/
   // Set data
   
   data = new_data;   

   instances.set_instances_number(data.get_rows_number());
   variables.set_variables_number(data.get_columns_number());

}


// void set_data_file_name(const std::string&) method

/// Sets the name of the data file.
/// It also loads the data from that file. 
/// Moreover, it sets the variables and instances objects. 
/// @param new_data_file_name Name of the file containing the data.

void DataSet::set_data_file_name(const std::string& new_data_file_name)
{   
   data_file_name = new_data_file_name;
}


// void set_header(const bool&) method

/// Sets if the data file contains a header with the names of the variables.

void DataSet::set_header(const bool& new_header)
{
    header = new_header;
}


// void set_separator(const std::string&) method

/// Sets a new separator character.
/// @param new_separator Separator character.

void DataSet::set_separator(const std::string& new_separator)
{
    separator = new_separator;
}


// void set_missing_values_label(const std::string&) method

/// Sets a new label for the missing values.
/// @param new_missing_values_label Label for the missing values.

void DataSet::set_missing_values_label(const std::string& new_missing_values_label)
{
    missing_values_label = new_missing_values_label;
}


// void set_lags_number(const size_t&)

/// Sets a new number of lags to be defined for a time series prediction application.
/// When loading the data file, the time series data will be modified according to this number.
/// @param new_lags_number Number of lags (x-1, ..., x-l) to be used.

void DataSet::set_lags_number(const size_t& new_lags_number)
{
    lags_number = new_lags_number;
}


// void set_autoassociation(const size_t&)

/// Sets a new autoasociation flag.
/// If the new value is true, the data will be processed for autoassociation when loading.
/// That is, the data file will contain the input data. The target data will be created as being equal to the input data.
/// If the autoassociation value is set to false, the data from the file will not be processed.
/// @param new_autoassociation Autoassociation value.

void DataSet::set_autoassociation(const bool& new_autoassociation)
{
    autoassociation = new_autoassociation;
}


// void set_angular_variables(const Vector<size_t>&)

void DataSet::set_angular_variables(const Vector<size_t>& new_angular_variables)
{
    angular_variables = new_angular_variables;
}


// void set_angular_units(AngularUnits&)

void DataSet::set_angular_units(AngularUnits& new_angular_units)
{
    angular_units = new_angular_units;
}



// void set_instances_number(const size_t&) method

/// Sets a new number of instances in the data set. 
/// All instances are also set for training. 
/// The indices of the inputs and target variables do not change. 
/// @param new_instances_number Number of instances. 

void DataSet::set_instances_number(const size_t& new_instances_number)
{
   const size_t variables_number = variables.get_variables_number();

   data.set(new_instances_number, variables_number);

   instances.set(new_instances_number);
}


// void set_variables_number(const size_t&) method

/// Sets a new number of input variables in the data set. 
/// The indices of the training, generalization and testing instances do not change. 
/// All variables are set as inputs. 
/// @param new_variables_number Number of variables. 

void DataSet::set_variables_number(const size_t& new_variables_number)
{
   const size_t instances_number = instances.get_instances_number();

   data.set(instances_number, new_variables_number);

   variables.set(new_variables_number);
}


// void set_instance(const size_t&, const Vector<double>&)

/// Sets new inputs and target values of a single instance in the data set. 
/// @param instance_index Index of the instance. 
/// @param instance New inputs and target values of the instance.

void DataSet::set_instance(const size_t& instance_index, const Vector<double>& instance)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const size_t instances_number = instances.get_instances_number();

   if(instance_index >= instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_instance(const size_t&, const Vector<double>&) method.\n"
             << "Index of instance must be less than number of instances.\n";

	  throw std::logic_error(buffer.str());
   }

   const size_t size = instance.size();
   const size_t variables_number = variables.get_variables_number();

   if(size != variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_instance(const size_t&, const Vector<double>&) method.\n"
             << "Size (" << size << ") must be equal to number of variables (" << variables_number << ").\n";

	  throw std::logic_error(buffer.str());
   } 

   #endif

   // Set instance

   data.set_row(instance_index, instance);
}


// void add_instance(const Vector<double>&) method

/// Adds a new instance to the data matrix from a vector of real numbers.
/// The size of that vector must be equal to the number of variables. 
/// Note that resizing is here necessary and therefore computationally expensive. 
/// All instances are also set for training. 
/// @param instance Input and target values of the instance to be added. 

void DataSet::add_instance(const Vector<double>& instance)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const size_t size = instance.size();
   const size_t variables_number = variables.get_variables_number();

   if(size != variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void add_instance(const Vector<double>&) method.\n"
             << "Size of instance must be equal to number of variables.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const size_t instances_number = instances.get_instances_number();

   data.append_row(instance);

   instances.set(instances_number+1);
}


// void subtract_instance(size_t) method

/// Substracts the inputs-targets instance with a given index from the data set.
/// All instances are also set for training. 
/// Note that resizing is here necessary and therefore computationally expensive. 
/// @param instance_index Index of instance to be removed. 

void DataSet::subtract_instance(const size_t& instance_index)
{
    const size_t instances_number = instances.get_instances_number();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(instance_index >= instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void subtract_instance(size_t) method.\n"
             << "Index of instance must be less than number of instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   data.subtract_row(instance_index);

   instances.set_instances_number(instances_number-1);

}


// void append_variable(const Vector<double>&) method

/// Appends a variable with given values to the data matrix.
/// @param variable Vector of values. The size must be equal to the number of instances. 

void DataSet::append_variable(const Vector<double>& variable)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const size_t size = variable.size();
   const size_t instances_number = instances.get_instances_number();

   if(size != instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void append_variable(const Vector<double>&) method.\n"
             << "Size of variable must be equal to number of instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const size_t variables_number = variables.get_variables_number();

   data.append_column(variable);

   Matrix<double> new_data(data);

   const size_t new_variables_number = variables_number + 1;

   set_variables_number(new_variables_number);

   set_data(new_data);
}


// void subtract_variable(size_t) method

/// Removes a variable with given index from the data matrix.
/// @param variable_index Index of variable to be subtracted. 

void DataSet::subtract_variable(const size_t& variable_index)
{
   const size_t variables_number = variables.get_variables_number();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(variable_index >= variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void subtract_variable(size_t) method.\n"
             << "Index of variable must be less than number of variables.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   data.subtract_column(variable_index);

   Matrix<double> new_data(data);

   const size_t new_variables_number = variables_number - 1;

   set_variables_number(new_variables_number);

   set_data(new_data);
}


// Vector<size_t> unuse_constant_variables(void) method

/// Removes the input of target indices of that variables with zero standard deviation.
/// It might change the size of the vectors containing the inputs and targets indices. 

Vector<size_t> DataSet::unuse_constant_variables(void)
{
   const size_t variables_number = variables.get_variables_number();

   // Control sentence (if debug)

   #ifndef NDEBUG

   if(variables_number == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<size_t> unuse_constant_variables(void) method.\n"
             << "Number of variables is zero.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Vector<size_t> constant_variables;

   for(size_t i = 0; i < variables_number; i++)
   {
      if(variables.get_use(i) != Variables::Unused
      && data.arrange_column(i).is_constant())
      {
         variables.set_use(i, Variables::Unused);
         constant_variables.push_back(i);
	  }
   }

   return(constant_variables);
}


// Vector<size_t> unuse_repeated_instances(void) method

/// Removes the training, generalization and testing indices of that instances which are repeated in the data matrix.
/// It might change the size of the vectors containing the training, generalization and testing indices. 

Vector<size_t> DataSet::unuse_repeated_instances(void)
{
    const size_t instances_number = instances.get_instances_number();

    // Control sentence (if debug)

    #ifndef NDEBUG

    if(instances_number == 0)
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception: DataSet class.\n"
              << "Vector<size_t> unuse_repeated_indices(void) method.\n"
              << "Number of instances is zero.\n";

       throw std::logic_error(buffer.str());
    }

    #endif

    Vector<size_t> repeated_instances;

	Vector<double> instance_i;
	Vector<double> instance_j;    

    int i = 0;

    #pragma omp parallel for private(i, instance_i, instance_j)

    for(i = 0; i < (int)instances_number; i++)
	{
	   instance_i = get_instance(i);

       for(size_t j = i+1; j < instances_number; j++)
	   {	      
          instance_j = get_instance(j);

          if(instances.get_use(j) != Instances::Unused
          && instance_j == instance_i)
		  {
              instances.set_use(j, Instances::Unused);
              repeated_instances.push_back(j);
		  }
	   }	    
	}

    return(repeated_instances);
}


// Vector<Histogram> calculate_data_histograms(const size_t&) const method

/// Returns a histogram for each variable with a given number of bins. 
/// The default number of bins is 10.
/// The format is a vector of subvectors of subsubvectors.
/// The size of the vector is the number of variables. 
/// The size of the subvectors is 2 (centers and frequencies).
/// The size of the subsubvectors is the number of bins.
/// @param bins_number Number of bins.

Vector< Histogram<double> > DataSet::calculate_data_histograms(const size_t& bins_number) const
{
   const size_t variables_number = variables.get_variables_number();

   const Vector< Vector<size_t> > missing_indices = missing_values.arrange_missing_indices(variables_number);

   return(data.calculate_histograms_missing_values(missing_indices, bins_number));
}


// Vector< Vector<double> > calculate_data_statistics(void) const method

/// Returns a vector of vectors containing some basic statistics of all the variables in the data set. 
/// The size of this vector is four. The subvectors are:
/// <ul>
/// <li> Minimum.
/// <li> Maximum.
/// <li> Mean.
/// <li> Standard deviation.
/// </ul> 

Vector< Statistics<double> > DataSet::calculate_data_statistics(void) const
{
    const size_t variables_number = variables.get_variables_number();

    const Vector< Vector<size_t> > missing_indices = missing_values.arrange_missing_indices(variables_number);

    return(data.calculate_statistics_missing_values(missing_indices));
}


// Matrix<double> calculate_data_statistics_matrix(void) const method

/// Returns all the variables statistics from a single matrix.
/// The number of rows is the number of variables.
/// The number of columns is four (minimum, maximum, mean and standard deviation).

Matrix<double> DataSet::calculate_data_statistics_matrix(void) const
{
    const size_t variables_number = variables.get_variables_number();

    const Vector< Vector<size_t> > missing_indices = missing_values.arrange_missing_indices(variables_number);

    const Vector< Statistics<double> > data_statistics = data.calculate_statistics_missing_values(missing_indices);

    Matrix<double> data_statistics_matrix(variables_number, 4);

    for(size_t i = 0; i < variables_number; i++)
    {
        data_statistics_matrix.set_row(i, data_statistics[i].to_vector());
    }

    return(data_statistics_matrix);
}


// Vector< Statistics<double> > calculate_training_instances_statistics(void) const method

/// Returns a vector of vectors containing some basic statistics of all variables on the training instances. 
/// The size of this vector is four. The subvectors are:
/// <ul>
/// <li> Training data mean.
/// <li> Training data standard deviation.
/// <li> Training data minimum.
/// <li> Training data maximum.
/// </ul> 

Vector< Statistics<double> > DataSet::calculate_training_instances_statistics(void) const
{
    const size_t variables_number = variables.get_variables_number();

   const Vector<size_t> training_indices = instances.arrange_training_indices();

   const Vector< Vector<size_t> > missing_indices = missing_values.arrange_missing_indices(variables_number);

   return(data.calculate_rows_statistics_missing_values(training_indices, missing_indices));
}


// Vector< Statistics<double> > calculate_generalization_instances_statistics(void) const method

/// Returns a vector of vectors containing some basic statistics of all variables on the generalization instances. 
/// The size of this vector is four. The subvectors are:
/// <ul>
/// <li> Generalization data mean.
/// <li> Generalization data standard deviation.
/// <li> Generalization data minimum.
/// <li> Generalization data maximum.
/// </ul> 

Vector< Statistics<double> > DataSet::calculate_generalization_instances_statistics(void) const
{
    const size_t variables_number = variables.get_variables_number();

    const Vector<size_t> generalization_indices = instances.arrange_generalization_indices();

    const Vector< Vector<size_t> > missing_indices = missing_values.arrange_missing_indices(variables_number);

   return(data.calculate_rows_statistics_missing_values(generalization_indices, missing_indices));
}


// Vector< Statistics<double> > calculate_testing_instances_statistics(void) const method

/// Returns a vector of vectors containing some basic statistics of all variables on the testing instances. 
/// The size of this vector is four. The subvectors are:
/// <ul>
/// <li> Testing data mean.
/// <li> Testing data standard deviation.
/// <li> Testing data minimum.
/// <li> Testing data maximum.
/// </ul> 

Vector< Statistics<double> > DataSet::calculate_testing_instances_statistics(void) const
{
    const size_t variables_number = variables.get_variables_number();

    const Vector<size_t> testing_indices = instances.arrange_testing_indices();

    const Vector< Vector<size_t> > missing_indices = missing_values.arrange_missing_indices(variables_number);

   return(data.calculate_rows_statistics_missing_values(testing_indices, missing_indices));
}


// Vector< Statistics<double> > calculate_inputs_statistics(void) const method

/// Returns a vector of vectors with some basic statistics of the input variables on all instances. 
/// The size of this vector is four. The subvectors are:
/// <ul>
/// <li> Input variables mean.
/// <li> Input variables standard deviation.
/// <li> Input variables minimum.
/// <li> Input variables maximum.
/// </ul> 

Vector< Statistics<double> > DataSet::calculate_inputs_statistics(void) const
{
    const size_t variables_number = variables.get_variables_number();

    const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();

    const Vector< Vector<size_t> > missing_indices = missing_values.arrange_missing_indices(variables_number);

   return(data.calculate_columns_statistics_missing_values(inputs_indices, missing_indices));
}


// Vector< Statistics<double> > calculate_targets_statistics(void) const method

/// Returns a vector of vectors with some basic statistics of the target variables on all instances. 
/// The size of this vector is four. The subvectors are:
/// <ul>
/// <li> Target variables mean.
/// <li> Target variables standard deviation.
/// <li> Target variables minimum.
/// <li> Target variables maximum.
/// </ul> 

Vector< Statistics<double> > DataSet::calculate_targets_statistics(void) const
{
    const size_t variables_number = variables.get_variables_number();

   const Vector<size_t> targets_indices = variables.arrange_targets_indices();

   const Vector< Vector<size_t> > missing_indices = missing_values.arrange_missing_indices(variables_number);

   return(data.calculate_columns_statistics_missing_values(targets_indices, missing_indices));
}


// Vector<double> calculate_training_target_data_mean(void) const method

/// Returns the mean values of the target variables on the training instances. 

Vector<double> DataSet::calculate_training_target_data_mean(void) const
{
   const size_t variables_number = variables.get_variables_number();

   const Vector<size_t> targets_indices = variables.arrange_targets_indices();

   const Vector<size_t> training_indices = instances.arrange_training_indices();

   const Vector< Vector<size_t> > missing_indices = missing_values.arrange_missing_indices(variables_number);

   return(data.calculate_mean_missing_values(training_indices, targets_indices, missing_indices));
}


// Vector<double> calculate_generalization_target_data_mean(void) const method

/// Returns the mean values of the target variables on the generalization instances. 

Vector<double> DataSet::calculate_generalization_target_data_mean(void) const
{
    const size_t variables_number = variables.get_variables_number();

    const Vector<size_t> targets_indices = variables.arrange_targets_indices();

   const Vector<size_t> generalization_indices = instances.arrange_generalization_indices();

   const Vector< Vector<size_t> > missing_indices = missing_values.arrange_missing_indices(variables_number);

   return(data.calculate_mean_missing_values(generalization_indices, targets_indices, missing_indices));
}


// Vector<double> calculate_testing_target_data_mean(void) const method

/// Returns the mean values of the target variables on the testing instances. 

Vector<double> DataSet::calculate_testing_target_data_mean(void) const
{
    const size_t variables_number = variables.get_variables_number();

    const Vector<size_t> testing_indices = instances.arrange_testing_indices();

   const Vector<size_t> targets_indices = variables.arrange_targets_indices();

   const Vector< Vector<size_t> > missing_indices = missing_values.arrange_missing_indices(variables_number);

   return(data.calculate_mean_missing_values(testing_indices, targets_indices, missing_indices));
}


// Matrix<double> calculate_linear_correlations(void) const method

/// Calculates the linear correlations between all outputs and all inputs.
/// It returns a matrix with number of rows the targets number and number of columns the inputs number.
/// Each element contains the linear correlation between a single target and a single output.

Matrix<double> DataSet::calculate_linear_correlations(void) const
{
    const size_t variables_number = variables.get_variables_number();

   const size_t inputs_number = variables.count_inputs_number();
   const size_t targets_number = variables.count_targets_number();

   const Vector<size_t> input_indices = variables.arrange_inputs_indices();
   const Vector<size_t> target_indices = variables.arrange_targets_indices();

   size_t input_index;
   size_t target_index;

   const size_t instances_number = instances.get_instances_number();

   const Vector< Vector<size_t> > missing_indices = missing_values.arrange_missing_indices(variables_number);

   Vector<double> input_variable(instances_number);
   Vector<double> target_variable(instances_number);

   Matrix<double> linear_correlations(targets_number, inputs_number);

   for(size_t i = 0; i < targets_number; i++)
   {
       target_index = target_indices[i];

       target_variable = data.arrange_column(target_index);

       for(size_t j = 0; j < inputs_number; j++)
       {
           input_index = input_indices[i];

           input_variable = data.arrange_column(input_index);

           linear_correlations(i,j) = target_variable.calculate_linear_correlation_missing_values(input_variable, missing_indices[input_index]);
       }
   }

   return(linear_correlations);
}


// void scale_data_mean_standard_deviation(const Vector< Statistics<double> >&) const method

/// Scales the data matrix with given mean and standard deviation values.
/// It updates the data matrix.
/// @param data_statistics Vector of statistics structures for all the variables in the data set.
/// The size of that vector must be equal to the number of variables.

void DataSet::scale_data_mean_standard_deviation(const Vector< Statistics<double> >& data_statistics)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   std::ostringstream buffer;

   const size_t columns_number = data.get_columns_number();

   const size_t statistics_size = data_statistics.size();

   if(statistics_size != columns_number)
   {
      buffer << "OpenNN Exception: DataSet class.\n"
             << "void scale_data_mean_standard_deviation(const Vector< Statistics<double> >&) method.\n"
             << "Size of statistics must be equal to number of columns.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const size_t variables_number = variables.get_variables_number();

   for(size_t i = 0; i < variables_number; i++)
   {
       if(display && data_statistics[i].standard_deviation < 1.0e-99)
       {
          std::cout << "OpenNN Warning: DataSet class.\n"
                    << "void scale_data_mean_standard_deviation(const Vector< Statistics<Type> >&) method.\n"
                    << "Standard deviation of variable " <<  i << " is zero.\n"
                    << "That variable won't be scaled.\n";
        }
    }

   data.scale_mean_standard_deviation(data_statistics);
}


// Vector< Statistics<double> > scale_data_minimum_maximum(void) method

/// Scales the data using the minimum and maximum method,
/// and the minimum and maximum values calculated from the data matrix.
/// It also returns the statistics from all columns.

Vector< Statistics<double> > DataSet::scale_data_minimum_maximum(void)
{
    const Vector< Statistics<double> > data_statistics = calculate_data_statistics();

    scale_data_minimum_maximum(data_statistics);

    return(data_statistics);
}


// Vector< Statistics<double> > scale_data_mean_standard_deviation(void) method

/// Scales the data using the mean and standard deviation method,
/// and the mean and standard deviation values calculated from the data matrix.
/// It also returns the statistics from all columns.

Vector< Statistics<double> > DataSet::scale_data_mean_standard_deviation(void)
{
    const Vector< Statistics<double> > data_statistics = calculate_data_statistics();

    scale_data_mean_standard_deviation(data_statistics);

    return(data_statistics);
}


// void scale_data_minimum_maximum(const Vector< Statistics<double> >&) method

/// Scales the data matrix with given minimum and maximum values.
/// It updates the data matrix.
/// @param data_statistics Vector of statistics structures for all the variables in the data set.
/// The size of that vector must be equal to the number of variables.

void DataSet::scale_data_minimum_maximum(const Vector< Statistics<double> >& data_statistics)
{
    const size_t variables_number = variables.get_variables_number();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   std::ostringstream buffer;

   const size_t statistics_size = data_statistics.size();

   if(statistics_size != variables_number)
   {
      buffer << "OpenNN Exception: DataSet class.\n"
             << "void scale_data_minimum_maximum(const Vector< Statistics<double> >&) method.\n"
             << "Size of data statistics must be equal to number of variables.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   for(size_t i = 0; i < variables_number; i++)
   {
       if(display && data_statistics[i].maximum-data_statistics[i].minimum < 1.0e-99)
       {
          std::cout << "OpenNN Warning: DataSet class.\n"
                    << "void scale_data_minimum_maximum(const Vector< Statistics<Type> >&) method.\n"
                    << "Range of variable " <<  i << " is zero.\n"
                    << "That variable won't be scaled.\n";
        }
    }


   data.scale_minimum_maximum(data_statistics);
}


// void scale_data(const std::string&, const Vector< Statistics<double> >&) method

/// Scales the data matrix.
/// The method to be used is that in the scaling and unscaling method variable. 
/// @param scaling_unscaling_method_string String with the name of the scaling-unscaling method
/// (MinimumMaximum or MeanStandardDeviation).
/// @param data_statistics Vector of statistics structures for all the variables in the data set.
/// The size of that vector must be equal to the number of variables.

void DataSet::scale_data(const std::string& scaling_unscaling_method_string, const Vector< Statistics<double> >& data_statistics)
{
   switch(get_scaling_unscaling_method(scaling_unscaling_method_string))
   {
      case MinimumMaximum:
      {
         scale_data_minimum_maximum(data_statistics);
      }            
      break;

      case MeanStandardDeviation:
      {
         scale_data_mean_standard_deviation(data_statistics);
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: DataSet class\n"
                << "void scale_data(const std::string&, const Vector< Vector<double> >&) method.\n"
                << "Unknown data scaling and unscaling method.\n";

	     throw std::logic_error(buffer.str());
      }
      break;
   }
}


// Vector< Statistics<double> > scale_data(void) method

/// Calculates the data statistics, scales the data with that values and returns the statistics. 
/// The method to be used is that in the scaling and unscaling method variable. 

Vector< Statistics<double> > DataSet::scale_data(const std::string& scaling_unscaling_method)
{
   const Vector< Statistics<double> > statistics = data.calculate_statistics();

   switch(get_scaling_unscaling_method(scaling_unscaling_method))
   {
      case MinimumMaximum:
      {
         scale_data_minimum_maximum(statistics);
      }            
      break;

      case MeanStandardDeviation:
      {
         scale_data_mean_standard_deviation(statistics);
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: DataSet class\n"
                << "Vector< Statistics<double> > scale_data(const std::string&) method.\n"
                << "Unknown scaling and unscaling method.\n";

	     throw std::logic_error(buffer.str());
      }
      break;
   }

   return(statistics);
}


// void scale_inputs_mean_standard_deviation(const Vector< Statistics<double> >&) method

/// Scales the input variables with given mean and standard deviation values.
/// It updates the input variables of the data matrix.
/// @param inputs_statistics Vector of statistics structures for the input variables.
/// The size of that vector must be equal to the number of inputs.

void DataSet::scale_inputs_mean_standard_deviation(const Vector< Statistics<double> >& inputs_statistics)
{
    const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();

    data.scale_columns_mean_standard_deviation(inputs_statistics, inputs_indices);
}


// Vector< Statistics<double> > scale_inputs_mean_standard_deviation(void) method

/// Scales the input variables with the calculated mean and standard deviation values from the data matrix.
/// It updates the input variables of the data matrix.
/// It also returns a vector of vectors with the variables statistics. 

Vector< Statistics<double> > DataSet::scale_inputs_mean_standard_deviation(void)
{
    // Control sentence (if debug)

    #ifndef NDEBUG

    if(data.empty())
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception: DataSet class.\n"
              << "Vector< Statistics<double> > scale_inputs_mean_standard_deviation(void) method.\n"
              << "Data file is not loaded.\n";

       throw std::logic_error(buffer.str());
    }

    #endif

   const Vector< Statistics<double> > inputs_statistics = calculate_inputs_statistics();

   scale_inputs_mean_standard_deviation(inputs_statistics);

   return(inputs_statistics);
}


// void scale_inputs_minimum_maximum(const Vector< Statistics<double> >&) method

/// Scales the input variables with given minimum and maximum values.
/// It updates the input variables of the data matrix.
/// @param inputs_statistics Vector of statistics structures for all the inputs in the data set.
/// The size of that vector must be equal to the number of input variables.

void DataSet::scale_inputs_minimum_maximum(const Vector< Statistics<double> >& inputs_statistics)
{
    const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();

    data.scale_columns_minimum_maximum(inputs_statistics, inputs_indices);
}


// Vector< Statistics<double> > scale_inputs_minimum_maximum(void) method

/// Scales the input variables with the calculated minimum and maximum values from the data matrix.
/// It updates the input variables of the data matrix.
/// It also returns a vector of vectors with the minimum and maximum values of the input variables. 

Vector< Statistics<double> > DataSet::scale_inputs_minimum_maximum(void)
{
    // Control sentence (if debug)

    #ifndef NDEBUG

    if(data.empty())
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception: DataSet class.\n"
              << "Vector< Statistics<double> > scale_inputs_minimum_maximum(void) method.\n"
              << "Data file is not loaded.\n";

       throw std::logic_error(buffer.str());
    }

    #endif

   const Vector< Statistics<double> > inputs_statistics = calculate_inputs_statistics();

   scale_inputs_minimum_maximum(inputs_statistics);

   return(inputs_statistics);
}


// Vector< Vector<double> > scale_inputs(const std::string&) method

/// Calculates the input and target variables statistics. 
/// Then it scales the input variables with that values.
/// The method to be used is that in the scaling and unscaling method variable. 
/// Finally, it returns the statistics. 

Vector< Statistics<double> > DataSet::scale_inputs(const std::string& scaling_unscaling_method)
{
    switch(get_scaling_unscaling_method(scaling_unscaling_method))
   {
      case MinimumMaximum:
      {
         return(scale_inputs_minimum_maximum());
      }            
      break;

      case MeanStandardDeviation:
      {
         return(scale_inputs_mean_standard_deviation());
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: DataSet class\n"
                << "Vector< Statistics<double> > scale_inputs(void) method.\n"
                << "Unknown scaling and unscaling method.\n";

	     throw std::logic_error(buffer.str());
      }
      break;
   }
}


// void scale_inputs(const std::string&, const Vector< Statistics<double> >&) method

/// Calculates the input and target variables statistics.
/// Then it scales the input variables with that values.
/// The method to be used is that in the scaling and unscaling method variable.

void DataSet::scale_inputs(const std::string& scaling_unscaling_method, const Vector< Statistics<double> >& inputs_statistics)
{
   switch(get_scaling_unscaling_method(scaling_unscaling_method))
   {
      case MinimumMaximum:
      {
         scale_inputs_minimum_maximum(inputs_statistics);
      }
      break;

      case MeanStandardDeviation:
      {
         scale_inputs_mean_standard_deviation(inputs_statistics);
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: DataSet class\n"
                << "void scale_inputs(const std::string&, const Vector< Statistics<double> >&) method.\n"
                << "Unknown scaling and unscaling method.\n";

         throw std::logic_error(buffer.str());
      }
      break;
   }
}


// void scale_targets_mean_standard_deviation(const Vector< Statistics<double> >&)

/// Scales the target variables with given mean and standard deviation values.
/// It updates the target variables of the data matrix.
/// @param targets_statistics Vector of statistics structures for all the targets in the data set.
/// The size of that vector must be equal to the number of target variables.

void DataSet::scale_targets_mean_standard_deviation(const Vector< Statistics<double> >& targets_statistics)
{
    const Vector<size_t> targets_indices = variables.arrange_targets_indices();

    data.scale_columns_mean_standard_deviation(targets_statistics, targets_indices);
}


// Vector< Statistics<double> > scale_targets_mean_standard_deviation(void) method

/// Scales the target variables with the calculated mean and standard deviation values from the data matrix.
/// It updates the target variables of the data matrix.
/// It also returns a vector of statistics structures with the basic statistics of all the variables.

Vector< Statistics<double> > DataSet::scale_targets_mean_standard_deviation(void)
{    
    // Control sentence (if debug)

    #ifndef NDEBUG

    if(data.empty())
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception: DataSet class.\n"
              << "Vector< Statistics<double> > scale_targets_mean_standard_deviation(void) method.\n"
              << "Data file is not loaded.\n";

       throw std::logic_error(buffer.str());
    }

    #endif

   const Vector< Statistics<double> > targets_statistics = calculate_targets_statistics();

   scale_targets_mean_standard_deviation(targets_statistics);

   return(targets_statistics);
}


// void scale_targets_minimum_maximum(const Vector< Statistics<double> >&) method

/// Scales the target variables with given minimum and maximum values.
/// It updates the target variables of the data matrix.
/// @param targets_statistics Vector of statistics structures for all the targets in the data set.
/// The size of that vector must be equal to the number of target variables.

void DataSet::scale_targets_minimum_maximum(const Vector< Statistics<double> >& targets_statistics)
{
    // Control sentence (if debug)

    #ifndef NDEBUG

    if(data.empty())
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception: DataSet class.\n"
              << "Vector< Statistics<double> > scale_targets_minimum_maximum(void) method.\n"
              << "Data file is not loaded.\n";

       throw std::logic_error(buffer.str());
    }

    #endif

    const Vector<size_t> targets_indices = variables.arrange_targets_indices();

    data.scale_columns_minimum_maximum(targets_statistics, targets_indices);
}


// Vector< Statistics<double> > scale_targets_minimum_maximum(void) method

/// Scales the target variables with the calculated minimum and maximum values from the data matrix.
/// It updates the target variables of the data matrix.
/// It also returns a vector of vectors with the statistics of the input target variables. 

Vector< Statistics<double> > DataSet::scale_targets_minimum_maximum(void)
{
   const Vector< Statistics<double> > targets_statistics = calculate_targets_statistics();

   scale_targets_minimum_maximum(targets_statistics);

   return(targets_statistics);
}


// Vector< Statistics<double> > scale_targets(const std::string&) method

/// Calculates the input and target variables statistics. 
/// Then it scales the target variables with that values.
/// The method to be used is that in the scaling and unscaling method variable. 
/// Finally, it returns the statistics. 

Vector< Statistics<double> > DataSet::scale_targets(const std::string& scaling_unscaling_method)
{
    switch(get_scaling_unscaling_method(scaling_unscaling_method))
   {
      case MinimumMaximum:
      {
         return(scale_targets_minimum_maximum());
      }            
      break;

      case MeanStandardDeviation:
      {
         return(scale_targets_mean_standard_deviation());
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: DataSet class\n"
                << "Vector< Statistics<double> > scale_targets(const std::string&) method.\n"
                << "Unknown scaling and unscaling method.\n";

	     throw std::logic_error(buffer.str());
      }
      break;
   }
}


// void scale_targets(const std::string&, const Vector< Statistics<double> >&) method

/// It scales the input variables with that values.
/// The method to be used is that in the scaling and unscaling method variable.

void DataSet::scale_targets(const std::string& scaling_unscaling_method, const Vector< Statistics<double> >& targets_statistics)
{
   switch(get_scaling_unscaling_method(scaling_unscaling_method))
   {
      case MinimumMaximum:
      {
         scale_targets_minimum_maximum(targets_statistics);
      }
      break;

      case MeanStandardDeviation:
      {
         scale_targets_mean_standard_deviation(targets_statistics);
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: DataSet class\n"
                << "void scale_targets(const std::string&, const Vector< Statistics<double> >&) method.\n"
                << "Unknown scaling and unscaling method.\n";

         throw std::logic_error(buffer.str());
      }
      break;
   }
}


// void unscale_data_mean_standard_deviation(const Vector< Statistics<double> >&) method

/// Unscales the data matrix with given mean and standard deviation values.
/// It updates the data matrix.
/// @param data_statistics Vector of statistics structures for all the variables in the data set.
/// The size of that vector must be equal to the number of variables.

void DataSet::unscale_data_mean_standard_deviation(const Vector< Statistics<double> >& data_statistics)
{
   data.unscale_mean_standard_deviation(data_statistics);
}


// void unscale_data_minimum_maximum(const Vector< Statistics<double> >&) method

/// Unscales the data matrix with given minimum and maximum values.
/// It updates the data matrix.
/// @param data_statistics Vector of statistics structures for all the variables in the data set.
/// The size of that vector must be equal to the number of variables.

void DataSet::unscale_data_minimum_maximum(const Vector< Statistics<double> >& data_statistics)
{
   data.unscale_minimum_maximum(data_statistics);
}


// void unscale_inputs_mean_standard_deviation(const Vector< Statistics<double> >&) method

/// Unscales the input variables with given mean and standard deviation values.
/// It updates the input variables of the data matrix.
/// @param inputs_statistics Vector of statistics structures for all the inputs in the data set.
/// The size of that vector must be equal to the number of input variables.

void DataSet::unscale_inputs_mean_standard_deviation(const Vector< Statistics<double> >& data_statistics)
{
    const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();

    data.unscale_columns_mean_standard_deviation(data_statistics, inputs_indices);
}


// void unscale_inputs_minimum_maximum(const Vector< Statistics<double> >&) method

/// Unscales the input variables with given minimum and maximum values.
/// It updates the input variables of the data matrix.
/// @param inputs_statistics Vector of statistics structures for all the inputs in the data set.
/// The size of that vector must be equal to the number of input variables.

void DataSet::unscale_inputs_minimum_maximum(const Vector< Statistics<double> >& data_statistics)
{
    const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();

    data.unscale_columns_minimum_maximum(data_statistics, inputs_indices);
}


// void unscale_targets_mean_standard_deviation(const Vector< Statistics<double> >&) method

/// Unscales the target variables with given mean and standard deviation values.
/// It updates the target variables of the data matrix.
/// @param targets_statistics Vector of statistics structures for all the targets in the data set.
/// The size of that vector must be equal to the number of targets.

void DataSet::unscale_targets_mean_standard_deviation(const Vector< Statistics<double> >& data_statistics)
{
    const Vector<size_t> targets_indices = variables.arrange_targets_indices();

    data.unscale_columns_mean_standard_deviation(data_statistics, targets_indices);
}


// void unscale_targets_minimum_maximum(const Vector< Statistics<double> >&) method

/// Unscales the target variables with given minimum and maximum values.
/// It updates the target variables of the data matrix.
/// @param targets_statistics Vector of statistics structures for all the targets.
/// The size of that vector must be equal to the number of target variables.

void DataSet::unscale_targets_minimum_maximum(const Vector< Statistics<double> >& data_statistics)
{
    const Vector<size_t> targets_indices = variables.arrange_targets_indices();

    data.unscale_columns_minimum_maximum(data_statistics, targets_indices);
}


// void initialize_data(const double& value) method

/// Initializes the data matrix with a given value.
/// @param new_value Initialization value. 

void DataSet::initialize_data(const double& new_value)
{
   data.initialize(new_value);
}


// void randomize_data_uniform(const double&, const double&) method

/// Initializes the data matrix with random values chosen from a uniform distribution
/// with given minimum and maximum.

void DataSet::randomize_data_uniform(const double& minimum, const double& maximum)
{
   data.randomize_uniform(minimum, maximum);
}


// void randomize_data_normal(const double&, const double&) method

/// Initializes the data matrix with random values chosen from a normal distribution
/// with given mean and standard deviation.

void DataSet::randomize_data_normal(const double& mean, const double& standard_deviation)
{
   data.randomize_normal(mean, standard_deviation);
}


// tinyxml2::XMLDocument* to_XML(void) const method

/// Serializes the data set object into a XML document of the TinyXML library. 

tinyxml2::XMLDocument* DataSet::to_XML(void) const
{
   tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument;

   std::ostringstream buffer;

   // Data set

   tinyxml2::XMLElement* data_set_element = document->NewElement("DataSet");
   document->InsertFirstChild(data_set_element);

   tinyxml2::XMLElement* element = NULL;
   tinyxml2::XMLText* text = NULL;

   // Data file name
   {
      element = document->NewElement("DataFileName");
      data_set_element->LinkEndChild(element);

      text = document->NewText(data_file_name.c_str());
      element->LinkEndChild(text);
   }

   // Header
   {
      element = document->NewElement("Header");
      data_set_element->LinkEndChild(element);

      buffer.str("");
      buffer << header;

      text = document->NewText(buffer.str().c_str());
      element->LinkEndChild(text);
   }

   // Separator
   {
      element = document->NewElement("Separator");
      data_set_element->LinkEndChild(element);

      text = document->NewText(separator.c_str());
      element->LinkEndChild(text);
   }

   // Missing values label
   {
      element = document->NewElement("MissingValuesLabel");
      data_set_element->LinkEndChild(element);

      text = document->NewText(missing_values_label.c_str());
      element->LinkEndChild(text);
   }

   // Variables 
   {
      element = document->NewElement("Variables");
      data_set_element->LinkEndChild(element);

      const tinyxml2::XMLDocument* variables_document = variables.to_XML();

      const tinyxml2::XMLElement* variables_element = variables_document->FirstChildElement("Variables");

      DeepClone(element, variables_element, document, NULL);

      delete variables_document;
   }

   // Instances
   {
       element = document->NewElement("Instances");
       data_set_element->LinkEndChild(element);

       const tinyxml2::XMLDocument* instances_document = instances.to_XML();

       const tinyxml2::XMLElement* instances_element = instances_document->FirstChildElement("Instances");

       DeepClone(element, instances_element, document, NULL);

       delete instances_document;
   }

   // Display
   {
      element = document->NewElement("Display");
      data_set_element->LinkEndChild(element);

      buffer.str("");
      buffer << display;

      text = document->NewText(buffer.str().c_str());
      element->LinkEndChild(text);
   }  

   return(document);
}


// void from_XML(const tinyxml2::XMLDocument&) method

/// Deserializes a TinyXML document into this data set object.
/// @param data_set_document XML document containing the member data.

void DataSet::from_XML(const tinyxml2::XMLDocument& data_set_document)
{

   std::ostringstream buffer;

   // Data set element

   const tinyxml2::XMLElement* data_set_element = data_set_document.FirstChildElement("DataSet");

   if(!data_set_element)
   {
       buffer << "OpenNN Exception: DataSet class.\n"
              << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
              << "Data set element is NULL.\n";

       throw std::logic_error(buffer.str());
   }


       // Data file name
    {
       const tinyxml2::XMLElement* data_file_name_element = data_set_element->FirstChildElement("DataFileName");

       if(!data_file_name_element)
       {
           buffer << "OpenNN Exception: DataSet class.\n"
                  << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
                  << "Data file name element is NULL.\n";

           throw std::logic_error(buffer.str());
       }

       if(data_file_name_element->GetText())
       {
            const std::string new_data_file_name = data_file_name_element->GetText();

            set_data_file_name(new_data_file_name);
       }
    }

      // Header
      {
         const tinyxml2::XMLElement* header_element = data_set_element->FirstChildElement("Header");

         if(header_element)
         {
            const std::string new_header_string = header_element->GetText();

            try
            {
               set_header(new_header_string != "0");
            }
            catch(const std::logic_error& e)
            {
               std::cout << e.what() << std::endl;
            }
         }
      }

      // Separator
    {
      const tinyxml2::XMLElement* separator_element = data_set_element->FirstChildElement("Separator");

      if(separator_element)
     {
          if(separator_element->GetText())
          {              
            const std::string new_separator = separator_element->GetText();

            set_separator(new_separator);
          }
          else
          {
              set_separator(" ");
          }
      }
      else
      {
          set_separator(" ");
      }

    }

    // Missing values label
    {
     const tinyxml2::XMLElement* missing_values_label_element = data_set_element->FirstChildElement("MissingValuesLabel");

     if(missing_values_label_element)
     {
         if(missing_values_label_element->GetText())
         {
            const std::string new_missing_values_label = missing_values_label_element->GetText();

            set_missing_values_label(new_missing_values_label);
         }
     }
    }

   // Variables
    {
   const tinyxml2::XMLElement* variables_element = data_set_element->FirstChildElement("Variables");

   if(variables_element)
   {
       tinyxml2::XMLDocument variables_document;

       tinyxml2::XMLElement* variables_element_clone = variables_document.NewElement("Variables");
       variables_document.InsertFirstChild(variables_element_clone);

       DeepClone(variables_element_clone, variables_element, &variables_document, NULL);

       variables.from_XML(variables_document);
   }
    }

   // Instances
    {
   const tinyxml2::XMLElement* instances_element = data_set_element->FirstChildElement("Instances");

   if(instances_element)
   {
       tinyxml2::XMLDocument instances_document;

       tinyxml2::XMLElement* instances_element_clone = instances_document.NewElement("Instances");
       instances_document.InsertFirstChild(instances_element_clone);

       DeepClone(instances_element_clone, instances_element, &instances_document, NULL);

       instances.from_XML(instances_document);
   }
    }

   // Display
   {
      const tinyxml2::XMLElement* display_element = data_set_element->FirstChildElement("Display");

      if(display_element)
      {
         const std::string new_display_string = display_element->GetText();

         try
         {
            set_display(new_display_string != "0");
         }
         catch(const std::logic_error& e)
         {
            std::cout << e.what() << std::endl;
         }
      }
   }

}


// std::string to_string(void) const method

/// Returns a string representation of the current data set object. 

std::string DataSet::to_string(void) const
{
   std::ostringstream buffer;

   buffer << "Data set object\n"
          << "Data file name: " << data_file_name << "\n"
          << "Header: " << header << "\n"
          << "Separator: " << separator << "\n"
          << "Missing values label: " << missing_values_label << "\n"
          << "Data:\n" << data << "\n"
          << "Display: " << display << "\n"
          << variables.to_string()
          << instances.to_string()
          << missing_values.to_string();

   return(buffer.str());
}


// void print(void) const method

/// Prints to the screen in text format the members of the data set object.

void DataSet::print(void) const
{
   if(display)
   {
      std::cout << to_string();
   }
}


// void print_summary(void) const method

/// Prints to the screen in text format the main numbers from the data set object.

void DataSet::print_summary(void) const
{
    if(display)
    {
        const size_t variables_number = variables.get_variables_number();
        const size_t instances_number = instances.get_instances_number();
        const size_t missing_values_number = missing_values.get_missing_values_number();

       std::cout << "Data set object summary:\n"
                 << "Number of variables: " << variables_number << "\n"
                 << "Number of instances: " << instances_number << "\n"
                 << "Number of missing values: " << missing_values_number << std::endl;
    }
}


// void save(const std::string&) const method

/// Saves the members of a data set object to a XML-type file in an XML-type format.
/// @param file_name Name of data set XML-type file.

void DataSet::save(const std::string& file_name) const
{
   tinyxml2::XMLDocument* document = to_XML();

   document->SaveFile(file_name.c_str());

   delete document;
}


// void load(const std::string&) method

/// Loads the members of a data set object from a XML-type file:
/// <ul>
/// <li> Instances number.
/// <li> Training instances number.
/// <li> Training instances indices.
/// <li> Generalization instances number.
/// <li> Generalization instances indices.
/// <li> Testing instances number.
/// <li> Testing instances indices.
/// <li> Input variables number.
/// <li> Input variables indices.
/// <li> Target variables number.
/// <li> Target variables indices.
/// <li> Input variables name. 
/// <li> Target variables name.
/// <li> Input variables description. 
/// <li> Target variables description.
/// <li> Display.
/// <li> Data.
/// </ul> 
/// Please mind about the file format. This is specified in the User's Guide.
/// @param file_name Name of data set XML-type file.

void DataSet::load(const std::string& file_name)
{
   tinyxml2::XMLDocument document;

   if(document.LoadFile(file_name.c_str()))
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void load(const std::string&) method.\n"
             << "Cannot load XML file " << file_name << ".\n";

      throw std::logic_error(buffer.str());
   }

   from_XML(document);
}


// void print_data(void) const method

/// Prints to the sceen the values of the data matrix.

void DataSet::print_data(void) const
{
   if(display)
   {
      std::cout << data << std::endl;
   }
}


// void print_data_preview(void) const method

/// Prints to the sceen a preview of the data matrix,
/// i.e., the first, second and last instances

void DataSet::print_data_preview(void) const
{
   if(display)
   {
       const size_t instances_number = instances.get_instances_number();

       if(instances_number > 0)
       {
          const Vector<double> first_instance = data.arrange_row(0);

          std::cout << "First instance:\n"
                    << first_instance << std::endl;
       }

       if(instances_number > 1)
       {
          const Vector<double> second_instance = data.arrange_row(1);

          std::cout << "Second instance:\n"
                    << second_instance << std::endl;
       }

       if(instances_number > 2)
       {
          const Vector<double> last_instance = data.arrange_row(instances_number-1);

          std::cout << "Instance " << instances_number << ":\n"
                    << last_instance << std::endl;
       }
    }
}


// void save_data(void) const method

/// Saves to the data file the values of the data matrix.

void DataSet::save_data(void) const
{
   std::ofstream file(data_file_name.c_str());

   if(!file.is_open())
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n" 
             << "void save_data(void) const method.\n"
             << "Cannot open data file.\n";

      throw std::logic_error(buffer.str());	  
   }
  
   if(header)
   {
       const Vector<std::string> variables_name = variables.arrange_names();

       file << variables_name << std::endl;
   }

   // Write data

   file << data;

   // Close file

   file.close();
}


// void save_data(const std::string&) const method

/// Saves to a file the values of the data matrix.
/// @param file_name Name of data file. 

void DataSet::save_data(const std::string& file_name) const
{
   std::ofstream file(file_name.c_str());

   if(!file.is_open())
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n" 
             << "void save_data(const std::string&) const method.\n"
             << "Cannot open data file.\n";

      throw std::logic_error(buffer.str());	  
   }
  
   // Write data

   file << data;

   // Close file

   file.close();
}


// Vector< Vector<std::string> > set_from_data_file(void)  method

/// Performs a first data file read in which the format is checked,
/// and the numbers of variables, instances and missing values are set.

Vector< Vector<std::string> > DataSet::set_from_data_file(void)
{
    Vector< Vector<std::string> > names;

    std::string line;

    std::string header_line;
    Vector<std::string> columns_name;

    // Read first line

    std::ifstream file(data_file_name.c_str());

    while(file.good())
    {
        std::getline(file, line);

        if(!line.empty())
        {
            if(header)
            {
                header_line = line;
                columns_name = get_tokens(line);
            }

            break;
        }
    }

    if(line.empty())
    {
        file.close();

        set();

        return(names);
    }

    if (line.find(separator) == std::string::npos)
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: DataSet class.\n"
               << "Vector< Vector<std::string> > DataSet::set_from_data_file(void).\n"
               << "Separator '" << separator << "' not found in data file " << data_file_name << ".\n";

        throw std::logic_error(buffer.str());
    }

    size_t rows_number = 1;
    const size_t columns_number = count_tokens(line);

    // Read rest of lines

    Vector<std::string> tokens(columns_number);

    names.set(columns_number);

    size_t variables_count = 0;

//     #pragma omp parallel private(line, tokens) reduction(+ : rows_number, variables_count)
     {
        while(file.good())
        {
            getline(file, line);

            if(!line.empty())
            {
               rows_number++;

               tokens = get_tokens(line);

               if(tokens.size() != columns_number)
               {
                   std::ostringstream buffer;

                   buffer << "OpenNN Exception: DataSet class.\n"
                          << "Vector< Vector<std::string> > DataSet::set_from_data_file(void).\n"
                          << "Row " << rows_number << ": Size of tokens (" << tokens.size() << ") is not equal to "
                          << "number of columns (" << columns_number << ").\n";

                   throw std::logic_error(buffer.str());
               }

               for(size_t j = 0; j < columns_number; j++)
               {
                   if(is_numeric(tokens[j]) && names[j].size() != 1)
                   {
                       if(header)
                       {
                           names[j].push_back(columns_name[j]);
                       }
                       else
                       {
                           names[j].push_back("new_variable");
                       }

                       variables_count++;
                   }
                   else if(!is_numeric(tokens[j])
                        && tokens[j] != missing_values_label
                        && !names[j].contains(tokens[j]))
                   {
                       names[j].push_back(tokens[j]);
                       variables_count++;
                   }
               }
            }
        }
    }

    file.close();

    // Set instances and variables number

    size_t instances_count;

    if(header)
    {
        instances_count = rows_number-1;
    }
    else
    {
        instances_count = rows_number;
    }

    if(lags_number != 0)
    {
        variables_count *= (1+lags_number);
        instances_count -= lags_number;

//        names = arrange_time_series_prediction_names(columns_name);
    }


    if(autoassociation)
    {
        //names = arrange_autoassociation_names(columns_name);
    }

    set(variables_count, instances_count);

    return(names);
}


// void read_from_data_file(Vector< Vector<std::string> >&) method

/// Performs a second data file read in which the data is set.

void DataSet::read_from_data_file(const Vector< Vector<std::string> >& names)
{
    const size_t instances_number = instances.get_instances_number();
    const size_t variables_number = variables.get_variables_number();

    std::ifstream file(data_file_name.c_str());

    std::string line;

    Vector<std::string> tokens;

    if(header)
    {
        getline(file, line);
    }

    int i = 0;

//    #pragma omp parallel for private(i, line, tokens)

    for(i = 0; i < (int)instances_number; i++)
    {
        getline(file, line);

        tokens = get_tokens(line);

        for(size_t j = 0; j < variables_number; j++)
        {            
            if(names[j].size() == 1) // No nominal values
            {
                if(get_trimmed(tokens[j]).compare(missing_values_label) != 0) // No missing values
                {
                    data(i,j) = atof(tokens[j].c_str());
                }
                else // Missing values
                {
                    missing_values.append(i, j);
                    data(i,j) = -99.9;
                }
            }

            else // Nominal values
            {
                if(get_trimmed(tokens[j]).compare(missing_values_label) != 0)
                {
                    for(size_t k = 0; k < names[j].size(); k++)
                    {
                        if(tokens[j] == names[j][k])
                        {
                            data(i,j+k) = 1.0;
                        }
                        else
                        {
                            data(i,j+k) = 0.0;
                        }
                    }
                }
                else // Missing values
                {
                    missing_values.append(i, j);
                    data(i,j) = -99.9;
                }
            }
        }

    }

    variables.set_names(names);

}


// Vector<std::string> arrange_time_series_prediction_names(const Vector<std::string>&) const method

/// Returns a vector with the names arranged for time series prediction, according to the number of lags.
/// @todo

Vector<std::string> DataSet::arrange_time_series_names(const Vector<std::string>&) const
{        
    Vector<std::string> time_series_prediction_names;
/*
    Vector< Vector<std::string> > new_names((1+columns_number)*lags_number);

    for(size_t i = 0; i < 1+lags_number; i++)
    {
        for(size_t j = 0; j < names.size(); j++)
        {
            new_names[i+j] = names[j];

            if(i != lags_number)
            {
                for(size_t k = 0; k < names[j].size();k++)
                {
                    new_names[i+j][k].append("_lag_").append(std::string::from_size_t(lags_number-i).c_str());
                }
            }
        }
    }
*/
    return(time_series_prediction_names);
}


// Vector<std::string> DataSet::arrange_autoassociation_names(const Vector<std::string>& names) const method

/// Returns a vector with the names arranged for autoassociation.
/// @todo

Vector<std::string> DataSet::arrange_autoassociation_names(const Vector<std::string>&) const
{
    Vector<std::string> autoassociation_names;

    return(autoassociation_names);
}


// void convert_time_series(void) method

/// Arranges an input-target matrix from a time series matrix, according to the number of lags.
/// @todo

void DataSet::convert_time_series(void)
{
    if(lags_number == 0)
    {
        return;
    }

    data.convert_time_series(lags_number);

    variables.convert_time_series(lags_number);

    instances.convert_time_series(lags_number);

    missing_values.convert_time_series(lags_number);


    if(lags_number == 0)
    {
        return;
    }

    const size_t variables_number = variables.get_variables_number();
    const size_t instances_number = instances.get_instances_number();

    if (instances_number <= lags_number)
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: DataSet class.\n"
               << "void convert_time_series(void).\n"
               << "Number of instances (" << instances_number << ") number must be greater than number of lags (" << lags_number << ").\n";

        throw std::logic_error(buffer.str());
    }

    const size_t new_variables_number = variables_number*(1+lags_number);
    const size_t new_instances_number = instances_number - lags_number;


    // Data

    Matrix<double> new_data(new_instances_number, new_variables_number);

    const Vector<size_t> indices(0, 1, (size_t)variables_number-1);

    Vector<double> row;

    for(size_t i = 0; i < instances_number-lags_number; i++)
    {
        row = data.arrange_row(i, indices);

        for(size_t j = 1; j <= lags_number; j++)
        {
            row = row.assemble(data.arrange_row(i+j, indices));
        }

        new_data.set_row(i, row);
    }

    // Names


    // Set

//    set(new_variables_number, new_instances_number);

    set_data(new_data);

    variables.convert_time_series(lags_number);

    missing_values.convert_time_series(lags_number);

}


// void convert_autoassociation(void) method

/// Arranges an input-target matrix from an autoassociation matrix, according to the number of lags.
/// @todo

void DataSet::convert_autoassociation(void)
{
    const Matrix<double> copy(data);

    data.assemble_columns(copy);
}



// void load_data(void) method

/// @todo This method will replace the load_data method.

void DataSet::load_data(void)
{
    if(data_file_name.empty())
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception: DataSet class.\n"
              << "void load_data(void) method.\n"
              << "Data file name has not been set.\n";

       throw std::logic_error(buffer.str());
    }

    std::ifstream file(data_file_name.c_str());

    if(!file.is_open())
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception: DataSet class.\n"
              << "void load_data(void) method.\n"
              << "Cannot open data file: " << data_file_name << "\n";

       throw std::logic_error(buffer.str());
    }

    const Vector< Vector<std::string> > names = set_from_data_file();

    read_from_data_file(names);

    // Angular variables

    if(!angular_variables.empty())
    {
        convert_angular_variables();
    }

    // Time series

    if(lags_number != 0)
    {
        convert_time_series();
    }

    // Autoassociation

    if(autoassociation)
    {
        convert_autoassociation();
    }

    file.close();
}


// void load_time_series_data(void) method

/// @todo This method is not implemented.
/*
void DataSet::load_time_series_data(void)
{
    if(lags_number <= 0)
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception: DataSet class.\n"
              << "void load_time_series_data(void) const method.\n"
              << "Number of lags (" << lags_number << ") must be greater than zero.\n";

       throw std::logic_error(buffer.str());
    }


    if(header)
    {
//        Vector<std::string> columns_name;

//        variables.set_names(names);
    }


    const Matrix<double> time_series_data(data_file_name);

    const size_t rows_number = time_series_data.get_rows_number();
    const size_t columns_number = time_series_data.get_columns_number();

    const size_t instances_number = rows_number - lags_number;
    const size_t variables_number = columns_number*(1 + lags_number);

    set(variables_number, instances_number);

    Vector<double> row(rows_number);

    for(size_t i = 0; i < instances_number; i++)
    {
        row = time_series_data.arrange_row(i);

        for(size_t j = 1; j <= lags_number; j++)
        {
            row = row.assemble(time_series_data.arrange_row(i+j));
        }

        data.set_row(i, row);
    }

    // Variables

    Vector<Variables::Use> uses(variables_number);

    std::fill(uses.begin(), uses.begin()+lags_number*variables_number/(lags_number+1)-1, Variables::Use::Input);
    std::fill(uses.begin()+lags_number*variables_number/(lags_number+1), uses.end(), Variables::Use::Target);

    variables.set_uses(uses);

}
*/

// Vector<size_t> calculate_target_class_distribution(void) const method

/// Returns a vector containing the number of instances of each class in the data set.
/// If the number of target variables is one then the number of classes is two.
/// If the number of target variables is greater than one then the number of classes is equal to the number 
/// of target variables.

Vector<size_t> DataSet::calculate_target_class_distribution(void) const
{ 
   // Control sentence (if debug)

   const size_t instances_number = instances.get_instances_number();
   const size_t targets_number = variables.count_targets_number();
   const Vector<size_t> targets_indices = variables.arrange_targets_indices();

   Vector<size_t> class_distribution;

   if(targets_number == 1) // Two classes
   {
      class_distribution.set(2, 0);

      size_t target_index = targets_indices[0];

      for(size_t instance_index = 0; instance_index < instances_number; instance_index++)
      {
          if(instances.get_use(instance_index) != Instances::Unused)
          {
             if(data(instance_index,target_index) < 0.5)
             {
                class_distribution[0]++;
             }
             else
             {
                class_distribution[1]++;
             }
          }
      }
   }
   else // More than two classes
   {
      class_distribution.set(targets_number, 0);
   
      for(size_t i = 0; i < instances_number; i++)
      {
          if(instances.get_use(i) != Instances::Unused)
          {
             for(size_t j = 0; j < targets_number; j++)
             {
                if(data(i,targets_indices[j]) > 0.5)
                {
                   class_distribution[j]++;
                }
             }
          }
      }
   }

   // Check data consistency

   const size_t used_instances_number = instances.count_used_instances_number();

   if(class_distribution.calculate_sum() != used_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n" 
             << "Vector<size_t> calculate_target_class_distribution(void) const method.\n"
             << "Sum of class distributions (" << class_distribution << ") is not equal to "
             << "number of used instances (" << used_instances_number << ")." << std::endl;

      throw std::logic_error(buffer.str());   
   }

   return(class_distribution);
}


// Vector<double> calculate_distances(void) const method

/// Returns a normalized distance between each instance and the mean instance.
/// The size of this vector is the number of instances.

Vector<double> DataSet::calculate_distances(void) const
{
    const Matrix<double> data_statistics_matrix = calculate_data_statistics_matrix();

    const Vector<double> means = data_statistics_matrix.arrange_column(2);
    const Vector<double> standard_deviations = data_statistics_matrix.arrange_column(3);

    const size_t instances_number = instances.get_instances_number();
    Vector<double> distances(instances_number);

    const size_t variables_number = variables.get_variables_number();
    Vector<double> instance(variables_number);

    int i = 0;

    #pragma omp parallel for private(i, instance)

    for(i = 0; i < (int)instances_number; i++)
    {
        instance = data.arrange_row(i);

        distances[i] = (instance-means/standard_deviations).calculate_norm();
    }

    return(distances);
}


// void DataSet::balance_data(const double&) method

/// @todo This method is not implemented.

void DataSet::balance_data(const double&)
{
/*
    const size_t instances_number = instances.count_used_instances_number();

    const Vector<double> distances = calculate_distances();

    // Sorted performance vector

    const Vector<size_t> rank = distances.calculate_greater_rank();

    // Perform linear ranking fitness assignment
    // Cannot do that without loop because of different types of fitness and rank vectors

    Vector<double> fitness(instances_number);

    const double selective_pressure = 1.5;

    for(size_t i = 0; i < instances_number; i++)
    {
       fitness[i] = selective_pressure*rank[i];
    }

    // Set selection vector to false

//    Vector<double> selection(instances_number, false);

    const size_t selection_target = instances_number/2;

    if(selection_target <= 0)
    {
        return;
    }

    // Cumulative fitness vector

    const Vector<double> cumulative_fitness = fitness.calculate_cumulative();

    const double fitness_sum = fitness.calculate_sum();

    // Select individuals until the desired number of selections is obtained

    size_t selection_count = 0;

    double pointer;

    while(selection_count != selection_target)
    {
       // Random number between 0 and total cumulative fitness

       pointer = calculate_random_uniform(0, fitness_sum);

       // Perform selection

       if(pointer < cumulative_fitness[0])
       {
          if(instances.is_used(0))
          {
             instances.set_use(0, "Unused");
             selection_count++;
          }
       }
       else
       {
           for(size_t i = 1; i < instances_number; i++)
           {
              if(pointer < cumulative_fitness[i] && pointer >= cumulative_fitness[i-1])
              {
                 if(instances.is_used(i))
                 {
                    instances.set_use(0, "Unused");
                    selection_count++;
                 }
              }
           }
       }
    }

    // Control sentence (if debug)

    #ifndef NDEBUG

    if(instances.count_used_instances_number() != instances_number/2)
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: DataSet class.\n"
               << "void perform_roulette_wheel_selection(void) method.\n"
               << "Selection count (" << instances.count_used_instances_number() << ") is not equal to half instances number (" << instances_number/2 << ").\n";

        throw std::logic_error(buffer.str());
    }

    #endif
*/
}


// void balance_target_class_distribution(void) method

/// @todo This method is not implemented.

void DataSet::balance_target_class_distribution(void)
{
/*
    const size_t instances_number = instances.count_used_instances_number();

    const size_t targets_number = variables.count_targets_number();

    const Vector<size_t> targets_indices = variables.arrange_targets_indices();

//    const size_t minimum = target_class_distribution.calculate_minimum();

//    const Matrix<double> target_data = arrange_target_data();

    Vector<size_t> target_class_distribution = calculate_target_class_distribution();

    size_t instance_index;

    Vector<double> instance;

    if(targets_number == 1) // Two classes
    {
        const size_t target_index = targets_indices[0];

        while(target_class_distribution[0] != target_class_distribution[1]);
        {
            instance_index = (size_t)calculate_random_uniform(0.0, instances_number);

            instance = get_instance(instance_index);

            if(instances.is_used(instance_index))
            {
                if(instance[target_index] == 0
                && target_class_distribution[0] > target_class_distribution[1])
                {
                    instances.set_use(instance_index, Instances::Unused);
                }
                else if(instance[target_index] == 1
                && target_class_distribution[1] > target_class_distribution[0])
                {
                    instances.set_use(instance_index, Instances::Unused);
                }
            }
        }
    }
*/
}


// bool has_data(void) const method

/// Returns true if the data matrix is not empty (it has not been loaded),
/// and false otherwise.

bool DataSet::has_data(void) const
{
    if(data.empty())
    {
        return(false);
    }
    else
    {
        return(true);
    }
}


// void filter_data(const Vector<double>&, const Vector<double>&) method

/// Unuses those instances with values outside a defined range.
/// @param minimums Vector of minimum values in the range.
/// The size must be equal to the number of variables.
/// @param maximums Vector of maximum values in the range.
/// The size must be equal to the number of variables.

void DataSet::filter_data(const Vector<double>& minimums, const Vector<double>& maximums)
{
    const size_t variables_number = variables.get_variables_number();

    // Control sentence (if debug)

    #ifndef NDEBUG

    if(minimums.size() != variables_number)
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: DataSet class.\n"
               << "void filter_data(const Vector<double>&, const Vector<double>&) method.\n"
               << "Size of minimums (" << minimums.size() << ") is not equal to number of variables (" << variables_number << ").\n";

        throw std::logic_error(buffer.str());
    }

    if(maximums.size() != variables_number)
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: DataSet class.\n"
               << "void filter_data(const Vector<double>&, const Vector<double>&) method.\n"
               << "Size of maximums (" << maximums.size() << ") is not equal to number of variables (" << variables_number << ").\n";

        throw std::logic_error(buffer.str());
    }

    #endif

    const size_t instances_number = instances.get_instances_number();

    int i = 0;

    #pragma omp parallel for private(i)

    for(i = 0; i < (int)instances_number; i++)
    {
        for(size_t j = 0; j < variables_number; j++)
        {
            if(data(i,j) < minimums[j] || data(i,j) > maximums[j])
            {
                instances.set_use(i, "Unused");
            }
        }
    }
}


// void convert_angular_variable_degrees(const size_t&) method

/// Replaces a given angular variable expressed in degrees by the sinus and cosinus of that variable.
/// This solves the discontinuity associated with angular variables.
/// Note that this method modifies the number of variables.
/// @param variable_index Index of angular variable.

void DataSet::convert_angular_variable_degrees(const size_t& variable_index)
{
    // Control sentence (if debug)

    #ifndef NDEBUG

    const size_t variables_number = variables.get_variables_number();

    if(variable_index >= variables_number)
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: DataSet class.\n"
               << "void convert_angular_variable_degrees(const size_t&) method.\n"
               << "Index of variable (" << variable_index << ") must be less than number of variables (" << variables_number << ").\n";

        throw std::logic_error(buffer.str());
    }

    #endif

    Vector<Variables::Item> items = variables.get_items();

    Variables::Item sin_item = items[variable_index];
    prepend("sin_", sin_item.name);

    Variables::Item cos_item = items[variable_index];
    prepend("cos_", cos_item.name);

    items[variable_index] = sin_item;
    items = items.insert_element(variable_index, cos_item);

    variables.set_items(items);

    data.convert_angular_variables_degrees(variable_index);

}


// void convert_angular_variable_radians(const size_t&) method

/// Replaces a given angular variable expressed in radians by the sinus and cosinus of that variable.
/// This solves the discontinuity associated with angular variables.
/// Note that this method modifies the number of variables.
/// @param variable_index Index of angular variable.

void DataSet::convert_angular_variable_radians(const size_t& variable_index)
{
    // Control sentence (if debug)

    #ifndef NDEBUG

    const size_t variables_number = variables.get_variables_number();

    if(variable_index >= variables_number)
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: DataSet class.\n"
               << "void convert_angular_variable_radians(const size_t&) method.\n"
               << "Index of variable (" << variable_index << ") must be less than number of variables (" << variables_number << ").\n";

        throw std::logic_error(buffer.str());
    }

    #endif

    Vector<Variables::Item> items = variables.get_items();

    Variables::Item sin_item = items[variable_index];
    prepend("sin_", sin_item.name);

    Variables::Item cos_item = items[variable_index];
    prepend("cos_", cos_item.name);

    items[variable_index] = sin_item;
    items = items.insert_element(variable_index, cos_item);

    variables.set_items(items);

    data.convert_angular_variables_radians(variable_index);

}


// void convert_angular_variables_degrees(const Vector<size_t>&)

/// Replaces a given set of angular variables expressed in degrees by the sinus and cosinus of that variable.
/// This solves the discontinuity associated with angular variables.
/// Note that this method modifies the number of variables.
/// @param indices Indices of angular variables.

void DataSet::convert_angular_variables_degrees(const Vector<size_t>& indices)
{
    // Control sentence (if debug)

    #ifndef NDEBUG

    const size_t variables_number = variables.get_variables_number();

    for(size_t i = 0; i < indices.size(); i++)
    {
        if(indices[i] >= variables_number)
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: DataSet class.\n"
                   << "void convert_angular_variables_degrees(const Vector<size_t>&) method.\n"
                   << "Index (" << i << ") must be less than number of variables (" << variables_number << ").\n";

            throw std::logic_error(buffer.str());
        }
    }

    #endif

    size_t size = indices.size();

    unsigned count = 0;

    size_t index;

    for(size_t i = 0; i < size; i++)
    {
        index = indices[i]+count;

        convert_angular_variable_degrees(index);

        count++;
    }
}


// void convert_angular_variables_radians(const Vector<size_t>&)

/// Replaces a given set of angular variables expressed in radians by the sinus and cosinus of that variable.
/// This solves the discontinuity associated with angular variables.
/// Note that this method modifies the number of variables.
/// @param indices Indices of angular variables.

void DataSet::convert_angular_variables_radians(const Vector<size_t>& indices)
{
    // Control sentence (if debug)

    #ifndef NDEBUG

    const size_t variables_number = variables.get_variables_number();

    for(size_t i = 0; i < indices.size(); i++)
    {
        if(indices[i] >= variables_number)
        {
            std::ostringstream buffer;

            buffer << "OpenNN Exception: DataSet class.\n"
                   << "void convert_angular_variables_radians(const Vector<size_t>&) method.\n"
                   << "Index (" << i << ") must be less than number of variables (" << variables_number << ").\n";

            throw std::logic_error(buffer.str());
        }
    }

    #endif

    size_t size = indices.size();

    unsigned count = 0;

    size_t index;

    for(size_t i = 0; i < size; i++)
    {
        index = indices[i]+count;

        convert_angular_variable_radians(index);

        count++;
    }
}


// void convert_angular_variables(void) method

void DataSet::convert_angular_variables(void)
{
    switch(angular_units)
    {
       case DataSet::Radians:
       {
            convert_angular_variables_radians(angular_variables);
       }
       break;

       case DataSet::Degrees:
       {
            convert_angular_variables_degrees(angular_variables);
       }
       break;

       default:
       {
          std::ostringstream buffer;

          buffer << "OpenNN Exception: DataSet class.\n"
                 << "void convert_angular_variables(void) method.\n"
                 << "Unknown angular units.\n";

          throw std::logic_error(buffer.str());
       }
       break;
    }

}


size_t DataSet::count_tokens(std::string& str) const
{
//    if(!(this->find(separator) != std::string::npos))
//    {
//        std::ostringstream buffer;
//
//        buffer << "OpenNN Exception:\n"
//               << "std::string class.\n"
//               << "inline size_t count_tokens(const std::string&) const method.\n"
//               << "Separator not found in string: \"" << separator << "\".\n";
//
//        throw std::logic_error(buffer.str());
//    }

    trim(str);

    size_t tokens_count = 0;

    // Skip delimiters at beginning.

    std::string::size_type last_pos = str.find_first_not_of(separator, 0);

    // Find first "non-delimiter".

    std::string::size_type pos = str.find_first_of(separator, last_pos);

    while (std::string::npos != pos || std::string::npos != last_pos)
    {
        // Found a token, add it to the vector

        tokens_count++;

        // Skip delimiters.  Note the "not_of"

        last_pos = str.find_first_not_of(separator, pos);

        // Find next "non-delimiter"

        pos = str.find_first_of(separator, last_pos);
    }

    return(tokens_count);
}


/// Splits the string into substrings (tokens) wherever separator occurs, and returns a vector with those strings.
/// If separator does not match anywhere in the string, this method returns a single-element list containing this string.
/// @param separator Separator value.

Vector<std::string> DataSet::get_tokens(std::string& str) const
{   
    Vector<std::string> tokens;

    trim(str);

    // Skip delimiters at beginning.

    std::string::size_type lastPos = str.find_first_not_of(separator, 0);

    // Find first "non-delimiter"

    std::string::size_type pos = str.find_first_of(separator, lastPos);

    while(std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector

        tokens.push_back(str.substr(lastPos, pos - lastPos));

        // Skip delimiters. Note the "not_of"

        lastPos = str.find_first_not_of(separator, pos);

        // Find next "non-delimiter"

        pos = str.find_first_of(separator, lastPos);
    }

    return(tokens);
}


bool DataSet::is_numeric(const std::string& str) const
{
    std::istringstream iss(str.data());

    double dTestSink;

    iss >> dTestSink;

    // was any input successfully consumed/converted?

    if(!iss)
    {
        return false;
    }

    // was all the input successfully consumed/converted?

    return(iss.rdbuf()->in_avail() == 0);
}


void DataSet::trim(std::string& str) const
{
    //prefixing spaces

    str.erase(0, str.find_first_not_of(' '));

    //surfixing spaces

    str.erase(str.find_last_not_of(' ') + 1);
}


std::string DataSet::get_trimmed(const std::string& str) const
{
    std::string output(str);

    //prefixing spaces

    output.erase(0, output.find_first_not_of(' '));

    //surfixing spaces

    output.erase(output.find_last_not_of(' ') + 1);

    return(output);
}


std::string DataSet::prepend(const std::string& pre, const std::string& str) const
{
    std::ostringstream buffer;

    buffer << pre << str;

    return(buffer.str());
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
