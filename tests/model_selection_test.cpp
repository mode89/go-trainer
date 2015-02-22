/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   M O D E L   S E L E C T I O N   T E S T   C L A S S                                                        */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - Making intelligent use of data                                                                 */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// Unit testing includes

#include "model_selection_test.h"

using namespace OpenNN;


ModelSelectionTest::ModelSelectionTest(void) : UnitTesting() 
{
}


ModelSelectionTest::~ModelSelectionTest(void) 
{
}


void ModelSelectionTest::test_constructor(void)
{
   message += "test_constructor\n";
}


void ModelSelectionTest::test_destructor(void)
{
   message += "test_destructor\n";
}


void ModelSelectionTest::test_get_training_strategy_pointer(void)
{
   message += "test_get_training_algorithm_pointer\n";
}


// @todo

void ModelSelectionTest::test_get_hidden_layer_sizes(void)
{
   message += "test_get_hidden_layer_sizes\n";

//   ModelSelection ms;

//   Vector<size_t> ghidden_perceptrons_numbers;

   // Test

//   hidden_perceptrons_numbers = ms.get_hidden_perceptrons_numbers();

//   assert_true(ghidden_perceptrons_numbers.size() == 0, LOG);

}


// @todo

void ModelSelectionTest::test_get_sample_size(void)
{
   message += "test_get_sample_size\n";

//   ModelSelection ms;

//   size_t sample_size;

   // Test

//   sample_size = mos.get_sample_size();

//   assert_true(sample_size == 0, LOG);

}


void ModelSelectionTest::test_get_display(void)
{
   message += "test_get_display\n";
}


void ModelSelectionTest::test_set_training_strategy_pointer(void)
{
   message += "test_set_training_strategy_pointer\n";
}


void ModelSelectionTest::test_set_default(void)
{
   message += "test_set_default\n";
}


void ModelSelectionTest::test_set_hidden_layer_sizes(void)
{
   message += "test_set_hidden_layer_sizes\n";
}


void ModelSelectionTest::test_set_sample_size(void)
{
   message += "test_set_sample_size\n";  
}


void ModelSelectionTest::test_set_assays_numbers(void)
{
   message += "test_set_assays_numbers\n";
}


void ModelSelectionTest::test_set_display(void)
{
   message += "test_set_display\n";
}


void ModelSelectionTest::test_calculate_linear_correlations(void)
{
    message += "test_calculate_linear_correlations\n";

    Matrix<double> data;

    DataSet ds;

    Instances* ip = ds.get_instances_pointer();

    NeuralNetwork nn;

    PerformanceFunctional pf(&nn, &ds);

    TrainingStrategy ts(&pf);

    ModelSelection ms(&ts);

    Matrix<double> correlations;

    // Test

    data.set(2, 2);
    data.randomize_normal();

    ds.set(2, 2);
    ds.set_data(data);

    ip->set_generalization();

    nn.set(1, 1);

    correlations = ms.calculate_linear_correlations();

    assert_true(correlations.get_rows_number() == 1, LOG);
    assert_true(correlations.get_columns_number() == 1, LOG);
}


// @todo

void ModelSelectionTest::test_calculate_logistic_correlations(void)
{
    message += "test_calculate_logistic_correlations\n";
/*
    Matrix<double> data;

    DataSet ds;

    Instances* ip = ds.get_instances_pointer();

    NeuralNetwork nn;

    PerformanceFunctional pf(&nn, &ds);

    TrainingStrategy ts(&pf);

    ModelSelection ms(&ts);

    Matrix<double> correlations;

    // Test

    data.set(2, 2);
    data.randomize_normal();

    ds.set(2, 2);
    ds.set_data(data);

    ip->set_generalization();

    nn.set(1, 1);

    correlations = ms.calculate_logistic_correlations();

    assert_true(correlations.get_rows_number() == 1, LOG);
    assert_true(correlations.get_columns_number() == 1, LOG);


        Vector<double> x;
        Vector<double> y;

        LogisticRegressionParameters<double> logistic_regression_parameters;

        // Test

        x.set(16);
        y.set(16);

        x[0]  =  0; y[0]  = 0.4;
        x[1]  =  1; y[1]  = 0.6;
        x[2]  =  2; y[2]  = 1.0;
        x[3]  =  3; y[3]  = 1.6;
        x[4]  =  4; y[4]  = 2.4;
        x[5]  =  5; y[5]  = 3.4;
        x[6]  =  6; y[6]  = 4.6;
        x[7]  =  7; y[7]  = 5.8;
        x[8]  =  8; y[8]  = 6.9;
        x[9]  =  9; y[9]  = 7.9;
        x[10] = 10; y[10] = 8.6;
        x[11] = 11; y[11] = 9.1;
        x[12] = 12; y[12] = 9.4;
        x[13] = 13; y[13] = 9.7;
        x[14] = 14; y[14] = 9.8;
        x[15] = 15; y[14] = 9.9;

        logistic_regression_parameters = y.calculate_logistic_regression_parameters(x);

    //    assert_true(fabs(fabs(logistic_regression_parameters.position) - fabs(-39.1468)) < 1.0, LOG);
    //    assert_true(fabs(logistic_regression_parameters.slope - 61.6746) < 1.0, LOG);
    //    assert_true(fabs(logistic_regression_parameters.correlation - 0.9945) < 1.0e-3, LOG);
    */
}


