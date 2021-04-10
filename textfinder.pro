#! [0]
#QT += designer
QT += widgets uitools designer core

HEADERS += textfinder.h
SOURCES += textfinder.cpp main.cpp
RESOURCES += textfinder.qrc
LIBS += -lQt5Concurrent
#! [0]

target.path = $$[QT_INSTALL_EXAMPLES]/uitools/textfinder
INSTALLS += target
