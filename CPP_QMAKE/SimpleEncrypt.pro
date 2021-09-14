#-------------------------------------------------
#
# Project created by QtCreator 2019-02-19T18:40:55
#
#-------------------------------------------------

QT       -= gui

TARGET = SimpleEncrypt
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += USE_SSL

SOURCES += \
    src/base64.cpp \
    src/simpleencrypt.cpp

HEADERS += \
    src/base64.h \
    src/simpleencrypt.h



#OS Based config
unix:{
    DEFINES += LINUX
    contains(DEFINES, USE_SSL) {
        #OpenSSL config
        INCLUDEPATH +=/home/shared/openssl-1.1.1g/include
        LIBS += -L/home/shared/openssl-1.1.1g/lib/ -lcrypto -lssl
    }
}

win32:{
    !contains(QMAKE_TARGET.arch, x86_64) {
        ## Windows x86 (32bit) specific build here
        INCLUDEPATH += C:/OpenSource/OpenSSL/Win32/include
        LIBS += -LC:\OpenSource\OpenSSL\Win32\lib -llibcrypto -llibssl
    } else {
        ## Windows x64 (64bit) specific build here
        INCLUDEPATH += C:/OpenSource/OpenSSL/x64/include
        LIBS += -LC:\OpenSource\OpenSSL\x64\lib -llibcrypto -llibssl
    }
}


linux{
    target.path = /usr/local/lib
    headers.path =/usr/local/include
    headers.files += *.h
    INSTALLS += target headers
}