// @todo

void ModelSelectionTest::test_perform_model_order_selection(void)
{
   message += "test_perform_model_order_selection\n";

   NeuralNetwork nn;

   DataSet ds;

   PerformanceFunctional pf(&nn, &ds);

   TrainingStrategy ts(&pf);

   ModelSelection ms(&ts);

//   Vector<int> hidden_layer_sizes;
//   int sample_size;

//   ModelSelection::ModelSelectionResults model_selection_results;

	// Test 

//   nn.set(1, 1);

//   ds.set(10, 1, 1);
//   ds.randomize_data_normal();
//   ds.split_random_indices();

//   gd.set_maximum_iterations_number(1);
//   gd.set_display(false);

//   hidden_layer_sizes.set(1, 1);
//   mos.set_hidden_layer_sizes(hidden_layer_sizes);

//   sample_size = 1;
//   mos.set_sample_size(sample_size);

//   mos.set_display(false);

//   model_order_selection_data = mos.perform_model_order_selection();

//   assert_true(model_order_selection_data.parameters_data.get_rows_number() == 1, LOG);
//   assert_true(model_order_selection_data.parameters_data.get_columns_number() == 1, LOG);

//   assert_true(model_order_selection_data.training_objective_data.get_rows_number() == 1, LOG);
//   assert_true(model_order_selection_data.training_objective_data.get_columns_number() == 1, LOG);

//   assert_true(model_order_selection_data.generalization_objective_data.get_rows_number() == 1, LOG);
//   assert_true(model_order_selection_data.generalization_objective_data.get_columns_number() == 1, LOG);

}


void ModelSelectionTest::test_to_XML(void)   
{
	message += "test_to_XML\n";
   
   ModelSelection ms;

   tinyxml2::XMLDocument* document;

   // Test

   document = ms.to_XML();

   assert_true(document != NULL, LOG);
}


void ModelSelectionTest::test_print(void)
{
	message += "test_print\n";
}


void ModelSelectionTest::test_save(void)
{
	message += "test_save\n";
}


// @todo

void ModelSelectionTest::test_load(void)
{
//    std::string file_name = "../data/model_selection.xml";

//   ModelSelection ms;

   // Test

//   ms.set_display(false);

//   ms.save(file_name);

//   ms.load(file_name);

//   assert_true(ms.get_display() == false, LOG);
}


void ModelSelectionTest::run_test_case(void)
{
   message += "Running model selection test case...\n";

   // Constructor and destructor methods

   test_constructor();
   test_destructor();

   // Get methods

   test_get_training_strategy_pointer();

   test_get_hidden_layer_sizes();
   test_get_sample_size();

   test_get_display();

   // Set methods

   test_set_training_strategy_pointer();

   test_set_default();

   test_set_hidden_layer_sizes();
   test_set_sample_size();

   test_set_assays_numbers();

   test_set_display();

   // Correlation methods

   test_calculate_linear_correlations();
   test_calculate_logistic_correlations();

   // Generalization analysis methods

   test_perform_model_order_selection();

   // Serialization methods

   test_to_XML();   

   test_print();
   test_save();

   test_load();

   message += "End of model selection test case.\n";
}


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2015 Roberto Lopez.
//
// This library is free software; you can redistribute it and/or
// modify it under the s of the GNU Lesser General Public
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
