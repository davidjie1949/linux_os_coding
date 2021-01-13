TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
#        main.cpp \
        soa-publish-test.cpp \
        soa-test-utils.cpp

HEADERS += \
    soa-test-utils.hpp

unix:!macx: LIBS += -L$$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/lib/ -lprotobuf
INCLUDEPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/local
DEPENDPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/local

unix:!macx: LIBS += -L$$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/lib/ -lsoaframework
INCLUDEPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/include/soa/framework
DEPENDPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/include/soa/framework

INCLUDEPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr
DEPENDPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr

#unix:!macx: LIBS += -L$$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/lib/arm-linux-gnueabihf/ -lpthread
#INCLUDEPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/lib/arm-linux-gnueabihf
#DEPENDPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/lib/arm-linux-gnueabihf
#unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../mnt/pi-toolchain/sysroot/usr/lib/arm-linux-gnueabihf/libpthread.a

INCLUDEPATH += /mnt/pi-toolchain/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/include/c++/7.5.0
