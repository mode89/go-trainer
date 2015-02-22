###################################################################################################
#                                                                                                 #
#   OpenNN: Open Neural Networks Library                                                          #
#   www.intelnics.com/opennn                                                                      #
#                                                                                                 #
#   I R I S   P L A N T   P R O J E C T                                                           #
#                                                                                                 #
#   Roberto Lopez                                                                                 #
#   Intelnics - Making intelligent use of data                                               #
#   robertolopez@intelnics.com                                                                    #
#                                                                                                 #
###################################################################################################

TEMPLATE = app
CONFIG += console

TARGET = iris_plant

DESTDIR = "$$PWD\bin"

SOURCES = main.cpp

win32-g++{
QMAKE_LFLAGS += -static-libgcc
QMAKE_LFLAGS += -static-libstdc++
QMAKE_LFLAGS += -static
}

# OpenNN library

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../source/release/ -lopennn
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../source/debug/ -lopennn
#else:unix: LIBS += -L$$OUT_PWD/../../source/ -lopennn

#INCLUDEPATH += $$PWD/../../source
#DEPENDPATH += $$PWD/../../source

#win32-msvc:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../source/release/opennn.lib
#else:win32-msvc:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../source/debug/opennn.lib

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../source/release/libopennn.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../source/debug/libopennn.a

#else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../source/libopennn.a


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../opennn/release/ -lopennn
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../opennn/debug/ -lopennn
else:unix: LIBS += -L$$OUT_PWD/../../opennn/ -lopennn

INCLUDEPATH += $$PWD/../../opennn
DEPENDPATH += $$PWD/../../opennn

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../opennn/release/libopennn.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../opennn/debug/libopennn.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../opennn/release/opennn.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../opennn/debug/opennn.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../opennn/libopennn.a
