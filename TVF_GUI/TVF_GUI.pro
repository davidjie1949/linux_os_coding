QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gpb/TVF_To_DXP.pb.cc \
    gpb/TVF_To_DXP_info.pb.cc \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    gpb/TVF_To_DXP.pb.h \
    gpb/TVF_To_DXP_info.pb.h \
    mainwindow.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /home/pi/$${TARGET}
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    gpb/TVF_To_DXP.proto \
#    gpb/TVF_To_DXP_info.proto

unix:!macx: LIBS += -L$$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/lib/ -lprotobuf
INCLUDEPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/include
DEPENDPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/include

unix:!macx: LIBS += -L$$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/lib/ -lsoaframework
INCLUDEPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/include/soa
DEPENDPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/include/soa

unix:!macx: LIBS += -L$$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/lib/arm-linux-gnueabihf/ -lpthread
INCLUDEPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/lib/arm-linux-gnueabihf
DEPENDPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/lib/arm-linux-gnueabihf
unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/lib/arm-linux-gnueabihf/libpthread.a


