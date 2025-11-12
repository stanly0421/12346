QT += widgets
CONFIG += c++11

TARGET = calculator
TEMPLATE = app

SOURCES += main.cpp \
           calculator.cpp

HEADERS += calculator.h

# Install
target.path = /usr/local/bin
INSTALLS += target
