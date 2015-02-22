/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   D A T A   S E T   T E S T   C L A S S                                                                      */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - Making intelligent use of data                                                                 */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// Unit testing includes

#include "data_set_test.h"

using namespace OpenNN;

// GENERAL CONSTRUCTOR

DataSetTest::DataSetTest(void) : UnitTesting() 
{
}



// DESTRUCTOR

DataSetTest::~DataSetTest(void)
{
}


// METHODS

void DataSetTest::test_constructor(void)
{
   message += "test_constructor\n";

   // Default constructor

   DataSet ds1;

   assert_true(ds1.get_variables().get_variables_number() == 0, LOG);
   assert_true(ds1.get_instances().get_instances_number() == 0, LOG);

   // Instances and variables number constructor

   DataSet ds2(1, 2);

   assert_true(ds2.get_variables().get_variables_number() == 1, LOG);
   assert_true(ds2.get_instances().get_instances_number() == 2, LOG);

   // Inputs, targets and instances numbers constructor

   DataSet ds3(1, 1, 1);

   assert_true(ds3.get_variables().get_variables_number() == 2, LOG);
   assert_true(ds3.get_instances().get_instances_number() == 1, LOG);

   // XML constructor

   tinyxml2::XMLDocument* document = ds3.to_XML();

   DataSet ds4(*document);

   assert_true(ds4.get_variables().get_variables_number() == 2, LOG);
   assert_true(ds4.get_instances().get_instances_number() == 1, LOG);

   delete document;

   // File constructor

   const std::string file_name = "../data/data_set.xml";

   ds1.save(file_name);

   DataSet ds5(file_name);

   assert_true(ds5.get_variables().get_variables_number() == 0, LOG);
   assert_true(ds5.get_instances().get_instances_number() == 0, LOG);

   // Copy constructor

   DataSet ds6(ds1);

   assert_true(ds6.get_variables().get_variables_number() == 0, LOG);
   assert_true(ds6.get_instances().get_instances_number() == 0, LOG);

}


void DataSetTest::test_destructor(void)
{
   message += "test_destructor\n";

   DataSet* dsp = new DataSet(1, 1, 1);

   delete dsp;
}


void DataSetTest::test_assignment_operator(void)
{
   message += "test_assignment_operator\n";

   DataSet ds1(1, 1, 1);
   DataSet ds2 = ds1;

   assert_true(ds2.get_instances().get_instances_number() == 1, LOG);
   assert_true(ds2.get_variables().get_variables_number() == 2, LOG);
}


void DataSetTest::test_get_instances_number(void) 
{
   message += "test_get_instances_number\n";

   DataSet ds;

   assert_true(ds.get_instances().get_instances_number() == 0, LOG);
}


void DataSetTest::test_get_variables_number(void) 
{
   message += "test_get_variables_number\n";

   DataSet ds;

   assert_true(ds.get_variables().get_variables_number() == 0, LOG);
}


void DataSetTest::test_get_variables(void) 
{
   message += "test_get_variables\n";

   DataSet ds(1, 3, 2);

   const Variables& variables = ds.get_variables();

   assert_true(variables.count_inputs_number() == 1, LOG);
   assert_true(variables.count_targets_number() == 3, LOG);
}


void DataSetTest::test_get_display(void) 
{
   message += "test_get_display\n";

   DataSet ds;

   ds.set_display(true);

   assert_true(ds.get_display() == true, LOG);

   ds.set_display(false);

   assert_true(ds.get_display() == false, LOG);
}


void DataSetTest::test_get_data(void) 
{
   message += "test_get_data\n";

   DataSet ds(1,1,1);

   ds.initialize_data(0.0);

   const Matrix<double>& data = ds.get_data();

   assert_true(data.get_rows_number() == 1, LOG);
   assert_true(data.get_columns_number() == 2, LOG);
   assert_true(data == 0.0, LOG);
}


void DataSetTest::test_arrange_training_data(void)
{
   message += "test_arrange_training_data\n";
}


void DataSetTest::test_arrange_generalization_data(void)
{
   message += "test_arrange_generalization_data\n";
}


void DataSetTest::test_arrange_testing_data(void)
{
   message += "test_arrange_testing_data\n";
}


void DataSetTest::test_arrange_input_data(void) 
{
   message += "test_arrange_input_data\n";

   DataSet ds(1, 3, 2);

   size_t instances_number = ds.get_instances().get_instances_number();
   size_t inputs_number = ds.get_variables().count_inputs_number();

   Matrix<double> input_data = ds.arrange_input_data();

   size_t rows_number = input_data.get_rows_number();
   size_t columns_number = input_data.get_columns_number();

   assert_true(instances_number == rows_number, LOG);
   assert_true(inputs_number == columns_number, LOG);
}


void DataSetTest::test_arrange_target_data(void) 
{
   message += "test_arrange_target_data\n";

   DataSet ds(1,3,2);

   size_t instances_number = ds.get_instances().get_instances_number();
   size_t targets_number = ds.get_variables().count_targets_number();

   Matrix<double> target_data = ds.arrange_target_data();

   size_t rows_number = target_data.get_rows_number();
   size_t columns_number = target_data.get_columns_number();

   assert_true(instances_number == rows_number, LOG);
   assert_true(targets_number == columns_number, LOG);
}


