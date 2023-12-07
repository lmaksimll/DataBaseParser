TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        console_ui.cpp \
        main.cpp \
        manager_db.cpp \
        parser.cpp \
        request.cpp

HEADERS += \
    console_ui.h \
    manager_db.h \
    parser.h \
    request.h
