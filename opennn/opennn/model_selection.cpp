/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   M O D E L   S E L E C T I O N   C L A S S                                                                  */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - Making intelligent use of data                                                                 */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// $Id: model_selection.cpp 30 2014-12-26 18:29:17Z uwrobertolopez $

// OpenNN includes

#include "model_selection.h"

namespace OpenNN
{

// DEFAULT CONSTRUCTOR

/// Default constructor. 

ModelSelection::ModelSelection(void)
 : training_strategy_pointer(NULL)
{
   set_default();
}


// TRAINING STRATEGY CONSTRUCTOR

/// Training strategy constructor. 
/// @param new_training_strategy_pointer Pointer to a gradient descent object.

ModelSelection::ModelSelection(TrainingStrategy* new_training_strategy_pointer)
 : training_strategy_pointer(new_training_strategy_pointer)
{
   set_default();
}


// FILE CONSTRUCTOR

/// File constructor. 
/// @param file_name Name of XML model selection file. 

ModelSelection::ModelSelection(const std::string& file_name)
 : training_strategy_pointer(NULL)
{
   load(file_name);
}


// XML CONSTRUCTOR

/// XML constructor. 
/// @param model_selection_document Pointer to a TinyXML document containing the model selection data.

ModelSelection::ModelSelection(const tinyxml2::XMLDocument& model_selection_document)
 : training_strategy_pointer(NULL)
{
   from_XML(model_selection_document);
}


// DESTRUCTOR

/// Destructor. 

ModelSelection::~ModelSelection(void)
{
}


// METHODS

// TrainingStrategy* get_training_strategy_pointer(void) const method

/// Returns a pointer to the training strategy object.

TrainingStrategy* ModelSelection::get_training_strategy_pointer(void) const
{
    #ifndef NDEBUG

    if(!training_strategy_pointer)
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "DataSet* get_training_strategy_pointer(void) const method.\n"
               << "Training strategy pointer is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    #endif

   return(training_strategy_pointer);   
}


// const Vector<size_t>& get_hidden_perceptrons_numbers(void) const method

/// Returns the complexities of the neural networks given by the numbers of hidden perceptrons. 

const Vector<size_t>& ModelSelection::get_hidden_perceptrons_numbers(void) const
{
   return(hidden_perceptrons_numbers);
}


// const size_t& get_parameters_assays_number(void) const method

/// Returns the number of trials for each network architecture. 

const size_t& ModelSelection::get_parameters_assays_number(void) const
{
   return(parameters_assays_number);
}


// const bool& get_reserve_parameters_data(void) const method

/// Returns true if the neural network parameters are to be reserved, and false otherwise. 

const bool& ModelSelection::get_reserve_parameters_data(void) const
{
   return(reserve_parameters_data);
}


// const bool& get_reserve_performance_data(void) const method

/// Returns true if the performance functional performances are to be reserved, and false otherwise. 

const bool& ModelSelection::get_reserve_performance_data(void) const
{
   return(reserve_performance_data);
}


// const bool& get_reserve_generalization_performance_data(void) const method

/// Returns true if the performance functional generalization performances are to be reserved, and false otherwise. 

const bool& ModelSelection::get_reserve_generalization_performance_data(void) const
{
   return(reserve_generalization_performance_data);
}


// const bool& get_reserve_minimal_parameters(void) const method

/// Returns true if the parameters vector of the neural network with minimum performance functional performance is to be reserved, and false otherwise. 

const bool& ModelSelection::get_reserve_minimal_parameters(void) const
{
   return(reserve_minimal_parameters);
}


// const bool& get_reserve_performance_data_statistics(void) const method

/// Returns true if the statistics of the performance data are to be inclued in the model selection results. 

const bool& ModelSelection::get_reserve_performance_data_statistics(void) const
{
   return(reserve_performance_data_statistics);
}


// const bool& get_reserve_generalization_performance_data_statistics(void) const method

/// Returns true if the statistics of the generalization performance data are to be inclued in the model selection results. 

const bool& ModelSelection::get_reserve_generalization_performance_data_statistics(void) const
{
   return(reserve_generalization_performance_data_statistics);
}


// const bool& get_reserve_model_order_selection_plot(void) const method

/// Returns true if the necessary data for plotting the model selection results is to be included in the results.

const bool& ModelSelection::get_reserve_model_order_selection_plot(void) const
{
   return(reserve_model_order_selection_plot);
}


// const InputsSelectionMethod& get_inputs_selection_method(void) const method

/// Returns the method for selecting those inputs which have more impact on the targets.

const ModelSelection::InputsSelectionMethod& ModelSelection::get_inputs_selection_method(void) const
{
    return(inputs_selection_method);
}


// const bool& get_display(void) const method

/// Returns true if messages from this class can be displayed on the screen,
/// or false if messages from this class can't be displayed on the screen.

const bool& ModelSelection::get_display(void) const
{
   return(display);     
}


// void set_training_strategy_pointer(TrainingStrategy*) method

/// Sets a new training strategy pointer.
/// @param new_training_strategy_pointer Pointer to a training strategy object.

void ModelSelection::set_training_strategy_pointer(TrainingStrategy* new_training_strategy_pointer)
{
   training_strategy_pointer = new_training_strategy_pointer;   
}


// void set_default(void) method

/// @todo

void ModelSelection::set_default(void)
{
//   set_assays_numbers(5, 3);

    correlation_goal = 0.5;

    display = true;
}


// void set_hidden_perceptrons_numbers(const Vector<size_t>&) method

/// Sets the number of complexities to be compared in the model order selection process.
/// @param new_hidden_perceptrons_numbers Vector with different hidden layers sizes. 

void ModelSelection::set_hidden_perceptrons_numbers(const Vector<size_t>& new_hidden_perceptrons_numbers)
{
   hidden_perceptrons_numbers = new_hidden_perceptrons_numbers;
}


// void set_parameters_assays_number(size_t) method

/// Sets the number of times that each different neural network is to be trained.
/// @param new_parameters_assays_number Number of assays for each set of parameters. 

void ModelSelection::set_parameters_assays_number(const size_t& new_parameters_assays_number) 
{
   parameters_assays_number = new_parameters_assays_number;
}


// void set_assays_numbers(const size_t&, const size_t&) method

/// Sets the numbers of complexities and assays. 
/// @param new_complexity_assays_number Number of hidden neurons. 
/// @param new_parameters_assays_number Number of trainings for each different neural network. 

void ModelSelection::set_assays_numbers(const size_t& new_complexity_assays_number, const size_t& new_parameters_assays_number)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(!training_strategy_pointer) 
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: ModelSelection class.\n"
             << "void set_assays_numbers(const size_t&, const size_t&) method.\n"
             << "Pointer to training strategy is NULL.\n";

