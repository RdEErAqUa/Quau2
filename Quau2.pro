QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport



CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Data/Group/group.cpp \
    Data/parameter.cpp \
    Data/sample.cpp \
    Models/Sample/qsampleitemmodel.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    Data/Group/group.h \
    Data/division.h \
    Data/parameter.h \
    Data/sample.h \
    Models/Sample/qsampleitemmodel.h \
    QListUseful.h \
    Quantile.h \
    StreamWork.h \
    Variation.h \
    XY.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Quau2_uk_UA.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc