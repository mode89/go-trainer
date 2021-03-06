/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   C O N J U G A T E   G R A D I E N T   T E S T   C L A S S                                                  */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - Making intelligent use of data                                                                 */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// Unit testing includes

#include "conjugate_gradient_test.h"

using namespace OpenNN;

// GENERAL CONSTRUCTOR

ConjugateGradientTest::ConjugateGradientTest(void) : UnitTesting() 
{
}


// DESTRUCTOR

ConjugateGradientTest::~ConjugateGradientTest(void)
{
}


// METHODS

void ConjugateGradientTest::test_constructor(void)
{
   message += "test_constructor\n"; 

   PerformanceFunctional pf;

   // Default constructor

   ConjugateGradient cg1; 
   assert_true(cg1.has_performance_functional() == false, LOG);

   // Performance functional constructor

   ConjugateGradient cg2(&pf); 
   assert_true(cg2.has_performance_functional() == true, LOG);
}


void ConjugateGradientTest::test_destructor(void)
{
   message += "test_destructor\n";
}


void ConjugateGradientTest::test_get_training_direction_method(void)
{
   message += "test_get_training_direction_method\n";

   ConjugateGradient cg;

   cg.set_training_direction_method(ConjugateGradient::PR);

   ConjugateGradient::TrainingDirectionMethod training_direction_method = cg.get_training_direction_method();

   assert_true(training_direction_method == ConjugateGradient::PR, LOG);
}


void ConjugateGradientTest::test_get_training_direction_method_name(void)
{
   message += "test_get_training_direction_method_name\n";
}


void ConjugateGradientTest::test_set_training_direction_method(void)
{
   message += "test_set_training_direction_method\n";

   ConjugateGradient cg;

   cg.set_training_direction_method(ConjugateGradient::FR);
   assert_true(cg.get_training_direction_method() == ConjugateGradient::FR, LOG);

   cg.set_training_direction_method(ConjugateGradient::PR);
   assert_true(cg.get_training_direction_method() == ConjugateGradient::PR, LOG);
}


void ConjugateGradientTest::test_set_reserve_all_training_history(void)
{
   message += "test_set_reserve_all_training_history\n";

   ConjugateGradient cg;
   cg.set_reserve_all_training_history(true);

   assert_true(cg.get_reserve_parameters_history() == true, LOG);
   assert_true(cg.get_reserve_parameters_norm_history() == true, LOG);

   assert_true(cg.get_reserve_performance_history() == true, LOG);
   assert_true(cg.get_reserve_gradient_history() == true, LOG);
   assert_true(cg.get_reserve_gradient_norm_history() == true, LOG);

   assert_true(cg.get_reserve_training_direction_history() == true, LOG);
   assert_true(cg.get_reserve_training_rate_history() == true, LOG);
   assert_true(cg.get_reserve_elapsed_time_history() == true, LOG);
   assert_true(cg.get_reserve_generalization_performance_history() == true, LOG);
}


void ConjugateGradientTest::test_calculate_PR_parameter(void)
{
   message += "test_calculate_PR_parameter\n";

   DataSet ds(1, 1, 2);
   ds.randomize_data_normal();

   NeuralNetwork nn(1 ,1);
   PerformanceFunctional pf(&nn, &ds);
   ConjugateGradient cg(&pf);

   nn.initialize_parameters(2.0);
   Vector<double> old_gradient = pf.calculate_gradient();

   nn.initialize_parameters(1.0);
   Vector<double> gradient = pf.calculate_gradient();

   double PR_parameter = cg.calculate_PR_parameter(old_gradient, gradient);

   assert_true(PR_parameter >= 0.0, LOG);
   assert_true(PR_parameter <= 1.0, LOG);
}


void ConjugateGradientTest::test_calculate_FR_parameter(void)
{
   message += "test_calculate_FR_parameter\n";

   DataSet ds(1, 1, 2);
   ds.randomize_data_normal();
   NeuralNetwork nn(1 ,1);
   PerformanceFunctional pf(&nn, &ds);
   ConjugateGradient cg(&pf);

   nn.initialize_parameters(2.0);
   Vector<double> old_gradient = pf.calculate_gradient();

   nn.initialize_parameters(1.0);
   Vector<double> gradient = pf.calculate_gradient();

   double FR_parameter = cg.calculate_FR_parameter(old_gradient, gradient);

   assert_true(FR_parameter >= 0.0, LOG);
   assert_true(FR_parameter <= 1.0, LOG);
}


void ConjugateGradientTest::test_calculate_PR_training_direction(void)
{
   message += "test_calculate_PR_training_direction\n";

   DataSet ds(1, 1, 2);
   ds.randomize_data_normal();
   NeuralNetwork nn(1 ,1);
   PerformanceFunctional pf(&nn, &ds);
   ConjugateGradient cg(&pf);

   nn.initialize_parameters(2.0);
   Vector<double> old_gradient = pf.calculate_gradient();
   Vector<double> old_training_direction = old_gradient;   

   nn.initialize_parameters(1.0);
   Vector<double> gradient = pf.calculate_gradient();

   Vector<double> PR_training_direction 
   = cg.calculate_PR_training_direction(old_gradient, gradient, old_training_direction);

   size_t parameters_number = nn.count_parameters_number();

   assert_true(PR_training_direction.size() == parameters_number, LOG);
}