      throw std::logic_error(buffer.str());
   }   

   if(training_strategy_pointer->get_performance_functional_pointer() == NULL) 
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: ModelSelection class.\n"
             << "void set_assays_numbers(const size_t&, const size_t&) method.\n"
             << "Pointer to performance functional is NULL.\n";      

      throw std::logic_error(buffer.str());
   }   

   if(training_strategy_pointer->get_performance_functional_pointer()->get_neural_network_pointer() == NULL) 
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: ModelSelection class.\n"
             << "void set_assays_numbers(const size_t&, const size_t&) method.\n"
             << "Pointer to multilayer perceptron is NULL.\n";

      throw std::logic_error(buffer.str());
   }   

   #endif
   
   hidden_perceptrons_numbers.set(new_complexity_assays_number);

//  const size_t inputs_number = training_strategy_pointer->get_performance_functional_pointer()->get_multilayer_perceptron_pointer()->get_inputs_number();
//  const size_t outputs_number = training_strategy_pointer->get_performance_functional_pointer()->get_multilayer_perceptron_pointer()->get_outputs_number();

//  const size_t minimum_hidden_layer_size = (int)sqrt((double)(inputs_number*inputs_number) + (double)(outputs_number*outputs_number));
//  const size_t maximum_hidden_layer_size = 2*(int)sqrt((double)(inputs_number*inputs_number) + (double)(outputs_number*outputs_number));


   const size_t minimum_hidden_layer_size = 1;
   const size_t maximum_hidden_layer_size = 12;

   size_t hidden_layer_size_increment = (maximum_hidden_layer_size-minimum_hidden_layer_size)/new_complexity_assays_number;

   if(hidden_layer_size_increment < 1)
   {
      hidden_layer_size_increment = 1;
   }

   for(size_t i = 0; i < new_complexity_assays_number; i++)
   {
      hidden_perceptrons_numbers[i] = minimum_hidden_layer_size + hidden_layer_size_increment*i;  
   } 

   parameters_assays_number = new_parameters_assays_number;
}


