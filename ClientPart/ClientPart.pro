TEMPLATE = app
QT += network widgets


RESOURCES += \
    images.qrc


FORMS   += MainWindow.ui 

HEADERS += MainWindow.h  

SOURCES += \
           main.cpp \
    MainWindow.cpp
RC_FILE += myapp.rc

DISTFILES += \
    client.ico \
    myapp.rc

