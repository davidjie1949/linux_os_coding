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
        main.cpp \
        utils.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /home/pi/$${TARGET}
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    gpb/TVF_To_DXP.pb.h \
    gpb/TVF_To_DXP_info.pb.h \
    utils.h

DISTFILES += \
    gpb/TVF_To_DXP.proto \
    gpb/TVF_To_DXP_info.proto

#unix:!macx: LIBS += -L$$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/lib/ -lprotobuf
#INCLUDEPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/include
#DEPENDPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/include

#unix:!macx: LIBS += -L$$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/lib/ -lsoaframework
#INCLUDEPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/include/soa/framework
#DEPENDPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/include/soa/framework

#unix:!macx: LIBS += -L$$PWD/../../../../../opt/qt5pi/sysroot/usr/lib/ -lprotobuf
#INCLUDEPATH += $$PWD/../../../../../opt/qt5pi/sysroot/usr/local/include
#DEPENDPATH += $$PWD/../../../../../opt/qt5pi/sysroot/usr/local/include

#unix:!macx: LIBS += -L$$PWD/../../../../../opt/qt5pi/sysroot/usr/lib/ -lsoaframework
#INCLUDEPATH += $$PWD/../../../../../opt/qt5pi/sysroot/usr/local/include/soa/framework
#DEPENDPATH += $$PWD/../../../../../opt/qt5pi/sysroot/usr/local/include/soa/framework


INCLUDEPATH += $$PWD/../../../../../mnt/piToolchain/sysroot/usr
DEPENDPATH += $$PWD/../../../../../mnt/piToolchain/sysroot/usr

unix:!macx: LIBS += -L$$PWD/../../../../../mnt/piToolchain/sysroot/usr/lib/ -lprotobuf
INCLUDEPATH += $$PWD/../../../../../mnt/piToolchain/sysroot/usr/local/include
DEPENDPATH += $$PWD/../../../../../mnt/piToolchain/sysroot/usr/local/include

unix:!macx: LIBS += -L$$PWD/../../../../../mnt/piToolchain/sysroot/usr/lib/ -lsoaframework
INCLUDEPATH += $$PWD/../../../../../mnt/piToolchain/sysroot/usr/include/soa/framework
DEPENDPATH += $$PWD/../../../../../mnt/piToolchain/sysroot/usr/include/soa/framework