// void set_reserve_parameters_data(const bool&)

/// Sets the reserve flag for the parameters data. 
/// @param new_reserve_parameters_data Flag value. 

void ModelSelection::set_reserve_parameters_data(const bool& new_reserve_parameters_data)
{
   reserve_parameters_data = new_reserve_parameters_data;
}


// void set_reserve_performance_data(const bool&)

/// Sets the reserve flag for the performance data. 
/// @param new_reserve_performance_data Flag value. 

void ModelSelection::set_reserve_performance_data(const bool& new_reserve_performance_data)
{
   reserve_performance_data = new_reserve_performance_data;
}


// void set_reserve_generalization_performance_data(const bool&)

/// Sets the reserve flag for the generalization performance data. 
/// @param new_reserve_generalization_performance_data Flag value. 

void ModelSelection::set_reserve_generalization_performance_data(const bool& new_reserve_generalization_performance_data)
{
   reserve_generalization_performance_data = new_reserve_generalization_performance_data;
}


// void set_reserve_minimal_parameters(const bool&)

/// Sets the reserve flag for the minimal parameters. 
/// @param new_reserve_minimal_parameters Flag value. 

void ModelSelection::set_reserve_minimal_parameters(const bool& new_reserve_minimal_parameters)
{
   reserve_minimal_parameters = new_reserve_minimal_parameters;
}


// void set_reserve_performance_data_statistics(const bool&)

/// Sets the reserve flag for the performance data statistics. 
/// @param new_reserve_performance_data_statistics Flag value. 

void ModelSelection::set_reserve_performance_data_statistics(const bool& new_reserve_performance_data_statistics)
{
   reserve_performance_data_statistics = new_reserve_performance_data_statistics;
}


// void set_reserve_generalization_performance_data_statistics(const bool&)

/// Sets the reserve flag for the generalization performance data statistics. 
/// @param new_reserve_generalization_performance_data_statistics Flag value. 

void ModelSelection::set_reserve_generalization_performance_data_statistics(const bool& new_reserve_generalization_performance_data_statistics)
{
   reserve_generalization_performance_data_statistics = new_reserve_generalization_performance_data_statistics;
}


// void set_reserve_model_order_selection_plot(const bool&)

/// Sets the reserve flag for the model order selection plot. 
/// @param new_reserve_model_order_selection_plot Flag value. 

void ModelSelection::set_reserve_model_order_selection_plot(const bool& new_reserve_model_order_selection_plot)
{
   reserve_model_order_selection_plot = new_reserve_model_order_selection_plot;
}


// void set_inputs_selection_method(const InputsSelectionMethod&) method

/// Sets a new method for selecting the inputs which have more impact on the targets.
/// @param new_inputs_selection_method Method for selecting the inputs (MaximumLinearCorrelation, MaximumLogisticCorrelation or Exhaustive).

void ModelSelection::set_inputs_selection_method(const ModelSelection::InputsSelectionMethod& new_inputs_selection_method)
{
    inputs_selection_method = new_inputs_selection_method;
}


// void set_display(const bool&) method

/// Sets a new display value. 
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.

void ModelSelection::set_display(const bool& new_display)
{
   display = new_display;
}


// void check(void) const method

/// Checks that the different pointers needed for performing the model selection are not NULL.