void DataSetTest::test_get_instance(void)
{
   message += "test_get_instance\n";

   DataSet ds;
   Vector<double> instance;

   // Test

   ds.set(1, 1, 1);
   ds.initialize_data(1.0);

   instance = ds.get_instance(0);

   assert_true(instance.size() == 2, LOG);
   assert_true(instance == 1.0, LOG);

}


void DataSetTest::test_set(void) 
{
   message += "test_set\n";

   DataSet ds;

   // Instances and inputs and target variables

   ds.set(1, 2, 3);

   assert_true(ds.get_variables().count_inputs_number() == 1, LOG);
   assert_true(ds.get_variables().count_targets_number() == 2, LOG);
   assert_true(ds.get_instances().get_instances_number() == 3, LOG);

   const Matrix<double>& data = ds.get_data();

   assert_true(data.get_rows_number() == 3, LOG);
   assert_true(data.get_columns_number() == 3, LOG);
}


void DataSetTest::test_set_instances_number(void) 
{
   message += "test_set_instances_number\n";

   DataSet ds(1,1,1);

   ds.set_instances_number(2);

   assert_true(ds.get_instances().get_instances_number() == 2, LOG);
}


void DataSetTest::test_set_variables_number(void) 
{
   message += "test_set_variables_number\n";

   DataSet ds(1, 1);

   ds.set_variables_number(2);

   assert_true(ds.get_variables().get_variables_number() == 2, LOG);
}


void DataSetTest::test_set_display(void) 
{
   message += "test_set_display\n";
}


void DataSetTest::test_set_data(void) 
{
   message += "test_set_data\n";

   DataSet ds(1, 1, 1);

   Matrix<double> new_data(1, 2, 0.0);

   ds.set_data(new_data);

   Matrix<double> data = ds.get_data();

   assert_true(data == new_data, LOG);
}


void DataSetTest::test_set_instance(void)
{
   message += "test_set_instance\n";

   DataSet ds(1, 1, 1);

   Vector<double> new_instance(2, 0.0);

   ds.set_instance(0, new_instance);

   Vector<double> instance = ds.get_instance(0);

   assert_true(instance == new_instance, LOG);
}


void DataSetTest::test_add_instance(void) 
{
   message += "test_add_instance\n";

   DataSet ds(1,1,1);

   Vector<double> new_instance(2, 0.0);

   ds.add_instance(new_instance);

   assert_true(ds.get_instances().get_instances_number() == 2, LOG);

   Vector<double> instance = ds.get_instance(1);

   assert_true(instance == new_instance, LOG);

}


void DataSetTest::test_subtract_instance(void) 
{
   message += "test_subtract_instance\n";

   DataSet ds(1, 1, 3);

   ds.subtract_instance(1);

   assert_true(ds.get_instances().get_instances_number() == 2, LOG);
}


void DataSetTest::test_calculate_data_statistics(void) 
{
   message += "test_calculate_data_statistics\n";

   DataSet ds(2, 2, 2);

   ds.initialize_data(0.0);

   Vector< Statistics<double> > statistics = ds.calculate_data_statistics();

   assert_true(statistics.size() == 4, LOG);

   assert_true(statistics[0].minimum == 0.0, LOG);
   assert_true(statistics[0].maximum == 0.0, LOG);
   assert_true(statistics[0].mean == 0.0, LOG);
   assert_true(statistics[0].standard_deviation == 0.0, LOG);

   assert_true(statistics[1].minimum == 0.0, LOG);
   assert_true(statistics[1].maximum == 0.0, LOG);
   assert_true(statistics[1].mean == 0.0, LOG);
   assert_true(statistics[1].standard_deviation == 0.0, LOG);

   assert_true(statistics[2].minimum == 0.0, LOG);
   assert_true(statistics[2].maximum == 0.0, LOG);
   assert_true(statistics[2].mean == 0.0, LOG);
   assert_true(statistics[2].standard_deviation == 0.0, LOG);

   assert_true(statistics[3].minimum == 0.0, LOG);
   assert_true(statistics[3].maximum == 0.0, LOG);
   assert_true(statistics[3].mean == 0.0, LOG);
   assert_true(statistics[3].standard_deviation == 0.0, LOG);
}


void DataSetTest::test_calculate_training_instances_statistics(void)
{
   message += "test_calculate_training_instances_statistics\n";

   DataSet ds;
   Vector< Statistics<double> > training_instances_statistics;

   Instances* instances_pointer;

   // Test

   ds.set(2, 2, 2);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_training();

   ds.initialize_data(0.0);

   ds.calculate_training_instances_statistics();

}


