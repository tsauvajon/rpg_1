QT += widgets
QT += multimedia

SOURCES += \
    main.cpp \
    fenetre.cpp \
    personnage.cpp \
    arme.cpp \
    fenetreparametres.cpp

HEADERS += \
    fenetre.h \
    personnage.h \
    arme.h \
    fenetreparametres.h

FORMS +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/openssl-0.9.8l/out32/ -llibeay32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/openssl-0.9.8l/out32/ -llibeay32d

INCLUDEPATH += $$PWD/openssl-0.9.8l/inc32
DEPENDPATH += $$PWD/openssl-0.9.8l/inc32

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/openssl-0.9.8l/out32/ -lssleay32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/openssl-0.9.8l/out32/ -lssleay32d

INCLUDEPATH += $$PWD/openssl-0.9.8l/inc32
DEPENDPATH += $$PWD/openssl-0.9.8l/inc32