void ModelSelection::check(void) const
{
   // Training algorithm stuff

  std::ostringstream buffer;

   if(!training_strategy_pointer) 
   {
      buffer << "OpenNN Exception: ModelSelection class.\n"
             << "void check(void) const method.\n"
             << "Pointer to training strategy is NULL.\n";

      throw std::logic_error(buffer.str());
   }   

   // Performance functional stuff

   const PerformanceFunctional* performance_functional_pointer = training_strategy_pointer->get_performance_functional_pointer();

   if(!performance_functional_pointer) 
   {
      buffer << "OpenNN Exception: ModelSelection class.\n"
             << "void check(void) const method.\n"
             << "Pointer to performance functional is NULL.\n";      

      throw std::logic_error(buffer.str());
   }   

   // Neural network stuff

   const NeuralNetwork* neural_network_pointer = performance_functional_pointer->get_neural_network_pointer(); 

   if(!neural_network_pointer) 
   {
      buffer << "OpenNN Exception: ModelSelection class.\n"
             << "void check(void) const method.\n"
             << "Pointer to neural network is NULL.\n";

      throw std::logic_error(buffer.str());
   }   

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   if(!multilayer_perceptron_pointer) 
   {
      buffer << "OpenNN Exception: ModelSelection class.\n"
             << "void check(void) const method.\n"
             << "Pointer to multilayer perceptron is NULL.\n";

      throw std::logic_error(buffer.str());
   }   

   // Data set stuff

   const DataSet* data_set_pointer = performance_functional_pointer->get_data_set_pointer();

   if(!data_set_pointer)
   {
      buffer << "OpenNN Exception: ModelSelection class.\n"
             << "void check(void) const method.\n"
             << "Pointer to data set is NULL.\n";

      throw std::logic_error(buffer.str());
   }

   const Instances& instances = data_set_pointer->get_instances();

   const size_t generalization_instances_number = instances.count_generalization_instances_number();

   if(generalization_instances_number == 0)
   {
      buffer << "OpenNN Exception: ModelSelection class.\n"
             << "void check(void) const method.\n"
             << "Number of generalization instances is zero.\n";

      throw std::logic_error(buffer.str());
   }

}


// Matrix<double> calculate_linear_correlations(void) const method

/// Returns a matrix with the linear correlations between all input and target variables.
/// The number of rows is the number of input variables.
/// The number of columns is the number of target variables.

Matrix<double> ModelSelection::calculate_linear_correlations(void) const
{
    // Control sentence (if debug)

    #ifndef NDEBUG

    check();

    #endif

    const PerformanceFunctional* performance_functional_pointer = training_strategy_pointer->get_performance_functional_pointer();

    const DataSet* data_set_pointer = performance_functional_pointer->get_data_set_pointer();

    const Variables& variables = data_set_pointer->get_variables();

    const size_t inputs_number = variables.count_inputs_number();
    const size_t targets_number = variables.count_targets_number();

    Matrix<double> linear_correlations(inputs_number, targets_number);

    const Vector<size_t> input_indices = variables.arrange_inputs_indices();
    const Vector<size_t> target_indices = variables.arrange_targets_indices();

    Vector<double> input(inputs_number);
    Vector<double> target(targets_number);

    for(size_t i = 0; i < inputs_number; i++)
    {
        input = data_set_pointer->get_variable(input_indices[i]);

        for(size_t j = 0; j < inputs_number; j++)
        {
            target = data_set_pointer->get_variable(target_indices[j]);

            linear_correlations(i,j) = target.calculate_linear_correlation(input);
        }
    }

    return(linear_correlations);
}


// Matrix<double> calculate_logistic_correlations(void) const method

/// Returns a matrix with the logistic correlations between all input and target variables.
/// The number of rows is the number of input variables.
/// The number of columns is the number of target variables.