void DataSetTest::test_calculate_generalization_instances_statistics(void)
{
   message += "test_calculate_generalization_instances_statistics\n";

   DataSet ds;
   Vector< Statistics<double> > generalization_instances_statistics;

   Instances* instances_pointer;

   // Test

   ds.set(2,2,2);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_generalization();

   ds.initialize_data(0.0);

   generalization_instances_statistics = ds.calculate_generalization_instances_statistics();
}


void DataSetTest::test_calculate_testing_instances_statistics(void)
{
   message += "test_calculate_testing_instances_statistics\n";

   DataSet ds;
   Vector< Statistics<double> > testing_instances_statistics;

   Instances* instances_pointer;

   // Test

   ds.set(2, 2, 2);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_testing();
   
   ds.initialize_data(0.0);

   testing_instances_statistics = ds.calculate_testing_instances_statistics();
}


void DataSetTest::test_calculate_input_variables_statistics(void)
{
   message += "test_calculate_input_variables_statistics\n";
}


void DataSetTest::test_calculate_targets_statistics(void)
{
   message += "test_calculate_targets_statistics\n";
}


void DataSetTest::test_scale_inputs_mean_standard_deviation(void) 
{
   message += "test_scale_inputs_mean_standard_deviation\n";

   DataSet ds;

   Vector< Statistics<double> > inputs_statistics;

   // Test

   ds.set(2, 2, 2);
   ds.randomize_data_normal();

   ds.scale_inputs_mean_standard_deviation();

   inputs_statistics = ds.calculate_inputs_statistics();

   assert_true(inputs_statistics[0].has_mean_zero_standard_deviation_one(), LOG);
}


void DataSetTest::test_scale_targets_mean_standard_deviation(void) 
{
   message += "test_scale_targets_mean_standard_deviation\n";

   DataSet ds;

   Vector< Statistics<double> > targets_statistics;

   // Test

   ds.set(2, 2, 2);
   ds.randomize_data_normal();

   ds.scale_targets_mean_standard_deviation();

   targets_statistics = ds.calculate_targets_statistics();

   assert_true(targets_statistics[0].has_mean_zero_standard_deviation_one(), LOG);
}


void DataSetTest::test_scale_inputs_minimum_maximum(void) 
{
   message += "test_scale_inputs_minimum_maximum\n";

   DataSet ds;

   Vector< Statistics<double> > inputs_statistics;

   // Test

   ds.set(2, 2, 2);
   ds.randomize_data_normal();

   ds.scale_inputs_minimum_maximum();

   inputs_statistics = ds.calculate_inputs_statistics();

   assert_true(inputs_statistics[0].has_minimum_minus_one_maximum_one(), LOG);
}


void DataSetTest::test_scale_targets_minimum_maximum(void) 
{
   message += "test_scale_targets_minimum_maximum\n";

   DataSet ds;

   Vector< Statistics<double> > targets_statistics;

   // Test

   ds.set(2, 2, 2);
   ds.randomize_data_normal();

   ds.scale_targets_minimum_maximum();

   targets_statistics = ds.calculate_targets_statistics();

   assert_true(targets_statistics[0].has_minimum_minus_one_maximum_one(), LOG);
}


void DataSetTest::test_scale_data_minimum_maximum(void)
{
   message += "test_scale_data_minimum_maximum\n";

   DataSet ds;

   Vector< Statistics<double> > data_statistics;

   Matrix<double> data;
   Matrix<double> scaled_data;

    // Test

   ds.set(2,2,2);
   ds.initialize_data(0.0);

   ds.set_display(false);

   data = ds.get_data();

   data_statistics = ds.scale_data_minimum_maximum();

   scaled_data = ds.get_data();

   assert_true(scaled_data == data, LOG);
}


void DataSetTest::test_scale_data_mean_standard_deviation(void)
{
   message += "test_scale_data_mean_standard_deviation\n";

   DataSet ds;

   Vector< Statistics<double> > data_statistics;

   Matrix<double> data;
   Matrix<double> scaled_data;

    // Test

   ds.set(2,2,2);
   ds.initialize_data(0.0);

   ds.set_display(false);

   data = ds.get_data();

   data_statistics = ds.scale_data_mean_standard_deviation();

   scaled_data = ds.get_data();

   assert_true(scaled_data == data, LOG);
}


void DataSetTest::test_unscale_data_mean_standard_deviation(void)
{
   message += "test_unscale_data_mean_standard_deviation\n";
}


void DataSetTest::test_unscale_data_minimum_maximum(void)
{
   message += "test_unscale_data_minimum_maximum\n";
}


void DataSetTest::test_unscale_inputs_mean_standard_deviation(void) 
{
   message += "test_unscale_inputs_mean_standard_deviation\n";

   DataSet ds(2, 2, 2);
   ds.initialize_data(0.0);

   ds.set_display(false);

   Vector< Statistics<double> > data_statistics;

   // Test

   Matrix<double> input_data = ds.arrange_input_data();

   data_statistics.set(4);

   ds.unscale_inputs_mean_standard_deviation(data_statistics);

   Matrix<double> new_input_data = ds.arrange_input_data();

   assert_true(new_input_data == input_data, LOG);

}


