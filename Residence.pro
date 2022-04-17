QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller.cpp \
    database.cpp \
    main.cpp \
    model.cpp \
    model/appartamento.cpp \
    model/camera.cpp \
    model/camper.cpp \
    model/hotel.cpp \
    model/residence.cpp \
    model/suite.cpp \
    view.cpp \
    view/clickablelabel.cpp \
    view/home.cpp \
    view/infodialog.cpp \
    view/servizi.cpp \
    view/structuredetailsview.cpp \
    view/structureview.cpp

HEADERS += \
    controller.h \
    model.h \
    model/appartamento.h \
    model/camera.h \
    model/camper.h \
    model/deep_unique_ptr.h \
    model/hotel.h \
    model/residence.h \
    model/suite.h \
    model/vettore.h \
    view.h \
    view/clickablelabel.h \
    view/home.h \
    view/infodialog.h \
    view/servizi.h \
    view/structuredetailsview.h \
    view/structureview.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    database.txt \
    database/database.txt \
    resources/Green.png \
    resources/GreenButton.png \
    resources/Maintenance.png \
    resources/MaintenanceButton.png \
    resources/Red.png \
    resources/RedButton.png \
    resources/alta.png \
    resources/appartamento.png \
    resources/bassa.png \
    resources/camera.png \
    resources/camper.png \
    resources/disabile.png \
    resources/disabile_si.png \
    resources/lavatrice_no.png \
    resources/lavatrice_si.png \
    resources/letto.png \
    resources/logo.png \
    resources/media.png \
    resources/suite.png

RESOURCES += \
    data.qrc \
    database.qrc