Matrix<double> ModelSelection::calculate_logistic_correlations(void) const
{
    // Control sentence (if debug)

    #ifndef NDEBUG

    check();

    #endif

    // Problem stuff

    const PerformanceFunctional* performance_functional_pointer = training_strategy_pointer->get_performance_functional_pointer();

    const DataSet* data_set_pointer = performance_functional_pointer->get_data_set_pointer();

    const Variables& variables = data_set_pointer->get_variables();

    const size_t inputs_number = variables.count_inputs_number();
    const size_t targets_number = variables.count_targets_number();

    const Instances& instances = data_set_pointer->get_instances();

    const size_t generalization_instances_number = instances.count_generalization_instances_number();

    const Vector<size_t> input_indices = variables.arrange_inputs_indices();
    const Vector<size_t> target_indices = variables.arrange_targets_indices();

    if(display)
    {
       std::cout << "Calculating logistic correlations...\n";
    }

    Matrix<double> correlations(inputs_number, targets_number);

    for(size_t i = 0; i < inputs_number; i++)
    {                
        const Vector<double> inputs = data_set_pointer->get_variable(input_indices[i]);

        for(size_t j = 0; j < targets_number; j++)
        {
            if(display)
            {
               std::cout << "\n#Input " << i+1 << ", target " << j+1 << ".\n\n";
            }

            const Vector<double> targets = data_set_pointer->get_variable(target_indices[j]);

            Matrix<double> data(generalization_instances_number, 2);

            data.set_column(0, inputs);
            data.set_column(1, targets);

            DataSet data_set(data);

            data_set.scale_inputs("MinimumMaximum");

            Instances* instances_pointer = data_set.get_instances_pointer();

            instances_pointer->set_training();

            NeuralNetwork neural_network(1, 1);

            MultilayerPerceptron* multilayer_perceptron_pointer = neural_network.get_multilayer_perceptron_pointer();

            multilayer_perceptron_pointer->set_layer_activation_function(0, Perceptron::Logistic);

            PerformanceFunctional performance_functional(&neural_network, &data_set);

            TrainingStrategy training_strategy(&performance_functional);

            training_strategy.set_main_type(TrainingStrategy::LEVENBERG_MARQUARDT_ALGORITHM);

            training_strategy.perform_training();

            const Vector<double> outputs = neural_network.calculate_output_data(inputs.to_column_matrix()).to_vector();

            correlations(i,j) = outputs.calculate_linear_correlation(inputs);
        }
    }

    return(correlations);
}


// void perform_maximum_linear_correlation_inputs_selection(void) const method

/// @todo This method is not implemented

void ModelSelection::perform_maximum_linear_correlation_inputs_selection(void) const
{
    const Matrix<double> correlations = calculate_linear_correlations();

    const Matrix<size_t> indices = correlations.calculate_greater_than_indices(correlation_goal);
}


// void perform_maximum_logistic_correlation_inputs_selection(void) const method

/// @todo This method is not implemented

void ModelSelection::perform_maximum_logistic_correlation_inputs_selection(void) const
{
     const Matrix<double> correlations = calculate_logistic_correlations();

     const Matrix<size_t> indices = correlations.calculate_greater_than_indices(correlation_goal);
}


// void perform_exhaustive_inputs_selection(void) const method

/// @todo This method is not implemented

void ModelSelection::perform_exhaustive_inputs_selection(void) const
{
    std::ostringstream buffer;

    buffer << "OpenNN Exception: ModelSelection class.\n"
           << "ModelSelectionResults perform_inputs_selection(void) const method.\n"
           << "This method is under development.\n";

    throw std::logic_error(buffer.str());

     #ifndef NDEBUG

     check();

     #endif

    /*

       // Training strategy stuff

       // Performance functional stuff

       const PerformanceFunctional* performance_functional_pointer = training_strategy_pointer->get_performance_functional_pointer();

       // Neural network stuff

       NeuralNetwork* neural_network_pointer = performance_functional_pointer->get_neural_network_pointer();

       MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

       #ifndef NDEBUG

       const size_t layers_number = multilayer_perceptron_pointer->get_layers_number();

       if(layers_number != 2)
       {
         std::ostringstream buffer;

          buffer << "OpenNN Exception: ModelSelection class.\n"
                 << "ModelSelectionResults perform_inputs_selection(void) method.\n"
                 << "Number of layers in multilayer perceptron must be two.\n";

          throw std::logic_error(buffer.str());
       }

       #endif

       // Model order selection stuff

       const size_t inputs_assays_number = hidden_perceptrons_numbers.size();

       ModelSelectionResults model_selection_results;
       model_selection_results.parameters_data.set(inputs_assays_number, parameters_assays_number);
       model_selection_results.performance_data.set(inputs_assays_number, parameters_assays_number);
       model_selection_results.generalization_performance_data.set(inputs_assays_number, parameters_assays_number);

       time_t beginning_time, current_time;
       time(&beginning_time);
       double elapsed_time;

       size_t assay_count = 0;

       for(size_t i = 0; i < inputs_assays_number; i++)
       {
          //multilayer_perceptron_pointer->set_inputs_number(1);

          for(size_t j = 0; j < parameters_assays_number; j++)
          {
             try
             {
                assay_count++;

                // Multilayer perceptron

                multilayer_perceptron_pointer->randomize_parameters_normal();

                // Performance functional

                // Training algorithm

                training_strategy_pointer->perform_training();

                // Model order selection

                model_selection_results.parameters_data(i,j) = multilayer_perceptron_pointer->arrange_parameters();

                model_selection_results.performance_data(i,j) = training_strategy_pointer->get_performance_functional_pointer()->calculate_performance();
                model_selection_results.generalization_performance_data(i,j) = training_strategy_pointer->get_performance_functional_pointer()->calculate_generalization_performance();

                time(&current_time);
                elapsed_time = difftime(current_time, beginning_time);

                if(display)
                {
                   std::cout << "Assay " << assay_count << ";\n"
                             << "Hidden layer size: " << hidden_perceptrons_numbers[i] << "\n"
                             << "Parameters set: " << j+1 << "\n"
                             << "performance: " << model_selection_results.performance_data(i,j) << "\n"
                             << "Generalization performance: " << model_selection_results.generalization_performance_data(i,j) << "\n"
                             << "Elapsed time: " << elapsed_time << std::endl;
                }
             }
             catch(const std::logic_error& e)
             {
                std::cerr << e.what() << std::endl;
             }
          }
       }

       const Vector<size_t> minimal_indices = model_selection_results.generalization_performance_data.calculate_minimal_indices();

       const Vector<double> minimal_parameters = model_selection_results.parameters_data[minimal_indices [0]][minimal_indices[1]];

       multilayer_perceptron_pointer->set_parameters(minimal_parameters);

       return(model_selection_results);
    */
}