void DataSetTest::test_unscale_targets_mean_standard_deviation(void) 
{
   message += "test_unscale_targets_mean_standard_deviation\n";
   
   DataSet ds(2, 2, 2);
   ds.initialize_data(0.0);

   ds.set_display(false);

   Matrix<double> target_data = ds.arrange_target_data();

   Vector< Statistics<double> > data_statistics(4);

   ds.unscale_targets_mean_standard_deviation(data_statistics);

   Matrix<double> new_target_data = ds.arrange_target_data();

   assert_true(new_target_data == target_data, LOG);
}


void DataSetTest::test_unscale_variables_mean_standard_deviation(void) 
{
   message += "test_unscale_variables_mean_standard_deviation\n";
}


void DataSetTest::test_unscale_inputs_minimum_maximum(void) 
{
   message += "test_unscale_inputs_minimum_maximum\n"; 

   DataSet ds(2, 2, 2);
   ds.initialize_data(0.0);

   ds.set_display(false);

   Vector< Statistics<double> > data_statistics;

   // Test

   Matrix<double> input_data = ds.arrange_input_data();

   data_statistics.set(4);

   ds.unscale_inputs_minimum_maximum(data_statistics);

   Matrix<double> new_input_data = ds.arrange_input_data();

   assert_true(new_input_data == input_data, LOG);
}


void DataSetTest::test_unscale_targets_minimum_maximum(void) 
{
   message += "test_unscale_targets_minimum_maximum\n";

   DataSet ds(2, 2, 2);
   ds.initialize_data(0.0);

   ds.set_display(false);

   Matrix<double> target_data = ds.arrange_target_data();

   Vector< Statistics<double> > data_statistics(4);

   ds.unscale_targets_minimum_maximum(data_statistics);

   Matrix<double> new_target_data = ds.arrange_target_data();

   assert_true(new_target_data == target_data, LOG);

}


void DataSetTest::test_unscale_variables_minimum_maximum(void) 
{
   message += "test_unscale_variables_minimum_maximum\n"; 
}


void DataSetTest::test_subtract_constant_variables(void)
{
   message += "test_subtract_constant_variables\n"; 

   DataSet ds;

   // Test 

   ds.set(1, 1, 2);

   ds.initialize_data(0.0);

   ds.unuse_constant_variables();

   assert_true(ds.get_variables().count_inputs_number() == 0, LOG);
   assert_true(ds.get_variables().count_targets_number() == 0, LOG);
}


void DataSetTest::test_subtract_repeated_instances(void)
{
   message += "test_subtract_repeated_instances\n"; 
}


void DataSetTest::test_initialize_data(void)
{
   message += "test_initialize_data\n";
}


void DataSetTest::test_calculate_target_class_distribution(void)
{
    message += "test_calculate_target_class_distribution\n";

}


/// @todo Make tests.

void DataSetTest::test_balance_target_class_distribution(void)
{
    message += "test_balance_target_class_distribution\n";

//    DataSet ds(2, 2, 2);
//    ds.initialize_data(0.0);

//    Vector<size_t> target_class_distribution;

//    // Test

//    ds.balance_target_class_distribution();

//    target_class_distribution = ds.calculate_target_class_distribution();

//    assert_true(target_class_distribution == 0, LOG);

}


void DataSetTest::test_to_XML(void) 
{
   message += "test_to_XML\n";

   DataSet ds;

   tinyxml2::XMLDocument* document;

   // Test

   document = ds.to_XML();

   assert_true(document != NULL, LOG);
}


void DataSetTest::test_from_XML(void) 
{
   message += "test_from_XML\n";

   DataSet ds;

   Variables* v = ds.get_variables_pointer();
   Instances* i = ds.get_instances_pointer();

   tinyxml2::XMLDocument* document;
   
   // Test

   document = ds.to_XML();

   ds.from_XML(*document);

   // Test

   ds.set(2, 2);

   v->set_use(0, Variables::Target);
   v->set_use(1, Variables::Unused);

   i->set_use(0, Instances::Unused);
   i->set_use(1, Instances::Testing);

   document = ds.to_XML();

   ds.set();

   ds.from_XML(*document);

   assert_true(v->get_variables_number() == 2, LOG);
   assert_true(v->get_use(0) == Variables::Target, LOG);
   assert_true(v->get_use(1) == Variables::Unused, LOG);
   assert_true(i->get_instances_number() == 2, LOG);
   assert_true(i->get_use(0) == Instances::Unused, LOG);
   assert_true(i->get_use(1) == Instances::Testing, LOG);
}


void DataSetTest::test_print(void) 
{
   message += "test_print\n";

   DataSet ds;

   ds.set_display(false);

//   ds.print();
}


void DataSetTest::test_save(void) 
{
   message += "test_save\n";

   std::string file_name = "../data/data_set.xml";

   DataSet ds;

   ds.set_display(false);

   ds.save(file_name);
}


