QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addbookdialog.cpp \
    addreaderdialog.cpp \
    author.cpp \
    book.cpp \
    catalogbook.cpp \
    infobookdialog.cpp \
    main.cpp \
    catalog.cpp \
    reader.cpp \
    readerinfodialog.cpp

HEADERS += \
    Person.h \
    addbookdialog.h \
    addreaderdialog.h \
    author.h \
    book.h \
    catalog.h \
    catalogbook.h \
    infobookdialog.h \
    reader.h \
    readerinfodialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS +=

DISTFILES += \
    booksData.dat \
    readersData.dat

RESOURCES += \
    icons/icon.qrc