// ModelSelectionResults perform_inputs_selection(void) const method

/// @todo

void ModelSelection::perform_inputs_selection(void) const
{
   switch(inputs_selection_method)
   {
        case MaximumLinearCorrelation:
        {
            perform_maximum_linear_correlation_inputs_selection();
        }
        break;

        case MaximumLogisticCorrelation:
        {
           perform_maximum_logistic_correlation_inputs_selection();
        }
        break;

        case Exhaustive:
        {
           perform_exhaustive_inputs_selection();
        }
        break;

        default:
        {
             std::ostringstream buffer;

             buffer << "OpenNN Exception: ModelSelection class.\n"
                    << "void perform_inputs_selection(void) const method.\n"
                    << "Unknown inputs selection method.\n";

             throw std::logic_error(buffer.str());
        }
        break;
   }
}


// ModelSelectionResults perform_order_selection(void) method

/// @todo

ModelSelection::ModelSelectionResults ModelSelection::perform_order_selection(void) const
{
   std::ostringstream buffer;

   buffer << "OpenNN Exception: ModelSelection class.\n"
          << "ModelSelectionResults perform_order_selection(void) method.\n"
          << "This method is under development.\n";

   throw std::logic_error(buffer.str());
/*
   // Training algorithm stuff

   #ifndef NDEBUG 

   check();

   #endif

   // Performance functional stuff

   const PerformanceFunctional* performance_functional_pointer = training_strategy_pointer->get_performance_functional_pointer();

   DataSet* data_set_pointer = performance_functional_pointer->get_objective_pointer()->get_data_set_pointer();

   Variables* variables_pointer = data_set_pointer->get_variables_pointer();

   // Neural network stuff

   NeuralNetwork* neural_network_pointer = performance_functional_pointer->get_neural_network_pointer(); 

   MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   #ifndef NDEBUG 

   const size_t layers_number = multilayer_perceptron_pointer->get_layers_number();

   if(layers_number != 2) 
   {
     std::ostringstream buffer;

      buffer << "OpenNN Exception: ModelSelection class.\n"
             << "ModelSelectionResults perform_order_selection(void) method.\n"
             << "Number of layers in multilayer perceptron must be two.\n";

      throw std::logic_error(buffer.str());
   }   

   #endif

   // Model order selection stuff

   const size_t complexity_assays_number = hidden_perceptrons_numbers.size();

   ModelSelectionResults model_order_selection_results;

   if(reserve_parameters_data)
   {
      model_order_selection_results.parameters_data.set(complexity_assays_number, parameters_assays_number);
   }  
	 
   if(reserve_performance_data)
   {
      model_order_selection_results.performance_data.set(complexity_assays_number, parameters_assays_number);
   }

   if(reserve_generalization_performance_data)
   {
      model_order_selection_results.generalization_performance_data.set(complexity_assays_number, parameters_assays_number);
   }

   time_t beginning_time, current_time;
   time(&beginning_time);
   double elapsed_time;

   size_t assay_count = 0;

   for(size_t i = 0; i < complexity_assays_number; i++)
   {
//	  variables_pointer->set_inputs_indices(inputs_indices[i]);

      //multilayer_perceptron_pointer->set_layer_perceptrons_number(0, hidden_perceptrons_numbers[i]);

      for(size_t j = 0; j < parameters_assays_number; j++)
	  {
         try
		 {
            assay_count++; 

			// Multilayer perceptron

            multilayer_perceptron_pointer->randomize_parameters_normal();

			// Performance functional 

			// Training algorithm

   	        training_strategy_pointer->perform_training();
	   
			// Model order selection

            if(reserve_parameters_data)
            {
		       model_order_selection_results.parameters_data(i,j) = multilayer_perceptron_pointer->arrange_parameters();
			}

            if(reserve_parameters_data)
            {
		       model_order_selection_results.performance_data(i,j) = training_strategy_pointer->get_performance_functional_pointer()->calculate_performance();
			}

            if(reserve_parameters_data)
            {
		       model_order_selection_results.generalization_performance_data(i,j) = training_strategy_pointer->get_performance_functional_pointer()->calculate_generalization_performance();			
			}

            time(&current_time);
            elapsed_time = difftime(current_time, beginning_time);

			if(display)
			{
               std::cout << "Assay " << assay_count << ";\n"
                         << "Hidden layer size: " << hidden_perceptrons_numbers[i] << "\n"
                         << "Parameters set: " << j+1 << "\n"
						 << "performance: " << model_order_selection_results.performance_data(i,j) << "\n"
						 << "Generalization performance: " << model_order_selection_results.generalization_performance_data(i,j) << "\n"
						 << "Elapsed time: " << elapsed_time << std::endl;
			}
		 }
         catch(const std::logic_error& e)
         {
            std::cerr << e.what() << std::endl;
         }
      }
   }

   const Vector<size_t> minimal_indices = model_order_selection_results.generalization_performance_data.calculate_minimal_indices();

   const Vector<double> minimal_parameters = model_order_selection_results.parameters_data[minimal_indices [0]][minimal_indices[1]];

   multilayer_perceptron_pointer->set_parameters(minimal_parameters);

   if(reserve_minimal_parameters)
   {
   }

// Vector< Vector<double> > calculate_performance_data_statistics(const ModelSelectionResults&) const method
//   return(model_order_selection_data.performance_data.calculate_transpose().calculate_statistics());  

// Vector< Vector<double> > calculate_generalization_performance_data_statistics(const ModelSelectionResults&) const method
   //   return(model_order_selection_data.generalization_performance_data.calculate_transpose().calculate_statistics());  

//  const size_t complexities_number = hidden_perceptrons_numbers.size();

//   file << "# Performance data\n\n";

//   for(size_t i = 0; i < complexities_number; i++)
//   {    
//      file << hidden_perceptrons_numbers[i] << " ";

//      for(size_t j = 0; j < parameters_assays_number; j++)
//	  {
//	     file << model_order_selection_data.performance_data(i,j) << " ";
//	  }

//	  file << "\n";
//   }

//   file << "\n";

//   file << "# Generalization performance data\n\n";

//   for(size_t i = 0; i < complexities_number; i++)
//   {    
//      file << hidden_perceptrons_numbers[i] << " ";

//      for(size_t j = 0; j < parameters_assays_number; j++)
//	  {
//	     file << model_order_selection_data.generalization_performance_data(i,j) << " ";
//	  }

//	  file << "\n";
//   }


   return(model_order_selection_results);
*/
}