void DataSetTest::test_load(void) 
{
   message += "test_load\n";

   std::string file_name = "../data/data_set.xml";
   std::string data_file_name = "../data/data.dat";

   DataSet ds;
   DataSet ds_copy;

   Matrix<double> data;

   // Test

   ds.set();

   ds.save(file_name);
   ds.load(file_name);

   // Test;

   ds.set();

   data.set(1, 2, 0.0);

   data.save(data_file_name);

   ds.set(2, 1);

   ds.set_data_file_name(data_file_name);

   ds.get_variables_pointer()->set_name(0, "x");
   ds.get_variables_pointer()->set_units(0, "[m]");
   ds.get_variables_pointer()->set_description(0, "distance");

   ds.get_variables_pointer()->set_name(1, "y");
   ds.get_variables_pointer()->set_units(1, "[s]");
   ds.get_variables_pointer()->set_description(1, "time");

   ds.save(file_name);
   ds_copy.load(file_name);

   assert_true(ds_copy.get_variables().get_variables_number() == 2, LOG);
   assert_true(ds_copy.get_instances().get_instances_number() == 1, LOG);

   assert_true(ds_copy.get_variables_pointer()->get_name(0) == "x", LOG);
   assert_true(ds_copy.get_variables_pointer()->get_unit(0) == "[m]", LOG);
   assert_true(ds_copy.get_variables_pointer()->get_description(0) == "distance", LOG);

   assert_true(ds_copy.get_variables_pointer()->get_name(1) == "y", LOG);
   assert_true(ds_copy.get_variables_pointer()->get_unit(1) == "[s]", LOG);
   assert_true(ds_copy.get_variables_pointer()->get_description(1) == "time", LOG);
}


void DataSetTest::test_print_data(void)
{
   message += "test_print_data\n";
}


void DataSetTest::test_save_data(void)
{
   message += "test_save_data\n";

   std::string data_file_name = "../data/data.dat";   

   DataSet ds(2,2,2);

   ds.set_display(false);

   ds.save_data(data_file_name);
}


/// @todo Fix bugs.

void DataSetTest::test_load_data(void) 
{
   message += "test_load_data\n";

   const std::string data_file_name = "../data/data.dat";

   std::ofstream file;

   DataSet ds;

   ds.set_data_file_name(data_file_name);

   Matrix<double> data;

   std::string data_string;

   // Test

   ds.set(2, 2, 2);
   ds.set_data_file_name(data_file_name);

   ds.initialize_data(0.0);

   ds.set_display(false);

   ds.save_data(data_file_name);

   ds.load_data();

   data = ds.get_data();

   assert_true(data == 0.0, LOG);

   // Test

   ds.set_separator(" ");

   data_string = "   1   2   \n   3   4   \n";

   file.open(data_file_name.c_str());
   file << data_string;
   file.close();

   ds.load_data();

   data = ds.get_data();

   assert_true(data(0,0) == 1, LOG);
   assert_true(data(0,1) == 2, LOG);
   assert_true(data(1,0) == 3, LOG);
   assert_true(data(1,1) == 4, LOG);

   // Test

   ds.set_separator("\t");

   data_string = "1 \t 2\n3 \t 4\n";

   file.open(data_file_name.c_str());
   file << data_string;
   file.close();

//   for(unsigned i = 0; i < 100; i++)
   {
   ds.load_data();

   data = ds.get_data();

   assert_true(data(0,0) == 1, LOG);
   assert_true(data(0,1) == 2, LOG);
   assert_true(data(1,0) == 3, LOG);
   assert_true(data(1,1) == 4, LOG);
   }

   // Test

   ds.set_header(true);
   ds.set_separator(" ");

   data_string = "x y\n1   2\n3   4\n";

   file.open(data_file_name.c_str());
   file << data_string;
   file.close();

   ds.load_data();

   data = ds.get_data();

   assert_true(ds.get_variables_pointer()->get_name(0) == "x", LOG);
   assert_true(ds.get_variables_pointer()->get_name(1) == "y", LOG);

   assert_true(data(0,0) == 1, LOG);
   assert_true(data(0,1) == 2, LOG);
   assert_true(data(1,0) == 3, LOG);
   assert_true(data(1,1) == 4, LOG);

   // Test
/*
   ds.set_header(true);
   ds.set_separator(",");

   data_string = "x , y\n"
                 "1 , 2\n"
                 "3 , 4\n";

   file.open(data_file_name);
   file << data_string;
   file.close();

   ds.load_data();

   data = ds.get_data();

   assert_true(ds.get_variables_pointer()->get_name(0) == "x", LOG);
   assert_true(ds.get_variables_pointer()->get_name(1) == "y", LOG);

   assert_true(data(0,0) == 1, LOG);
   assert_true(data(0,1) == 2, LOG);
   assert_true(data(1,0) == 3, LOG);
   assert_true(data(1,1) == 4, LOG);

/*
      ds.set_header(true);
      ds.set_separator(",");

      data_string = "x , y\n"
                    "1 , 2\n"
                    "3 , 4\n";

      file.open(data_file_name);
      file << data_string;
      file.close();

      ds.load_data();

      data = ds.get_data();

      assert_true(ds.get_variables_pointer()->get_name(0) == "x", LOG);
      assert_true(ds.get_variables_pointer()->get_name(1) == "y", LOG);

      assert_true(data(0,0) == 1, LOG);
      assert_true(data(0,1) == 2, LOG);
      assert_true(data(1,0) == 3, LOG);
      assert_true(data(1,1) == 4, LOG);
*/

}


