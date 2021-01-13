TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
#        main.cpp \
        soa-subscribe-test.cpp \
        soa-test-utils.cpp

HEADERS += \
    soa-test-utils.hpp

INCLUDEPATH += $$PWD/../../../../../mnt/piToolchain/sysroot/usr
DEPENDPATH += $$PWD/../../../../../mnt/piToolchain/sysroot/usr

unix:!macx: LIBS += -L$$PWD/../../../../../mnt/piToolchain/sysroot/usr/lib/ -lprotobuf
INCLUDEPATH += $$PWD/../../../../../mnt/piToolchain/sysroot/usr/local/include
DEPENDPATH += $$PWD/../../../../../mnt/piToolchain/sysroot/usr/local/include

unix:!macx: LIBS += -L$$PWD/../../../../../mnt/piToolchain/sysroot/usr/lib/ -lsoaframework
INCLUDEPATH += $$PWD/../../../../../mnt/piToolchain/sysroot/usr/include/soa/framework
DEPENDPATH += $$PWD/../../../../../mnt/piToolchain/sysroot/usr/include/soa/framework


#INCLUDEPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot_original/usr
#DEPENDPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot_original/usr

#unix:!macx: LIBS += -L$$PWD/../../../../../mnt/pi-toolchain/sysroot_original/usr/lib/ -lprotobuf
#INCLUDEPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot_original/usr/include
#DEPENDPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot_original/usr/include

#unix:!macx: LIBS += -L$$PWD/../../../../../mnt/pi-toolchain/sysroot_original/usr/lib/ -lsoaframework
#INCLUDEPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot_original/usr/include/soa/framework
#DEPENDPATH += $$PWD/../../../../../mnt/pi-toolchain/sysroot_original/usr/include/soa/framework
