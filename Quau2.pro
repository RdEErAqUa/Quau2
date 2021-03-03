QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport



CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Data/Group/group.cpp \
    Data/Sample/HigherDimSample/higherdimsample.cpp \
    Data/Sample/OneDimSample/onedimsample.cpp \
    Data/Sample/TwoDimSample/Regression/Storage/regression.cpp \
    Data/Sample/TwoDimSample/Regression/linearregression.cpp \
    Data/Sample/TwoDimSample/Regression/nonlinearregression.cpp \
    Data/Sample/TwoDimSample/Regression/parabolicregression.cpp \
    Data/Sample/TwoDimSample/Regression/pyatorichkaregression.cpp \
    Data/Sample/TwoDimSample/twodimparameter.cpp \
    Data/Sample/TwoDimSample/twodimsample.cpp \
    Data/StreamWork/streamwork.cpp \
    Data/basesampletree.cpp \
    Data/distribution.cpp \
    Data/division.cpp \
    Data/parameter.cpp \
    Data/sample.cpp \
    Data/twodimdivision.cpp \
    Data/xmultipley.cpp \
    Delegate/qcomboboxdelegate.cpp \
    Models/Sample/qparameteritemmodel.cpp \
    Models/Sample/qregressiontablemodel.cpp \
    Models/Sample/qsampleitemmodel.cpp \
    Models/Sample/qtwodimparameter.cpp \
    QListUseful.cpp \
    Quantile.cpp \
    Variation.cpp \
    XY.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    Data/Group/group.h \
    Data/Sample/HigherDimSample/higherdimsample.h \
    Data/Sample/OneDimSample/onedimsample.h \
    Data/Sample/TwoDimSample/Regression/Storage/regression.h \
    Data/Sample/TwoDimSample/Regression/linearregression.h \
    Data/Sample/TwoDimSample/Regression/nonlinearregression.h \
    Data/Sample/TwoDimSample/Regression/parabolicregression.h \
    Data/Sample/TwoDimSample/Regression/pyatorichkaregression.h \
    Data/Sample/TwoDimSample/twodimparameter.h \
    Data/Sample/TwoDimSample/twodimsample.h \
    Data/StreamWork/streamwork.h \
    Data/basesampletree.h \
    Data/distribution.h \
    Data/division.h \
    Data/parameter.h \
    Data/sample.h \
    Data/twodimdivision.h \
    Data/xmultipley.h \
    Delegate/qcomboboxdelegate.h \
    Models/Sample/qparameteritemmodel.h \
    Models/Sample/qregressiontablemodel.h \
    Models/Sample/qsampleitemmodel.h \
    Models/Sample/qtwodimparameter.h \
    QListUseful.h \
    Quantile.h \
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
