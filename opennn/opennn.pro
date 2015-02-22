###################################################################################################
#                                                                                                 #
#   OpenNN: Open Neural Networks Library                                                          #
#   www.intelnics.com/opennn                                                                      #
#                                                                                                 #
#   O P E N N N   Q T   C R E A T O R   P R O J E C T                                             #
#                                                                                                 #
#   Roberto Lopez                                                                                 #
#   Intelnics - Making intelligent use of data                                               #
#   robertolopez@intelnics.com                                                                    #
#                                                                                                 #
# $Id: opennn.pro 53 2015-01-15 13:22:11Z uwrobertolopez $
#
###################################################################################################

QT = # Do not use qt

TARGET = opennn

TEMPLATE = lib

CONFIG += staticlib

# Eigen library

INCLUDEPATH += eigen

QMAKE_CXXFLAGS += -openmp
QMAKE_LFLAGS   += -openmp


#win32-msvc*{
#QMAKE_CXXFLAGS += -openmp
#QMAKE_LFLAGS   += -openmp
#}

#linux-g++ {
#QMAKE_CXXFLAGS += -fopenmp
#QMAKE_LFLAGS   += -fopenmp
#}


HEADERS += \
    variables.h \
    instances.h \
    missing_values.h \
    data_set.h \
    plug_in.h \
    ordinary_differential_equations.h \
    mathematical_model.h \
    inputs.h \
    outputs.h \
    unscaling_layer.h \
    scaling_layer.h \
    probabilistic_layer.h \
    perceptron_layer.h \
    perceptron.h \
    neural_network.h \
    multilayer_perceptron.h \
    independent_parameters.h \
    conditions_layer.h \
    bounding_layer.h \
    sum_squared_error.h \
    solutions_error.h \
    root_mean_squared_error.h \
    performance_term.h \
    performance_functional.h \
    outputs_integrals.h \
    normalized_squared_error.h \
    neural_parameters_norm.h \
    minkowski_error.h \
    mean_squared_error.h \
    inverse_sum_squared_error.h \
    independent_parameters_error.h \
    final_solutions_error.h \
    cross_entropy_error.h \
    training_strategy.h \
    training_algorithm.h \
    training_rate_algorithm.h \
    random_search.h \
    quasi_newton_method.h \
    newton_method.h \
    levenberg_marquardt_algorithm.h \
    gradient_descent.h \
    evolutionary_algorithm.h \
    conjugate_gradient.h \
    testing_analysis.h \
    model_selection.h \
    vector.h \
    matrix.h \
    numerical_integration.h \
    numerical_differentiation.h \
    linear_algebraic_equations.h \
    tinyxml2.h \
    opennn.h

SOURCES += \
    variables.cpp \
    instances.cpp \
    missing_values.cpp \
    data_set.cpp \
    plug_in.cpp \
    ordinary_differential_equations.cpp \
    mathematical_model.cpp \
    inputs.cpp \
    outputs.cpp \
    unscaling_layer.cpp \
    scaling_layer.cpp \
    probabilistic_layer.cpp \
    perceptron_layer.cpp \
    perceptron.cpp \
    neural_network.cpp \
    multilayer_perceptron.cpp \
    independent_parameters.cpp \
    conditions_layer.cpp \
    bounding_layer.cpp \
    sum_squared_error.cpp \
    solutions_error.cpp \
    root_mean_squared_error.cpp \
    performance_term.cpp \
    performance_functional.cpp \
    outputs_integrals.cpp \
    normalized_squared_error.cpp \
    neural_parameters_norm.cpp \
    minkowski_error.cpp \
    mean_squared_error.cpp \
    inverse_sum_squared_error.cpp \
    independent_parameters_error.cpp \
    final_solutions_error.cpp \
    cross_entropy_error.cpp \
    training_strategy.cpp \
    training_algorithm.cpp \
    training_rate_algorithm.cpp \
    random_search.cpp \
    quasi_newton_method.cpp \
    newton_method.cpp \
    levenberg_marquardt_algorithm.cpp \
    gradient_descent.cpp \
    evolutionary_algorithm.cpp \
    conjugate_gradient.cpp \
    testing_analysis.cpp \
    model_selection.cpp \
    numerical_integration.cpp \
    numerical_differentiation.cpp \
    linear_algebraic_equations.cpp \
    tinyxml2.cpp