void DataSetTest::test_get_data_statistics(void)
{
   message += "test_get_data_statistics\n";

   DataSet ds(1,1,1);
}


void DataSetTest::test_print_data_statistics(void)
{
   message += "test_print_data_statistics\n";
}


void DataSetTest::test_get_training_instances_statistics(void)
{
   message += "test_get_training_instances_statistics\n";

}


void DataSetTest::test_save_training_instances_statistics(void)
{
   message += "test_save_training_instances_statistics\n";
}


void DataSetTest::test_print_training_instances_statistics(void)
{
   message += "test_print_training_instances_statistics\n";
}


void DataSetTest::test_get_generalization_instances_statistics(void)
{
   message += "test_get_generalization_instances_statistics\n";
}


void DataSetTest::test_save_generalization_instances_statistics(void)
{
   message += "test_save_generalization_instances_statistics\n";
}


void DataSetTest::test_print_generalization_instances_statistics(void)
{
   message += "test_print_generalization_instances_statistics\n";
}


void DataSetTest::test_get_testing_instances_statistics(void)
{
   message += "test_get_testing_instances_statistics\n";
}


void DataSetTest::test_save_testing_instances_statistics(void)
{
   message += "test_save_testing_instances_statistics\n";
}


void DataSetTest::test_print_testing_instances_statistics(void)
{
   message += "test_print_testing_instances_statistics\n";
}


void DataSetTest::test_get_instances_statistics(void)
{
   message += "test_get_instances_statistics\n";
}


void DataSetTest::test_save_instances_statistics(void)
{
   message += "test_save_instances_statistics\n";
}


void DataSetTest::test_print_instances_statistics(void)
{
   message += "test_print_instances_statistics\n";
}


/// @todo Complete method and tests.

void DataSetTest::test_convert_time_series(void)
{
   message += "test_convert_time_series\n";

//   DataSet ds;

//   Matrix<double> data;

//   // Test

//   data.set(2, 2, 3.1416);

//   ds.set_data(data);

//   ds.set_lags_number(1);

//   ds.convert_time_series();

//   assert_true(ds.get_instances().get_instances_number() == 1, LOG);
//   assert_true(ds.get_variables().get_variables_number() == 4, LOG);

//   assert_true(ds.get_variables().count_inputs_number() == 2, LOG);
//   assert_true(ds.get_variables().count_targets_number() == 2, LOG);

   // Test


}


void DataSetTest::test_convert_autoassociation(void)
{
   message += "test_convert_autoassociation\n";
}


void DataSetTest::test_convert_angular_variable_degrees(void)
{
   message += "test_convert_angular_variable_degrees\n";
}


void DataSetTest::test_convert_angular_variable_radians(void)
{
   message += "test_convert_angular_variable_radians\n";
}


void DataSetTest::test_convert_angular_variables_degrees(void)
{
   message += "test_convert_angular_variables_degrees\n";

   DataSet ds;

   Matrix<double> data;

   Vector<size_t> angular_variables;

   // Test

   data.set(2,2, 1.234);

   ds.set(data);

   angular_variables.set(1, 0);

   ds.convert_angular_variables_degrees(angular_variables);

   assert_true(ds.get_variables().get_variables_number() == 3, LOG);
   assert_true(ds.get_data().arrange_column(0).calculate_absolute_value() <= 1.0, LOG);
   assert_true(ds.get_data().arrange_column(1).calculate_absolute_value() <= 1.0, LOG);
   assert_true(ds.get_data().arrange_column(2).calculate_absolute_value() == 1.234, LOG);

   // Test

   data.set(2,2, 1.234);

   ds.set(data);

   angular_variables.set(0,1,1);

   ds.convert_angular_variables_degrees(angular_variables);

   assert_true(ds.get_variables().get_variables_number() == 4, LOG);
   assert_true(ds.get_data().arrange_column(0).calculate_absolute_value() <= 1.0, LOG);
   assert_true(ds.get_data().arrange_column(1).calculate_absolute_value() <= 1.0, LOG);
   assert_true(ds.get_data().arrange_column(2).calculate_absolute_value() <= 1.0, LOG);
   assert_true(ds.get_data().arrange_column(3).calculate_absolute_value() <= 1.0, LOG);
}


void DataSetTest::test_convert_angular_variables_radians(void)
{
   message += "test_convert_angular_variables_radians\n";

   DataSet ds;

   Matrix<double> data;

   Vector<size_t> angular_variables;

   // Test

   data.set(2,2, 1.234);

   ds.set(data);

   angular_variables.set(1, 0);

   ds.convert_angular_variables_radians(angular_variables);

   assert_true(ds.get_variables().get_variables_number() == 3, LOG);
   assert_true(ds.get_data().arrange_column(0).calculate_absolute_value() <= 1.0, LOG);
   assert_true(ds.get_data().arrange_column(1).calculate_absolute_value() <= 1.0, LOG);
   assert_true(ds.get_data().arrange_column(2).calculate_absolute_value() == 1.234, LOG);

   // Test

   data.set(2,2, 1.234);

   ds.set(data);

   angular_variables.set(0,1,1);

   ds.convert_angular_variables_radians(angular_variables);

   assert_true(ds.get_variables().get_variables_number() == 4, LOG);
   assert_true(ds.get_data().arrange_column(0).calculate_absolute_value() <= 1.0, LOG);
   assert_true(ds.get_data().arrange_column(1).calculate_absolute_value() <= 1.0, LOG);
   assert_true(ds.get_data().arrange_column(2).calculate_absolute_value() <= 1.0, LOG);
   assert_true(ds.get_data().arrange_column(3).calculate_absolute_value() <= 1.0, LOG);
}


void DataSetTest::test_convert_angular_variables(void)
{
   message += "test_convert_angular_variables\n";
}


void DataSetTest::test_trim(void)
{
   message += "test_trim\n";

   DataSet ds;

   std::string str;

   // Test

   str.assign(" hello");

   ds.trim(str);

   assert_true(str.compare("hello") == 0, LOG);

   // Test

   str.assign("hello ");

   ds.trim(str);

   assert_true(str.compare("hello") == 0, LOG);

   // Test

   str.assign(" hello ");

   ds.trim(str);

   assert_true(str.compare("hello") == 0, LOG);

   // Test

   str.assign("   hello   ");

   ds.trim(str);

   assert_true(str.compare("hello") == 0, LOG);
}


void DataSetTest::test_get_trimmed(void)
{
   message += "test_get_trimmed\n";

   DataSet ds;

   std::string str1;
   std::string str2;

   // Test

   str1.assign(" hello");

   str2 = ds.get_trimmed(str1);

   assert_true(str2.compare("hello") == 0, LOG);

   // Test

   str1.assign("hello ");

   str2 = ds.get_trimmed(str1);

   assert_true(str2.compare("hello") == 0, LOG);

   // Test

   str1.assign(" hello ");

   str2 = ds.get_trimmed(str1);

   assert_true(str2.compare("hello") == 0, LOG);

   // Test

   str1.assign("   hello   ");

   str2 = ds.get_trimmed(str1);

   assert_true(str2.compare("hello") == 0, LOG);
}


void DataSetTest::test_count_tokens(void)
{
   message += "test_count_tokens\n";

   DataSet ds;

   std::string str;

   size_t tokens_number;

   // Test

   str.assign(" hello ");

   tokens_number = ds.count_tokens(str);

   assert_true(tokens_number == 1, LOG);

   // Test

   str.assign(" hello");

   tokens_number = ds.count_tokens(str);

   assert_true(tokens_number == 1, LOG);

   // Test

   str.assign(" hello bye ");

   tokens_number = ds.count_tokens(str);

   assert_true(tokens_number == 2, LOG);

   // Test

   str.assign(" hello   bye ");

   tokens_number = ds.count_tokens(str);

   assert_true(tokens_number == 2, LOG);

   // Test

   ds.set_separator(",");

   str.assign("1, 2, 3, 4");

   tokens_number = ds.count_tokens(str);

   assert_true(tokens_number == 4, LOG);

   // Test

   ds.set_separator(",");

   str.assign(",1, 2, 3, 4,");

   tokens_number = ds.count_tokens(str);

   assert_true(tokens_number == 4, LOG);

   // Test

   str.assign(",1,2,3,4,");

   tokens_number = ds.count_tokens(str);

   assert_true(tokens_number == 4, LOG);

   // Test

   str.assign(" , 1 , 2 , 3 , 4, ");

   tokens_number = ds.count_tokens(str);

   assert_true(tokens_number == 4, LOG);

}


/// @todo White spaces

