QT += quick

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        gpb/TVF_To_DXP.pb.cc \
        gpb/TVF_To_DXP_info.pb.cc \
        gpb/paho_test_utils.cpp \
        main.cpp \
        tvf_dxp_interface.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    gpb/TVF_To_DXP.pb.h \
    gpb/TVF_To_DXP_info.pb.h \
    gpb/paho_test_utils.h \
    tvf_dxp_interface.h

DISTFILES += \
    gpb/TVF_To_DXP.proto \
    gpb/TVF_To_DXP_info.proto

unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lprotobuf
unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lpaho-mqtt3c
INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

