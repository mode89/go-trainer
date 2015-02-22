###################################################################################################
#                                                                                                 #
#   OpenNN: Open Neural Networks Library                                                          #
#   www.intelnics.com/opennn                                                                      #
#                                                                                                 #
#   O P E N N N   P R O J E C T                                                                   #
#                                                                                                 #
#   Roberto Lopez                                                                                 #
#   Intelnics - Making intelligent use of data                                               #
#   robertolopez@intelnics.com                                                                    #
#                                                                                                 #
###################################################################################################

# CONFIGURATION

TEMPLATE = subdirs

CONFIG += ordered

CONFIG(release, debug|release) {
DEFINES += NDEBUG
}

SUBDIRS += opennn
SUBDIRS += examples
SUBDIRS += tests