void ConjugateGradientTest::test_calculate_FR_training_direction(void)
{
   message += "test_calculate_FR_training_direction\n";

   DataSet ds(1, 1, 2);
   ds.randomize_data_normal();
   NeuralNetwork nn(1 ,1);
   PerformanceFunctional pf(&nn, &ds);
   ConjugateGradient cg(&pf);

   nn.initialize_parameters(2.0);
   Vector<double> old_gradient = pf.calculate_gradient();
   Vector<double> old_training_direction = old_gradient;   

   nn.initialize_parameters(1.0);
   Vector<double> gradient = pf.calculate_gradient();
	
   Vector<double> FR_training_direction 
   = cg.calculate_FR_training_direction(old_gradient, gradient, old_training_direction);

   size_t parameters_number = nn.count_parameters_number();

   assert_true(FR_training_direction.size() == parameters_number, LOG);
}


void ConjugateGradientTest::test_calculate_training_direction(void)
{
   message += "test_calculate_training_direction\n";

}


void ConjugateGradientTest::test_perform_training(void)
{
   message += "test_perform_training\n";

   DataSet ds(1, 1, 1);
   ds.randomize_data_normal();

   NeuralNetwork nn(1, 1, 1);

   PerformanceFunctional pf(&nn, &ds);

   pf.set_objective_type(PerformanceFunctional::SUM_SQUARED_ERROR_OBJECTIVE);

   double old_performance;
   double performance;

   double performance_goal;

   ConjugateGradient cg(&pf);

   double minimum_parameters_increment_norm;

   // Test

   nn.randomize_parameters_normal();

   old_performance = pf.calculate_performance();

   cg.set_display(false);
   cg.set_maximum_iterations_number(1);

   cg.perform_training();

   performance = pf.calculate_performance();

   assert_true(performance < old_performance, LOG);

   // Minimum parameters increment norm

   nn.initialize_parameters(-1.0);

   minimum_parameters_increment_norm = 0.1;

   cg.set_minimum_parameters_increment_norm(minimum_parameters_increment_norm);
   cg.set_performance_goal(0.0);
   cg.set_minimum_performance_increase(0.0);
   cg.set_gradient_norm_goal(0.0);
   cg.set_maximum_iterations_number(1000);
   cg.set_maximum_time(1000.0);

   cg.perform_training();

   // Performance goal

   nn.initialize_parameters(-1.0);

   performance_goal = 0.1;

   cg.set_minimum_parameters_increment_norm(0.0);
   cg.set_performance_goal(performance_goal);
   cg.set_minimum_performance_increase(0.0);
   cg.set_gradient_norm_goal(0.0);
   cg.set_maximum_iterations_number(1000);
   cg.set_maximum_time(1000.0);

   cg.perform_training();

   performance = pf.calculate_performance();

   assert_true(performance < performance_goal, LOG);

   // Minimum evaluation improvement

   nn.initialize_parameters(-1.0);

   double minimum_performance_increase = 0.1;

   cg.set_minimum_parameters_increment_norm(0.0);
   cg.set_performance_goal(0.0);
   cg.set_minimum_performance_increase(minimum_performance_increase);
   cg.set_gradient_norm_goal(0.0);
   cg.set_maximum_iterations_number(1000);
   cg.set_maximum_time(1000.0);

   cg.perform_training();

   // Gradient norm goal 

   nn.initialize_parameters(-1.0);

   double gradient_norm_goal = 0.1;

   cg.set_minimum_parameters_increment_norm(0.0);
   cg.set_performance_goal(0.0);
   cg.set_minimum_performance_increase(0.0);
   cg.set_gradient_norm_goal(gradient_norm_goal);
   cg.set_maximum_iterations_number(1000);
   cg.set_maximum_time(1000.0);

   cg.perform_training();

   double gradient_norm = pf.calculate_gradient().calculate_norm();

   assert_true(gradient_norm < gradient_norm_goal, LOG);

}


void ConjugateGradientTest::test_to_XML(void)   
{
   message += "test_to_XML\n";

   ConjugateGradient cg;

   tinyxml2::XMLDocument* cgd = cg.to_XML();
   assert_true(cgd != NULL, LOG);
}


void ConjugateGradientTest::test_from_XML(void)
{
   message += "test_from_XML\n";

   ConjugateGradient cg1;
   ConjugateGradient cg2;

   tinyxml2::XMLDocument* document;

   // Test

   cg1.initialize_random();

   document = cg1.to_XML();

   cg2.from_XML(*document);

   delete document;

   assert_true(cg1 == cg2, LOG);

}


void ConjugateGradientTest::run_test_case(void)
{
   message += "Running conjugate gradient test case...\n";

   // Constructor and destructor methods

   test_constructor();
   test_destructor();

   // Get methods

   test_get_training_direction_method();
   test_get_training_direction_method_name();

   // Set methods

   test_set_training_direction_method();

   // Training methods

   test_calculate_PR_parameter();
   test_calculate_FR_parameter();

   test_calculate_FR_training_direction();
   test_calculate_PR_training_direction();

   test_calculate_training_direction();

   test_perform_training();

   // Training history methods

   test_set_reserve_all_training_history();

   // Serialization methods

   test_to_XML();   
   test_from_XML();

   message += "End of conjugate gradient test case.\n";
}


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2015 Roberto Lopez.
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