// ModelSelectionResults perform_model_selection(void) const method

/// @todo

ModelSelection::ModelSelectionResults ModelSelection::perform_model_selection(void) const
{
   std::ostringstream buffer;

   buffer << "OpenNN Exception: ModelSelection class.\n"
          << "ModelSelectionResults perform_model_selection(void) method.\n"
          << "This method is under development.\n";

   throw std::logic_error(buffer.str());

//   ModelSelectionResults model_selection_results;

//   return(model_selection_results);
}


// tinyxml2::XMLDocument* to_XML(void) const method

/// Serializes the model selection object into a XML document of the TinyXML library. 
/// See the OpenNN manual for more information about the format of this document. 

tinyxml2::XMLDocument* ModelSelection::to_XML(void) const
{
   tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument;

   std::ostringstream buffer; 

   // Model order selection

   tinyxml2::XMLElement* model_selection_element = document->NewElement("ModelSelection");

   document->InsertFirstChild(model_selection_element);

   // Hidden layer sizes

   tinyxml2::XMLElement* hidden_perceptrons_numbers_element = document->NewElement("HiddenLayerSizes");
   model_selection_element->LinkEndChild(hidden_perceptrons_numbers_element);

   buffer.str("");
   buffer << hidden_perceptrons_numbers;

   tinyxml2::XMLText* hidden_perceptrons_numbers_text = document->NewText(buffer.str().c_str());
   hidden_perceptrons_numbers_element->LinkEndChild(hidden_perceptrons_numbers_text);

   // ParametersAssaysNumber

   tinyxml2::XMLElement* parameters_assays_number_element = document->NewElement("ParametersAssaysNumber");
   model_selection_element->LinkEndChild(parameters_assays_number_element);

   buffer.str("");
   buffer << parameters_assays_number;

   tinyxml2::XMLText* parameters_assays_number_text = document->NewText(buffer.str().c_str());
   parameters_assays_number_element->LinkEndChild(parameters_assays_number_text);

   return(document);
}