void DataSetTest::test_get_tokens(void)
{
   message += "test_get_tokens\n";

   DataSet ds;

   std::string str;

   Vector<std::string> tokens;

   // Test

   str.assign(" hello ");

   tokens = ds.get_tokens(str);

   assert_true(tokens.size() == 1, LOG);
   assert_true(tokens[0].compare("hello") == 0, LOG);

   // Test

   str.assign(" hello");

   tokens = ds.get_tokens(str);

   assert_true(tokens.size() == 1, LOG);
   assert_true(tokens[0].compare("hello") == 0, LOG);

   // Test

   str.assign(" hello bye ");

   tokens = ds.get_tokens(str);

   assert_true(tokens.size() == 2, LOG);
   assert_true(tokens[0].compare("hello") == 0, LOG);
   assert_true(tokens[1].compare("bye") == 0, LOG);

   // Test

   ds.set_separator(",");

   str.assign("1,2,3,4");

   tokens = ds.get_tokens(str);

   assert_true(tokens.size() == 4, LOG);
   assert_true(tokens[0].compare("1") == 0, LOG);
   assert_true(tokens[1].compare("2") == 0, LOG);
   assert_true(tokens[2].compare("3") == 0, LOG);
   assert_true(tokens[3].compare("4") == 0, LOG);

   // Test

   ds.set_separator(",");

   str.assign(",1,2,3,4,");

   tokens = ds.get_tokens(str);

   assert_true(tokens.size() == 4, LOG);
   assert_true(tokens[0].compare("1") == 0, LOG);
   assert_true(tokens[1].compare("2") == 0, LOG);
   assert_true(tokens[2].compare("3") == 0, LOG);
   assert_true(tokens[3].compare("4") == 0, LOG);

   // Test

   ds.set_separator(",");

   str.assign(" , 1 , 2 , 3 , 4 , ");

   tokens = ds.get_tokens(str);

   assert_true(tokens.size() == 4, LOG);

   assert_true(ds.get_trimmed(tokens[0]).compare("1") == 0, LOG);
   assert_true(ds.get_trimmed(tokens[1]).compare("2") == 0, LOG);
   assert_true(ds.get_trimmed(tokens[2]).compare("3") == 0, LOG);
   assert_true(ds.get_trimmed(tokens[3]).compare("4") == 0, LOG);

}


void DataSetTest::test_is_numeric(void)
{
   message += "test_is_numeric\n";

   DataSet ds;

   std::string str;

   // Test

   str.assign("hello");

   assert_true(!ds.is_numeric(str), LOG);

   // Test

   str.assign("0");

   assert_true(ds.is_numeric(str), LOG);

   // Test

   str.assign("-1.0e-99");

   assert_true(ds.is_numeric(str), LOG);
}


void DataSetTest::run_test_case(void)
{
   message += "Running data set test case...\n";

   // Constructor and destructor methods

   test_constructor();
   test_destructor();

   // Assignment operators methods

   test_assignment_operator();

   // Get methods

   test_get_instances_number();
   test_get_variables_number();
 
   test_get_variables();

   test_get_display();

   // Data methods

   test_get_data();

   test_arrange_training_data();
   test_arrange_generalization_data();
   test_arrange_testing_data();

   test_arrange_input_data();
   test_arrange_target_data();

   // Instance methods

   test_get_instance();

   // Set methods

   test_set();

   test_set_display();

   // Data methods

   test_set_data();

   test_set_instances_number();
   test_set_variables_number();

   // Instance methods

   test_set_instance();

   // Data resizing methods

   test_add_instance();
   test_subtract_instance();

   test_subtract_constant_variables();
   test_subtract_repeated_instances();

   // Initialization methods

   test_initialize_data();

   // Statistics methods

   test_calculate_data_statistics();

   test_calculate_training_instances_statistics();
   test_calculate_generalization_instances_statistics();
   test_calculate_testing_instances_statistics();

   test_calculate_input_variables_statistics();
   test_calculate_targets_statistics();
  
   // Data scaling

   test_scale_data_mean_standard_deviation();  
   test_scale_data_minimum_maximum(); 

   // Input variables scaling

   test_scale_inputs_mean_standard_deviation();
   test_scale_inputs_minimum_maximum();

   // Target variables scaling

   test_scale_targets_mean_standard_deviation();
   test_scale_targets_minimum_maximum();

   // Data unscaling

   test_unscale_data_mean_standard_deviation();
   test_unscale_data_minimum_maximum();

   // Input variables unscaling

   test_unscale_inputs_mean_standard_deviation();
   test_unscale_inputs_minimum_maximum();

   // Target variables unscaling

   test_unscale_targets_mean_standard_deviation();
   test_unscale_targets_minimum_maximum();

   // Input-target variables unscaling

   test_unscale_variables_mean_standard_deviation();
   test_unscale_variables_minimum_maximum();

   // Pattern recognition methods

   test_calculate_target_class_distribution();
   test_balance_target_class_distribution();

   // Serialization methods

   test_to_XML();
   test_from_XML();

   test_print();
   test_save();
   test_load();

   test_print_data();
   test_save_data();
   test_load_data();

   test_get_data_statistics();
   test_print_data_statistics();

   test_get_training_instances_statistics();
   test_print_training_instances_statistics();
   test_save_training_instances_statistics();

   test_get_generalization_instances_statistics();
   test_print_generalization_instances_statistics();
   test_save_generalization_instances_statistics();

   test_get_testing_instances_statistics();
   test_print_testing_instances_statistics();
   test_save_testing_instances_statistics();

   test_get_instances_statistics();
   test_print_instances_statistics();
   test_save_instances_statistics();

   test_convert_time_series();
   test_convert_autoassociation();

   test_convert_angular_variable_degrees();
   test_convert_angular_variable_radians();

   test_convert_angular_variables();

   // String utilities

   test_trim();
   test_get_trimmed();

   test_count_tokens();
   test_get_tokens();

   test_is_numeric();

   message += "End of data set test case.\n";
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