// void from_XML(const tinyxml2::XMLDocument&) method

/// @todo

void ModelSelection::from_XML(const tinyxml2::XMLDocument&)
{
}


// void print(void) method

/// Prints to the screen the XML representation of this model selection object. 

void ModelSelection::print(void) const
{
   std::cout << to_XML();
}


// void save(const std::string&) const method

/// Saves the model selection members to a XML file. 
/// @param file_name Name of model selection XML file. 

void ModelSelection::save(const std::string& file_name) const
{
   tinyxml2::XMLDocument* document = to_XML();

   document->SaveFile(file_name.c_str());

   delete document;
}


// void load(const std::string&) method

/// Loads the model selection members from a XML file. 
/// @param file_name Name of model selection XML file. 

void ModelSelection::load(const std::string& file_name)
{
   std::ostringstream buffer;

   tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument;

   if(document->LoadFile(file_name.c_str()))
   {
      buffer << "OpenNN Exception: ModelSelection class.\n"
             << "void load(const std::string&) method.\n"
             << "Cannot load XML file " << file_name << ".\n";

      throw std::logic_error(buffer.str());
   }

   // Root
   
   tinyxml2::XMLElement* model_selection_element = document->FirstChildElement("ModelSelection");

   if(!model_selection_element)
   {
      buffer << "OpenNN Exception: ModelSelection class.\n"
             << "void load(const std::string&) method.\n"
             << "Invalid model order selection XML root element.\n";

      throw std::logic_error(buffer.str());
   }
    
   // Hidden layer sizes
   
   tinyxml2::XMLElement* hidden_perceptrons_numbers_element = model_selection_element->FirstChildElement("HiddenLayerSizes");

   if(hidden_perceptrons_numbers_element)
   {
      Vector<size_t> new_hidden_perceptrons_numbers;
      new_hidden_perceptrons_numbers.parse(hidden_perceptrons_numbers_element->GetText());

      try
      {
         set_hidden_perceptrons_numbers(new_hidden_perceptrons_numbers);
      }
      catch(const std::logic_error& e)
      {
         std::cout << e.what() << std::endl;		 
      }
   }

   // Parameters assays number
   
   tinyxml2::XMLElement* parameters_assays_number_element = model_selection_element->FirstChildElement("ParametersAssaysNumber");

   if(parameters_assays_number_element)
   {
      parameters_assays_number = atoi(parameters_assays_number_element->GetText());           
   }
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
